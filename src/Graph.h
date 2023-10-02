#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>

using namespace std;
typedef vector<tuple<int, int, int>> tupleVec;

class Graph
{
protected:
    vector<vector<int>> matrix;
    int g_size;
public:
    Graph(vector<vector<int>> m);
    int GetSize();

    int weight(int Vi, int Vj);

    bool is_edge(int Vi, int Vj);

    vector<vector<int>> adjacency_matrix();

    virtual vector<int> adjacency_list(int V);

    virtual tupleVec list_of_edges();

    tupleVec list_of_edges(int V);

    bool is_directed();
};

class AdvancedGraph : public Graph {
private:
    int nullEdged_number = -1;
    vector<vector<bool>> corrected_marks;
public:
    AdvancedGraph(vector<vector<int>> m);
    int Get_nullEdged_number();

    tupleVec list_of_edges() override;
    vector<int> adjacency_list(int V) override;

    void setUpdatedweight(int i, int j, int w);
    void add_NullEdged_vertex();
    void delete__NullEdged_vertex();
};



