#include "Task4.h"

void Task4::Prima() {
    set<int> v = {0};
    tuple<int, int, int> minEdge;
    int weight = 0;
    tupleVec edges = gr_forTask->list_of_edges();

    while (v.size() != size) {
        get<2>(minEdge) = 1000000;
        for (const auto &e : edges) {
            if (get<2>(e) < get<2>(minEdge)) {
                set<int>::iterator it_f = v.find(get<0>(e));
                set<int>::iterator it_s = v.find(get<1>(e));
                if ((it_f != v.end() || it_s != v.end()) && (it_f == v.end() || it_s == v.end())) {
                    minEdge = e;
                }
            }
        }

        ostov.push_back(minEdge);
        v.insert(get<0>(minEdge));
        v.insert(get<1>(minEdge));
        weight += get<2>(minEdge);
    }
    ostov_weight = weight;
}

void Task4::Cruscal() {
    tupleVec edges = gr_forTask->list_of_edges();
    int weight = 0;

    sort(edges.begin(), edges.end(), Task4::comp_forTuple);
    vector<int> comp_n(size);
    for (int i = 0; i < size; i++) comp_n[i] = i;

    for (int i = 0; i < edges.size(); i++) {
        int first = get<0>(edges[i]);
        int second = get<1>(edges[i]);
        int e_weight = get<2>(edges[i]);

        if (comp_n[first] != comp_n[second]) {
            weight += e_weight;
            ostov.push_back(edges[i]);

            int forchange = comp_n[second];
            for (int j = 0; j < size; j++)
                if (comp_n[j] == forchange) comp_n[j] = comp_n[first];
        }
    }

    ostov_weight = weight;
}

void Task4::Boruvka() {
    tupleVec edges = gr_forTask->list_of_edges();
    int weight = 0;
    int components_count = size;

    vector<int> comp_n(size);
    for (int i = 0; i < size; i++) comp_n[i] = i;

    while (components_count > 1) {
        vector<int> numbers_minEdges;
        numbers_minEdges.assign(size, -1);

        for (int i = 0; i < edges.size(); i++) {
            tuple<int, int, int> edge = edges[i];

            if (comp_n[get<0>(edge)] == comp_n[get<1>(edge)]) continue;

            int numb_first = comp_n[get<0>(edge)];
            int numb_second = comp_n[get<1>(edge)];

            if ((numbers_minEdges[numb_first] == -1) ||
                (get<2>(edge) < get<2>(edges[numbers_minEdges[numb_first]]))) {
                numbers_minEdges[numb_first] = i;
            }

            if ((numbers_minEdges[numb_second] == -1) ||
                (get<2>(edge) < get<2>(edges[numbers_minEdges[numb_second]]))) {
                numbers_minEdges[numb_second] = i;
            }
        }

        for (int i = 0; i < size; i++) {
            if (numbers_minEdges[i] != -1) {
                int numb_first = comp_n[get<0>(edges[numbers_minEdges[i]])];
                int numb_second = comp_n[get<1>(edges[numbers_minEdges[i]])];

                if (numb_first == numb_second) continue;

                int forchange = comp_n[numb_second];
                for (int i = 0; i < size; i++) {
                    if (comp_n[i] == forchange) comp_n[i] = comp_n[numb_first];
                }

                ostov.push_back(edges[numbers_minEdges[i]]);
                components_count--;

                weight += get<2>(edges[numbers_minEdges[i]]);
            }
        }
    }

    ostov_weight = weight;
}

bool Task4::comp_forTuple(tuple<int, int, int> a, tuple<int, int, int> b) {
    return get<2>(a) < get<2>(b) || (get<2>(a) == get<2>(b) && get<0>(a) < get<0>(b));
}

void Task4::setRes() {
    string res_str = "";
    res_str += "Minimum spanning tree:\n{ ";
    for (int i = 0; i < ostov.size(); i++) {
        res_str += "( " + to_string(get<0>(ostov[i]) + 1) + ", " + to_string(get<1>(ostov[i]) + 1) + ", " +
                   to_string(get<2>(ostov[i])) + " ) ";
    }

    res_str += "}\nWeight of spanning tree: " + to_string(ostov_weight) + "\n";
    if (allAlg) {
        res_str += "Prima time = " + to_string(timer_p) + " milliseconds\n";
        res_str += "Cruscal time = " + to_string(timer_k) + " milliseconds\n";
        res_str += "Boruvka time = " + to_string(timer_b) + " milliseconds\n";
    }

    this->res_str = res_str;
}

Task4::Task4(Graph &G, int alg) {
    gr_forTask = &G;
    size = gr_forTask->GetSize();

    switch (alg) {
        case 1:
            Cruscal();
            break;
        case 2:
            Prima();
            break;

        case 3:
            Boruvka();
            break;
        case 4:
            allAlg = true;

            auto Start = chrono::steady_clock::now();
            Cruscal();
            auto End = chrono::steady_clock::now();
            timer_k = chrono::duration_cast<chrono::milliseconds>(End - Start).count();

            Start = chrono::steady_clock::now();
            Prima();
            End = chrono::steady_clock::now();
            timer_p = chrono::duration_cast<chrono::milliseconds>(End - Start).count();

            Start = chrono::steady_clock::now();
            Boruvka();
            End = chrono::steady_clock::now();
            timer_b = chrono::duration_cast<chrono::milliseconds>(End - Start).count();
            break;
    }

    setRes();
}
string Task4::getRes() { return res_str; }