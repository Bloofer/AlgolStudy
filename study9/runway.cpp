#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int T, N, X;
int arr[20][20];
int chkRowCol[40];

typedef struct{
    int height;
    bool hasRunway;
}Runway;
Runway runway[20];

void print_runway_vec(vector< pair<int, int> > &runwayVec){
    for(int i=0; i<runwayVec.size(); i++){
        cout << "[" << runwayVec.at(i).first << "," << runwayVec.at(i).second << "]";
    }
}

bool has_runway(){
    bool has = false;
    for(int i=0; i<N; i++) has |= runway[i].hasRunway;
    return has;
}

int abs(int n){
    return n > 0 ? n : -n; 
}

bool chk_runway(){

    // if all of the array indices has same height, return true
    bool same = true;
    int num = runway[0].height;
    for(int i=1; i<N; i++) same &= (runway[i].height == num);
    if(same) return true;

    bool has = false;

    // 1. find and mark the possible runway sites
    // put the runway close to the higher site
    for(int i=1; i<=6; i++){
        int frt, bck, cnt;
        bool cont = false;
        vector< pair<int, int> > runwayVec;
        bool chk[N];
        for(int j=0; j<N; j++) chk[j] = false;
        for(int j=0; j<N; j++){
            if(runway[j].height == i) chk[j] = true;
        }
        for(int j=0; j<N; j++){
            if(j == N-1 && chk[j] && cont){
                if (cnt >= X-1) {
                    bck = j;
                    runwayVec.push_back(pair<int, int>(frt, bck));
                }
            } else if(chk[j] && !cont){
                frt = j;
                cont = true;
                cnt = 1;
            } else if(chk[j] && cont){
                cnt++;
            } else if(!chk[j] && cont){
                if (cnt >= X) {
                    bck = j-1;
                    runwayVec.push_back(pair<int, int>(frt, bck));
                    frt = bck = -1;
                    cnt = 0;
                    cont = false;
                } else {
                    frt = bck = -1;
                    cnt = 0;
                    cont = false;
                }
            } else {
                continue;
            }
        }

        if (!runwayVec.empty()){
            /* cout << "height #" << i << " : ";
            print_runway_vec(runwayVec);
            cout << endl; */

            // set runway to possible position
            for(int j=0; j<runwayVec.size(); j++){
                int front = runwayVec.at(j).first;
                int back = runwayVec.at(j).second;
                int frtPad, bckPad; 
                int frtGap, bckGap;
                if (front > 0 && back < N-1) {
                    frtPad = runway[front-1].height;
                    bckPad = runway[back+1].height;
                    frtGap = frtPad - runway[front].height;
                    bckGap = bckPad - runway[back].height;
                    if(abs(frtGap) > 1 || abs(bckGap) > 1) return false;

                    if (frtPad == (runway[front].height+1) && bckPad == (runway[back].height+1)) {
                        if (back - front + 1 >= 2 * X && frtGap > 0 && bckGap > 0) {
                            for (int k=front; k<front+X; k++) runway[k].hasRunway = true;
                            for (int k=back; k>front-X; k--) runway[k].hasRunway = true;
                        } else if (back - front + 1 >= X && frtGap > 0){
                            for (int k=front; k<front+X; k++) runway[k].hasRunway = true;
                        } else if (back - front + 1 >= X && bckGap > 0){
                            for (int k=back; k>front-X; k--) runway[k].hasRunway = true;
                        } else {
                            return false;
                        }
                    } else if (frtPad == (runway[front].height+1)) {
                        if (back - front + 1 >= X && frtGap > 0){
                            for (int k=front; k<front+X; k++) runway[k].hasRunway = true;
                        } else {
                            return false;
                        }
                    } else if (bckPad == (runway[back].height+1)) {
                        if (back - front + 1 >= X && bckGap > 0){
                            for (int k=back; k>front-X; k--) runway[k].hasRunway = true;
                        } else {
                            return false;
                        }
                    }
                } else if (front == 0) {
                    bckPad = runway[back+1].height;
                    bckGap = bckPad - runway[back].height;
                    if(abs(bckGap) > 1) return false;

                    if (bckPad == (runway[back].height+1)) {
                        for (int k=back; k>front-X; k--) runway[k].hasRunway = true;
                    }
                } else if (back == N-1) {
                    frtPad = runway[front-1].height;
                    frtGap = frtPad - runway[front].height;
                    if(abs(bckGap) > 1) return false;

                    if (frtPad == (runway[front].height+1)) {
                        for (int k=front; k<front+X; k++) runway[k].hasRunway = true;
                    }
                }
            }

            has |= has_runway();
        }
    }

    // 2. traverse array and check the flight is possible
    // check both inc/decreasing site number has runway back and forth
    return has;

}

void start_alg(){

    // 1. search rows
    // & check possible runways to chk array (0 ~ N-1 indices)
    //cout << "row ";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) runway[j].height = arr[i][j];
        runway[i].hasRunway = false;
        chkRowCol[i] = chk_runway();
        //if(chk_runway()) cout << i+1;
    }

    // 2. search cols
    // & check possible runways to chk array (0 ~ N-1 indices)
    //cout << "col ";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) runway[i].height = arr[j][i];
        runway[i].hasRunway = false;
        chkRowCol[i+N] = chk_runway();
        //if(chk_runway()) cout << i+1;
    }

    // 3. get checked sum
    int sol = 0;
    for(int i=0; i<2*N; i++) if(chkRowCol[i]) sol++;
    cout << sol << endl;

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
        //cout << "Test #" << i+1 << endl;
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