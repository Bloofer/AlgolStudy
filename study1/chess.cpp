#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

// constant variables
const static int MAX_N = 10000;
const static int MAX_M = 10000;
const static int MAX_K = 2000;
const static int MAX_TEST_NUM = 20;
const static int MOD = 1000000007;

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
void print_point();

// with better method
int compare_point(const void *a, const void *b);
int solve(int i);
int num_of_paths(int i, int j);
int combination(int a, int b);
long long int factorial(long long int x);
unsigned long long int factorial_iter(int number);


// function implementations
// Dynamic Search

void init(){

    /* count = 0;

    // init board 2D array
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            board[i][j] = false;
        }
    }

    // mark the obstacle indices
    for (int i=1; i<=k; i++){
        board[k_pair[i].x][k_pair[i].y] = true;        
    } */

    qsort(k_pair, k+2, sizeof(K_pair), compare_point);

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

        for(int j=1; j<=k; j++){
            cfile >> k_pair[j].x >> k_pair[j].y;
        }

        // K0 = leftest&top point, Kk+1 = rightest&bottom point
        k_pair[0].x = k_pair[0].y = 1;
        k_pair[k+1].x = n;
        k_pair[k+1].y = m;

        init();
        //go(1,1);
        
        test_result[i] = solve(0);

        //cout << test_result[i] << endl;
    }

}



// function implementations
// With better method

int compare_point(const void *a, const void *b){
    
    K_pair *k1 = (K_pair *)a;
    K_pair *k2 = (K_pair *)b;

    if (k1->x > k2->x)
        return 1;
    else if ((k1->x == k2->x) && (k1->y > k2->y))
        return 1;
    else if (k1->x < k2->x)
        return -1;
    else if ((k1->x == k2->x) && (k1->y < k2->y))
        return -1;
    else 
        return 0;

}

int solve(int i){

    int j = i + 1;

    if (i > k) return 1;
    else return num_of_paths(i, k+1) - (num_of_paths(i, j) * solve(j));

}

int num_of_paths(int i, int j){

    int a = (k_pair[j].x - k_pair[i].x) + (k_pair[j].y - k_pair[i].y);
    int b = (k_pair[j].x - k_pair[i].x);
    cout << combination(a, b) << endl;
    return combination(a, b);

}

int combination(int a, int b){

    if ((factorial_iter(b) * factorial_iter(a - b)) == 0) return 0;
    else return (int)(factorial_iter(a)) / (factorial_iter(b) * factorial_iter(a - b));

}

long long int factorial(long long int x){

    if(x > 1) return (x % MOD * factorial(x - 1) % MOD);
    else return 1;

}

unsigned long long int factorial_iter(int number)
{
   int fact = 1;

   for (int i = 1; i <= number; i++)
      fact = fact * i % MOD;

   return fact % MOD;
}


// test print functions

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

void print_point(){

    for(int i=0; i<=k+1; i++){
        cout << "(" << k_pair[i].x << ", " << k_pair[i].y << ")\n";
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
    cout << combination(200,100);

    //factorial_iter(100) % MOD;

    // for test
    /* n = 3;
    m = 4;
    k = 2;
    k_pair[0].x = k_pair[0].y = 1;
    k_pair[k+1].x = n;
    k_pair[k+1].y = m;
    k_pair[1].x = 2;
    k_pair[1].y = 2;
    k_pair[2].x = 2;
    k_pair[2].y = 3;
    cout<< solve(0); */

    return 0;
}