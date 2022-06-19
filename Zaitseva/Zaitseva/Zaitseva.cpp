#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "input.h"
using namespace std;

void DrawMenu() {
    cout << "1. Добавить трубу " << endl <<
        "2. Добавить КС  " << endl <<
        "3. Просмотр всех объектов  " << endl <<
        "4. Редактировать трубу  " << endl <<
        "5. Редактировать КС  " << endl <<
        "6. Сохранить  " << endl <<
        "7. Загрузить  " << endl <<
        "8. Удалить трубу  " << endl <<
        "9. Удалить КС  " << endl <<
        "10. Фильтры/пакетное редактирование " << endl <<
        "0. Выход  " << endl <<
        "Выберите пункт меню: ";
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    char inputmenu;
    while (true) {
        DrawMenu();
        inputmenu = NumberInput(0);
        switch (inputmenu) {
        case 1: {
            cout << "1\n";
            break;
        }
        case 2: {
            cout << "2\n";
            break;
        }
        case 3: {
            cout << "3\n";
            break;
        }
        case 4: {
            cout << "4\n";
            break;
        }
        case 5: {
            cout << "5\n";
            break;
        }
        case 6: {
            cout << "6\n";
            break;
        }
        case 7: {
            cout << "7\n";
            break;
        }
        case 8: {
            cout << "8\n";
            break;
        }
        case 9: {
            cout << "9\n";
            break;
        }
        case 10: {
            cout << "10\n";
            break;
        }
        case 0: {
            cout << "0\n";
            break;
        }
        default: {
            cout << "такого пункта меню нет";
        }
        }
        cout << "\n\n\n\n\n";
    }
    return 0;
}