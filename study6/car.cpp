#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

typedef struct{
    int n; // Customer number
    int t; // process time
} Customer;

typedef struct{
    int idx; // desk number which Customer used
    int n;   // Customer number
    int t;   // queue incoming time
} Queue;

int a[10]; // reception process time
int b[10]; // repair process time
Customer rec[10]; // Customer info which used reception desk
Customer rep[10]; // Customer info which used repair desk
Customer aQueue[1001]; // reception desk queue
Queue bQueue[1001];    // repair desk queue
int recOut; // reception desk out index
int repIn, repOut; // repair desk in/out index

int T;
int N, M, K, A, B;

int cmp(const void *a, const void *b){
    Customer *c1 = (Customer *)a;
    Customer *c2 = (Customer *)b;

    if(c1->t > c2->t || (c1->t == c2->t && c1->n > c2->n)) return 1;
    else return -1;
}

int start_alg(){

    int ans = 0;

    recOut = repIn = repOut = 0;

    qsort( aQueue, K, sizeof(Customer), cmp );

    for(int cnt=1, tim=aQueue[0].t; cnt<=K; ++tim){

        // for reception desk
        for(int i=1; i<=N; ++i){
            if(rec[i].t>0){
                if(--rec[i].t == 0){
                    bQueue[repIn++] = { i, rec[i].n, tim };
                }
            }
            if(rec[i].t==0){
                if(recOut<K && aQueue[recOut].t<=tim){
                    Customer customer = aQueue[recOut++];
                    rec[i] = { customer.n, a[i] };
                }
            }
        }

        for(int i=1; i<=M; ++i){
            if(rep[i].t>0){
                if(--rep[i].t==0){
                    ++cnt;
                }
            }
            if(rep[i].t==0){
                if(repOut < repIn){
                    Queue queue = bQueue[repOut++];
                    rep[i] = { queue.n, b[i] };
                    if(queue.idx == A && i == B) ans+=queue.n;
                }
            }
        }
    }

    if (ans == 0) return -1;
    else return ans;

}

int main(int argv, char** argc){

    /* if(argv < 2){
        cerr << "Usage : ./a.out INPUTFILE" << endl;
        return 1;
    } */

    //ifstream cFile(argc[1]);
    cin >> T;

    for(int i=1; i<=T; i++){
        cin >> N >> M >> K >> A >> B;
        for(int j=1; j<=N; ++j) cin >> *(a+j);
        for(int j=1; j<=M; ++j) cin >> *(b+j);
        for(int j=0; j<K; ++j) cin >> aQueue[j].t, aQueue[j].n = j+1;
        cout << "#" << i << " " << start_alg() << endl;
    }

    return 0;

}