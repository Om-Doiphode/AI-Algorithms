#include <bits/stdc++.h>
using namespace std;
vector<char>alphabets={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z'};
void printVector(vector<char>v)
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
    int t_hold=10,i=0;
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
int main()
{
    int n,m,k=3;
    cout<<char(toupper('a'))<<endl;
    cout<<"Enter the number of clauses in the formula: ";
    cin>>m;

    cout<<"Enter number of variables: ";
    cin>>n;


    tuple<vector<char>,vector<vector<tuple<char, char, char>>>> result=makeProblem(n,m,k);

    vector<char> variables=get<0>(result);
    vector<vector<tuple<char, char, char>>>problems=get<1>(result);
    printVector(variables);

    for (const vector<tuple<char, char, char>>& problem : problems) {
        for (const tuple<char, char, char>& tuple : problem) {
            cout << get<0>(tuple) << ' ' << get<1>(tuple) << ' ' << get<2>(tuple) << " | ";
        }
        cout << endl;
    }
}