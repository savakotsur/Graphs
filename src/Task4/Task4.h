#pragma once
#include <chrono>
#include <set>

#include "../Graph.h"

typedef vector<tuple<int, int, int>> tupleVec;

class Task4 {
   private:
    Graph* gr_forTask;
    string res_str;
    bool allAlg = false;
    int size;

    int timer_k = 0;
    int timer_p = 0;
    int timer_b = 0;

    tupleVec ostov = {};
    int ostov_weight = 0;

    void Prima();
    void Cruscal();
    void Boruvka();

    static bool comp_forTuple(tuple<int, int, int> a, tuple<int, int, int> b);

    void setRes();

   public:
    Task4(Graph& G, int alg);
    string getRes();
};
