#include <windows.h>
#include <iostream>

using namespace std;

//functions
int iCreateDir();

int main()
{
    char op;

    cout << "...DIGITE 'M' PARA ACESSAR O MENU..." << endl;

    do{
    cin >> op;
    op = toupper(op);

    switch(op){
    case 'A':
        system("cls");
        cout << "...Create new directory..." << endl;
        int iCreateDir();
        break;
    case 'B':
        system("cls");
        cout << "...Remove directory..." << endl;
        break;
    case 'C':
        system("cls");
        cout << "...Create new file..." << endl;
        break;
    case 'D':
        system("cls");
        cout << "...Remove File..." << endl;
        break;
    case 'E':
        system("cls");
        cout << "...Write File..." << endl;
        break;
    case 'M':
        system("cls");
        cout << "...MENU..." << endl;
        cout << "a...Create new directory..." << endl;
        cout << "b...Remove directory..." << endl;
        cout << "c...Create new file..." << endl;
        cout << "d...Remove File..." << endl;
        cout << "e...Write File..." << endl;
        break;
    default:
        cout << "invalid!" << endl;
        break;
    }

    }while((op != 'A') || (op != 'B') || (op != 'C') || (op != 'D') || (op != 'E') || (op != 'M'));

    return 0;
}

int iCreateDir()
{

    BOOL bDir;
    bDir = CreateDirectory("c:\\filemanipulation", NULL);

    if(bDir == FALSE)
    {
        cout << "CreateDirectory - failed & error:  " << GetLastError() <<  endl;
    }else
    {
        cout << "CreateDirectory - sucess..." << endl;
    }
}

int iRemoveDir()
{








    return 0;
}
