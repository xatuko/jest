#include "Header.h"

void converted(int n = 0)
{
    ifstream temp;
    temp.open("temp.txt", ios::in);
    ofstream move;
    move.open("converteted.txt", ios::out | ios::trunc);
    POINT beg, pt, buf;
    buf.x = buf.y = 0;
    int lenX = 0, lenY = 0;
    temp >> beg.x >> beg.y;
    move << buf.x << '\t' << buf.y << endl;
    cout << buf.x << '\t' << buf.y << endl;
    while (!temp.eof())
    {
        temp >> pt.x >> pt.y;
        if (pt.x == beg.x)
            ++lenX;
        else if (lenX > 1)
        {
            if (pt.y - beg.y >= 0)
                ++buf.y;
            else
                --buf.y;
            lenX = 0;
            beg = pt;
            move << buf.x << '\t' << buf.y << endl;
        }
        if (pt.y == beg.y)
            ++lenY;
        else if (lenY > 1)
        {
            if (pt.x - beg.x >= 0)
                ++buf.x;
            else
                --buf.x;
            lenY = 0;
            beg = pt;
            move << buf.x << '\t' << buf.y << endl;
        }
    }
    if (lenX > 1)
    {
        if (pt.y - beg.y >= 0)
            ++buf.y;
        else
            --buf.y;
        move << buf.x << '\t' << buf.y << endl;
    }
    if (lenY > 1)
    {
        if (pt.x - beg.x >= 0)
            ++buf.x;
        else
            --buf.x;
        move << buf.x << '\t' << buf.y << endl;
    }
    temp.close();
    move.close();
}

POINT* getJest(int &n)
{
    ifstream move;
    move.open("converteted.txt", ios::in);
    POINT buf[32], *jest;
    n = 0;
    while(!move.eof())
    {
        move >> buf[n].x >> buf[n].y;
        ++n;
    }
    --n;
    jest = new POINT[n];
    for(int i = 0; i < n; i++)
        jest[i] = buf[i];
    move.close();
    return jest; 
}

void getEvent(char* action)
{
    if(!strcmp(action, "show"))
        ShowWindow(GetConsoleWindow(), SW_SHOW);
    if(!strcmp(action, "showcmd"))
        system("start cmd.exe");
    if(!strcmp(action, "showcalc"))
        system("start calc.exe");
    if(!strcmp(action, "showreg"))
        system("start regedit.exe");
        
}


void unkJest(Jest j)
{
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    cout << endl << endl << "Unknown movement. Do you want do add new action for it? (y/n)";
    char ans;
    cin >> ans;
    if(ans == 'y')
    {
        cout << endl << "Specify the location of the .exe file which should be run after this movement: ";
        char path[256];
        cin >> path;
        j.setAction(path);
        list.addMove(j);
    }
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void event()
{
    int n;
    POINT* mas = getJest(n);
    Jest j(n, mas);
    char* action = list.getAction(j);
    if(action != NULL)
        getEvent(action);
    else
        unkJest(j);
}

void getMove()
{
    temp.open("temp.txt", ios::out);
    int n = 0, wX, wY;
    POINT pt, buf, beg;
    while(!strcmp(status, "procced"))
    {
        if( keyStatus == 1)
        {
            if(n == 0)
            {
                GetCursorPos(&pt);
                temp << 0 << '\t' << 0 << endl;
                ++n;
                beg = pt;
                buf.x = 0;
                buf.y = 0;
            }
            else
            {
                GetCursorPos(&pt);
                if(abs(pt.x - beg.x) > 20  || abs(pt.y - beg.y) > 20)
                {
                    wX = pt.x - beg.x;
                    if(abs(wX) > 19)
                    {
                        if(wX > 0)
                            ++buf.x;
                        else
                            --buf.x;
                    }
                    wY = pt.y - beg.y;
                    if(abs(wY) > 19)
                    {
                        if (wY > 0)
                            ++buf.y;
                        else
                            --buf.y;  
                    }
                    beg = pt;
                    temp << buf.x << '\t' << buf.y << endl;
                }
            }
        }
        Sleep(1);
    }
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    BOOL fEatKeystroke = FALSE;
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam; // 162 - ctrl
    if(nCode == HC_ACTION && p->vkCode == 162)
    {
        switch(wParam)
        {
            case WM_KEYDOWN:
                keyStatus = 1;
                break;
            case WM_KEYUP:
                keyStatus = 0;
                temp.close();
                converted();
                remove("temp.txt");
                temp.open("temp.txt", ios::out);
                event();
                break;
            case WM_SYSKEYDOWN:
                break;
            case WM_SYSKEYUP:
                break;
        }
    }
    return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

void startHook()
{
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    if(!hhkLowLevelKybd)
    {
        cout << endl << "unable to hook keyboard" << endl;
        return;
    }
    MSG msg;
    int igetok = 0;
    while (igetok = GetMessage(&msg, NULL, NULL, NULL) != 0) {    //this while loop keeps the hook
        TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }
    UnhookWindowsHookEx(hhkLowLevelKybd);
}

int convCom(char* command)
{
    if(!strcmp(command, "hide"))
        return 1;
    if(!strcmp(command, "add new move"))
        return 2;
    if(!strcmp(command, "delete move"))
        return 3;
    if(!strcmp(command, "disp moves"))
        return 4; 
    if(!strcmp(command, "start"))
        return 5; 
    return -1;
}