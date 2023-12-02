#include <bits/stdc++.h>
using namespace std;
bool matricesAreEqual(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
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

        cout<<"States explored: "<<num_explored<<endl;

        vector<string>action=solution.first;
        vector<pair<vector<vector<int>>,pair<int,int>>>cell=solution.second;
        cout<<"Goal Reached!!"<<endl;
    }
    void dfs_solve() {
    Node* newNode = new Node(start, nullptr, "");
    stack<Node*> s;
    s.push(newNode);

    set<pair<vector<vector<int>>, pair<int, int>>> visited;

    while (!s.empty()) {
        auto node = s.top();
        s.pop();
        num_explored++;

        if (matricesAreEqual(node->state.first, goal.first)) {
            vector<string> actions;
            vector<pair<vector<vector<int>>, pair<int, int>>> cells;

            while (node->parent != nullptr) {
                actions.push_back(node->action);
                cells.push_back(node->state);
                node = node->parent;
            }

            reverse(actions.begin(), actions.end());
            reverse(cells.begin(), cells.end());
            solution = {actions, cells};
            return;
        }
        visited.insert(node->state);

        auto temp = moveGen(node->state);

        bool hasUnvisitedChild = false;

        for (int i = 0; i < temp.size(); i++) {
            string action = temp[i].first;
            pair<vector<vector<int>>, pair<int, int>> state = temp[i].second;

            if (visited.find(state) == visited.end()) {
                hasUnvisitedChild = true;
                Node* child = new Node(state, node, action);
                s.push(child);
            }
        }

        if (!hasUnvisitedChild) {
            delete node;
        }
    }

    throw runtime_error("No solution");
}

};

int main()
{
    vector<vector<int>> s={{1,2,3},{8,0,4},{7,6,5}};
    vector<vector<int>>g={{2,8,1},{0,4,3},{7,6,5}};


    pair<int,int> startIndex={1,1};
    pair<int,int> goalIndex={1,0};

    pair<vector<vector<int>>,pair<int,int>> start={s,startIndex};
    pair<vector<vector<int>>,pair<int,int>> goal={g,goalIndex};

    Puzzle *p= new Puzzle(start,goal);
    p->dfs_solve();
    p->print();
}