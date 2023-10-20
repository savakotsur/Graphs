#include "Task7.h"

vector<int> Task7::Dijkstra(int st_vert) {
    vector<int> weights;
    weights.assign(size, INF);
    vector<bool> visited;
    visited.assign(size, false);
    int curr = st_vert;
    int visited_amount = 1;
    visited[curr] = true;
    weights[curr] = 0;

    while (visited_amount != size) {
        vector<int> adj_v = gr_forTask->adjacency_list(curr);

        for (int i : adj_v) {
            int new_w = weights[curr] + gr_forTask->weight(curr, i);
            if (new_w < weights[i]) {
                weights[i] = new_w;
            }
        }
        visited[curr] = true;
        visited_amount++;

        curr = chooseNextV(weights, visited);
    }

    return weights;
}

void Task7::Bellman_Ford(int st_vert, vector<int> &h) {
    vector<tuple<int, int, int>> edges = gr_forTask->list_of_edges();
    vector<int> weights;
    weights.assign(size, INF);
    weights[st_vert] = 0;

    for (int i = 0; i < size - 1; i++) {
        for (const auto &e : edges) {
            weights[get<1>(e)] = fmin(weights[get<1>(e)], weights[get<0>(e)] + get<2>(e));
        }
    }

    for (const auto &e : edges) {
        if (weights[get<1>(e)] > weights[get<0>(e)] + get<2>(e)) {
            negative_cycle = true;
            break;
        }
    }

    h = weights;
}

void Task7::Johnson() {
    vector<vector<int>> weights;

    vector<int> potentials;

    gr_forTask->add_NullEdged_vertex();
    size++;

    vector<tuple<int, int, int>> edges = gr_forTask->list_of_edges();

    Bellman_Ford(gr_forTask->Get_nullEdged_number(), potentials);

    if (negative_cycle) return;

    for (auto &e : edges) {
        get<2>(e) = get<2>(e) + potentials[get<0>(e)] - potentials[get<1>(e)];
        gr_forTask->setUpdatedweight(get<0>(e), get<1>(e), get<2>(e));
    }

    gr_forTask->delete__NullEdged_vertex();
    size--;

    for (int i = 0; i < edges.size(); i++) {
        if (get<0>(edges[i]) == size) {
            edges.erase(edges.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < size; i++) {
        weights.push_back(Dijkstra(i));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (weights[i][j] != INF) weights[i][j] = weights[i][j] - potentials[i] + potentials[j];
        }
    }

    this->weights = weights;
}

int Task7::chooseNextV(vector<int> w, vector<bool> u) {
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

void Task7::setRes() {
    string res_str = "";

    if (negative_cycle)
        res_str += "Graph contains a negative cycle.\n";
    else {
        if (negative_weights)
            res_str += "Graph contains edges with negative weight.\n";
        else
            res_str += "Graph doesn't contain edges with negative weight.\n";

        res_str += "Shortest paths lengths:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (weights[i][j] != INF && i != j) {
                    res_str +=
                        to_string(i + 1) + " - " + to_string(j + 1) + ": " + to_string(weights[i][j]) + "\n";
                }
            }
        }
    }

    this->res_str = res_str;
}

void Task7::check_negativeWeights() {
    vector<tuple<int, int, int>> edges = gr_forTask->list_of_edges();

    for (int i = 0; i < edges.size(); i++) {
        if (get<2>(edges[i]) < 0) {
            negative_weights = true;
            break;
        }
    }
}

Task7::Task7(AdvancedGraph &G) {
    gr_forTask = &G;
    size = gr_forTask->GetSize();

    check_negativeWeights();

    Johnson();

    setRes();
}

string Task7::getRes() { return res_str; }
