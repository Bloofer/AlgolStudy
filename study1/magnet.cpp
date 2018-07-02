#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int t, k;
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
            Node *delNode = nextNode;
            nextNode = nextNode->next;
            delete delNode;
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

// magnets
Magnet *magnets[4];

int evaluate(){
    int val = 1;
    int sum = 0;

    for(int i=0; i<4; i++){
        if((*magnets[i]).get_head()) sum += val;
        val *= 2;
    }

    return sum;
}

bool check_same(Magnet *lMagnet, Magnet *rMagnet){
    return ((*lMagnet).get_right() == (*rMagnet).get_left());
}

void init_rotate(){
    for(int i=0; i<3; i++){
        rotate[i] = !check_same(magnets[i], magnets[i+1]);
    }
}

void rotate_sub(int lNum, int rNum, int rotation){
    // [lNum, rNum]; the scope of rotation application
    // rotation; the direction of rotation. clockwise - 1 / counterclockwise - 0  

    int cnt = 0;
    for(int i=lNum-1; i<rNum; i++){
        if ((cnt % 2) == 0) (*magnets[i]).rotate(rotation);
        else (*magnets[i]).rotate(-rotation);
        cnt++;
    }
}

pair<int, int> get_range(int from){
    if(!rotate[0] && !rotate[1] && !rotate[2]) return pair<int, int>(0, 0);
    else if (rotate[0] && rotate[1] && rotate[2]) return pair<int, int>(1, 4);
    else if (rotate[0] && rotate[1] && !rotate[2] && (from != 4)) return pair<int, int>(1, 3);
    else if (!rotate[0] && rotate[1] && rotate[2] && (from != 1)) return pair<int, int>(2, 4);
    else {
        for(int i=0; i<3; i++) {
            if(rotate[i] && ((from == i+1) || (from == i+2))) return pair<int, int>(i+1, i+2);
        }
    }
    
    return pair<int, int>(0, 0);
}

void start_rotate(int mNum, int rotation){
    // mNum; magnet number
    // rotation; the direction of rotation. clockwise - 1 / counterclockwise - 0  

    int from, to;
    pair<int, int> rPair = get_range(mNum);
    from = rPair.first;
    to = rPair.second;

    if((from == 0) && (to == 0)) (*magnets[mNum-1]).rotate(rotation);
    else if (((mNum - from) % 2) == 0) rotate_sub(from, to, rotation);
    else rotate_sub(from, to, (-rotation));
}

void start_alg(){
//void start_alg(string fileName){
    //fstream mfile(fileName.c_str());
    //mfile >> t;
    cin >> t;

    for(int i=0; i<t; i++){

        //mfile >> k;
        cin >> k;

        int p;
        int cnt = 0;
        rotate[0] = rotate[1] = rotate[2] = false;
        for(int j=0; j<4; j++){
            magnets[j] = new Magnet();
        }

        for(int j=1; j<=32; j++) {
            //mfile >> p;
            cin >> p;

            if (cnt == 0){
                (*magnets[cnt]).add_value(p);    
            } else if (cnt == 1){
                (*magnets[cnt]).add_value(p);
            } else if (cnt == 2){
                (*magnets[cnt]).add_value(p);
            } else {
                (*magnets[cnt]).add_value(p);
            }

            if (j % 8 == 0) cnt++;
        }

        for(int j=0; j<4; j++){
            (*magnets[j]).init();
        }

        int fst, snd;
        for(int j=0; j<k; j++){
            //mfile >> fst >> snd;
            cin >> fst >> snd;
            init_rotate();
            start_rotate(fst, snd);
        }

        cout << "#" << (i+1) << " " << evaluate() << endl;
    }
}

int main(int argc, char** argv){

    //start_alg("sample_input.txt");
    start_alg();

    return 0;

}