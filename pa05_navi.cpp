#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<math.h>
#include <stack>
#include <set>
#include<memory.h>
using namespace std;
constexpr int MAX = 201;
constexpr double INF = 1e9 + 7;
const int dx1[4] = { 0, 0, 1, -1 };
const int dy1[4] = { -1, 1, 0, 0 };
using Pair = pair<int, int>;
using pPair = pair<double, Pair>;
char zmap[MAX][MAX];
int ROW = 0, COL = 0;
struct Cell {
    int parent_x, parent_y;
    double f, g, h;
};
bool isDestination(int row, int col, Pair dst) {
    if (row == dst.first && col == dst.second) return true;
    return false;
}

bool isInRange(int row, int col) {
    return (row >= 0 && row < ROW&& col >= 0 && col < COL);
}

bool isUnBlocked(std::vector<std::vector<int>>& map, int row, int col) {
    return (map[row][col] == 0);
}

double GethValue(int row, int col, Pair dst) {
    return (double)sqrt(pow(row - dst.first, 2) + pow(col - dst.second, 2));
}
int GetMin(int a, int b) {
    if (a > b) {
        return b;
    }
    return a;
}
int GetMax(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
void tracePath(Cell cellDetails[MAX][MAX], Pair dst) {
    int g = 0;
    stack<Pair> s;
    int y = dst.first;
    int x = dst.second;
    s.push({ y, x });
    while (!(cellDetails[y][x].parent_x == x && cellDetails[y][x].parent_y == y)) {
        int tempy = cellDetails[y][x].parent_y;
        int tempx = cellDetails[y][x].parent_x;
        y = tempy;
        x = tempx;
        s.push({ y, x });
    }
    while (!s.empty()) {
        zmap[s.top().first][s.top().second] = '*';
        g += 3;
        s.pop();
    }
    cout << g - 3;
}
int a_star(vector<vector<int>>& map, Pair src, Pair dst) {
    bool closedList[MAX][MAX];
    memset(closedList, false, sizeof(closedList));
    Cell cellDetails[MAX][MAX];
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = INF;
            cellDetails[i][j].parent_x = cellDetails[i][j].parent_y = -1;
        }
    }
    int sy = src.first;
    int sx = src.second;
    cellDetails[sy][sx].f = cellDetails[sy][sx].g = cellDetails[sy][sx].h = 0.0;
    cellDetails[sy][sx].parent_x = sx;
    cellDetails[sy][sx].parent_y = sy;
    set<pPair> openList;
    openList.insert({ 0.0, { sy, sx } });
    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        int y = p.second.first;
        int x = p.second.second;
        closedList[y][x] = true;
        double ng, nf, nh;
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy1[i];
            int nx = x + dx1[i];
            if (isInRange(ny, nx)) {
                if (isDestination(ny, nx, dst)) {
                    cellDetails[ny][nx].parent_y = y;
                    cellDetails[ny][nx].parent_x = x;
                    tracePath(cellDetails, dst);
                    return true;
                }
                else if (!closedList[ny][nx] && isUnBlocked(map, ny, nx)) {
                    ng = cellDetails[y][x].g + 3.0;
                    nh = GethValue(ny, nx, dst);
                    nf = ng + nh;
                    if (cellDetails[ny][nx].f == INF || cellDetails[ny][nx].f > nf) {
                        cellDetails[ny][nx].f = nf;
                        cellDetails[ny][nx].g = ng;
                        cellDetails[ny][nx].h = nh;
                        cellDetails[ny][nx].parent_x = x;
                        cellDetails[ny][nx].parent_y = y;
                        openList.insert({ nf, { ny, nx } });
                    }
                }
            }
        }

    }
    return 0;
}
void make_blank(vector<vector<int>>& list, int x1, int y1, int x2, int y2) {
    for (int k = 0; k < ROW; ++k) {
        for (int j = 0; j < COL; ++j) {
            if (k >= GetMin(x1, x2) && j >= GetMin(y1, y2) && k <= GetMax(x1, x2) && j <= GetMax(y1, y2)) {
                list[k][j] = 1;
            }
        }
    }
}
int main() {
    Pair src, dst;
    int row, col;
    int x, y = 0;
    int x2, y2 = 0;
    int blank;
    string  s;
    cin >> row >> col;
    cin.ignore();
    cin >> blank;
    cin.ignore();
    ROW = row;
    COL = col;
    vector<vector<int>> arr(row, vector<int>(col));
    for (int j = 0; j < blank; ++j) {
        cin >> s >> x >> y;
        cin.ignore();
        arr[x][y] = 1;
    }
    cin >> s >> x >> y;
    cin.ignore();
    src = { x, y };
    cin >> s >> x >> y;
    cin.ignore();
    dst = { x, y };
    cin >> s >> blank;
    cin.ignore();
    for (int j = 0; j < blank; ++j) {
        cin >> x >> y >> x2 >> y2;
        cin.ignore();
        make_blank(arr, x, y, x2, y2);
    }
    a_star(arr, src, dst);
    return 0;
}