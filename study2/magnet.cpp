#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int t;
int k;
bool rotate[3];

class Magnet{

    struct Node {
        int pole; // 0 - N / 1 - S
        Node *next;
    };

public:
    Magnet(){
        head = NULL;
        nodeNum = 0;
    }

    ~Magnet(){
        Node *nextNode = head;

        while(nextNode != tail) {
            Node *deleteMe = nextNode;
            nextNode = nextNode->next;
            delete deleteMe;
        }

        delete nextNode;
    }

    void add_value(int pol){
        Node *n = new Node();
        n->pole = pol;
        n->next = head;

        head = n;
        nodeNum++;
    }

    void empty_magnet(){
        do{
            Node *n = head;
            head = head->next;
            delete n;
        } while(head != NULL);
    }

    void init(){
        reverse();
        right = head->next->next;
        left = right->next->next->next->next;
        tail = left->next;
        tail->next = head;
    }

    void reverse(){
        Node *current = head;
        Node *next = NULL, *prev = NULL;

        while(current != NULL){
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    int get_head(){
        return head->pole;
    }

    int get_left(){
        return left->pole;
    }
    
    int get_right(){
        return right->pole;
    }

    void rotate(int n){
        if (n == 1) rotate_right();
        else if (n == -1) rotate_left();
    }

    void rotate_right(){
        head = left->next;
        right = head->next->next;
        left = right->next->next->next->next;
        tail = left->next;
    }

    void rotate_left(){
        head = head->next;
        right = right->next;
        left = left->next;
        tail = tail->next;
    }

    void print_magnet(){
        Node *ptr = head;

        while((ptr->next != NULL) && (ptr->next != head)){
            cout << ptr->pole << " ";
            ptr = ptr->next;
        }
        cout << ptr->pole << endl;
    }

private:
    Node *head, *left, *right, *tail;
    int nodeNum;

};

// main functions
Magnet *fstMagnet, *sndMagnet, *thdMagnet, *fthMagnet;

int evaluate(){
    int fst, snd, thd, fth;
    fst = snd = thd = fth = 0;

    if ((*fstMagnet).get_head()) fst = 1;
    if ((*sndMagnet).get_head()) snd = 2;
    if ((*thdMagnet).get_head()) thd = 4;
    if ((*fthMagnet).get_head()) fth = 8;

    return (fst + snd + thd + fth);
}

bool check_same(Magnet *lMagnet, Magnet *rMagnet){

    return ((*lMagnet).get_right() == (*rMagnet).get_left());

}

void get_rotate_info(){

    rotate[0] = !check_same(fstMagnet, sndMagnet);
    rotate[1] = !check_same(sndMagnet, thdMagnet);
    rotate[2] = !check_same(thdMagnet, fthMagnet);

}

void apply_gravity(int lNum, int rNum, int rotation){
    
    // [lNum, rNum]; the scope of rotation application
    // rotation; the direction of rotation. clockwise - 1 / counterclockwise - 0  

    if(lNum == 1) {
        if(rNum == 2) {
            (*fstMagnet).rotate(rotation);
            (*sndMagnet).rotate(-rotation);
        } else if(rNum == 3) {
            (*fstMagnet).rotate(rotation);
            (*sndMagnet).rotate(-rotation);
            (*thdMagnet).rotate(rotation);
        } else if(rNum == 4) {
            (*fstMagnet).rotate(rotation);
            (*sndMagnet).rotate(-rotation);
            (*thdMagnet).rotate(rotation);
            (*fthMagnet).rotate(-rotation);
        } 

    } else if(lNum == 2) {
        if(rNum == 3) {
            (*sndMagnet).rotate(rotation);
            (*thdMagnet).rotate(-rotation);
        } else if(rNum == 4) {
            (*sndMagnet).rotate(rotation);
            (*thdMagnet).rotate(-rotation);
            (*fthMagnet).rotate(rotation);
        } 

    } else if(lNum == 3) {
        (*thdMagnet).rotate(rotation);
        (*fthMagnet).rotate(-rotation);
    }

}

void start_rotate(int mNum, int rotation){
    // mNum; magnet number
    // rotation; the direction of rotation. clockwise - 1 / counterclockwise - 0  
    if (mNum == 1){
    // rotation start at the first magnet
        if (rotate[0] && rotate[1] && rotate[2]) apply_gravity(1, 4, rotation);
        else if (rotate[0] && rotate[1]) apply_gravity(1, 3, rotation);
        else if (rotate[0]) apply_gravity(1, 2, rotation);
        else (*fstMagnet).rotate(rotation);
    } else if (mNum == 2){
    // rotation start at the second magnet
        if (rotate[0] && rotate[1] && rotate[2]) apply_gravity(1, 4, (-rotation));
        else if (rotate[1] && rotate[2]) apply_gravity(2, 4, rotation);
        else if (rotate[0] && rotate[1]) apply_gravity(1, 3, (-rotation));
        else if (rotate[1]) apply_gravity(2, 3, rotation);
        else if (rotate[0]) apply_gravity(1, 2, (-rotation));
        else (*sndMagnet).rotate(rotation);
    } else if (mNum == 3){
    // rotation start at the third magnet
        if (rotate[0] && rotate[1] && rotate[2]) apply_gravity(1, 4, rotation);
        else if (rotate[0] && rotate[1]) apply_gravity(1, 3, rotation);
        else if (rotate[1] && rotate[2]) apply_gravity(2, 4, (-rotation));
        else if (rotate[1]) apply_gravity(2, 3, (-rotation));
        else if (rotate[2]) apply_gravity(3, 4, rotation);
        else (*thdMagnet).rotate(rotation);
    } else {
    // rotation start at the fourth magnet
        if (rotate[0] && rotate[1] && rotate[2]) apply_gravity(1, 4, (-rotation));
        else if (rotate[1] && rotate[2]) apply_gravity(2, 4, rotation);
        else if (rotate[2]) apply_gravity(3, 4, (-rotation));
        else (*fthMagnet).rotate(rotation);
    }

}

void start_alg(){

    //fstream mfile(fileName.c_str());
    //mfile >> t;
    cin >> t;

    for(int i=0; i<t; i++){

        //mfile >> k;
        cin >> k;

        int p;
        int cnt = 0;
        rotate[0] = rotate[1] = rotate[2] = false;
        fstMagnet = new Magnet();
        sndMagnet = new Magnet();
        thdMagnet = new Magnet();
        fthMagnet = new Magnet();

        for(int j=1; j<=32; j++) {
            //mfile >> p;
            cin >> p;

            if (cnt == 0){
                (*fstMagnet).add_value(p);    
            } else if (cnt == 1){
                (*sndMagnet).add_value(p);    
            } else if (cnt == 2){
                (*thdMagnet).add_value(p);    
            } else {
                (*fthMagnet).add_value(p);    
            }

            if (j % 8 == 0) cnt++;
        }

        (*fstMagnet).init();
        (*sndMagnet).init();
        (*thdMagnet).init();
        (*fthMagnet).init();

        int fst, snd;
        for(int j=0; j<k; j++){
            //mfile >> fst >> snd;
            cin >> fst >> snd;
            get_rotate_info();
            start_rotate(fst, snd);
        }

        cout << "#" << (i+1) << " " << evaluate() << endl;
        delete fstMagnet;
        delete sndMagnet;
        delete thdMagnet;
        delete fthMagnet;
    }

}

int main(int argc, char** argv){

    /* if (argc < 2) {
        cerr << "Usage : " << argv[0] << "TESTFILE" << endl;
        return 1;
    } */

    start_alg();

    return 0;

}
