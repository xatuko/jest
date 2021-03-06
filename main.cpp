#include "Jest.h"
ifstream get;
ofstream set, newJest;
int ss = 0;

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

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    BOOL fEatKeystroke = FALSE;
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
    
    switch(wParam)
    {
        case WM_KEYDOWN:
            if(p->vkCode == 162)
            {
                cout << p->vkCode << 'd' << endl;
                ss = 1;
            }
            break;
        case WM_KEYUP:
            if(p->vkCode == 162)
            {
                cout << p->vkCode << 'u' << endl;
                ss = 0;
            }
            break;
        case WM_SYSKEYDOWN:
            if(p->vkCode == 162)
            {
                cout << p->vkCode << 'd' << endl;
                ss = 1;
            }
            break;
        case WM_SYSKEYUP:
            if(p->vkCode == 162)
            {
                cout << p->vkCode << 'u' << endl;
                ss = 0;
            }
            break;
    }
    return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
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
}

