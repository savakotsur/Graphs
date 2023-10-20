#pragma once
#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class InputMech {
   protected:
    bool succes_flag = false;
    bool h = false;
    ifstream file;
    string inpPath = "";
    string outPath = "";
    int input_key = 0;

    vector<vector<int> > matrix_From_EdgesList();
    vector<vector<int> > matrix_From_AdjMatrix();
    vector<vector<int> > matrix_From_AdjList();

    void matrix_Addfiller(int m_size, vector<vector<int> >& M);
    bool fileOpener();
    virtual void help();

   public:
    InputMech(vector<string> inp_str);
    InputMech();

    bool checkSucces();
    vector<vector<int> > getMatrix();
    string getOutPath();
};

class InputMech_SPtask4 : public InputMech {
   private:
    int algorithm_mode = 0;
    void help() override;

   public:
    InputMech_SPtask4(vector<string> inp_str);
    int getAlgorithm();
};

class InputMech_SPtask5 : public InputMech {
   private:
    pair<int, int> st_end;
    void help() override;

   public:
    InputMech_SPtask5(vector<string> inp_str);
    pair<int, int> getVpare();
};

class InputMech_SPtask6 : public InputMech {
   private:
    pair<int, int> alg_vert;
    void help() override;

   public:
    InputMech_SPtask6(vector<string> inp_str);
    pair<int, int> getPare();
};

class InputMech_SPtask8 : public InputMech {
   private:
    pair<pair<int, int>, pair<int, int> > st_end;
    void help() override;

   public:
    InputMech_SPtask8(vector<string> inp_str);
    pair<pair<int, int>, pair<int, int> > getPare();
};