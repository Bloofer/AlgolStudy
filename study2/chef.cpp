#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <fstream>

using namespace std;

int t; // number of tests
int n; // number of ingredients

const static int MAX_N = 16;
int synergy[MAX_N][MAX_N];

typedef struct{
    //int p, q; // index of the array
    vector<int> indices;
    int totalVal; // total value (= Sij + Sji)
    int gap;
}value;
value *valueArr;
int valArrSize;
int *valArrIdx;
int position;
int sum;

/* bool overlapped(value &v1, value &v2){
    // compare two value and returns true if they have overlapped indices
    return ( (v1.p == v2.p) || (v1.p == v2.q) || (v1.q == v2.p) || (v1.q == v2.q) );
} */

bool contains(vector<int> *v, int i){
    for(vector<int>::iterator it = v->begin(), end = v->end(); it != end; ++it){
        if ((*it) == i) return true;
    }
    return false;
}

bool overlapped(value *v1, value *v2){
    // compare two value and returns true if they have overlapped indices
    //find(v2->indices.begin(), v2->indices.end(), (*it));

    for(vector<int>::iterator it = v1->indices.begin(), end = v1->indices.end(); it != end; ++it){
        cout << contains(&(v2->indices), (*it));
        if (contains(&(v2->indices), (*it))) return true;
    }

    return false;
}

int compare_value(const void *a, const void *b){
    value *v1 = (value *)a;
    value *v2 = (value *)b;

    if(v1->gap > v2->gap)
        return 1;
    else if(v1->gap < v2->gap)
        return -1;
    else
        return 0;
}

/* int get_one_to_m(int m){
    return m * (m+1) / 2;
} */

unsigned long long int factorial(int i){
    if (i <= 1) return 1;
    else return i * factorial(i-1);
}

int combination(int i, int j){
    return factorial(i) / (factorial(i - j) * factorial(j));
}

void print_comb(int *arr, int length){
    for(int i=0; i<length; i++){
        cout << arr[i];        
    }
    cout << endl;
}

void copy_arr(value *vArr, int *arr){
    for(int i=0; i<n/2; i++){
        vArr[position].indices.push_back(arr[i]);
    }
    position++;
}

void comb(value *vArr, int *arr, int index, int n, int r, int target) { 
    if (r == 0) copy_arr(vArr, arr);
    else if (target == n) return; 
    else { 
        arr[index] = target; 
        comb(vArr, arr, index + 1, n, r - 1, target + 1); 
        comb(vArr, arr, index, n, r, target + 1); 
        }         
}

int get_total_val(int p, int q){
    return synergy[q][p] + synergy[p][q];
}

void evaluate_synergy_sub(int *iArr, int *arr){
    //cout << iArr[arr[0]] << iArr[arr[1]] << endl;
    sum += get_total_val(iArr[arr[0]], iArr[arr[1]]);
}

void comb_two(int *iArr, int *arr, int index, int n, int r, int target) { 
    if (r == 0) evaluate_synergy_sub(iArr, arr);
    else if (target == n) return; 
    else { 
        arr[index] = target; 
        comb_two(iArr, arr, index + 1, n, r - 1, target + 1); 
        comb_two(iArr, arr, index, n, r, target + 1); 
        }         
}

bool arr_has(vector<int> &v, int a){
    for(vector<int>::iterator it = v.begin(), end = v.end(); it != end; ++it){
        if((*it) == a) return true;
    }
    return false;
}

void opposite_indices(vector<int> &v, int **to_idx){
    int cnt = 0;
    for(int i=0; i<n; i++){
        if(!arr_has(v, i)) *to_idx[cnt++] = i;
    }
}

void print_indices(value *v){
    for(vector<int>::iterator it = v->indices.begin(), end = v->indices.end(); it != end; ++it){
        cout << (*it);
    }
}

void get_gap(value *v){
    int *opposite_idx = new int[n/2];
    print_indices(v);
    opposite_indices((v->indices), &opposite_idx);
    for(int i=0; i<n/2; i++){
        cout << opposite_idx[i];
    }
    cout << endl;
    sum = 0;
    int *twoIdx = new int[2];
    comb_two(opposite_idx, twoIdx, 0, n/2, 2, 0);
    int opposite_sum = sum;
    v->gap = abs(opposite_sum - v->totalVal);
}

void evaluate_synergy(value *vArr){
    //print_indices(vArr);
    sum = 0;
    int *vIndices = new int[n/2];
    int *twoIdx = new int[2];
    int idx = 0;
    for(vector<int>::iterator it = vArr->indices.begin(), end = vArr->indices.end(); it != end; ++it){
        vIndices[idx++] = (*it);
    }
    comb_two(vIndices, twoIdx, 0, n/2, 2, 0);
    vArr->totalVal = sum;
}

void print_value(){
    for(int i=0; i<valArrSize; i++){
        /* cout << "(";
        print_indices(&valueArr[i]);
        cout << ")=" << valueArr[i].totalVal << " "; */
        cout << valueArr[i].totalVal << endl;
    }
}

void get_value(){
    /* valArrSize = get_one_to_m(n-1);
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
    qsort(valueArr, valArrSize, sizeof(value), compare_value); */

    valArrSize = combination(n, n/2);
    valueArr = new value[valArrSize];
    //cout << "size : " << valArrSize << endl;
    valArrIdx = new int[n/2];
    position = 0;
    comb(valueArr, valArrIdx, 0, n, n/2, 0);
    
    for(int i=0; i<valArrSize; i++){
        evaluate_synergy(&valueArr[i]);
        get_gap(&valueArr[i]);
    }

    qsort(valueArr, valArrSize, sizeof(value), compare_value);
    //print_value();

}

void init_array(){
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            synergy[i][j] = 0;
        }
    }
}

/* int find_min_gap(){
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
} */

int find_min_gap(){
    /* int minGap = INT_MAX;

    for(int i=0; i<valArrSize - 1; i++){
        if (!overlapped(&valueArr[i], &valueArr[i+1])){
            //cout << (valueArr[i+1].totalVal - valueArr[i].totalVal) << endl;
            if ((valueArr[i+1].totalVal - valueArr[i].totalVal) < minGap) {
                minGap = (valueArr[i+1].totalVal - valueArr[i].totalVal);
                //cout << i << "\t";
            }
        }
    }

    return minGap; */
    return valueArr[0].gap;
}

/* void print_value(){
    for(int i=0; i<valArrSize; i++){
        cout << "(" << valueArr[i].p << ", " << valueArr[i].q << ")=" << valueArr[i].totalVal << " ";
    }
} */

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
        //print_value();
        cout << find_min_gap() << endl;
    }
}

int main(int argc, char** argv){

    read_file(argv[1]); 

    return 0;

}