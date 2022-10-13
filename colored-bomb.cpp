//
//  main.cpp
//  colored_bomb
//
//  Created by dong ha kim on 2022/10/12.
//
// url: https://www.codetree.ai/frequent-problems/colored-bomb/description
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int n, m;
int score = 0;
int A[20][20];
int tmp[20][20] = {0, };
int dr[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

bool visited[20][20] = {false, };

void destroy(int x, int y){
    int res = 0;
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            visited[i][j] = false;
        }
    }
    int val = A[x][y];
    queue<P> q;
    visited[x][y] = true;
    q.push({x, y});
    while(!q.empty()){
        P cur = q.front();
        A[cur.X][cur.Y] = -2;
        res ++;
        q.pop();
        for(int i = 0 ; i < 4 ; i ++){
            int nx = cur.X + dr[i][0];
            int ny = cur.Y + dr[i][1];
            if(nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
            if(A[nx][ny] < 0) continue;
            if(A[nx][ny] != 0 and A[nx][ny] != val) continue;
            if(visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    score += res * res;
}
void show() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == -1) cout << "- ";
            else if (A[i][j] == -2) cout << "  ";
            else cout << A[i][j] << " ";
        }
        cout << '\n';
    }
    for (int i = 0; i < 2 * n; i++) cout << "-";
    cout << '\n';
}
void rotate(){
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            tmp[n-1-j][i] = A[i][j];
        }
    }
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            A[i][j] = tmp[i][j];
        }
    }
}
void gravity(){
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            if(A[i][j] == -1) tmp[i][j] = -1;
            else tmp[i][j] = -2;
        }
    }
    for(int i = n - 1 ; i >= 0 ; i --){
        for(int j = 0 ; j < n ; j ++){
            if(A[i][j] >= 0) {
                int x = i;
                int y = j;
                int nx = x;
                int ny = y;
                for(nx = x + 1 ; nx < n ; nx ++){
                    if(tmp[nx][ny] != -2) {
                        nx --;
                        break;
                    }
                }
                if(nx == n) nx--;
                tmp[nx][ny] = A[x][y];                
            }
        }
    }
    
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            A[i][j] = tmp[i][j];
        }
    }
}

void check(){
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            int x = i;
            int y = j;
            for(int k = 0 ; k < 4 ; k ++){
                int nx = x + dr[k][0];
                int ny = y + dr[k][1];
                if(nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
            }
        }
    }
}
P bfs(int x, int y){
    int red = 0;
    int me = 0;
    vector<P> reds;
    queue<P> q;
    q.push({x, y});
    visited[x][y] = true;
    while (!q.empty()) {
        P cur = q.front();
        if (A[cur.X][cur.Y] == 0) {
            red++;
            reds.push_back(cur);
        }
        me++;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = cur.X + dr[i][0];
            int ny = cur.Y + dr[i][1];
            if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
            if (A[nx][ny] < 0) continue;
            if (A[nx][ny] != 0 and A[nx][ny] != A[x][y]) continue;
            if (visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push({ nx, ny });
        }
    }

    // recover red visits
    for (auto red : reds) visited[red.X][red.Y] = false;

    return {red, me};
}

P getMax(){
    P maxV = {40000, 1};
    P pos = {-1, -1};
    for(int i = n - 1 ; i >= 0 ; i--){
        for(int j = 0 ; j < n ; j ++){
            if(A[i][j] <= 0) continue;
            if(!visited[i][j]){
                P res = bfs(i, j);
                if(res.second == 1) continue;
                if(res.second > maxV.second){
                    maxV = res;
                    pos = {i, j};
                    continue;
                }
                if(res.second == maxV.second and res.first < maxV.first){
                    maxV = res;
                    pos = {i, j};
                    continue;
                }
            }
        }
    }
    return pos;
}

int main(int argc, const char * argv[]) {
    cin >> n >> m;
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            cin >> A[i][j];
        }
    }
    
    while(true){
        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ; j < n ; j ++){
                visited[i][j] = false;
            }
        }
        P pos = getMax();
        if (pos.X == -1 and pos.Y == -1) break;
        destroy(pos.X, pos.Y);
        gravity();
        rotate();
        gravity();

    }
    cout << score;
    
    
    return 0;
}
