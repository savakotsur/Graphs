#pragma once
#include "../Map.h"
#define INF 1000000000

using namespace std;
class Evristic {
   public:
    Evristic();
    virtual ~Evristic();
    virtual int evristic(Cell a, Cell b) = 0;
};

class Manhetten : public Evristic {
   public:
    Manhetten();
    int evristic(Cell a, Cell b) override;
};
class Evclid : public Evristic {
   public:
    Evclid();
    int evristic(Cell a, Cell b) override;
};
class Chebushev : public Evristic {
   public:
    Chebushev();
    int evristic(Cell a, Cell b) override;
};
class Zero : public Evristic {
   public:
    Zero();
    int evristic(Cell a, Cell b) override;
};

class Task8 {
   private:
    Map* map_forTask;
    int size;
    string res_str;

    Cell* st;
    Cell* end;

    vector<Cell> path;
    int lenth = 0;
    int viewed = 0;

    void Astar(Evristic* h);

    void setRes(int par);

   public:
    Task8(Map& G, pair<pair<int, int>, pair<int, int>> p);
    ~Task8();
    string getRes();
};
