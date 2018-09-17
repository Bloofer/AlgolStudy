#include <iostream>
#include <fstream>
using namespace std;

int N, M;
int cell[8][8], **tempCell, **copyCell;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int ans;

void eval() {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (copyCell[i][j] == 0)
                ++cnt;
        }
    }

    if (cnt > ans)
        ans = cnt;
}

void taint(int y, int x) {
    for (int i = 0; i < 4; i++) {
        // traverse every 4 direction near cell
        int nx = dx[i] + x;
        int ny = dy[i] + y;

        if (0 <= ny && ny < N && 0 <= nx && nx < M) {
            if (copyCell[ny][nx] == 0) {
                copyCell[ny][nx] = 3;
                // if traversable path is empty,
                // taint cell with 3 (new taint area)
                taint(ny, nx);
            }
        }
    }
}

void dfs(int v, int cnt) {
    // v : encoded index, cnt : counter for wall (Max upto 3)
    // decode indices
    int col = (int)(v / (M * 1.0));
    int row = v % M;

    if (cnt == 3) {
        copyCell = new int*[N];
        for (int i = 0; i < N; i++) copyCell[i] = new int[M];        

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                copyCell[i][j] = tempCell[i][j];
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (copyCell[i][j] == 2) {
                    taint(i, j);
                }
            }
        }
        eval();
    } else {
        for (int i = v + 1; i < N * M; i++) {
            int col_sub = (int)(i / (M * 1.0));
            int row_sub = i % M;

            if (tempCell[col_sub][row_sub] == 0) {
                tempCell[col_sub][row_sub] = 1;
                dfs(i, cnt + 1);
            }
        }
    }

    tempCell[col][row] = 0;
    --cnt;
}

//void read_file(string fileName) {
void read_file() {
    //ifstream iFile(fileName.c_str());
    //iFile >> N >> M;
    cin >> N >> M;
    tempCell = new int*[N];
    for (int i = 0; i < N; i++) tempCell[i] = new int[M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            //iFile >> cell[i][j];
            cin >> cell[i][j];
            tempCell[i][j] = cell[i][j];
        }
    }

    // encode 2-dimensional indices into 1-dimensional integer
    for (int i = 0; i < N * M; i++) {

        // decode indices
        int col = (int)(i / (M * 1.0));
        int row = i % M;

        if (tempCell[col][row] == 0) {
            tempCell[col][row] = 1;
            dfs(i, 1);
            tempCell[col][row] = 0;
        }
    }

    cout << ans << endl;
}

void test_print() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << cell[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char **argv) {

    /* if (argc < 2) {
        cerr << "Usage : ./a.out INPUTFILE" << endl;
        return 1;
    } */

    //read_file(argv[1]);
    read_file();

}