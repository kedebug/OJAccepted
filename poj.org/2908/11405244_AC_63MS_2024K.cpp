
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct ST {
    int state, cost;
    ST(int _state, int _cost) : state(_state), cost(_cost) {}
    bool operator < (const ST& other) const { return cost > other.cost; }
};

struct OP {
    int op_and, op_or, op_xor;
    int cost;
} op[40];

int L, N, M;
bool vis[1<<20];

int bfs(int s, int t) {
    priority_queue<ST> Q;
    Q.push(ST(s, 0));

    memset(vis, false, sizeof(bool)*(1<<L));
    vis[s] = true;

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        if (u.state == t) 
            return u.cost;

        for (int i = 0; i < N; i++) {
            int v = u.state;
            v &= op[i].op_and;
            v |= op[i].op_or;
            v ^= op[i].op_xor;
            if (!vis[v] || v == t) {
                vis[v] = true;
                Q.push(ST(v, u.cost + op[i].cost));
            }
        }
    }
    return -1;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d%d%d", &L, &N, &M);
        for (int i = 0; i < N; i++) {
            char s[30];
            scanf("%s%d", s, &op[i].cost);
            op[i].op_and = op[i].op_or = op[i].op_xor = 0;
            for (int j = 0; s[j]; j++) {
                op[i].op_and <<= 1;
                op[i].op_or <<= 1;
                op[i].op_xor <<= 1;
                if (s[j] == 'N') 
                    op[i].op_or |= 0;
                else if (s[j] == 'C') 
                    op[i].op_and |= 1;
                else if (s[j] == 'F')
                    op[i].op_xor |= 1;
                else if (s[j] == 'S')
                    op[i].op_or |= 1;
            }
            op[i].op_and = ~op[i].op_and;
        }
        for (int i = 0; i < M; i++) {
            char src[30], dst[30];
            int u = 0, v = 0;
            scanf("%s%s", src, dst);
            for (int j = 0; src[j]; j++)
                u <<= 1, u |= (src[j] - '0');
            for (int j = 0; dst[j]; j++)
                v <<= 1, v |= (dst[j] - '0');
            int ans = bfs(u, v);
            if (ans != -1) 
                printf("%d", ans);
            else 
                printf("NP");
            printf("%c", i == M-1 ? '\n' : ' ');
        }
    }
    return 0;
}