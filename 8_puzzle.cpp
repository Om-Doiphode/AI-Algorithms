#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    vector<vector<int>> state;
    Node* parent;
    string action;

    Node(vector<vector<int>> s, Node* p, string a) : state(s), parent(p), action(a) {}
};

class Puzzle {
public:
    vector<vector<int>> start;
    vector<vector<int>> goal;
    pair<int, int> startIndex;
    pair<int, int> goalIndex;
    pair<vector<string>, vector<vector<vector<int>>>> solution;
    int numExplored;
    int searchDepth;
    int maxSearchDepth;
    double runningTime;

    Puzzle(vector<vector<int>> s, pair<int, int> si, vector<vector<int>> g, pair<int, int> gi)
        : start(s), startIndex(si), goal(g), goalIndex(gi), solution({{}, {}}), numExplored(0), searchDepth(0), maxSearchDepth(0), runningTime(0) {}

    vector<pair<string, vector<vector<int>>>> neighbors(vector<vector<int>> state) {
        vector<pair<string, vector<vector<int>>>> results;
        int row = startIndex.first;
        int col = startIndex.second;
        cout<<"row: "<<row<<" col: "<<col<<endl;
        vector<vector<int>> mat = state;

        if (row > 0) {
            vector<vector<int>> mat1 = mat;
            mat1[row][col] = mat1[row - 1][col];
            mat1[row - 1][col] = 0;
            results.push_back({"up", mat1});
        }

        if (col > 0) {
            vector<vector<int>> mat1 = mat;
            mat1[row][col] = mat1[row][col - 1];
            mat1[row][col - 1] = 0;
            results.push_back({"left", mat1});
        }

        if (row < 2) {
            vector<vector<int>> mat1 = mat;
            mat1[row][col] = mat1[row + 1][col];
            mat1[row + 1][col] = 0;
            results.push_back({"down", mat1});
        }

        if (col < 2) {
            vector<vector<int>> mat1 = mat;
            mat1[row][col] = mat1[row][col + 1];
            mat1[row][col + 1] = 0;
            results.push_back({"right", mat1});
        }

        return results;
    }

    void print() {
        cout << "Start State:" << endl;
        for (auto row : start) {
            for (auto num : row) {
                cout << num << " ";
            }
            cout << endl;
        }
        cout << "Goal State:" << endl;
        for (auto row : goal) {
            for (auto num : row) {
                cout << num << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "States Explored: " << numExplored << endl;
        cout << "Solution:" << endl;
        for (int i = 0; i < solution.first.size(); i++) {
            cout << "action: " << solution.first[i] << endl;
            for (auto row : solution.second[i]) {
                for (auto num : row) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }
        cout << "Goal Reached!!" << endl;
    }

    void solve() {
        clock_t startTime = clock();
        set<vector<vector<int>>> visited;
        Node* startNode = new Node(start, nullptr, "");
        queue<Node*> frontier;
        frontier.push(startNode);

        while (!frontier.empty()) {
            Node* node = frontier.front();
            frontier.pop();
            numExplored++;

            if (node->state == goal) {
                vector<string> actions;
                vector<vector<vector<int>>> cells;
                while (node->parent != nullptr) {
                    actions.push_back(node->action);
                    cells.push_back(node->state);
                    node = node->parent;
                }
                reverse(actions.begin(), actions.end());
                reverse(cells.begin(), cells.end());
                solution = {actions, cells};
                break;
            }

            visited.insert(node->state);

            for (auto neighbor : neighbors(node->state)) {
                vector<vector<int>> nextState = neighbor.second;
                if (visited.find(nextState) == visited.end()) {
                    Node* child = new Node(nextState, node, neighbor.first);
                    frontier.push(child);
                    maxSearchDepth = max(maxSearchDepth, (int)frontier.size());
                }
            }
        }

        clock_t endTime = clock();
        runningTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    }
};

int main() {
    vector<vector<int>> start = {{1,2,3}, {0, 4, 6}, {7, 5, 8}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    pair<int, int> startIndex = {1, 0};
    pair<int, int> goalIndex = {2, 2};

    Puzzle p(start, startIndex, goal, goalIndex);
    p.solve();
    p.print();

    cout << "Start State:" << endl;
    for (auto row : start) {
        for (auto num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << "Goal State:" << endl;
    for (auto row : goal) {
        for (auto num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << "Path to Goal:";
    for (string action : p.solution.first) {
        cout << " " << action;
    }
    cout << endl;
    cout << "Cost of Path: " << p.solution.first.size() << endl;
    cout << "Running Time: " << p.runningTime << " seconds" << endl;
    cout << "Search Depth: " << p.searchDepth << endl;
    cout << "Max Search Depth: " << p.maxSearchDepth << endl;

    return 0;
}
