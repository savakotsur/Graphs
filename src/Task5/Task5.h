#pragma once
#include "../Graph.h"
#define INF 1000000000

class Task5 {
   private:
    Graph* gr_forTask;
    int size;
    string res_str;

    int st_vertex;
    int end_vertex;

    vector<int> pathes_cost;
    vector<tuple<int, int, int>> path;

    int chooseNextV(vector<int> w, vector<bool> u);
    void checkPath(vector<int> p);

    void Dijkstra();
    void setRes();

   public:
    Task5(Graph& G, pair<int, int> p);
    string getRes();
};
