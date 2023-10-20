#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class OutputMech {
   private:
    string path;
    bool isFileNeeded = false;

   public:
    void Print(string out_str);
    OutputMech(string path, string res_str);
};
