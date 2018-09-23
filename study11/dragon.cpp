#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int N, G, X, Y;
bool rowMap[101][100];
bool colMap[100][101];
vector<int> dcStack;
int cnt;

void test_print(){
    
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            cout << rowMap[i][j];
        }
        cout << endl;
    }

    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            cout << colMap[i][j];
        }
        cout << endl;
    }

}

void init(){

    for(int i=0; i<101; i++){
        for(int j=0; j<100; j++){
            rowMap[i][j] = false;
        }
    }

    for(int i=0; i<100; i++){
        for(int j=0; j<101; j++){
            colMap[i][j] = false;
        }
    }

    cnt = 0;

}

void eval(){

    // count squares which points are marked to dragon curve
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            if( rowMap[i][j] && rowMap[i+1][j] &&
                colMap[i][j] ) cnt++;
            else if( rowMap[i][j] && rowMap[i+1][j] &&
                colMap[i][j+1] ) cnt++;
            else if( rowMap[i][j] &&
                colMap[i][j] && colMap[i][j+1] ) cnt++;
            else if( rowMap[i+1][j] &&
                colMap[i][j] && colMap[i][j+1] ) cnt++;
            else if( colMap[i][j] && colMap[i][j+1] ) cnt++;
            else if( rowMap[i][j] && rowMap[i+1][j] ) cnt++;
        }
    }

}

void draw_map(){

    // draw direction map for evaluation
    int x = X;
    int y = Y;

    for(int i=0; i<dcStack.size(); i++){
        if(dcStack.at(i) == 0){
            rowMap[y][x] = true;
            x++; 
        } else if(dcStack.at(i) == 1){
            colMap[y-1][x] = true;
            y--;
        } else if(dcStack.at(i) == 2){
            rowMap[y][x-1] = true;
            x--;
        } else if(dcStack.at(i) == 3){
            colMap[y][x] = true;
            y++;
        }
    }

}

int rotate(int i){
    if(i == 0) return 1;
    else if(i == 1) return 2;
    else if(i == 2) return 3;
    else if(i == 3) return 0;
    else {
        cerr << "rotate input must be in between 0~3" << endl;
        return -1;
    }
}

void dragon_curve(int gen){

    if (gen == G){
        // base case
        draw_map();
    } else {
        // 1. rotate 270 degrees(90 to rotate + 180 to reverse) to curve stack
        vector<int> tmpStack;
        for(int i=0; i<dcStack.size(); i++){
            int rIdx = rotate(dcStack.at(i));
            tmpStack.push_back(rIdx);
        }
        
        // 3. append in reversed row
        for(int i=tmpStack.size()-1; i>=0; i--){
            dcStack.push_back(tmpStack.at(i));
        }

        dragon_curve(gen+1);
    }

}

//void read_file(string fileName){
void read_file(){

    //ifstream iFile(fileName.c_str());
    //iFile >> N;
    cin >> N;

    init();

    for(int i=0; i<N; i++){
        X = Y = G = 0;
        dcStack.clear();
        int d;
        //iFile >> X >> Y >> d >> G;
        cin >> X >> Y >> d >> G;
        dcStack.push_back(d);
        dragon_curve(0);
    }

    eval();
    //test_print();

}

int main(int argc, char **argv){

    /* if(argc < 2){
        cerr << "USAGE : ./a.out INPUTFILE" << endl;
        return 1;
    } */

    //read_file(argv[1]);
    read_file();
    cout << cnt << endl;

    return 0;

}