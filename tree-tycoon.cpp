// url: https://www.codetree.ai/frequent-problems/tree-tycoon/description
#include <iostream>
#include <vector>
#include <string>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int dr[8][2] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
int n, m;
int grid[15][15][2];
vector<P> sup;

void move(int d, int p){
    for(auto& s : sup){
        s.X = (s.X + p * dr[d][0] + p * n) % n;
        s.Y = (s.Y + p * dr[d][1] + p * n) % n;
        grid[s.X][s.Y][0] ++;
    }
}
void grow(){
    bool used[20][20];
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            grid[i][j][1] = 0;
            used[i][j] = false;
        }
    }
    for(auto& s : sup){
        int x = s.X;
        int y = s.Y;
        used[x][y] = true;
        for(int i = 1 ; i < 8 ; i += 2){
            int nx = x + dr[i][0];
            int ny = y + dr[i][1];
            if(nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
            if(grid[nx][ny][0] > 0) grid[x][y][1] ++;
        }
    }
    sup.clear();
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            grid[i][j][0] += grid[i][j][1];
            if(!used[i][j] and grid[i][j][0] >= 2){
                sup.push_back({i, j});
                grid[i][j][0] -= 2;
            }
        }
    }
}

int score(){
    int res = 0;
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            res += grid[i][j][0];
        }
    }
    return res;
}

int main(int argc, const char * argv[]) {
    cin >> n >> m;
    for(int i = 0; i < n ; i ++){
        for(int j = 0  ; j < n ; j ++){
            cin >> grid[i][j][0];
        }
    }
    sup = vector<P>({{n - 1, 0}, {n - 2, 0}, {n - 1, 1}, {n - 2, 1}});

    for(int i = 0 ; i < m ; i ++){
        int d, p;
        cin >> d >> p;
        move(d - 1, p);
        grow();
    }
    cout << score();
    return 0;
}
