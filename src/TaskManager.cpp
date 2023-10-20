#include <dirent.h>

#include <cstring>
#include <iostream>

#include "Graph.h"
#include "InputMech.h"
#include "Map.h"
#include "OutputMech.h"
#include "Task1/Task1.h"
#include "Task2/Task2.h"
#include "Task3/Task3.h"
#include "Task4/Task4.h"
#include "Task5/Task5.h"
#include "Task6/Task6.h"
#include "Task7/Task7.h"
#include "Task8/Task8.h"

using namespace std;

void file_choice(string dirpath);
vector<string> InputString(string dirpath);
void task1(string dirpath);
void task2(string dirpath);
void task3(string dirpath);
void task4(string dirpath);
void task5(string dirpath);
void task6(string dirpath);
void task7(string dirpath);
void task8(string dirpath);

int main() {
    int task_number = 0;
    while (task_number != -1) {
        cout << "Input number of Task (1-8) or -1 for exit: ";
        string dirpath = "Tests/Test";
        cin >> task_number;
        if (cin.fail() || task_number > 8 || task_number < -1 || task_number == 0) {
            cout << "Incorrect input. Please retry\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            switch (task_number) {
                case 1:
                    dirpath = dirpath + to_string(task_number);
                    task1(dirpath);
                    break;
                case 2:
                    dirpath = dirpath + to_string(task_number);
                    task2(dirpath);
                    break;
                case 3:
                    dirpath = dirpath + to_string(task_number);
                    task3(dirpath);
                    break;
                case 4:
                    dirpath = dirpath + to_string(task_number);
                    task4(dirpath);
                    break;
                case 5:
                    dirpath = dirpath + to_string(task_number);
                    task5(dirpath);
                    break;
                case 6:
                    dirpath = dirpath + to_string(task_number);
                    task6(dirpath);
                    break;
                case 7:
                    dirpath = dirpath + to_string(task_number);
                    task7(dirpath);
                    break;
                case 8:
                    dirpath = dirpath + to_string(task_number);
                    task8(dirpath);
                    break;
            }
        }
    }
}

void file_choice(string dirpath) {
    DIR *dir;
    struct dirent *entry1;

    if ((dir = opendir(dirpath.c_str())) != nullptr) {
        int counter = 1;
        while ((entry1 = readdir(dir)) != nullptr) {
            if (entry1->d_type == DT_REG) {
                cout << counter << ". " << dirpath << "/" << entry1->d_name << "\n";
                counter++;
            }
        }
        closedir(dir);
    } else {
        cerr << "Failed to open the directory."
             << "\n";
    }
}

vector<string> InputString(string dirpath) {
    string argument;
    vector<string> inp_str;
    file_choice(dirpath);
    while (argument != "-1") {
        cout << "Enter arguments of input string (-1 to stop): ";
        cin >> argument;
        inp_str.push_back(argument);
    }
    return inp_str;
}

void task1(string dirpath) {
    vector<string> inp_str = InputString(dirpath);
    InputMech input(inp_str);
    if (!input.checkSucces()) return;

    Graph G(input.getMatrix());

    Task1 T1(G);

    OutputMech Out(input.getOutPath(), T1.getRes());
}

void task2(string dirpath) {
    vector<string> inp_str = InputString(dirpath);

    InputMech input(inp_str);
    if (!input.checkSucces()) return;

    Graph G(input.getMatrix());
    Task2 T2(G);
    OutputMech Out(input.getOutPath(), T2.getRes());
}

void task3(string dirpath) {
    vector<string> inp_str = InputString(dirpath);

    InputMech input(inp_str);
    if (!input.checkSucces()) return;

    Graph G(input.getMatrix());
    Task3 T3(G);
    OutputMech OUT(input.getOutPath(), T3.getRes());
}

void task4(string dirpath) {
    vector<string> inp_str = InputString(dirpath);

    InputMech_SPtask4 input(inp_str);
    if (!input.checkSucces()) return;

    Graph G(input.getMatrix());
    Task4 T4(G, input.getAlgorithm());
    OutputMech OUT(input.getOutPath(), T4.getRes());
}

void task5(string dirpath) {
    vector<string> inp_str = InputString(dirpath);

    InputMech_SPtask5 input(inp_str);
    if (!input.checkSucces()) return;

    Graph G(input.getMatrix());

    Task5 T5(G, input.getVpare());
    OutputMech OUT(input.getOutPath(), T5.getRes());
}

void task6(string dirpath) {
    vector<string> inp_str = InputString(dirpath);

    InputMech_SPtask6 input(inp_str);
    if (!input.checkSucces()) return;

    Graph G(input.getMatrix());

    Task6 T6(G, input.getPare().first, input.getPare().second);
    OutputMech OUT(input.getOutPath(), T6.getRes());
}

void task7(string dirpath) {
    vector<string> inp_str = InputString(dirpath);

    InputMech input(inp_str);
    if (!input.checkSucces()) return;

    AdvancedGraph G(input.getMatrix());

    Task7 T7(G);

    OutputMech OUT(input.getOutPath(), T7.getRes());
}

void task8(string dirpath) {
    vector<string> inp_str = InputString(dirpath);

    InputMech_SPtask8 input(inp_str);
    if (!input.checkSucces()) return;

    Map M(input.getMatrix());

    Task8 T8(M, input.getPare());

    OutputMech OUT(input.getOutPath(), T8.getRes());
}