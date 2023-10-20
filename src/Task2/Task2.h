#pragma once
#include <iostream>
#include <queue>
#include <stack>

#include "../Graph.h"

using namespace std;

class Task2 {
   private:
    Graph* gr_forTask;
    string res_str;
    bool connectivity = true;
    bool strong = false;
    bool weak = false;
    int connectedComp_amount = 0;
    int strongConnectedComp_amount = 0;
    vector<vector<int>> connectedComp;
    vector<vector<int>> strongConnectedComp;

    vector<bool> BFS(int V, vector<vector<int>> matrix);
    void tactDFS(int V, vector<int>& tacts, vector<bool>& used_V);
    void DFS(int V, vector<bool>& used_V, vector<vector<int>>& invertM);
    void check_Connectivity();
    void check_strongConnectivity();
    void connectedComponents();
    void strongConnectedComponents();
    vector<vector<int>> create_corrMatrix();
    vector<vector<int>> create_invertMatrix();
    void setRes();

   public:
    string getRes();
    Task2(Graph& G);
};