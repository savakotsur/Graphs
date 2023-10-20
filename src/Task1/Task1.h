#pragma once
#include <iostream>

#include "../Graph.h"

#define INF 1000000000

using namespace std;

class Task1 {
   private:
    Graph *gr_forTask;

    string res_str;
    vector<vector<int> > distance_matrix;

    vector<vector<int> > deg_vector;

    vector<int> eccentry;
    int diameter = 0;
    int radius = 0;

    vector<int> central;
    vector<int> perefirial;

    void FloydWarshall(vector<vector<int> > &M, int size);
    bool checkConnectivity();

    void make_distanceMatrix();
    void make_degVector();

    void eccentricity();
    void calculate_DandR();

    void centPerefirial_distribution();

    void setRes();

   public:
    string getRes();
    Task1(Graph &G);
};
