#include <iostream>
#include <cstdlib>
#include <climits>
#include <fstream>

using namespace std;

int t; // number of tests
int n; // number of ingredients

const static int MAX_N = 16;
int synergy[MAX_N][MAX_N];

typedef struct{
    int p, q; // index of the array
    int totalVal; // total value (= Sij + Sji)
}value;
value *valueArr;
int valArrSize;

bool overlapped(value &v1, value &v2){
    // compare two value and returns true if they have overlapped indices
    return ( (v1.p == v2.p) || (v1.p == v2.q) || (v1.q == v2.p) || (v1.q == v2.q) );
}

int compare_value(const void *a, const void *b){
    value *v1 = (value *)a;
    value *v2 = (value *)b;

    if(v1->totalVal > v2->totalVal)
        return 1;
    else if(v1->totalVal < v2->totalVal)
        return -1;
    else
        return 0;
}

int get_one_to_m(int m){
    return m * (m+1) / 2;
}

void get_value(){
    valArrSize = get_one_to_m(n-1);
    valueArr = new value[valArrSize];
    int valCnt = 0;

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            valueArr[valCnt].p = i;
            valueArr[valCnt].q = j;
            valueArr[valCnt].totalVal = synergy[i][j] + synergy[j][i];
            valCnt++;
        }
    }
    qsort(valueArr, valArrSize, sizeof(value), compare_value);
}

void init_array(){
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            synergy[i][j] = 0;
        }
    }
}

int find_min_gap(){
    int minGap = INT_MAX;

    for(int i=0; i<valArrSize - 1; i++){
        if (!overlapped(valueArr[i], valueArr[i+1])){
            if ((valueArr[i+1].totalVal - valueArr[i].totalVal) < minGap) {
                minGap = (valueArr[i+1].totalVal - valueArr[i].totalVal);
                cout << i << "\t";
            }
        }
    }

    return minGap;
}

void print_value(){
    for(int i=0; i<valArrSize; i++){
        cout << "(" << valueArr[i].p << ", " << valueArr[i].q << ")=" << valueArr[i].totalVal << " ";
    }
}

void print_array(){
    cout << n << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << synergy[i][j] << "\t";
        }
        cout << endl;
    }
}

void read_file(string fileName){
    fstream cfile(fileName.c_str());
    cfile >> t;
    
    for(int i=0; i<t; i++){
        cfile >> n;

        init_array();
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                cfile >> synergy[j][k];
            }
        }
        get_value();
        print_value();
        cout << endl << find_min_gap() << endl;
    }
}


int main(int argc, char** argv){

    read_file(argv[1]); 

    return 0;

}