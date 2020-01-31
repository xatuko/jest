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
    void setAction(char* action)
    {
        strcpy(this->action, action);
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

    Jest& operator=(const Jest& jest)
    {
        strcpy(this->action, jest.action);
        this->mas = jest.mas;
        this->numbOfPoints = jest.numbOfPoints;
        return *this;
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
        moves.close();
    }

    void addMove(Jest j)
    {
        Jest* newlist = new Jest[++numbOfMoves];
        int i = 0;
        for(; i < numbOfMoves-1; i++)
            newlist[i] = list[i];
        newlist[i] = j;
        list = newlist;
        rewrite();
    }

    void rewrite()
    {
        ofstream newmoves;
        newmoves.open("nmoves.txt", ios::out);
        newmoves << numbOfMoves << endl;
        for(int i = 0; i < numbOfMoves; i++)
        {
            int nop = list[i].numbOfPoints;
            newmoves << nop << ' ';
            for(int j = 0; j < nop; j++)
                newmoves << list[i].mas[j].x << ' ' << list[i].mas[j].y << ' ';
            newmoves << ": " << list[i].action << endl;
        }
        newmoves.close();
        remove("moves.txt");
        rename("nmoves.txt", "moves.txt");
    }

    char* getAction(Jest j)
    {
        for(int i = 0; i < numbOfMoves; i++)
            if(list[i] == j)
                return list[i].action;
        return NULL;
    }

    Jest& operator[](const int index)
    {
        return list[index];
    }

    ListOfJest& operator=(const ListOfJest& list)
    {
       this->numbOfMoves = list.numbOfMoves;
       this->list = list.list;
       return *this;
    }
};
