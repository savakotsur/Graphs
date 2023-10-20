#include "Task2.h"

Task2::Task2(Graph &G) {
    gr_forTask = &G;
    string res_str;
    check_Connectivity();
    connectedComponents();

    if (gr_forTask->is_directed()) {
        if (connectivity) check_strongConnectivity();
        strongConnectedComponents();
    }

    setRes();
}

vector<bool> Task2::BFS(int V, vector<vector<int>> matrix) {
    queue<int> q;
    vector<bool> used_v(gr_forTask->GetSize());

    q.push(V);
    used_v[V] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[cur][i] != 0) {
                if (!used_v[i]) {
                    q.push(i);
                    used_v[i] = true;
                }
            }
        }
    }

    return used_v;
}

void Task2::tactDFS(int V, vector<int> &tacts_forV, vector<bool> &used_V) {
    stack<int> s;
    static int tact = 0;
    s.push(V);

    while (!s.empty()) {
        int curr = s.top();
        tact++;
        tacts_forV[curr] = tact;
        used_V[curr] = true;

        for (int i = 0; i < gr_forTask->adjacency_matrix()[curr].size(); i++) {
            if ((gr_forTask->adjacency_matrix()[curr][i] != 0 && !used_V[i])) {
                curr = i;
                i = 0;
                s.push(curr);
                tact++;
                tacts_forV[curr] = tact;
                used_V[curr] = true;
            }
        }
        s.pop();
    }
}
void Task2::DFS(int V, vector<bool> &used_V, vector<vector<int>> &invertM) {
    stack<int> s;
    s.push(V);

    while (!s.empty()) {
        int curr = s.top();
        used_V[curr] = true;

        for (int i = 0; i < invertM[curr].size(); i++) {
            if ((invertM[curr][i] != 0 && !used_V[i])) {
                curr = i;
                i = 0;
                s.push(curr);
                used_V[curr] = true;
            }
        }
        s.pop();
    }
}

void Task2::check_Connectivity() {
    vector<bool> used_v;

    if (!gr_forTask->is_directed()) {
        used_v = BFS(0, gr_forTask->adjacency_matrix());
    } else {
        used_v = BFS(0, create_corrMatrix());
    }

    for (int i = 0; i < used_v.size(); i++) {
        if (used_v[i] == false) {
            connectivity = false;
            break;
        }
    }

    if (gr_forTask->is_directed() && connectivity) weak = true;
}
void Task2::check_strongConnectivity() {
    int count_false = 0;
    vector<vector<bool>> bypass_matrix;

    for (int i = 0; i < gr_forTask->GetSize(); i++) {
        bypass_matrix.push_back(BFS(i, gr_forTask->adjacency_matrix()));
    }

    for (int i = 0; i < bypass_matrix.size(); i++) {
        for (int j = i; j < bypass_matrix.size(); j++) {
            if (bypass_matrix[i][j] == false) count_false++;
        }
    }

    if (count_false == 0) strong = true;
}

void Task2::connectedComponents() {
    vector<int> vertexes, component;
    vector<bool> k;

    for (int i = 0; i < gr_forTask->GetSize(); i++) {
        vertexes.push_back(i);
    }

    while (vertexes.size() > 0) {
        if (gr_forTask->is_directed())
            k = BFS(vertexes[0], create_corrMatrix());
        else
            k = BFS(vertexes[0], gr_forTask->adjacency_matrix());

        for (int i = 0; i < k.size(); i++) {
            if (k[i]) {
                component.push_back(i);
                vertexes.erase(find(vertexes.begin(), vertexes.end(), i));
            }
        }

        connectedComp.push_back(component);
        component.clear();
    }

    connectedComp_amount = connectedComp.size();
}
void Task2::strongConnectedComponents() {
    vector<bool> used_v(gr_forTask->GetSize());
    vector<int> tacts_forV(gr_forTask->GetSize());
    vector<vector<int>> invertM = create_invertMatrix();

    for (int i = 0; i < used_v.size(); i++) {
        if (used_v[i] == false) tactDFS(i, tacts_forV, used_v);
    }
    used_v.assign(used_v.size(), false);

    vector<int> vertexes, component;
    for (int i = 0; i < gr_forTask->GetSize(); i++) {
        vertexes.push_back(i);
    }

    while (vertexes.size() > 0) {
        int pos =
            find(tacts_forV.begin(), tacts_forV.end(), *max_element(tacts_forV.begin(), tacts_forV.end())) -
            tacts_forV.begin();
        DFS(pos, used_v, invertM);

        for (int i = 0; i < used_v.size(); i++) {
            if (used_v[i] && tacts_forV[i] != 0) {
                tacts_forV[i] = 0;

                component.push_back(i);
                vertexes.erase(find(vertexes.begin(), vertexes.end(), i));
            }
        }

        strongConnectedComp.push_back(component);
        component.clear();
    }

    strongConnectedComp_amount = strongConnectedComp.size();
}

vector<vector<int>> Task2::create_corrMatrix() {
    vector<vector<int>> correlated_m = gr_forTask->adjacency_matrix();
    for (int i = 0; i < correlated_m.size(); i++) {
        for (int j = 0; j < correlated_m.size(); j++) {
            if (correlated_m[i][j] != 0) {
                correlated_m[j][i] = correlated_m[i][j];
            }
        }
    }
    return correlated_m;
}
vector<vector<int>> Task2::create_invertMatrix() {
    vector<vector<int>> invert_m = gr_forTask->adjacency_matrix();
    for (int i = 0; i < invert_m.size(); i++) {
        for (int j = i; j < invert_m.size(); j++) {
            int g = invert_m[j][i];
            invert_m[j][i] = invert_m[i][j];
            invert_m[i][j] = g;
        }
    }
    return invert_m;
}

void Task2::setRes() {
    string res_str = "";
    if (gr_forTask->is_directed()) {
        if (connectivity)
            res_str += "Diraph is connected.\n";
        else
            res_str += "Diraph is not connected.\n";
    } else {
        if (connectivity)
            res_str += "Graph is connected.\n";
        else
            res_str += "Graph is not connected.\n";
    }

    res_str += "It contains " + to_string(connectedComp_amount) + " connected components: {";
    for (int i = 0; i < connectedComp.size(); i++) {
        res_str += " { ";
        for (int j = 0; j < connectedComp[i].size(); j++) {
            res_str += to_string(connectedComp[i][j] + 1) + " ";
        }
        res_str += "} ";
    }
    res_str += "}\n";

    if (gr_forTask->is_directed()) {
        if (strong)
            res_str += "Digraph is strongly connected.\n";
        else if (weak)
            res_str += "Digraph is weakly connected.\n";
        else
            res_str += "Digraph is totally not connected.\n";

        res_str += "It contains " + to_string(strongConnectedComp_amount) + " strong connected components: {";
        for (int i = 0; i < strongConnectedComp.size(); i++) {
            res_str += " { ";
            for (int j = 0; j < strongConnectedComp[i].size(); j++) {
                res_str += to_string(strongConnectedComp[i][j] + 1) + " ";
            }
            res_str += "} ";
        }
        res_str += "}\n";
    }
    this->res_str = res_str;
}

string Task2::getRes() { return res_str; }