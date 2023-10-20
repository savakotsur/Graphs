#include "Task8.h"
class Evristic;
class Manhetten;
void Task8::Astar(Evristic* h) {
    vector<Cell> path = {};
    vector<Cell> openCells = {*st};
    vector<Cell> closedCells;

    Cell curr = *st;
    curr.offset = make_pair(0, 0);

    while (curr.getX() != end->getX() || curr.getY() != end->getY()) {
        int min = INF;
        int minIndex = -1;
        for (int i = 0; i < openCells.size(); i++) {
            Cell c = openCells[i];
            if (c.weight < min) {
                min = c.weight;
                minIndex = i;
            }
        }

        curr = openCells[minIndex];

        openCells.erase(openCells.begin() + minIndex);
        closedCells.push_back(curr);

        vector<Cell> neighbours = map_forTask->neighbours(curr);

        for (auto& n : neighbours) {
            if (find_if(closedCells.begin(), closedCells.end(), [&](Cell r) {
                    return n.getX() == r.getX() && n.getY() == r.getY();
                }) != closedCells.end())
                continue;

            auto it = find_if(openCells.begin(), openCells.end(),
                              [&](Cell r) { return n.getX() == r.getX() && n.getY() == r.getY(); });
            if (it != openCells.end()) {
                int newD = curr.distanceFromSt + map_forTask->distance(curr, n);

                if (n.distanceFromSt > newD) {
                    n.distanceFromSt = newD;
                    n.offset = make_pair(n.getX() - curr.getX(), n.getY() - curr.getY());
                    n.weight = n.distanceFromSt + h->evristic(n, *end);
                }
            } else {
                n.offset = make_pair(n.getX() - curr.getX(), n.getY() - curr.getY());
                n.distanceFromSt = curr.distanceFromSt + map_forTask->distance(curr, n);
                n.weight = n.distanceFromSt + h->evristic(n, *end);
                openCells.push_back(n);
            }
        }
    }

    lenth = curr.distanceFromSt;

    while (curr.offset != make_pair(0, 0)) {
        path.push_back(curr);
        auto it = find_if(closedCells.begin(), closedCells.end(), [&](Cell r) {
            return curr.getX() - curr.offset.first == r.getX() &&
                   curr.getY() - curr.offset.second == r.getY();
        });
        curr = *it;
    }
    path.push_back(curr);
    reverse(path.begin(), path.end());

    this->path = path;
    viewed = closedCells.size();
}

void Task8::setRes(int par) {
    string res_str = "";

    switch (par) {
        case 0:
            res_str += "Manhetten:\n";
            break;
        case 1:
            res_str += "Evclid:\n";
            break;
        case 2:
            res_str += "Chebushev:\n";
            break;
        case 3:
            res_str += "Zero:\n";
            break;
    }

    res_str += to_string(lenth) + " - length of path between " + "(" + to_string(st->getX()) + ", " +
               to_string(st->getY()) + ") and " + "(" + to_string(end->getX()) + ", " +
               to_string(end->getY()) + ") points.\n";

    res_str += "Path:\n[ ";

    for (auto c : path) {
        res_str += "(" + to_string(c.getX()) + ", " + to_string(c.getY()) + ") ";
    }

    res_str += "]\n";

    res_str += "Percent of viewed cells is " + to_string(100 * double(viewed / pow(size, 2))) + "\n\n";

    this->res_str += res_str;
}

Task8::Task8(Map& M, pair<pair<int, int>, pair<int, int>> p) {
    map_forTask = &M;

    size = map_forTask->getSize();

    st = new Cell(p.first.first, p.first.second);
    end = new Cell(p.second.first, p.second.second);

    Manhetten();

    Evristic* h[4] = {new Manhetten(), new Evclid(), new Chebushev(), new Zero()};

    for (int i = 0; i < 4; i++) {
        Astar(h[i]);
        setRes(i);
    }

    for (int i = 0; i < 4; i++) {
        delete h[i];
    }
}

Task8::~Task8() {
    delete st;
    delete end;
}

string Task8::getRes() { return res_str; }

Manhetten::Manhetten() : Evristic() {}

int Manhetten::evristic(Cell a, Cell b) {
    return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY());
    ;
}

Evclid::Evclid() : Evristic() {}

int Evclid::evristic(Cell a, Cell b) {
    return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
}

Chebushev::Chebushev() : Evristic() {}

int Chebushev::evristic(Cell a, Cell b) { return fmax(abs(a.getX() - b.getX()), abs(a.getY() - b.getY())); }

Zero::Zero() : Evristic() {}

int Zero::evristic(Cell a, Cell b) { return 0; }

Evristic::Evristic() {}

Evristic::~Evristic() = default;
