#pragma once
#include<vector>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;
class Cell {
private:
    int X;
    int Y;
public:
    pair<int,int> offset;
    int distanceFromSt = 0;
    int weight = 0;
    
    Cell(int x, int y);
    int getX();
    int getY();
};

class Map
{
private:
    vector<vector<int>> matrix;
    int size;
public:
    Map(vector<vector<int>> m);
    int getHeight(int x, int y);
    int getSize();
    int distance(Cell a, Cell b);
    vector<Cell> neighbours(Cell c);
};
