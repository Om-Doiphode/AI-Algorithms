#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

std::vector<std::string> ascii_lowercase = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

std::vector<std::vector<std::string>> combinations(const std::vector<std::string>& variables, int k) {
    std::vector<std::vector<std::string>> result;
    std::vector<bool> bitmask(k, true);
    bitmask.resize(variables.size(), false);
    do {
        std::vector<std::string> combination;
        for (int i = 0; i < variables.size(); i++) {
            if (bitmask[i]) {
                combination.push_back(variables[i]);
            }
        }
        result.push_back(combination);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    return result;
}

std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> makeProblem(int m, int k, int n) {
    std::vector<std::string> pos_var(ascii_lowercase.begin(), ascii_lowercase.begin() + n);
    std::vector<std::string> neg_var;
    for (const auto& c : pos_var) {
        neg_var.push_back(std::string(1, char(toupper(c))));
    }
    std::vector<std::string> variables;
    variables.insert(variables.end(), pos_var.begin(), pos_var.end());
    variables.insert(variables.end(), neg_var.begin(), neg_var.end());
    int t_hold = 10;
    std::vector<std::vector<std::string>> problems;
    std::vector<std::vector<std::string>> allCombos = combinations(variables, k);
    int i = 0;
    while (i < t_hold) {
        std::vector<std::vector<std::string>> x;
        std::sample(allCombos.begin(), allCombos.end(), std::back_inserter(x), m, std::mt19937{std::random_device{}()});
        if (std::find(problems.begin(), problems.end(), x) == problems.end()) {
            i++;
            problems.push_back(x);
        }
    }
    return std::make_pair(variables, problems);
}

int solve(const std::vector<std::vector<std::string>>& problem, const std::map<std::string, int>& assign) {
    int count = 0;
    for (const auto& sub : problem) {
        std::vector<int> z;
        for (const auto& val : sub) {
            z.push_back(assign.at(val));
        }
        count += std::any_of(z.begin(), z.end(), [](int val){ return val != 0; });
    }
    return count;
}

std::map<std::string, int> variableNeighbor(const std::vector<std::vector<std::string>>& problem, const std::map<std::string, int>& assign, int b, int step) {
    std::map<std::string, int> b_A = assign;
    std::vector<int> assignValues;
    std::vector<std::string> assignKeys;
    std::vector<int> steps;
    std::vector<std::map<std::string, int>> poss_Assigns;
    std::vector<int> poss_Scores;
    std::map<std::string, int> editAssign = assign;
    int initial = solve(problem, assign);
    if (initial == problem.size()) {
        std::string p = std::to_string(step) + "/" + std::to_string(step);
        return std::make_pair(assign, p, b);
    }
    for (const auto& assignPair : assign) {
        assignValues.push_back(assignPair.second);
        assignKeys.push_back(assignPair.first);
    }
    for (int i = 0; i < assignValues.size(); i++) {
        step++;
        editAssign[assignKeys[i]] = abs(assignValues[i] - 1);
        int c = solve(problem, editAssign);
        poss_Assigns.push_back(editAssign);
    }
}