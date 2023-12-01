#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

class waterJugProblem {
    int jugAAmount;
    int jugBAmount;
    int target;
    int pathExplored;
public:
    waterJugProblem(int x, int y, int z): jugAAmount(x), jugBAmount(y), target(z), pathExplored(0) {}
    
    void printpath(map<pii, pii> mp, pii u) {
        if (u.first == 0 && u.second == 0) {
            cout << 0 << " " << 0 << endl;
            return;
        }
        printpath(mp, mp[u]);
        cout << u.first << " " << u.second << endl;
    }

    void moveGen(int jugA, int jugB, map<pii, int>& vis, map<pii, pii>& mp) {
        // Empty Jug B
        if (vis[{jugA, 0}] != 1) {
            mp[{jugA, 0}] = {jugA, jugB};
            vis[{jugA, 0}] = 1;
			pathExplored++;
            moveGen(jugA, 0, vis, mp);
        }

        // Empty Jug A
        if (vis[{0, jugB}] != 1) {
            mp[{0, jugB}] = {jugA, jugB};
            vis[{0, jugB}] = 1;
			pathExplored++;
            moveGen(0, jugB, vis, mp);
        }

        // Completely fill the Jug B
        if (vis[{jugA, jugBAmount}] != 1) {
            mp[{jugA, jugBAmount}] = {jugA, jugB};
            vis[{jugA, jugBAmount}] = 1;
			pathExplored++;
            moveGen(jugA, jugBAmount, vis, mp);
        }

        // Completely fill the Jug A
        if (vis[{jugAAmount, jugB}] != 1) {
            mp[{jugAAmount, jugB}] = {jugA, jugB};
            vis[{jugAAmount, jugB}] = 1;
			pathExplored++;
            moveGen(jugAAmount, jugB, vis, mp);
        }

        // Transfer Jug A --> Jug B
        int d = jugBAmount - jugB;
        if (jugA >= d) {
            int c = jugA - d;
            if (vis[{c, jugBAmount}] != 1) {
                mp[{c, jugBAmount}] = {jugA, jugB};
                vis[{c, jugBAmount}] = 1;
				pathExplored++;
                moveGen(c, jugBAmount, vis, mp);
            }
        }
        // Transfer Jug B --> Jug A
        else {
            int c = jugA + jugB;
            if (vis[{0, c}] != 1) {
                mp[{0, c}] = {jugA, jugB};
                vis[{0, c}] = 1;
				pathExplored++;
                moveGen(0, c, vis, mp);
            }
        }
    }

    bool goalTest(pii u) {
        return u.first == target || u.second == target;
    }

    void dfs_solve() {
        map<pii, int> vis;
        bool isSolvable = false;
        map<pii, pii> mp;

        vis[{0, 0}] = 1; // Start from the initial state
        moveGen(0, 0, vis, mp);

        for (const auto& state : vis) {
            if (goalTest(state.first)) {
                isSolvable = true;
                printpath(mp, state.first);
                if (state.first.first == target && state.first.second != 0) {
                    cout << state.first.first << " " << 0 << endl;
                } else if (state.first.first != 0) {
                    cout << 0 << " " << state.first.second << endl;
                }
                break;
            }
        }

        if (!isSolvable) {
            cout << "No solution" << endl;
        }
    }
	int get_no_path_explored()
    {
        return pathExplored;
    }
};

int main() {
    waterJugProblem *p = new waterJugProblem(4, 3, 2);
    p->dfs_solve();
	cout<<"No. of paths explored: "<<p->get_no_path_explored()<<endl;
    return 0;
}
