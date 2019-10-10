#include "Jest.h"

ofstream temp;
int keyStatus = 0;
char  status[128];
/*
void saveMove()
{
    
    set.open("move.txt", ios::out|ios::trunc);
    POINT pt, buf;
    int i = 0;
    while(true)
        if(ss == 1)
        {
            if(i == 0)
            {
                GetCursorPos(&pt);
                set << pt.x << '\t' << pt.y << endl;
                i++;
                buf = pt;
            }
            else
            {
                GetCursorPos(&pt);
                if(abs(pt.x - buf.x) > 20  || abs(pt.y - buf.y) > 20)
                {
                    set << pt.x << '\t' << pt.y << endl;
                    buf = pt;
                }
            }
        }
    set.close();
}



void main()
{
    system("C:\\Windows\\system32\\notepad.exe");
    int t, n;
    cout << "its time to choose: "<< endl;
    cin >> t;

    while(t != 0)
    {
        thread thr;
        HHOOK hhkLowLevelKybd;
        switch(t)
        {
            case 1:
                thr = thread(saveMove);
                
                // Install the low-level keyboard & mouse hooks
                hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

                // Keep this app running until we're told to stop
                MSG msg;
                while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                }

                UnhookWindowsHookEx(hhkLowLevelKybd);
                break;
            case 2:
                char* filename = "move.txt";
                POINT* points = numbOfPoints(filename, n);
                newJest.open("new.txt", ios::out | ios::trunc);
                for(int i = 0; i < n; i++)
                {
                    newJest << points[i].x << '\t' << points[i].y << endl;
                    cout << points[i].x << '\t' << points[i].y << endl;
                }
                converted(points, n);
                _getch();
            break;
        }
        cout << "its time to choose: "<< endl;
        cin >> t;
    }
}*/

void getMove()
{
    temp.open("temp.txt", ios::out);
    int n = 0;
    POINT pt, buf;
    while(!strcmp(status, "procced"))
    {
        if(keyStatus)
        {
            if(n == 0)
            {
                GetCursorPos(&pt);
                temp << pt.x << '\t' << pt.y << endl;
                n++;
                buf = pt;
            }
            else
            {
                GetCursorPos(&pt);
                if(abs(pt.x - buf.x) > 20  || abs(pt.y - buf.y) > 20)
                {
                    temp << pt.x << '\t' << pt.y << endl;
                    buf = pt;
                }
            }
        }
    }
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    BOOL fEatKeystroke = FALSE;
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam; // 162 - ctrl
    if(nCode == HC_ACTION)
    {
        switch(wParam)
        {
            case WM_KEYDOWN:
                if(p->vkCode == 162)
                    keyStatus = 1;
                break;
            case WM_KEYUP:
                if(p->vkCode == 162)
                {
                    keyStatus = 0;
                    int n;
                    POINT* mas = numbOfPoints("temp.txt", n);
                    for(int i = 0; i < n; i++)
                        cout << mas[i].x << '\t' << mas[i].y << endl;
                    temp.close();
                    temp.open("temp.txt", ios::trunc);
                    temp.close();
                    temp.open("temp.txt", ios::out);
                    POINT* conv = converted(mas,n);
                    for(int i = 0; i < n; i++)
                        cout << conv[i].x << '\t' << conv[i].y << endl;
                }
                break;
            case WM_SYSKEYDOWN:
                break;
            case WM_SYSKEYUP:
                break;
        }
    }
    return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
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

void startHook()
{
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    if(!hhkLowLevelKybd)
    {
        cout << endl << "unable to hook keyboard" << endl;
        return;
    }
    thread mouse(getMove);
    MSG msg;
    while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hhkLowLevelKybd);
    mouse.join();
}



void main()
{
    thread hooker;
    char command[128];
    cout << " >> ";
    cin.getline(command, 128);
    while(strcmp(command, "quit") != 0)
    {
        switch(convCom(command))
        {
            case 1:
                ShowWindow(GetConsoleWindow(), SW_HIDE);
                break;
            case 2:
                cout << "added" << endl;
                break;
            case 3:
                cout << "deleted" << endl;
                break;
            case 4:
                cout << "disped" << endl;
                break;
            case 5:
                strcpy(status, "procced");
                hooker = thread(startHook);
                break;
            default:
                cout << "unknown command" << endl;
                break;
        }  
        cout << " >> ";
        cin.getline(command, 128);
    }
    SendMessage(GetConsoleWindow(), WM_CLOSE, NULL, NULL);
}