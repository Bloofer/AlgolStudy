#include <iostream>
#include <fstream>
using namespace std;

int T, K;
bool **MM;
// 0: head , 2: rh , 6: lh
bool mlink[3];

void rotate(bool *M){
    bool tmp = M[7];
    for(int i=6; i>=0; i--){
        M[i+1] = M[i];
    }
    M[0] = tmp;
}

void rev_rotate(bool *M){
    bool tmp = M[0];
    for(int i=0; i<7; i++){
        M[i] = M[i+1];
    }
    M[7] = tmp;
}

void dir_rotate(bool *M, int dir){
    if(dir == 1) rotate(M);
    else if(dir == -1) rev_rotate(M);
}

void print(bool *M){
    for(int i=0; i<8; i++){
        cout << M[i] << " ";
    }
    cout << endl;
}

bool is_opposite(bool *fstM, bool *sndM){
    return (fstM[2] != sndM[6]);
}

void get_link(){
    mlink[0] = mlink[1] = mlink[2] = false;
    if(is_opposite(MM[0], MM[1])) mlink[0] = true; 
    if(is_opposite(MM[1], MM[2])) mlink[1] = true;
    if(is_opposite(MM[2], MM[3])) mlink[2] = true;
}

pair<int, int> get_range(int m_num){
    if(!mlink[0] && !mlink[1] && !mlink[2]) return pair<int, int>(0, 0);
    else if(mlink[0] && mlink[1] && mlink[2]) return pair<int, int>(1, 4);
    else if(mlink[0] && mlink[1] && !mlink[2] && (m_num != 4)) return pair<int, int>(1, 3);
    else if(!mlink[0] && mlink[1] && mlink[2] && (m_num != 1)) return pair<int, int>(2, 4);
    else {
        for(int i=0; i<3; i++){
            if(mlink[i] && ((m_num == i+1 || m_num == i+2))) return pair<int, int>(i+1, i+2);
        }
    }
    return pair<int, int>(0, 0);
}

void turn(int m_num, int dir){

    get_link();
    pair<int, int> range = get_range(m_num);
    //cout << range.first << " " << range.second << endl;

    // rotate
    if(range.first != 0 && range.second != 0){
        for(int i=range.first; i<=range.second; i++){
            if((i - m_num) % 2 == 0) dir_rotate(MM[i-1], dir);
            else if((i - m_num) % 2 == 1 || (i - m_num) % 2 == -1) dir_rotate(MM[i-1], -dir);
        }
    } else{
        dir_rotate(MM[m_num - 1], dir);
    }    

}

int eval(){
    int sum = 0;
    if(MM[0][0]) sum += 1;
    if(MM[1][0]) sum += 2;
    if(MM[2][0]) sum += 4;
    if(MM[3][0]) sum += 8;
    return sum;
}

void init(){
    MM = new bool*[4];
    for(int i=0; i<4; i++) MM[i] = new bool[8];
}

//void read_file(string fileName){
void read_file(){
    //ifstream iFile(fileName.c_str());

    //iFile >> T;
    cin >> T;

    for(int i=0; i<T; i++){
        //iFile >> K;
        cin >> K;
        init();
        for(int j=0; j<4; j++){
            for(int k=0; k<8; k++){
                //iFile >> MM[j][k];
                cin >> MM[j][k];
            }
        }
        for(int j=0; j<K; j++){
            int mnum, dnum;
            //iFile >> mnum >> dnum;
            cin >> mnum >> dnum;
            turn(mnum, dnum);
        }
        cout << "#" << i+1 << " " << eval() << endl;
    }
}

int main(int argc, char** argv){

    /* if(argc < 2){
        cerr << "Usage: ./a.out INPUTFILE" << endl;
        return -1;
    }

    read_file(argv[1]); */
    read_file();

    return 0;
}