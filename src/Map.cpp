#include "Map.h"

Map::Map(vector<vector<int>> m) {
    matrix = m;
    size = matrix.size();
}

int Map::getHeight(int x, int y) { return matrix[x][y]; }

int Map::getSize() { return size; }

int Map::distance(Cell a, Cell b) {
    return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY()) +
           abs(getHeight(a.getX(), a.getY()) - getHeight(b.getX(), b.getY()));
}

vector<Cell> Map::neighbours(Cell c) {
    vector<Cell> neighbours;

    if (c.getX() + 1 != matrix.size()) neighbours.push_back(Cell(c.getX() + 1, c.getY()));

    if (c.getY() + 1 != matrix.size()) neighbours.push_back(Cell(c.getX(), c.getY() + 1));

    if (c.getX() != 0) neighbours.push_back(Cell(c.getX() - 1, c.getY()));

    if (c.getY() != 0) neighbours.push_back(Cell(c.getX(), c.getY() - 1));

    return neighbours;
}

Cell::Cell(int x, int y) {
    X = x;
    Y = y;
}

int Cell::getX() { return X; }

int Cell::getY() { return Y; }
