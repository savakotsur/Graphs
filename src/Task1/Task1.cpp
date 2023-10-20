#include "Task1.h"

Task1::Task1(Graph &G) {
    gr_forTask = &G;

    make_degVector();
    make_distanceMatrix();

    if (checkConnectivity()) {
        eccentricity();
        if (!gr_forTask->is_directed()) {
            calculate_DandR();
            centPerefirial_distribution();
        }
    }

    setRes();
}

void Task1::FloydWarshall(vector<vector<int>> &M, int size) {
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            if (M[i][k] != 0 && M[i][k] != INF) {
                for (int j = 0; j < size; j++) {
                    if (M[i][j] > M[i][k] + M[k][j]) {
                        M[i][j] = M[i][k] + M[k][j];
                    }
                }
            }
        }
    }
}

bool Task1::checkConnectivity() {
    for (int i = 0; i < distance_matrix.size(); i++) {
        for (int j : distance_matrix[i]) {
            if (j == INF) {
                return false;
            }
        }
    }
    return true;
}

void Task1::make_distanceMatrix() {
    distance_matrix = gr_forTask->adjacency_matrix();
    int size = gr_forTask->adjacency_matrix().size();

    for (int i = 0; i < distance_matrix.size(); i++) {
        for (int j = 0; j < distance_matrix.size(); j++) {
            if (distance_matrix[i][j] == 0 && i != j) {
                distance_matrix[i][j] = INF;
            }
        }
    }

    FloydWarshall(distance_matrix, size);
}

void Task1::make_degVector() {
    int degree;
    int deg_inp, deg_out;
    vector<vector<int>> m = gr_forTask->adjacency_matrix();

    if (!gr_forTask->is_directed()) {
        deg_vector.push_back({});

        for (int i = 0; i < m.size(); i++) {
            degree = 0;

            for (int j = 0; j < m.size(); j++) {
                if (m[i][j] != 0) degree++;
            }

            deg_vector[0].push_back(degree);
        }
    }

    else {
        deg_vector.push_back({});
        deg_vector.push_back({});

        for (int i = 0; i < m.size(); i++) {
            deg_inp = 0;
            deg_out = 0;

            for (int j = 0; j < m.size(); j++) {
                if (m[j][i] != 0) deg_inp++;
                if (m[i][j] != 0) deg_out++;
            }

            deg_vector[0].push_back(deg_inp);
            deg_vector[1].push_back(deg_out);
        }
    }
}

void Task1::eccentricity() {
    for (int i = 0; i < distance_matrix.size(); i++) {
        eccentry.push_back(*max_element(distance_matrix[i].begin(), distance_matrix[i].end()));
    }
}

void Task1::calculate_DandR() {
    diameter = *max_element(eccentry.begin(), eccentry.end());
    radius = *min_element(eccentry.begin(), eccentry.end());
}

void Task1::centPerefirial_distribution() {
    for (int i = 0; i < eccentry.size(); i++) {
        if (eccentry[i] == diameter) perefirial.push_back(i);
        if (eccentry[i] == radius) central.push_back(i);
    }
}

void Task1::setRes() {
    string res_str = "";
    for (int i = 0; i < deg_vector.size(); i++) {
        if (deg_vector.size() == 1) res_str += "deg = { ";
        if (deg_vector.size() == 2 && i == 0) res_str += "deg+ = { ";
        if (deg_vector.size() == 2 && i == 1) res_str += "\ndeg- = { ";

        for (int j = 0; j < deg_vector[i].size(); j++) {
            res_str += to_string(deg_vector[i][j]);
            if (j + 1 == deg_vector[i].size())
                res_str += " ";
            else
                res_str += ", ";
        }
        res_str += "}\n\n";
    }

    res_str += "Distancies:\n";
    for (int i = 0; i < distance_matrix.size(); i++) {
        for (int j = 0; j < distance_matrix.size(); j++) {
            if (distance_matrix[i][j] == INF)
                res_str += "INF\t";
            else
                res_str += (to_string(distance_matrix[i][j]) + "\t");
        }
        res_str += "\n\n";
    }

    if (checkConnectivity()) {
        res_str += "Eccentricity: { ";
        for (int i : eccentry) {
            res_str += (to_string(i) + " ");
        }
        res_str += "}\n";

        if (!gr_forTask->is_directed()) {
            res_str += ("D = " + to_string(diameter) + "\nR = " + to_string(radius) + "\n");

            res_str += "Z: { ";
            for (int i : central) res_str += (to_string(i + 1) + " ");
            res_str += "}\n";
            res_str += "P: { ";
            for (int i : perefirial) res_str += (to_string(i + 1) + " ");
            res_str += "}\n";
        }
    }

    this->res_str = res_str;
}

string Task1::getRes() { return res_str; }
