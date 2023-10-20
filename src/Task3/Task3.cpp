#include "Task3.h"

Task3::Task3(Graph &G) {
    gr_forTask = &G;

    calculateTask();

    setRes();
}

void Task3::calculateTask() {
    vector<bool> used_v;
    vector<int> tin, tup;
    used_v.assign(gr_forTask->GetSize(), false);
    tin.assign(gr_forTask->GetSize(), 0);
    tup.assign(gr_forTask->GetSize(), 0);

    int P = -1;
    for (int i = 0; i < used_v.size(); i++) {
        if (!used_v[i]) DFS(i, P, used_v, tin, tup);
    }
}

void Task3::DFS(int V, int P, vector<bool> &used_v, vector<int> &tin, vector<int> &tup) {
    static int timer = 0;

    used_v[V] = true;
    tin[V] = tup[V] = timer++;

    int child_counter = 0;

    for (int i = 0; i < gr_forTask->GetSize(); i++) {
        if (gr_forTask->is_edge(V, i) && !used_v[i]) {
            child_counter++;
            DFS(i, V, used_v, tin, tup);

            tup[V] = fmin(tup[V], tup[i]);
            if (tin[V] < tup[i]) {
                tuple<int, int> br = make_tuple(V, i);
                briges.push_back(br);
            }
            if (tin[V] <= tup[i] && P != -1) {
                cut_vertexes.insert(V);
            }
        }
        if (gr_forTask->is_edge(V, i) && used_v[i] && i != P) {
            tup[V] = fmin(tup[V], tin[i]);
        }
    }

    if (P == -1 && child_counter > 1) cut_vertexes.insert(V);
}

void Task3::setRes()

{
    string res_str = "";
    res_str += "Bridges:\n{ ";
    for (int i = 0; i < briges.size(); i++) {
        res_str += "(" + to_string(get<0>(briges[i]) + 1) + ", " + to_string(get<1>(briges[i]) + 1) + ") ";
    }
    res_str += "}";

    res_str += "\nCut vertexes:\n{ ";
    for (int i : cut_vertexes) res_str += to_string(i + 1) + " ";
    res_str += "}\n";

    this->res_str = res_str;
}
string Task3::getRes() { return res_str; }
