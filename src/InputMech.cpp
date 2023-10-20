#include "InputMech.h"

vector<vector<int>> InputMech::matrix_From_EdgesList() {
    vector<vector<int>> M;
    string s;
    stringstream strS;
    int m_size = 0, str_size = 0, col_size = 0;
    int i, j, len;
    int last_firstV = -1, last_secondV = -1;

    while (!file.eof()) {
        getline(file, s);
        if (s == "") break;
        strS << s;
        s.clear();

        i = 0;
        j = 0;
        len = 1;

        strS >> i >> j >> len;
        i--;
        j--;

        if (i != last_firstV) {
            last_secondV = -1;
            int dif = i - last_firstV;
            for (int g = 0; g < dif; g++) {
                M.push_back({});
                col_size++;
            }
        }

        for (int h = last_secondV + 1; h < j; h++) {
            M[i].push_back(0);
        }
        M[i].push_back(len);

        if ((int)M[i].size() > str_size) str_size = M[i].size();

        last_firstV = i;
        last_secondV = j;

        strS.str(string());
        strS.clear();
    }

    m_size = fmax(str_size, col_size);

    matrix_Addfiller(m_size, M);

    return M;
}

vector<vector<int>> InputMech::matrix_From_AdjMatrix() {
    vector<vector<int>> M;
    int i = 0;
    string s;
    stringstream strS;

    while (!file.eof()) {
        getline(file, s);
        if (s == "") break;
        strS << s;
        s.clear();

        M.push_back({});
        while (!strS.eof()) {
            strS >> s;
            if (s == "") break;
            M[i].push_back(stoi(s));
            s.clear();
        }
        i++;
        strS.str(string());
        strS.clear();
    }

    return M;
}

vector<vector<int>> InputMech::matrix_From_AdjList() {
    vector<vector<int>> M;
    vector<int> adj_vertex;
    int m_size = 0, str_size = 0, col_size = 0;
    int i = 0;
    string s;
    stringstream strS;

    while (!file.eof()) {
        getline(file, s);
        if (s == "") break;
        strS << s;
        s.clear();

        M.push_back({});
        col_size++;

        while (!strS.eof()) {
            strS >> s;
            if (s == "") break;
            adj_vertex.push_back(stoi(s) - 1);
            s.clear();
        }
        sort(adj_vertex.begin(), adj_vertex.end());

        for (int k = 0; k < (int)adj_vertex.size(); k++) {
            for (int j = M[i].size(); j < adj_vertex[k]; j++) {
                M[i].push_back(0);
            }
            M[i].push_back(1);
        }
        if (str_size < (int)M[i].size()) str_size = M[i].size();

        i++;
        adj_vertex.clear();
        strS.str(string());
        strS.clear();
    }

    m_size = fmax(str_size, col_size);

    matrix_Addfiller(m_size, M);

    return M;
}

void InputMech::matrix_Addfiller(int m_size, vector<vector<int>> &M) {
    for (int g = M.size(); g < m_size; g++) {
        M.push_back({});
    }

    for (int k = 0; k < m_size; k++) {
        for (int j = M[k].size(); j < m_size; j++) {
            M[k].push_back(0);
        }
    }
}

bool InputMech::fileOpener() {
    file.open(inpPath);
    if (!file.is_open()) {
        cout << "Input file is not found. Further working is impossible.\n";
        return false;
    }

    if (file.peek() == EOF) {
        cout << "Input file is empty. Further working is impossible.\n";
        return false;
    }

    return true;
}

void InputMech::help() {
    cout << "\nAuthors: Kotsur S.V., Vinokurova A.V.\nGroup: M3O-219Bk-21.\n\n";
    cout << "Key-list:\n-e /edges_list_file_path/ - file with the list of "
            "edges.\n";
    cout << "-m /adjacency_matrix_file_path/ - file with the adjacency matrix.\n";
    cout << "-l /adjacency_list_file_path/ - file with the adjacency list.\n";
    cout << "-o /output_file_path/ - file for the output data.\n";

    h = true;
}

InputMech::InputMech(vector<string> inp_str) {
    if (find(inp_str.begin(), inp_str.end(), "-h") != inp_str.end()) {
        help();
        return;
    }
    string inputType = "";
    vector<string>::iterator key_index[3] = {};

    key_index[0] = find(inp_str.begin(), inp_str.end(), "-e");
    if (key_index[0] != inp_str.end()) inputType += "1";

    key_index[1] = find(inp_str.begin(), inp_str.end(), "-m");
    if (key_index[1] != inp_str.end()) inputType += "2";

    key_index[2] = find(inp_str.begin(), inp_str.end(), "-l");
    if (key_index[2] != inp_str.end()) inputType += "3";

    if (inputType.size() != 1) {
        cout << "\nInput string includes invalid keypack.\n";
        return;
    } else
        input_key = stoi(inputType);

    inpPath = *(key_index[input_key - 1] + 1);

    if (!fileOpener()) {
        return;
    }

    vector<string>::iterator out = find(inp_str.begin(), inp_str.end(), "-o");
    if (out != inp_str.end()) {
        outPath = *(out + 1);
    }

    succes_flag = true;
}

InputMech::InputMech() {}

bool InputMech::checkSucces() { return succes_flag; }

vector<vector<int>> InputMech::getMatrix() {
    switch (input_key) {
        case 1:
            return matrix_From_EdgesList();
        case 2:
            return matrix_From_AdjMatrix();
        case 3:
            return matrix_From_AdjList();
    }
    return matrix_From_AdjList();
}

string InputMech::getOutPath() { return outPath; }

void InputMech_SPtask4::help() {
    cout << "-k - Cruskal algorithm.\n";
    cout << "-p - Prima algorithm.\n";
    cout << "-b - Boruvka algorithm.\n";
    cout << "-s - All three algorithms above.\n";
}

InputMech_SPtask4::InputMech_SPtask4(vector<string> inp_str) : InputMech(inp_str) {
    if (h) {
        help();
        return;
    }

    succes_flag = false;
    string inputType = "";

    if (find(inp_str.begin(), inp_str.end(), "-s") != inp_str.end()) {
        algorithm_mode = 4;
        succes_flag = true;
        return;
    }

    if (find(inp_str.begin(), inp_str.end(), "-k") != inp_str.end()) inputType += "1";

    if (find(inp_str.begin(), inp_str.end(), "-p") != inp_str.end()) inputType += "2";

    if (find(inp_str.begin(), inp_str.end(), "-b") != inp_str.end()) inputType += "3";

    if (inputType.size() != 1) {
        cout << "\nInput string includes invalid keypack.\n";
        return;
    } else
        algorithm_mode = stoi(inputType);

    succes_flag = true;
}

int InputMech_SPtask4::getAlgorithm() { return algorithm_mode; }

void InputMech_SPtask5::help() {
    cout << "-n /begin_vertex_number/ - number os starting vertex.\n";
    cout << "-d /end_vertex_number/ - number os ending vertex.\n";
}

InputMech_SPtask5::InputMech_SPtask5(vector<string> inp_str) : InputMech(inp_str) {
    if (h) {
        help();
        return;
    }

    succes_flag = false;

    vector<string>::iterator key_index[2] = {};
    key_index[0] = find(inp_str.begin(), inp_str.end(), "-n");
    key_index[1] = find(inp_str.begin(), inp_str.end(), "-d");

    if (key_index[0] == inp_str.end() || key_index[1] == inp_str.end()) {
        cout << "\nInput string includes invalid keypack.\n";
        return;
    }

    st_end = make_pair(stoi(*(key_index[0] + 1)) - 1, stoi(*(key_index[1] + 1)) - 1);

    succes_flag = true;
}

pair<int, int> InputMech_SPtask5::getVpare() { return st_end; }

void InputMech_SPtask6::help() {
    cout << "-d - Dijkstra algorithm.\n";
    cout << "-b - Bellman-Ford-Muur algorithm.\n";
    cout << "-t - Levit algorithm.\n";
    cout << "-n - begin_vertex_number.\n";
}

InputMech_SPtask6::InputMech_SPtask6(vector<string> inp_str) : InputMech(inp_str) {
    if (h) {
        help();
        return;
    }

    succes_flag = false;
    string inputType = "";

    if (find(inp_str.begin(), inp_str.end(), "-d") != inp_str.end()) inputType += "1";

    if (find(inp_str.begin(), inp_str.end(), "-b") != inp_str.end()) inputType += "2";

    if (find(inp_str.begin(), inp_str.end(), "-t") != inp_str.end()) inputType += "3";

    if (inputType.size() != 1) {
        cout << "\nInput string includes invalid keypack.\n";
        return;
    } else
        alg_vert.first = stoi(inputType);

    vector<string>::iterator it = find(inp_str.begin(), inp_str.end(), "-n");
    if (it != inp_str.end()) {
        alg_vert.second = stoi(*(it + 1));
    } else
        return;

    succes_flag = true;
}

pair<int, int> InputMech_SPtask6::getPare() { return alg_vert; }

void InputMech_SPtask8::help() {
    cout << "\nAuthors: Kotsur S.V. Vinokurova A.V.\nGroup: M3O-219Bk-21.\n\n";
    cout << "Key-list:\n-m /map_file_path/ - file with the matrix for the map.\n";
    cout << "-n /begin_vertex_x begin_vertex_y/ - coordinates of starting cell.\n";
    cout << "-d /end_vertex_x end_vertex_y/ - coordinates of ending cell.\n";
    cout << "-o /output_file_path/ - file for the output data.\n";

    h = true;
}

InputMech_SPtask8::InputMech_SPtask8(vector<string> inp_str) {
    if (find(inp_str.begin(), inp_str.end(), "-h") != inp_str.end()) {
        help();
        return;
    }

    input_key = 2;

    vector<string>::iterator key_index[3] = {};

    key_index[0] = find(inp_str.begin(), inp_str.end(), "-m");
    key_index[1] = find(inp_str.begin(), inp_str.end(), "-n");
    key_index[2] = find(inp_str.begin(), inp_str.end(), "-d");

    if (key_index[0] == inp_str.end() || key_index[1] == inp_str.end() || key_index[2] == inp_str.end()) {
        cout << "\nInput string includes invalid keypack.\n";
        return;
    }

    inpPath = *(key_index[0] + 1);

    if (!fileOpener()) {
        return;
    }

    st_end.first = make_pair(stoi(*(key_index[1] + 1)), stoi(*(key_index[1] + 2)));
    st_end.second = make_pair(stoi(*(key_index[2] + 1)), stoi(*(key_index[2] + 2)));

    vector<string>::iterator out = find(inp_str.begin(), inp_str.end(), "-o");
    if (out != inp_str.end()) {
        outPath = *(out + 1);
    }

    succes_flag = true;
}

pair<pair<int, int>, pair<int, int>> InputMech_SPtask8::getPare() { return st_end; }
