#include "OutputMech.h"

void OutputMech::Print(string out_str) {
    if (isFileNeeded) {
        ofstream file(path);
        file << out_str;
    } else
        cout << out_str;
}

OutputMech::OutputMech(string path, string res_str) {
    if (path != "") isFileNeeded = true;
    this->path = path;

    Print(res_str);
}
