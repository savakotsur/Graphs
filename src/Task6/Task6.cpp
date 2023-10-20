#include "Task6.h"

void Task6::Dijkstra() {
    vector<int> weights;
    weights.assign(size, INF);
    vector<bool> visited;
    visited.assign(size, false);
    vector<int> count_visits;
    count_visits.assign(size, 0);
    int curr = st_vertex;
    int visited_amount = 1;
    visited[curr] = true;
    weights[curr] = 0;

    while (visited_amount != size) {
        vector<int> adj_v = gr_forTask->adjacency_list(curr);

        for (int i : adj_v) {
            int new_w = weights[curr] + gr_forTask->weight(curr, i);
            if (new_w < weights[i]) {
                weights[i] = new_w;

                if (visited[i]) {
                    visited[i] = false;
                    visited_amount--;
                }
            }
        }
        visited[curr] = true;
        count_visits[curr]++;
        visited_amount++;

        if (find(count_visits.begin(), count_visits.end(), size) != count_visits.end()) {
            negative_cycle = true;
            break;
        }
        curr = chooseNextV(weights, visited);
    }

    this->weights = weights;
}

void Task6::Bellman_Ford() {
    vector<tuple<int, int, int>> edges = gr_forTask->list_of_edges();
    vector<int> weights;
    weights.assign(size, INF);
    weights[st_vertex] = 0;

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

    this->weights = weights;
}

void Task6::Levit() {
    vector<int> set_nambers;
    set_nambers.assign(size, 2);
    set_nambers[st_vertex] = 1;
    vector<int> weights;
    weights.assign(size, INF);
    weights[st_vertex] = 0;

    queue<int> mainQ;
    queue<int> urgentQ;
    mainQ.push(st_vertex);

    while (!mainQ.empty() || !urgentQ.empty()) {
        int f_vert;
        if (urgentQ.empty()) {
            f_vert = mainQ.front();
            mainQ.pop();
        } else {
            f_vert = urgentQ.front();
            urgentQ.pop();
        }

        vector<tuple<int, int, int>> edges = gr_forTask->list_of_edges(f_vert);
        for (const auto &e : edges) {
            int sec_vert = get<1>(e);

            if (set_nambers[sec_vert] == 2) {
                weights[sec_vert] = weights[f_vert] + get<2>(e);
                mainQ.push(sec_vert);
                set_nambers[sec_vert] = 1;
            }

            else if (set_nambers[sec_vert] == 1) {
                weights[sec_vert] = fmin(weights[sec_vert], weights[f_vert] + get<2>(e));
            }

            else if (set_nambers[sec_vert] == 0) {
                if (weights[sec_vert] > weights[f_vert] + get<2>(e)) {
                    weights[sec_vert] = weights[f_vert] + get<2>(e);
                    urgentQ.push(sec_vert);
                    set_nambers[sec_vert] = 1;
                }
            }
        }

        for (int w : weights) {
            if (w < 0) {
                negative_cycle = true;
                return;
            }
        }

        set_nambers[f_vert] = 0;
    }

    this->weights = weights;
}

int Task6::chooseNextV(vector<int> w, vector<bool> u) {
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

void Task6::check_negativeWeights() {
    vector<tuple<int, int, int>> edges = gr_forTask->list_of_edges();

    for (int i = 0; i < edges.size(); i++) {
        if (get<2>(edges[i]) < 0) {
            negative_weights = true;
            break;
        }
    }
}

void Task6::setRes() {
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
            if (i == st_vertex) continue;

            res_str += to_string(st_vertex + 1) + " - " + to_string(i + 1) + ": ";

            if (weights[i] < INF)
                res_str += to_string(weights[i]) + "\n";
            else
                res_str += "INF\n";
        }
    }

    this->res_str = res_str;
}

Task6::Task6(Graph &G, int alg, int vert) {
    gr_forTask = &G;
    size = gr_forTask->GetSize();

    st_vertex = vert - 1;

    check_negativeWeights();

    switch (alg) {
        case 1:
            Dijkstra();
            break;
        case 2:
            Bellman_Ford();
            break;
        case 3:
            Levit();
            break;
    }

    setRes();
}

string Task6::getRes() { return res_str; }
