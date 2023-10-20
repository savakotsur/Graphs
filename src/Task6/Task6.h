#pragma once
#include <queue>

#include "../Graph.h"
#define INF 1000000000

class Task6 {
   private:
    Graph* gr_forTask;
    int size;
    string res_str;
    int st_vertex;

    bool negative_weights = false;
    bool negative_cycle = false;
    vector<int> weights;

    void Dijkstra();
    void Bellman_Ford();
    void Levit();

    int chooseNextV(vector<int> w, vector<bool> u);

    void check_negativeWeights();
    void setRes();

   public:
    Task6(Graph& G, int alg, int vert);

    string getRes();
};
