#include <iostream>
#include <vector>
using namespace std;

int saw[4][8]; // 1~4번 톱니바퀴, 1~8번째 날 (N:0, S:1)
vector< pair<int, int> > moves;
bool link[3]; // 1~4번 톱니바퀴의 맞닿은 부분의 극이 다른지 여부

void test_print_saw(){
    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            cout << saw[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void chk_link(){
    // 서로 맞닿은 부분의 자성이 달라야 연쇄회전가능
    link[0] = (saw[0][2] != saw[1][6]);
    link[1] = (saw[1][2] != saw[2][6]);
    link[2] = (saw[2][2] != saw[3][6]);
}

void rotate(int idx, int dir){
    if(dir == 1){
        // 톱니바퀴를 시계방향으로 회전
        int tmp = saw[idx][7];
        for(int i=6; i>=0; i--) saw[idx][i+1] = saw[idx][i];
        saw[idx][0] = tmp;
    } else if(dir == -1){
        // 톱니바퀴를 반시계방향으로 회전
        int tmp = saw[idx][0];
        for(int i=1; i<=7; i++) saw[idx][i-1] = saw[idx][i];
        saw[idx][7] = tmp;
    }
    
}

void move(){
    for(auto i: moves){
        chk_link();
        rotate(i.first-1, i.second);
        if(i.first == 1){
            for(int j=0; j<3; j++){
                if(!link[j]) break;
                else {
                    i.second = -i.second;
                    rotate(j+1, i.second);
                }
            }
        } else if(i.first == 2){
            if(link[0]) rotate(0, -i.second);
            for(int j=1; j<3; j++){
                if(!link[j]) break;
                else {
                    i.second = -i.second;
                    rotate(j+1, i.second);
                }
            }
        } else if(i.first == 3){
            if(link[2]) rotate(3, -i.second);
            for(int j=1; j>=0; j--){
                if(!link[j]) break;
                else {
                    i.second = -i.second;
                    rotate(j, i.second);
                }
            }
        } else if(i.first == 4){
            for(int j=2; j>=0; j--){
                if(!link[j]) break;
                else {
                    i.second = -i.second;
                    rotate(j, i.second);
                }
            }
        }
    }
}

int eval(){
    int sum = 0;
    int num = 1;
    for(int i=0; i<4; i++){
        if(saw[i][0]) sum += num;
        num *= 2;
    }
    return sum;
}

int main(){
    for(int i=0; i<4; i++){
        string saws;
        cin >> saws;
        for(int j=0; j<8; j++) saw[i][j] = saws.at(j) - '0';
    }

    int N;
    cin >> N;
    for(int i=0; i<N; i++){
        int cnt, dir;
        cin >> cnt >> dir;
        moves.push_back(pair<int, int>(cnt, dir));        
    }

    move();
    cout << eval() << endl;
}