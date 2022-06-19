#include <iostream>
#include <string>
#include <conio.h>
#include <sstream>
#include <vector>

using namespace std;


struct pipe {
    unsigned int id;
    double length, diameter;
    bool repair;
};
vector<pipe> pipes;


int main()
{
    setlocale(LC_CTYPE, "Russian");
    string s;
    int input_menu;
    pipes.resize(0);
    while (true)
    {
        system("cls");
        cout << "1. Добавить трубу \n2. Добавить КС \n3. Просмотр всех объектов \n4. Редактировать трубу \n5. Редактировать КС \n6. Сохранить \n7. Загрузить \n0. Выход \n";
        input_menu = _getch();
        switch (input_menu)
        {
        case '1':
            system("cls");
            cout << "1\n";
            cin >> s;
            break;
        case '2':
            system("cls");
            cout << "2\n";
            cin >> s;
            break;
        case '3':
            system("cls");
            cout << "3\n";
            cin >> s;
            break;
        case '4':
            system("cls");
            cout << "4\n";
            cin >> s;
            break;
        case '5':
            system("cls");
            cout << "5\n";
            cin >> s;
            break;
        case '6':
            system("cls");
            cout << "6\n";
            cin >> s;
            break;
        case '7':
            system("cls");
            cout << "7\n";
            cin >> s;
            break;
        case '0':
            system("cls");
            cout << "0\n";
            cin >> s;
            break;
        }
    }
    return 0;
}