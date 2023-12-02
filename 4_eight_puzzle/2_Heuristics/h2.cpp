#include <bits/stdc++.h>
using namespace std;
bool goalTest(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        return false;
    }
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[i].size(); ++j) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }
    return true;
}
int calcHeuristic(vector<vector<int>>& matrix1, vector<vector<int>>&matrix2)
{
    int cnt=0;
    map<int,pair<int,int>>hash;

    for(int i=0;i<matrix1.size();i++)
    {
        for(int j=0;j<matrix1[i].size();j++)
        {
            hash[matrix1[i][j]]={i,j};
        }
    }

    for(int i=0;i<matrix1.size();i++)
    {
        for(int j=0;j<matrix1[i].size();j++)
        {
            int val=matrix2[i][j];

            if(val==0)
                continue;
            int x1=i,y1=j;

            int x2=hash[val].first,y2=hash[val].second;

            cnt+=abs(x1-x2)+abs(y1-y2);
        }
    }

    return cnt;
}
class Node
{
    public:
    pair<vector<vector<int>>,pair<int,int>> state;
    Node* parent;
    string action;

    Node(pair<vector<vector<int>>,pair<int,int>> vec,Node *temp, string s)
    :state(vec),parent(temp),action(s){}
};

class Puzzle
{
    public:
    pair<vector<vector<int>>,pair<int,int>> start;
    pair<vector<vector<int>>,pair<int,int>> goal;
    pair<vector<string>,vector<pair<vector<vector<int>>,pair<int,int>>>>solution;
    vector<pair<vector<vector<int>>,pair<int,int>>> explored;
    int num_explored=0;

    Puzzle(pair<vector<vector<int>>,pair<int,int>> start, pair<vector<vector<int>>,pair<int,int>> goal)
    :start(start),goal(goal){}

    bool contains_state(priority_queue<pair<int,Node*>, vector<pair<int,Node*>>, greater<pair<int,Node*>>> q, pair<vector<vector<int>>, pair<int, int>> state) 
    {
        while (!q.empty()) {
            auto currentNode = q.top();
            q.pop();
            if ( goalTest(currentNode.second->state.first,state.first)) 
            {
                return true;
            }
        }
        return false;
    }

    bool does_not_contain_state(pair<vector<vector<int>>, pair<int, int>> state)
    {
        for(int i=0;i<explored.size();i++)
        {
            vector<vector<int>> st=explored[i].first;
            if(goalTest(st,state.first))
                return false;
        }
        return true;
    }

    vector<pair<string,pair<vector<vector<int>>,pair<int,int>>>> moveGen(pair<vector<vector<int>>,pair<int,int>> state)
    {
        vector<pair<string,pair<vector<vector<int>>,pair<int,int>>>>results;
        vector<vector<int>>mat= state.first;
        int row=state.second.first;
        int col=state.second.second;

        if(row>0)
        {
            vector<vector<int>>mat1=mat;
            mat1[row][col]=mat1[row-1][col];
            mat1[row-1][col]=0;
            results.push_back({"up",{mat1,{row-1,col}}});
        }

        if(col>0)
        {
            vector<vector<int>>mat1 = mat;
			mat1[row][col] = mat1[row][col - 1];
			mat1[row][col - 1] = 0;
            results.push_back({"left",{mat1,{row,col-1}}});
        }

        if(row<2)
        {
            vector<vector<int>>mat1 = mat;
			mat1[row][col] = mat1[row + 1][col];
			mat1[row + 1][col] = 0;
            results.push_back({"down",{mat1,{row+1,col}}});          
        }

        if(col<2)
        {
            vector<vector<int>>mat1 = mat;
			mat1[row][col] = mat1[row][col + 1];
			mat1[row][col + 1] = 0;
            results.push_back({"right",{mat1,{row,col+1}}});                    
        }


        return results;
    }

    void print()
    {
        cout<<"Start State: "<<endl;
        for(auto vec:start.first)
        {
            for(auto ele:vec)
                cout<<ele<<" ";
            cout<<endl;
        }

        cout<<"Goal State: "<<endl;
        for(auto vec:goal.first)
        {
            for(auto ele:vec)
                cout<<ele<<" ";
            cout<<endl;
        }


        vector<string>action=solution.first;
        vector<pair<vector<vector<int>>,pair<int,int>>>cell=solution.second;

        for(int i=0;i<cell.size();i++)
        {
            cout<<"action: "<<action[i]<<endl;
            for(auto vec:cell[i].first)
            {
                for(auto ele: vec)
                {
                    cout<<ele<<" ";
                }
                cout<<endl;
            }
        }
        cout<<"Goal Reached!!"<<endl;
        cout<<"States explored: "<<num_explored<<endl;
    }
    void solve()
    {
        Node* newNode = new Node(start, NULL, "");
        priority_queue<pair<int,Node*>, vector<pair<int,Node*>>, greater<pair<int,Node*>>> q;
        q.push({0,newNode});

        while(true)
        {
            if(q.empty())
                throw runtime_error("No solution");

            auto node=q.top();
            q.pop();
            num_explored++;
            if(goalTest(node.second->state.first,goal.first))
            {
                vector<string>actions;
                vector<pair<vector<vector<int>>,pair<int,int>>>cells;

                while(node.second->parent!=NULL)
                {
                    actions.push_back(node.second->action);
                    cells.push_back(node.second->state);
                    node.second=node.second->parent;
                }

                reverse(actions.begin(),actions.end());
                reverse(cells.begin(),cells.end());
                solution={actions,cells};
                return;
            }

            explored.push_back(node.second->state);
            auto temp=moveGen(node.second->state);

            for(int i=0;i<temp.size();i++)
            {
                string action=temp[i].first;
                pair<vector<vector<int>>,pair<int,int>> state=temp[i].second;

                if(!contains_state(q,state) && does_not_contain_state(state))
                {
                    Node *child=new Node(state,node.second,action);
                    int hVal=calcHeuristic(state.first,goal.first);
                    q.push({hVal,child});
                }
            }

        }
    }
};

int main()
{
    // vector<vector<int>> s={{1,2,3},{0,4,6},{7,5,8}};
    vector<vector<int>> s={{1,2,3},{8,0,4},{7,6,5}};
    vector<vector<int>>g={{2,8,1},{0,4,3},{7,6,5}};

    pair<int,int> startIndex={1,1};
    pair<int,int> goalIndex={1,0};

    pair<vector<vector<int>>,pair<int,int>> start={s,startIndex};
    pair<vector<vector<int>>,pair<int,int>> goal={g,goalIndex};

    Puzzle *p= new Puzzle(start,goal);
    auto start_time = chrono::high_resolution_clock::now();
    p->solve();
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<float> elapsed_time = end_time - start_time;

    p->print();
    cout << "Elapsed Time: " << elapsed_time.count() << " seconds" << endl;

    return 0;
}