#include "Graph.h"

Graph::Graph(vector<vector<int>> m) {
    matrix = m;
    g_size = matrix.size();
}

int Graph::GetSize() { return g_size; }

int Graph::weight(int Vi, int Vj) { return matrix[Vi][Vj]; }

bool Graph::is_edge(int Vi, int Vj) {
    if ((Vi != Vj) && (matrix[Vi][Vj] != 0))
        return true;
    else
        return false;
}

vector<vector<int>> Graph::adjacency_matrix() { return matrix; }

vector<int> Graph::adjacency_list(int V) {
    vector<int> adj_list = {};
    for (int i = 0; i < (int)matrix.size(); i++) {
        if ((V != i) && (matrix[V][i] != 0)) adj_list.push_back(i);
    }

    return adj_list;
}

vector<tuple<int, int, int>> Graph::list_of_edges() {
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix.size(); j++) {
            if ((i != j) && (matrix[i][j] != 0)) edges.push_back(make_tuple(i, j, matrix[i][j]));
        }
    }
    return edges;
}

vector<tuple<int, int, int>> Graph::list_of_edges(int V) {
    vector<tuple<int, int, int>> edgesV;
    for (int i = 0; i < (int)matrix.size(); i++) {
        if ((V != i) && (matrix[V][i] != 0)) edgesV.push_back(make_tuple(V, i, matrix[V][i]));
    }
    return edgesV;
}

bool Graph::is_directed() {
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = i; j < (int)matrix.size(); j++) {
            if (matrix[i][j] != matrix[j][i]) return true;
        }
    }
    return false;
}

AdvancedGraph::AdvancedGraph(vector<vector<int>> m) : Graph(m) {
    corrected_marks.assign(g_size + 1, {});
    for (int i = 0; i < g_size + 1; i++) {
        corrected_marks[i].assign(g_size + 1, false);
    }
}

vector<tuple<int, int, int>> AdvancedGraph::list_of_edges() {
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix.size(); j++) {
            if (i != j && (matrix[i][j] != 0 || i == nullEdged_number))
                edges.push_back(make_tuple(i, j, matrix[i][j]));
        }
    }
    return edges;
}

vector<int> AdvancedGraph::adjacency_list(int V) {
    vector<int> adj_list = {};
    for (int i = 0; i < (int)matrix.size(); i++) {
        if ((V != i) && (matrix[V][i] != 0 || corrected_marks[V][i] == true)) adj_list.push_back(i);
    }

    return adj_list;
}

void AdvancedGraph::setUpdatedweight(int i, int j, int w) {
    matrix[i][j] = w;
    corrected_marks[i][j] = true;
}

void AdvancedGraph::add_NullEdged_vertex() {
    nullEdged_number = g_size;
    g_size++;
    vector<int> newEdges_weights;
    newEdges_weights.assign(g_size, 0);
    matrix.push_back(newEdges_weights);

    for (int i = 0; i < g_size - 1; i++) {
        matrix[i].push_back(0);
    }
}

void AdvancedGraph::delete__NullEdged_vertex() {
    for (int i = 0; i < g_size - 1; i++) {
        matrix[i].pop_back();
    }
    matrix.pop_back();

    g_size--;
    nullEdged_number = -1;
}

int AdvancedGraph::Get_nullEdged_number() { return nullEdged_number; }
