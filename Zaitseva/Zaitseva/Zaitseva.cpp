#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "input.h"
#include "pipe.h"
#include <unordered_map>
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

void ShowAllPipes(const unordered_map<int, pipe>& pipes) {
    cout << "Трубопроводы" << endl;
    pipe::DrawHeader();
    for (auto& [i, p] : pipes) cout << setw(10) << i << p;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    unordered_map<int, pipe> pipes; 
    char inputmenu;
    while (true) {
        DrawMenu();
        inputmenu = NumberInput(0);
        switch (inputmenu) {
        case 1: {
            pipe NewPipe;
            int NewID = ++NewPipe.MaxId;
            cin >> NewPipe;
            pipes.insert({ NewID, NewPipe });
            break;
        }
        case 2: {
            cout << "2\n";
            break;
        }
        case 3: {
            if (pipes.size() == 0)
                cout << "Трубы не были добавлены, выводить нечего" << endl;
            else
                ShowAllPipes(pipes);
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