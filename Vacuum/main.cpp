#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

class Environment {
    int N, M; // Grid of N*M
    std::vector<std::vector<int>> floor; // Image of the floor with cleaned/uncleaned tiles

public:
    void generateEnvironment(int n, int m) {
        this->N = n;
        this->M = m;
        floor.resize(this->N, std::vector<int>(this->M, 0)); // Initialize with zeros (clean)

        generateDirtForEnvironment(); // Randomly generate dirt
    }

    void generateDirtForEnvironment() {
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++)
                floor[i][j] = rand() % 2;
        }
    }

    int getWidth() {
        return this->M;
    }

    int getLength() {
        return this->N;
    }

    std::vector<std::vector<int>>& getFloor() {
        return this->floor;
    }

    void printFloor() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                std::cout << floor[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

class VacuumAgent {
    double count;
    std::vector<double> performance; // The no. of cells cleaned/total number of cells
    int N, M; // n*m grid
    std::vector<std::vector<bool>> cleaned; // Grid to record the number of clean cells

public:
    void createVacuumAgent(int n, int m) {
        N = n;
        M = m;
        cleaned.resize(n, std::vector<bool>(m, false)); // Initialize with false (uncleaned)
    }

    void cleanFloor(std::vector<std::vector<int>>& floor) {
        count = 0; // Number of items cleaned;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cleaned[i][j] = false;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!cleaned[i][j] && floor[i][j] == 1) {
                    clean(i, j, floor);
                }
            }
        }

        std::cout << "Performance of this instance with count " << count << " is " << count / (N * M) << std::endl;
        performance.push_back(count / (N * M));
    }

    void clean(int i, int j, std::vector<std::vector<int>>& floor) {
        cleaned[i][j] = true;
        count++;

        int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int k = 0; k < 8; k++) {
            if (isSafe(i + x[k], j + y[k]) && floor[i + x[k]][j + y[k]] == 1) {
                clean(i + x[k], j + y[k], floor);
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
            sum += performance[i];
        }
        return sum / performance.size();
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Environment environment;
    VacuumAgent agent;

    for (int i = 0; i < 3; i++) {
        environment.generateEnvironment(1 + (rand() % 10), 1 + (rand() % 10));
        environment.printFloor();

        agent.createVacuumAgent(environment.getLength(), environment.getWidth());
        agent.cleanFloor(environment.getFloor());
    }

    std::cout << "Performance of Agent: " << agent.calculateAveragePerformance() << std::endl;

    return 0;
}
