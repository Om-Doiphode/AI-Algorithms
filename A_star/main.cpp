#include <bits/stdc++.h>
using namespace std;
class Node
{
    public:
    int id;
    int g;
    int h;
    int f;
    Node *previousNode;
    Node(int nodeId, int hValue)
    {
        id=nodeId;
        g=INT_MAX;
        h=hValue;
        f=INT_MAX;
        previousNode=NULL;
    }   
};
int calcHeuristic(pair<int,int>a,pair<int,int>b)
{
    int x_diff=pow((a.first-b.first),2);
    int y_diff=pow((a.second-b.second),2);

    return x_diff + y_diff;
}

vector<Node*>initializeNodes(const vector<pair<int,int>>adj[],int V,map<int,pair<int,int>>coord,int dest)
{
    vector<Node*>nodes;
    for(int i=0;i<V;i++)
    {
        nodes.push_back(new Node(i,calcHeuristic(coord[i],coord[dest])));
    }

    return nodes;
}
vector<Node*>backtrackPath(Node *targetNode)
{
    if(targetNode->previousNode==NULL)
    {
        return {};
    }
    Node *currentNode=targetNode;
    vector<Node*>path;

    while(currentNode)
    {
        path.push_back(currentNode);
        currentNode=currentNode->previousNode;
    }

    reverse(path.begin(),path.end());

    return path;
}
struct CompareNodes {
    bool operator()(const Node* a, const Node* b) {
        return a->f > b->f;
    }
};

vector<Node*> AstarAlgorithm(vector<pair<int,int>>adj[],int start, int target,int V,map<int,pair<int,int>>coord,map<int,char>hashAlpha)
{
    vector<Node*>nodes=initializeNodes(adj,V,coord,target);
    Node* startNode=nodes[start];
    Node* targetNode=nodes[target];

    // set distance to start node to itself as 0
    startNode->g=0;
    startNode->f=startNode->g+startNode->h;

    priority_queue <Node*, vector<Node*>, CompareNodes> openList;
    unordered_map<Node*,int>hash;
    openList.push(startNode);
    hash[startNode]=1;

    while(!openList.empty())
    {
        // remove the node with the lowest f-value
        Node *currentNode=openList.top();
        openList.pop();
        hash[currentNode]=0;

        if(currentNode==targetNode)
            break;
        
        // populate all current nodes neighbours
        vector<pair<int,int>> neighbors = adj[currentNode->id];
        for(auto neighbor : neighbors)
        {
            int idx=neighbor.first;
            int dist=neighbor.second;
            Node *neighborNode=nodes[idx];

            // Check if a better path is found
            int new_neighbour_g=currentNode->g + dist;
            if(new_neighbour_g>=neighborNode->g)
                continue;

            // Update neighbour's g,h,f and previousNode
            neighborNode->previousNode=currentNode;
            neighborNode->g=new_neighbour_g;
            neighborNode->f=neighborNode->g + neighborNode->h;

            // Check if the neighbour is in the openlist
            if(hash.find(neighborNode)==hash.end())
            {
                openList.push(neighborNode);
                hash[neighborNode]=1;
            }
            else
            {
                // Update the openList
                priority_queue <Node*, vector<Node*>, CompareNodes> tempQueue;
                while(!openList.empty())
                {
                    Node *tempNode=openList.top();
                    openList.pop();
                    if(tempNode==neighborNode)
                    {
                        tempNode->g=neighborNode->g;
                        tempNode->f=neighborNode->f;
                        tempNode->previousNode=neighborNode->previousNode;
                    }
                    tempQueue.push(tempNode);
                }
                openList.swap(tempQueue);
            }
            vector<Node*> currentPath = backtrackPath(neighborNode);
            int size = currentPath.size();
            for(auto node : currentPath)
            {
                size--;
                if(size!=0)
                    cout << hashAlpha[node->id] << " --> ";
                else
                    cout << hashAlpha[node->id];
            }
            cout << endl;
        }
    }

    return backtrackPath(targetNode);
}
int main()
{
    int V=20;
    vector<pair<int,int>>adj[V];
    map<int,char>hash;
    for(int i=0;i<25;i++)
    {
        hash[i]=char('A'+i);
    }

    // A
    // (node, g)
    adj[0].push_back({1,11});
    adj[0].push_back({3,32});
    adj[0].push_back({7,36});

    // B
    adj[1].push_back({0,11});
    adj[1].push_back({2,24});
    adj[1].push_back({10,42});

    // C
    adj[2].push_back({1,24});
    adj[2].push_back({4,40});

    // D
    adj[3].push_back({0,32});
    adj[3].push_back({5,24});
    adj[3].push_back({8,26});
    adj[3].push_back({18,25});

    // E
    adj[4].push_back({2,24});
    adj[4].push_back({10,32});

    // F
    adj[5].push_back({3,24});
    adj[5].push_back({11,27});

    // G (6)
    adj[6].push_back({13,42});
    adj[6].push_back({19,32});

    // H
    adj[7].push_back({0,36});
    adj[7].push_back({10,28});
    adj[7].push_back({9,22});
    adj[7].push_back({13,44});

    // I
    adj[8].push_back({3,26});
    adj[8].push_back({11,21});
    adj[8].push_back({12,32});

    // J
    adj[9].push_back({7,22});
    adj[9].push_back({12,20});

    // K
    adj[10].push_back({1,42});
    adj[10].push_back({4,32});
    adj[10].push_back({7,28});
    adj[10].push_back({13,27});
    adj[10].push_back({16,62});

    // L
    adj[11].push_back({5,27});
    adj[11].push_back({8,21});
    adj[11].push_back({14,26});

    // M
    adj[12].push_back({8,32});
    adj[12].push_back({9,20});
    adj[12].push_back({15,23});

    // N
    adj[13].push_back({6,42});
    adj[13].push_back({7,44});
    adj[13].push_back({10,27});
    adj[13].push_back({16,32});

    // O
    adj[14].push_back({11,26});
    adj[14].push_back({17,27});

    // P
    adj[15].push_back({12,23});

    // Q
    adj[16].push_back({10,62});
    adj[16].push_back({13,32});

    // R
    adj[17].push_back({14,27});
    adj[17].push_back({19,52});

    // S (18)
    adj[18].push_back({3,25});

    // T
    adj[19].push_back({6,32});
    adj[19].push_back({17,52});

    map<int,pair<int,int>>coord;
    coord={{0,{3,6}},
        {1,{4,6}},
        {2,{6,6}},
        {3,{1,5}},
        {4,{8,5}},
        {5,{0,4}},
        {6,{8,0}},
        {7,{4,4}},
        {8,{1,3}},
        {9,{3,3}},
        {10,{6,4}},
        {11,{0,2}},
        {12,{3,2}},
        {13,{6,2}},
        {14,{1,1}},
        {15,{4,1}},
        {16,{8,1}},
        {17,{2,0}},
        {18,{0,6}},
        {19,{6,0}}};

    vector<Node*>path=AstarAlgorithm(adj,18,6,V,coord,hash);
    int size=path.size();
    cout<<"Final Path: "<<endl;
    for(auto node:path)
    {
        size--;
        if(size!=0)
        cout<<hash[node->id]<<" --> ";
        else
        cout<<hash[node->id];

    }
    cout<<endl;
    for (Node* node : path) {
        delete node;
    }
}