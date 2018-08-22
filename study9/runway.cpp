#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int T, N, X;
int arr[20][20];
int chk[40];

typedef struct{
    int height;
    bool hasRunway;
}Runway;
Runway runway[20];

bool chk_runway(){

    // if all of the array indices has same height, return true
    bool same = true;
    int num = runway[0].height;
    for(int i=1; i<N; i++) same &= (runway[i].height == num);
    if(same) return true;

    // 1. find and mark the possible runway sites
    // put the runway close to the higher site

    // 2. traverse array and check the flight is possible
    // check both inc/decreasing site number has runway back and forth

    return false;

}

void start_alg(){

    // 1. search rows
    // & check possible runways to chk array (0 ~ N-1 indices)
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) runway[i].height = arr[i][j];
        runway[i].hasRunway = false;
        chk[i] = chk_runway();
    }

    // 2. search cols
    // & check possible runways to chk array (0 ~ N-1 indices)
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) runway[i].height = arr[j][i];
        runway[i].hasRunway = false;
        chk[i+N] = chk_runway();
    }

    // 3. get checked sum
    int sol = 0;
    for(int i=0; i<2*N; i++) if(chk[i]) sol++;
    //cout << sol << endl;

}

void test_print(){

    cout << N << "\t" << X << endl;
    for(int j=0; j<N; j++) { 
        for(int k=0; k<N; k++) { 
            cout << arr[j][k] << " ";
        }
        cout << endl;
    }

}

void read_file(string fileName){

    ifstream iFile(fileName.c_str());

    iFile >> T;

    for(int i=0; i<T; i++){
        iFile >> N >> X;
        for(int j=0; j<N; j++) for(int k=0; k<N; k++) iFile >> arr[j][k];
        //test_print();
        start_alg();
    }  

}

int main(int argc, char **argv){

    if(argc < 2){
        cerr << "Usage : ./a.out INPUTFILE" << endl;
        return 1;
    }

    read_file(argv[1]);

    return 0;

}