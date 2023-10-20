#pragma once
#include "../Graph.h"
#define INF 1000000000

class Task7 {
   private:
    AdvancedGraph* gr_forTask;
    int size;
    string res_str;

    bool negative_cycle = false;
    bool negative_weights = false;
    vector<vector<int>> weights;

    vector<int> Dijkstra(int st_vert);
    void Bellman_Ford(int st_vert, vector<int>& h);
    void Johnson();

    int chooseNextV(vector<int> w, vector<bool> u);
    void check_negativeWeights();
    void setRes();

   public:
    Task7(AdvancedGraph& G);

    string getRes();
};
