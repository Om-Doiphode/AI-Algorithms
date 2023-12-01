#include <bits/stdc++.h>
using namespace std;
class Environment {
    int N, M; 
    int dirtyCells;
    vector<vector<int>> floor; 

public:
    void generateEnvironment(int n, int m) {
        this->N = n;
        this->M = m;
        floor.resize(this->N, vector<int>(this->M, 0)); 

        generateDirtForEnvironment(); 
    }

    int getDirtyCells()
    {
        return this->dirtyCells;
    }
    void generateDirtForEnvironment() {
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++)
            {
                floor[i][j] = rand() % 2;
                if(floor[i][j]==1)
                    dirtyCells++;
            }
        }
    }

    int getWidth() {
        return this->M;
    }

    int getLength() {
        return this->N;
    }

    vector<vector<int>>& getFloor() {
        return this->floor;
    }

    void printFloor() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << floor[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class VacuumAgent {
    double count;
    vector<double> performance; 
    int N, M; 
    vector<vector<bool>> cleaned; // Grid to record the number of clean cells
    int statesExploredDFS;
    int statesExploredBFS;
    

public:
    void createVacuumAgent(int n, int m) {
        N = n;
        M = m;
        cleaned.resize(n, vector<bool>(m, false)); // Initialize with false (uncleaned)
    }

    // Clean using DFS
    void cleanFloorDFS(vector<vector<int>>& floor, int dirtyCells) {
        count = 0; // Number of items cleaned;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cleaned[i][j] = false;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!cleaned[i][j] && floor[i][j] == 1) {
                    cleanDFS(i, j, floor);
                }
            }
        }

        cout << "Performance of this instance with DFS count " << count << " is " << count / (dirtyCells) << endl;
        cout<<"States explored: "<<statesExploredDFS<<endl;
        performance.push_back(count / (N * M));
    }

    // Clean using BFS
    void cleanFloorBFS(vector<vector<int>>& floor,int dirtyCells) {
        count = 0; // Number of items cleaned;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cleaned[i][j] = false;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!cleaned[i][j] && floor[i][j] == 1) {
                    cleanBFS(i, j, floor);
                }
            }
        }
        cout << "Performance of this instance with BFS is " << count / (dirtyCells) << endl;
        cout<<"States explored: "<<statesExploredBFS<<endl;
        performance.push_back(count / (N * M));
    }

    // DFS Algorithm
    void cleanDFS(int i, int j, vector<vector<int>>& floor) {
        cleaned[i][j] = true;
        count++;
        statesExploredDFS++;

        int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int k = 0; k < 8; k++) {
            if (isSafe(i + x[k], j + y[k]) && floor[i + x[k]][j + y[k]] == 1) {
                cleanDFS(i + x[k], j + y[k], floor);
            }
        }
    }

    // BFS Algorithm
    void cleanBFS(int i, int j, vector<vector<int>>& floor) {
        queue<pair<int, int>> q;
        q.push({i, j});
        cleaned[i][j] = true;
        count++;

        int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();

            for (int k = 0; k < 8; k++) {
                int ni = current.first + x[k];
                int nj = current.second + y[k];

                if (isSafe(ni, nj) && floor[ni][nj] == 1 && !cleaned[ni][nj]) {
        statesExploredBFS++;
                    q.push({ni, nj});
                    cleaned[ni][nj] = true;
                    count++;
                }
            }
        }
    }

    bool isSafe(int i, int j) {
        if (0 <= j && j < M && 0 <= i && i < N && !cleaned[i][j])
            return true;
        return false;
    }

    double calculateAveragePerformance() {
        double sum = 0;
        for (int i = 0; i < performance.size(); i++) {
            cout<<"perf: "<<performance[i]<<endl;
            sum += performance[i];
        }
        return sum / performance.size();
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Environment environment;
    VacuumAgent agent;

    Environment environment2;
    VacuumAgent agent2;

    // for (int i = 0; i < 3; i++) 
    {
        environment.generateEnvironment(6, 6);
        environment.printFloor();

        agent.createVacuumAgent(environment.getLength(), environment.getWidth());

        // Clean using DFS
        agent.cleanFloorDFS(environment.getFloor(),environment.getDirtyCells());

        // Clean using BFS
        agent.cleanFloorBFS(environment.getFloor(),environment.getDirtyCells());
    }

    {
        environment2.generateEnvironment(6, 6);
        environment2.printFloor();

        agent2.createVacuumAgent(environment2.getLength(), environment2.getWidth());

        // Clean using DFS
        agent2.cleanFloorDFS(environment2.getFloor(),environment2.getDirtyCells());

        // Clean using BFS
        agent2.cleanFloorBFS(environment2.getFloor(),environment2.getDirtyCells());
    }

    // std::cout << "Average Performance of Agent: " << agent.calculateAveragePerformance() << std::endl;

    return 0;
}
