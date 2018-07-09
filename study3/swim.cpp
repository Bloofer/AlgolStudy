#include <iostream>
#include <fstream>
using namespace std;

int t;
int price[4];
int month[12];
int monthPrice[12];
int totalPrice[12];

int min(int a, int b){
    return (a < b) ? a : b;
}

void start_alg(){
    // 1. get monthly price
    for(int i=0; i<12; i++){
        monthPrice[i] = min(price[0] * month[i], price[1]);
    }

    // 2. get total price using recurrence formula
    for(int i=0; i<12; i++){
        if (i<1){
            totalPrice[i] = monthPrice[i];
        } else if (i<2){
            totalPrice[i] = totalPrice[i-1] + monthPrice[i];
        } else {
            totalPrice[i] = min(totalPrice[i-1] + monthPrice[i], totalPrice[i-3] + price[2]);
        }
    }

    // 3. compare final value with yearly price
    totalPrice[11] = min(totalPrice[11], price[3]);
}

void init(){
    for(int i=0; i<12; i++){
        monthPrice[i] = totalPrice[i] = 0;
    }
}

//void read_file(string fileName){
void read_file(){
    //fstream sfile(fileName.c_str());
    //sfile >> t;
    cin >> t;

    for(int i=0; i<t; i++){
        for(int j=0; j<4; j++){
            //sfile >> price[j];
            cin >> price[j];
        }
        for(int k=0; k<12; k++){
            //sfile >> month[k];
            cin >> month[k];
        }
        init();
        start_alg();
        cout << "#" << i+1 << " " << totalPrice[11] << endl;
    }
}

int main(int argc, char **argv){
    //read_file(argv[1]);
    read_file();
    return 0;
}