#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
class waterJugProblem
{
    int jugAAmount;
    int jugBAmount;
    int target;
    int pathExplored;
    public:

    waterJugProblem(int x,int y, int z):jugAAmount(x),jugBAmount(y),target(z),pathExplored(0){}
    void printpath(map<pii, pii> mp, pii u)
    {
        if (u.first == 0 && u.second == 0) {
            cout << 0 << " " << 0 << endl;
            return;
        }
        printpath(mp, mp[u]);
        cout << u.first << " " << u.second << endl;
    }

    void moveGen(int jugA, int jugB, map<pii,int>&vis,map<pii,pii>&mp,queue<pii>&q)
    {
        // Empty Jug B
        if(vis[{jugA,0}]!=1)
        {
            q.push({jugA,0});
            mp[{jugA,0}]={jugA,jugB};
        }

        // Empty Jug A
        if(vis[{0,jugB}]!=1)
        {
            q.push({0,jugB});
            mp[{0,jugB}]={jugA,jugB};
        }

        // Completely fill the Jug B
        if (vis[{ jugA, jugBAmount }] != 1) {
            q.push({ jugA, jugBAmount });
            mp[{ jugA, jugBAmount }] = {jugA,jugB};
        }

        // Completely fill the Jug A
        if (vis[{ jugAAmount, jugB }] != 1) {
            q.push({ jugAAmount, jugB });
            mp[{ jugAAmount, jugB }] = {jugA,jugB};
        }

        // Transfer Jug A --> Jug B
        int d = jugBAmount - jugB;
        if (jugA >= d) {
            int c = jugA - d;
            if (vis[{ c, jugBAmount }] != 1) {
                q.push({ c, jugBAmount });
                mp[{ c, jugBAmount }] = {jugA,jugB};
            }
        }
        // Transfer Jug B --> Jug A
        else {
            int c = jugA + jugB;
            if (vis[{ 0, c }] != 1) {
                q.push({ 0, c });
                mp[{ 0, c }] = {jugA,jugB};
            }
        }
    }

    bool goalTest(pii u)
    {
        return u.first==target || u.second==target;
    }
    void bfs_solve()
    {
        map<pii,int>vis;
        bool isSolvable = false;
        map<pii,pii>mp;

        queue<pii>q;

        q.push({0,0});

        while (!q.empty())
        {
            auto u=q.front();
            q.pop();

            if(vis[u]==1)
                continue;

            if(u.first>jugAAmount || u.second>jugBAmount || u.first<0 || u.second<0)
                continue;

            vis[u] = 1;

            if(goalTest(u))
            {
                isSolvable=true;
                printpath(mp,u);
                if(u.first==target)
                {
                    if(u.second!=0)
                    {
                        cout<<u.first<<" "<<0<<endl;
                    }
                }
                else
                {
                    if(u.first!=0)
                    {
                        cout<<0<<" "<<u.second<<endl;
                    }
                }

                return;
            }

            pathExplored++;
            moveGen(u.first,u.second,vis,mp,q);
        }
        if(!isSolvable)
            cout<<"No solution"<<endl;  
    }

    int get_no_path_explored()
    {
        return pathExplored;
    }
};

int main()
{
    waterJugProblem *p=new waterJugProblem(4,3,2);
    p->bfs_solve();
    cout<<"No. of paths explored: "<<p->get_no_path_explored()<<endl;
    return 0;
}