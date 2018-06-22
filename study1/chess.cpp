#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// constant variables
const static int MAX_N = 10000;
const static int MAX_M = 10000;
const static int MAX_K = 2000;
const static int MAX_TEST_NUM = 20;

// input variables
int test_num;
int n, m, k, count;

// board array starts at (1,1) and ends at (n,m) b.c. of the problem condition
bool board[MAX_N+1][MAX_M+1];

// test results
int test_result[MAX_TEST_NUM];

// k pair of obstacles
typedef struct{
    int x;
    int y;
}K_pair;
K_pair k_pair[MAX_K];

// functions used for the algorithm
void init();
bool is_arrived(int x, int y);
void go(int x, int y);
void start_alg(string fileName); // main function for algorithm
void print_result();
void print_array();



// function implementations

void init(){

    count = 0;

    // init board 2D array
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            board[i][j] = false;
        }
    }

    // mark the obstacle indices
    for (int i=0; i<k; i++){
        board[k_pair[i].x][k_pair[i].y] = true;        
    }

}

bool is_arrived(int x, int y){
    return ((x == n) && (y == m));
}

void go(int x, int y){

    // if arrived to (N, M) increment counter
    if ( is_arrived(x, y) ) {
        count++;
        return;    
    }
    
    // check the path and go 
    if ((x+1) <= n) { if (!board[x+1][y]) go(x+1, y); }
    if ((y+1) <= m) { if (!board[x][y+1]) go(x, y+1); }

}

void start_alg(string fileName){
    
    fstream cfile(fileName.c_str());
    cfile >> test_num;

    for(int i=0; i<test_num; i++){

        cfile >> n >> m >> k;

        for(int j=0; j<k; j++){
            cfile >> k_pair[j].x >> k_pair[j].y;
        }

        init();
        go(1,1);
        test_result[i] = count;

        cout << test_result[i] << endl;
    }

}

void print_result(){

    for(int i=0; i<test_num; i++){
        cout << test_result[i] % 1000000007 << endl;
    }

}

void print_array(){

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(!board[i][j]) cout << "0 ";
            else cout << "1 "; 
        }
        cout << endl;
    }

}


// main function

int main(int argc, char** argv) 
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " TESTFILE" << endl;
        return 1;
    }

    start_alg(argv[1]);
    print_result();

    return 0;
}