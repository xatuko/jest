#pragma comment(lib, "user32")

#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <thread>
#include <fstream>
#include <math.h>

using namespace std;


class Jest
{
    char* name;
    POINT* mas;
    public:
        Jest(int n = 1)
        {
            mas = new POINT[n];
            name = "";
        }
        void hlopok(char* filename)
        {

        }

};

POINT* numbOfPoints(char* filename, int& n)
{ 
    ifstream f;
    f.open(filename, ios::in);
    n = 0;
    int wX, wY;
    POINT* points = new POINT[512];
    points[0].x = points[0].y = 0;
    if(f.is_open())
    {
        POINT buf, beg;
        int lenX = 0, lenY = 0;
        f >> beg.x >> beg.y;
        while(!f.eof())
        {
            f >> buf.x >> buf.y;
            ++n;
            wX = buf.x - beg.x;
            if(abs(wX) > 19)
            {
                if(wX > 0)
                    points[n].x = points[n-1].x+1;
                else
                    points[n].x = points[n-1].x-1;
            }
            else 
                points[n].x = points[n-1].x;
            wY = buf.y - beg.y;
            if(abs(wY) > 19)
            {
                if(wY > 0)
                    points[n].y = points[n-1].y+1;
                else
                    points[n].y = points[n-1].y-1;
            }
            else 
                points[n].y = points[n-1].y;
            beg = buf;
            /*if(abs(buf.x - beg.x) < 20)
                ++lenX;
            else if(lenX > 0)
            {
                ++n;
                points[n].x = points[n-1].x;
                if(beg.y - buf.y < 0)
                    points[n].y = points[n-1].y-1;
                else
                    points[n].y = points[n-1].y+1;
                beg = buf;
                lenX = 0;
                lenY = 0;
            }
            if(abs(buf.y - beg.y) < 20)
                ++lenY;
            else if(lenY > 0)
            {
                ++n;
                if(beg.x - buf.x < 0)
                    points[n].x = points[n-1].x-1;
                else
                    points[n].x = points[n-1].x+1;
                points[n].y = points[n-1].y;
                beg = buf;
                lenY = 0;
                lenX = 0;
            }*/
        }
    }
    ++n;
    f.close();
    return points;
}

POINT* converted(POINT* mas, int n)
{
    int lenX = 0, lenY = 0, nn = 1;
    POINT buf = mas[0];
    for(int i = 1; i < n; ++i)
    {
        if(mas[i].x == buf.x)
            ++lenX;
        else if(lenX > 1)
        {
            ++nn;
            lenX = 0;
            buf = mas[i];
        }
        if(mas[i].y == buf.y)
            ++lenY;
        else if(lenY > 1)
        {
            ++nn;
            lenY = 0;
            buf = mas[i];
        }
    }
    cout << endl <<  nn << endl;
    ++nn;
    POINT* jest = new POINT[nn];
    jest[0].x = jest[0].y = 0;
    nn = 0;
    lenX = lenY = 0;
    buf = mas[0];
    for(int i = 1; i < n; ++i)
    {
        if(mas[i].x == buf.x)
            ++lenX;
        else if(lenX > 1)
        {
            ++nn;
            jest[nn].x = jest[nn-1].x;
            if(mas[i].y - buf.y >= 0)
                jest[nn].y = jest[nn-1].y+1;
            else 
                jest[nn].y = jest[nn-1].y-1;
            lenX = 0;
            buf = mas[i];
        }
        if(mas[i].y == buf.y)
            ++lenY;
        else if(lenY > 1)
        {
            ++nn;
            jest[nn].y = jest[nn-1].y;
            if(mas[i].x - buf.x >= 0)
                jest[nn].x = jest[nn-1].x+1;
            else 
                jest[nn].x = jest[nn-1].x-1;
            lenY = 0;
            buf = mas[i];
        }
    }
    if(lenX > 1)
        {
        ++nn;
        jest[nn].x = jest[nn-1].x;
        if(mas[n-1].y - buf.y >= 0)
            jest[nn].y = jest[nn-1].y+1;
        else 
            jest[nn].y = jest[nn-1].y-1;
        lenX = 0;
    }
    if(lenY > 1)
    {
        ++nn;
        jest[nn].y = jest[nn-1].y;
        if(mas[n-1].x - buf.x >= 0)
            jest[nn].x = jest[nn-1].x+1;
        else 
              jest[nn].x = jest[nn-1].x-1;
        lenY = 0;
    }
    ++nn;
    cout << endl << endl;
    for(int i = 0; i < nn; ++i)
        cout << jest[i].x << '\t' << jest[i].y << endl;
    return jest;
}
