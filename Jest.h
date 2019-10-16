#pragma comment(lib, "user32")

#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <thread>
#include <fstream>
#include <math.h>
#include <string>
using namespace std;

class Jest
{
    char action[256];
    POINT *mas;
    int numbOfPoints;

public:
    Jest() {}
    Jest(int n, POINT* mas)
    {
        numbOfPoints = n;
        this->mas = mas;
    }
    void fillMas(POINT* points)
    {
        for(int i = 0; i < numbOfPoints; i++)
            mas[i] = points[i];
    }
    friend bool operator ==(const Jest &j1, const Jest &j2)
    {
        if(j1.numbOfPoints != j2.numbOfPoints)
            return false;
        for(int i = 0; i < j1.numbOfPoints; i++)
            if(j1.mas[i].x != j2.mas[i].x || j1.mas[i].y != j2.mas[i].y)
                return false;
        return true;
    }
    friend class ListOfJest;
};

class ListOfJest
{
    int numbOfMoves;
    Jest* list;
public:
    ListOfJest()
    {
        ifstream moves;
        moves.open("moves.txt", ios::in);
        moves >> numbOfMoves;
        list = new Jest[numbOfMoves];
        int n;
        for(int i = 0; i < numbOfMoves && !moves.eof(); i++)
        {
            moves >> list[i].numbOfPoints;
            list[i].mas = new POINT[list[i].numbOfPoints];
            for(int j = 0; j < list[i].numbOfPoints; j++)
            {
                moves >> list[i].mas[j].x;
                moves >> list[i].mas[j].y;
            }
            char a;
            moves >> a;
            moves >> list[i].action; 
        }
    }
    char* getAction(Jest j)
    {
        for(int i = 0; i < numbOfMoves; i++)
            if(list[i] == j)
                return list[i].action;
        return NULL;
    }
};
