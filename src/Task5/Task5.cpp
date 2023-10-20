#include "Task5.h"

void Task5::Dijkstra() {
    vector<int> weights;
    weights.assign(size, INF);
    vector<bool> visited;
    visited.assign(size, false);
    vector<int> parents(size);

    int curr = st_vertex;
    int visited_count = 1;
    visited[curr] = true;
    weights[curr] = 0;
    parents[curr] = -1;

    while (visited_count != size) {
        vector<int> adj_v = gr_forTask->adjacency_list(curr);

        for (int i : adj_v) {
            int new_w = weights[curr] + gr_forTask->weight(curr, i);
            if (new_w < weights[i]) {
                weights[i] = new_w;
                parents[i] = curr;
            }
        }
        visited[curr] = true;
        visited_count++;

        curr = chooseNextV(weights, visited);
    }

    if (weights[end_vertex] != INF) checkPath(parents);
    pathes_cost = weights;
}

Task5::Task5(Graph &G, pair<int, int> p) {
    gr_forTask = &G;
    size = gr_forTask->GetSize();

    st_vertex = p.first;
    end_vertex = p.second;

    Dijkstra();
    setRes();
}

int Task5::chooseNextV(vector<int> w, vector<bool> u) {
    int min_w = INF;
    int vert = 0;

    for (int i = 0; i < size; i++) {
        if (w[i] < min_w && u[i] == false) {
            min_w = w[i];
            vert = i;
        }
    }
    return vert;
}

void Task5::checkPath(vector<int> parents) {
    int i = end_vertex;

    while (parents[i] != -1) {
        path.push_back(make_tuple(parents[i], i, gr_forTask->weight(parents[i], i)));
        i = parents[i];
    }

    reverse(path.begin(), path.end());
}

void Task5::setRes() {
    string res_str = "";
    if (pathes_cost[end_vertex] < INF) {
        res_str += "Shortest path length between " + to_string(st_vertex + 1) + " and " +
                   to_string(end_vertex + 1) + " vertices: " + to_string(pathes_cost[end_vertex]) + "\n";

        res_str += "{ ";
        for (int i = 0; i < path.size(); i++) {
            res_str += "( " + to_string(get<0>(path[i]) + 1) + ", " + to_string(get<1>(path[i]) + 1);

            if (get<2>(path[i]) != 1) res_str += ", " + to_string(get<2>(path[i]));

            res_str += " ) ";
        }
        res_str += "}\n";
    } else
        res_str += "There is no path between the vertices " + to_string(st_vertex + 1) + " and " +
                   to_string(end_vertex + 1) + "\n";
    this->res_str = res_str;
}

string Task5::getRes() { return res_str; }