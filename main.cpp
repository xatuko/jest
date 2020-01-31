#include "fun.cpp"

void main()
{
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    strcpy(status, "procced");
    thread tr = thread(getMove);
    thread tr1 = thread(startHook);
    
    
    //char command[128];
    //cout << " >> ";
    //cin.getline(command, 128);
    
    
    //hooker.join();
    //while(strcmp(command, "quit") != 0)
    /*{
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
        //cin.getline(command, 128);
        Sleep(10);
    }*/
    while(1)
        Sleep(1);
    
    SendMessage(GetConsoleWindow(), WM_CLOSE, NULL, NULL);
}