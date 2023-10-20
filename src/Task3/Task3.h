#pragma once
#include <set>

#include "../Graph.h"

using namespace std;

class Task3 {
   private:
    Graph* gr_forTask;
    string res_str;
    vector<tuple<int, int>> briges;
    set<int> cut_vertexes;

    void calculateTask();
    void DFS(int V, int P, vector<bool>& used_v, vector<int>& tin, vector<int>& tup);

    void setRes();

   public:
    string getRes();
    Task3(Graph& G);
};
