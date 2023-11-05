#include <bits/stdc++.h>
using namespace std;
vector<char>alphabets={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z'};
void printVector(vector<int>v)
{
    for(auto ele:v)
        cout<<ele<<" ";
    cout<<endl;
}
void print2DVector(vector<vector<char>>v)
{
    for(auto vec:v)
    {
        for(auto ele:vec)
        {
            cout<<ele<<" ";
        }
        cout<<endl;
    }
}
void printProblem(vector<tuple<char,char,char>>problem,int m)
{
    int i=0;
    for(auto tup:problem)
    {
        cout<<"("<<get<0>(tup)<<" v "<<get<1>(tup)<<" v "<<get<2>(tup)<<")";
        if((i++)<m-1)
            cout<<" ^ ";
    }
    cout<<endl;
}
void combinations(int ind,vector<char>&arr,vector<char>&ds,int k,int n,vector<tuple<char,char,char>>&ans)
{
    if(ind==n)
    {
        if(ds.size()==k)
        {
            tuple<char,char,char>temp(ds[0],ds[1],ds[2]);
            ans.push_back(temp);
        }
        return;
    }
    if(ds.size()==k)
    {
        tuple<char,char,char>temp(ds[0],ds[1],ds[2]);
        ans.push_back(temp);
        return;
    }
    ds.push_back(arr[ind]);
    combinations(ind+1,arr,ds,k,n,ans);
    ds.pop_back();
    combinations(ind+1,arr,ds,k,n,ans);
}
tuple<vector<char>,vector<vector<tuple<char, char, char>>>> makeProblem(int n, int m, int k)
{
    auto first=alphabets.begin();
    auto end=alphabets.begin()+n;
    vector<char>pos_var(first,end),neg_var;
    for(auto ele:pos_var)
    {
        neg_var.push_back(char(toupper(ele)));
    }
    vector<char>variables;
    variables.insert(variables.end(),pos_var.begin(),pos_var.end());
    variables.insert(variables.end(),neg_var.begin(),neg_var.end());
    vector<tuple<char,char,char>>allCombos;
    vector<char>ds;
    combinations(0,variables,ds,k,variables.size(),allCombos);
    int t_hold=101,i=0;
    vector<vector<tuple<char, char, char>>> problems;

    srand(static_cast<unsigned>(time(nullptr)));

    while (i < t_hold) {
        vector<tuple<char, char, char>> x;
        for (int j = 0; j < m; j++) {
            int randomIndex = rand() % allCombos.size();
            x.push_back(allCombos[randomIndex]);
        }
        bool isInProblems = false;
        for (const vector<tuple<char, char, char>>& problem : problems) {
            if (problem == x) {
                isInProblems = true;
                break;
            }
        }

        if (!isInProblems) {
            i++;
            problems.push_back(x);
        }
    }
    return tuple<vector<char>,vector<vector<tuple<char, char, char>>>> (variables,problems);
    
}

map<char,int> assignment(vector<char> variables,int n)
{
    vector<int>forPositive,forNegative,assign;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0,1);

    for(int i=0;i<n;i++)
    {
        int randVal=distribution(gen);
        forPositive.push_back(randVal);
    }

    for(int i=0;i<n;i++)
    {
        forNegative.push_back(abs(1-forPositive[i]));
    }

    for(int i=0;i<n;i++)
    {
        assign.push_back(forPositive[i]);
    }
    for(int i=0;i<n;i++)
    {
        assign.push_back(forNegative[i]);
    }

    map<char,int>var_assign;
    int j=0;
    for(auto ch: variables)
    {
        var_assign[ch]=assign[j++];
    }

    return var_assign;
}

int solve(vector<tuple<char, char, char>> problem, map<char,int>assign)
{
    int count=0;
    for(auto sub: problem)
    {
        if(assign[get<0>(sub)]==1 ||assign[get<1>(sub)]==1 || assign[get<2>(sub)]==1)
        {
            count++;
        }
    }

    return count;
}

tuple<map<char,int>,int,string> hillClimbing(vector<tuple<char,char,char>>problem, map<char,int>assign,int parentNum,int received,int step,int &hcStatesExplored )
{
    map<char,int> b_A=assign;
    vector<char>a_Keys;
    vector<int>a_Values;
    for(auto it:b_A)
    {
        a_Values.push_back(it.second);
        a_Keys.push_back(it.first);
    }

    int maxNum=parentNum;
    map<char,int>maxAssign=assign;
    map<char,int>editAssign=assign;


    for(int i=0;i<a_Values.size();i++)
    {
        step+=1;
        editAssign[a_Keys[i]]=abs(a_Values[i]-1);
        int c=solve(problem,editAssign);
        hcStatesExplored++; 

        if(maxNum<c)
        {
            received=step;
            maxNum=c;
            maxAssign=editAssign;
        }
    }

    if(maxNum==parentNum)
    {
        string s=to_string(received)+"/"+to_string(step-a_Values.size());

        return tuple<map<char,int>,int,string>(b_A,maxNum,s);
    }

    else
    {
        parentNum=maxNum;
        map<char,int> bestassign=maxAssign;
        return hillClimbing(problem,bestassign,parentNum,received,step,hcStatesExplored);
    }
}

pair<map<char,int>,string> beamSearch(vector<tuple<char,char,char>>problem, map<char,int>assign,int b, int stepSize,int &bsStatesExplored)
{
    vector<char>a_Keys;
    vector<int>a_Values;
    vector<int>steps,p_Scores;
    vector<map<char,int>>p_Assigns;

    for(auto it:assign)
    {
        a_Values.push_back(it.second);
        a_Keys.push_back(it.first);
    }

    map<char,int>editAssign=assign;
    int initial=solve(problem,assign);

    if(initial==problem.size())
    {
        string p=to_string(stepSize)+"/"+to_string(stepSize);
        return {assign,p};
    }
    while(stepSize<=b)
    {
        
        for(int i=0;i<a_Values.size();i++)
        {
            stepSize+=1;
            editAssign[a_Keys[i]]=abs(a_Values[i]-1);
            int c=solve(problem,editAssign);
            p_Assigns.push_back(editAssign);
            p_Scores.push_back(c);
            steps.push_back(stepSize);
            bsStatesExplored++;
        }

        for(int i=0;i<p_Scores.size();i++)
        {
            if(problem.size()==p_Scores[i])
            {
                vector<int>index;
                for(int j=0;j<p_Scores.size();j++)
                {
                    index.push_back(j);
                }

                string p=to_string(steps[index[0]])+"/"+to_string(steps[steps.size()-2]);

                return {p_Assigns[index[0]],p};
            }

            else
            {
                vector<int> selected(p_Scores.size());
                iota(selected.begin(), selected.end(), 0);

                sort(selected.begin(), selected.end(), [&p_Scores](int a, int b) {
                    return p_Scores[a] < p_Scores[b];
                });

                selected.erase(selected.begin(), selected.end() - b);

                vector<map<char,int>> s_Assigns;
                for (auto ele:selected)
                {
                    s_Assigns.push_back(p_Assigns[ele]);
                }
                assign=s_Assigns[0];
            }
        }
    }

    return {assign,to_string(stepSize)+"/"+to_string(stepSize)};
}
// Function to generate a random neighbor by flipping the values of two random variables
map<char, int> generateRandomNeighbor(const map<char, int>& currentSolution, const vector<char>& variables) {
    map<char, int> neighbor = currentSolution;
    random_device rd;
    mt19937 gen(rd());

    // Randomly select two different variables to flip
    uniform_int_distribution<int> distribution(0, variables.size() - 1);
    int randomIndex1, randomIndex2;
    do {
        randomIndex1 = distribution(gen);
        randomIndex2 = distribution(gen);
    } while (randomIndex1 == randomIndex2);

    char variable1 = variables[randomIndex1];
    char variable2 = variables[randomIndex2];

    // Flip the values of the selected variables
    neighbor[variable1] = 1 - currentSolution.at(variable1);
    neighbor[variable2] = 1 - currentSolution.at(variable2);

    return neighbor;
}

// Tabu Search function
pair<map<char, int>, int> tabuSearch(const vector<tuple<char, char, char>>& problem, const vector<char>& variables, int maxIterations, int tabuSize,map<char,int>assign) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);

    int bestSolutionValue = 0;
    // map<char, int> currentSolution = assignment(variables, variables.size());

    // Initialize the tabu list
    vector<map<char, int>> tabuList;

    for (int iter = 0; iter < maxIterations; iter++) {
        int bestNeighborValue = -1;
        map<char, int> bestNeighbor;

        // Generate tabuSize neighbors
        for (int i = 0; i < tabuSize; i++) {
            map<char, int> neighbor = generateRandomNeighbor(assign, variables);

            // Check if the neighbor is in the tabu list
            if (find(tabuList.begin(), tabuList.end(), neighbor) == tabuList.end()) {
                int neighborValue = solve(problem, neighbor);
                if (neighborValue > bestNeighborValue) {
                    bestNeighborValue = neighborValue;
                    bestNeighbor = neighbor;
                }
            }
        }

        // Add the best neighbor to the tabu list
        tabuList.push_back(bestNeighbor);

        // If the tabu list is too big, remove the oldest element
        if (tabuList.size() > tabuSize) {
            tabuList.erase(tabuList.begin());
        }

        // Update the current solution
        assign = bestNeighbor;

        // Update the best solution if a better solution is found
        if (bestNeighborValue > bestSolutionValue) {
            bestSolutionValue = bestNeighborValue;
        }
    }

    return make_pair(assign, bestSolutionValue);
}
// Neighborhood Function 1: Flip the value of a random variable
void neighborhoodFunction1(std::map<char, int>& solution) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, solution.size() - 1);
    auto it = solution.begin();
    std::advance(it, distribution(gen)); // Randomly select a variable
    it->second = 1 - it->second; // Flip the value of the selected variable
}

// Neighborhood Function 2: Swap values of two random variables
void neighborhoodFunction2(std::map<char, int>& solution) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, solution.size() - 1);
    
    auto it1 = solution.begin();
    std::advance(it1, distribution(gen)); // Randomly select the first variable
    auto it2 = solution.begin();
    std::advance(it2, distribution(gen)); // Randomly select the second variable
    
    std::swap(it1->second, it2->second); // Swap the values of the two selected variables
}

// Neighborhood Function 3: Change the value of a random variable
void neighborhoodFunction3(std::map<char, int>& solution) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, solution.size() - 1);
    auto it = solution.begin();
    std::advance(it, distribution(gen)); // Randomly select a variable
    it->second = 1 - it->second; // Change the value of the selected variable
}

// Variable Neighborhood Descent
map<char,int> variableNeighborhoodDescent(const std::vector<std::tuple<char, char, char>>& problem, std::map<char, int>& solution, int maxIterations) {
    int bestSolutionValue = solve(problem, solution);

    for (int iter = 0; iter < maxIterations; ++iter) {
        int currentSolutionValue = bestSolutionValue;

        // Try neighborhood function 1
        std::map<char, int> neighborSolution1 = solution;
        neighborhoodFunction1(neighborSolution1);
        int neighborValue1 = solve(problem, neighborSolution1);

        // Try neighborhood function 2
        std::map<char, int> neighborSolution2 = solution;
        neighborhoodFunction2(neighborSolution2);
        int neighborValue2 = solve(problem, neighborSolution2);

        // Try neighborhood function 3
        std::map<char, int> neighborSolution3 = solution;
        neighborhoodFunction3(neighborSolution3);
        int neighborValue3 = solve(problem, neighborSolution3);

        // Find the best neighbor
        int bestNeighborValue = std::max({neighborValue1, neighborValue2, neighborValue3});
        if (bestNeighborValue > currentSolutionValue) {
            if (bestNeighborValue > bestSolutionValue) {
                bestSolutionValue = bestNeighborValue;
                solution = (bestNeighborValue == neighborValue1) ? neighborSolution1 :
                           (bestNeighborValue == neighborValue2) ? neighborSolution2 : neighborSolution3;
            }
        }
    }

    return solution;
}

int main()
{
    int n=4,m=4,k=3;
    // cout<<"Enter the number of clauses in the formula: ";
    // cin>>m;

    // cout<<"Enter number of variables: ";
    // cin>>n;
        // Define the output file stream
    std::ofstream outputFile("output.txt");

    // Redirect stdout to the output file
    std::streambuf* originalStdout = std::cout.rdbuf();
    std::cout.rdbuf(outputFile.rdbuf());



    tuple<vector<char>,vector<vector<tuple<char, char, char>>>> result=makeProblem(n,m,k);

    vector<char> variables=get<0>(result);
    vector<vector<tuple<char, char, char>>>problems=get<1>(result);

    map<char,int> assign=assignment(variables,n);
    cout<<"Initial assignment: ";
    cout<<"{ ";
        for(auto it:assign)
        {
            cout<<it.first<<": "<<it.second<<", ";
        }
        cout<<"}"<<endl;


    vector<map<char,int>> h_Assigns;
    vector<map<char,int>> assigns;
    vector<int> h_n,initials;
    vector<string>hill_penetrations;
    int i=0;

    for(auto problem:problems)
    {
        i+=1;
        int initial=solve(problem,assign);
        int hcStatesExplored = 0;

        cout<<"Problem "<<i<<": ";
        printProblem(problem,m);

        clock_t hcStartTime = clock();
        tuple<map<char,int>,int,string> HCresults=hillClimbing(problem,assign,initial,1,1,hcStatesExplored);
        clock_t hcEndTime = clock();
        double hcExecutionTime = (double)(hcEndTime - hcStartTime) / CLOCKS_PER_SEC;

        auto b_A=get<0>(HCresults);
        auto score=get<1>(HCresults);
        auto hp=get<2>(HCresults);

        h_Assigns.push_back(b_A);
        assigns.push_back(assign);
        h_n.push_back(score);
        initials.push_back(initial);
        hill_penetrations.push_back(hp);

        int bsStatesExplored=0;
        clock_t bsStartTime = clock();
        auto BSresults=beamSearch(problem,assign,3,1,bsStatesExplored);
        clock_t bsEndTime = clock();
        double bsExecutionTime = (double)(bsEndTime - bsStartTime) / CLOCKS_PER_SEC;
        auto h3=get<0>(BSresults);
        auto b3s=get<1>(BSresults);

        int b4sStatesExplored=0;
        clock_t b4sStartTime = clock();
        auto B4Sresults=beamSearch(problem,assign,4,1,b4sStatesExplored);
        clock_t b4sEndTime = clock();
        double b4sExecutionTime = (double)(b4sEndTime - b4sStartTime) / CLOCKS_PER_SEC;
        auto h4=get<0>(B4Sresults);
        auto b4s=get<1>(B4Sresults);

        clock_t tsStartTime = clock();
        pair<map<char, int>, int> tabuSearchResult = tabuSearch(problems[i], variables, 100, 10,assign); // Adjust the number of iterations and tabu list size as needed.
        clock_t tsEndTime = clock();
        double tsExecutionTime = (double)(tsEndTime - tsStartTime) / CLOCKS_PER_SEC;

        clock_t vndStartTime = clock();
        auto bestAssignment = variableNeighborhoodDescent(problem, assign, 100);
        clock_t vndEndTime = clock();
        double vndExecutionTime = (double)(vndEndTime - vndStartTime) / CLOCKS_PER_SEC;
        

        cout<<"Hill Climbing: ";
        cout<<"{ ";
        for(auto it:b_A)
        {
            cout<<it.first<<": "<<it.second<<", ";
        }
        cout<<"}"<<endl;

        cout<<"Beam Search with beam width of 3: ";
        cout<<"{ ";
        for(auto it:h3)
        {
            cout<<it.first<<": "<<it.second<<", ";
        }
        cout<<"}"<<endl;

        cout<<"Beam Search with beam width of 4: ";
        cout<<"{ ";
        for(auto it:h4)
        {
            cout<<it.first<<": "<<it.second<<", ";
        }
        cout<<"}"<<endl;
    
        cout << "Tabu Search: ";
        cout << "{ ";
        for (auto it : tabuSearchResult.first) {
            cout << it.first << ": " << it.second << ", ";
        }
        cout << "}" << endl;

        cout<<"VND: ";
        cout<<"{ ";
        for (const auto& pair : bestAssignment) {
            cout << pair.first << ": " << pair.second << ", ";
        }
        cout<<"}"<<endl;


        cout << "Hill Climbing Execution Time: " << hcExecutionTime << " seconds" << endl;
        cout << "Beam Search Execution Time: " << bsExecutionTime << " seconds" << endl;
        cout << "Tabu Search Execution Time: " << tsExecutionTime << " seconds" << endl;
        cout << "VND Execution Time: " << vndExecutionTime << " seconds" << endl;
        cout << endl;

    }
        outputFile.close();
        cout.rdbuf(originalStdout);
        return 0;
}