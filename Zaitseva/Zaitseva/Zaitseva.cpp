#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "input.h"
#include "pipe.h"
#include <unordered_map>
#include "KS.h"
using namespace std;

template<typename T>
int SearchId(const T& map, int id) {
    if (map.find(id) != map.end()) return id;
    return -1;
}

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

void ShowAllKompres(const unordered_map<int, KS>& kompres) {
    cout << "Компрессорные станции" << endl;
    KS::DrawHeader();
    for (auto& [i, k] : kompres) cout << setw(10) << i << k;
}

void EditAllPipes(unordered_map<int, pipe>& pipes) {
    cout << "Введите id трубы, которую хотите изменить: " << endl;
    int id = NumberInput(0);
    if (SearchId(pipes, id) != -1) {
        pipes[id].edit();
        pipe::DrawHeader();
        cout << setw(10) << id << pipes[id] << "Успешное редактирование" << endl;
        return;
    }
    else
        cout << "Такого id не существует " << endl;
}

void EditAllKompres(unordered_map<int, KS>& kompres) {
    cout << "Введите id станции, которую хотите изменить: " << endl;
    int NewCountInWork, id = NumberInput(0);
    if (SearchId(kompres, id) != -1) {
        cout << "Введите количество цехов в работе: " << endl;
        NewCountInWork = NumberInput(0, kompres[id].Count);
        kompres[id].edit(NewCountInWork);
        KS::DrawHeader();
        cout << setw(10) << id << kompres[id] << "Успешное редактирование" << endl;
        return;
    }
    else
        cout << "Такого id не существует " << endl;
}

bool CreateFile(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres, const string& FileName) {
    ofstream fout;
    fout.open(FileName);
    if (!fout.is_open())
        return false;
    if (pipes.size() > 0) {
        fout << "pipe" << endl << pipes.size() << endl << pipe::MaxId << endl;
        for (auto& [i, p] : pipes) {
            fout << i << endl;
            fout << p;
        }
    }
    else
        fout << "nopipe" << endl;
    if (kompres.size() > 0) {
        fout << "kc" << endl << kompres.size() << endl << KS::MaxId << endl;
        for (auto& [i, k] : kompres) {
            fout << i << endl;
            fout << k;
        }
    }
    else
        fout << "nokc" << endl;
    fout.close();
    return true;
}

bool ReadFile(unordered_map<int, pipe>& pipes, unordered_map<int, KS>& kompres, const string& FileName) {
    pipes.clear();
    ifstream fin;
    string input;
    fin.open(FileName);
    if (!fin.is_open())
        return false;
    fin >> input;
    if (input != "nopipe") {
        int n;
        pipe NewPipe;
        int id;
        fin >> n;
        fin >> pipe::MaxId;
        for (int i = 0; i < n; ++i) {
            fin >> id;
            fin >> NewPipe;
            pipes.insert({ id, NewPipe });
        }
    }
    kompres.clear();
    fin >> input;
    if (input != "nokc") {
        KS NewKS;
        int id;
        int n;
        fin >> n;
        fin >> KS::MaxId;
        for (int i = 0; i < n; ++i) {
            fin >> id;
            fin >> NewKS;
            kompres.insert({ id, NewKS });
        }
    }
    return true;
}

template<typename T>
void DeleteElement(T& map, int id) {
    if (map.find(id) != map.end())
        map.erase(id);
}

template<typename T>
void Delete(unordered_map<int, T>& map) {
    cout << endl << "Введите id элемента, который хотите удалить (или 0 чтобы вернуться в меню): ";
    while (true) {
        int id = NumberInput(0);
        if (id == 0) return;
        if (SearchId(map, id) != -1) {
            DeleteElement(map, id);
            cout << "Элемент с id " << id << " удален";
            return;
        }
        else
            cout << "ID не найден, попробуйте еще раз: ";
    }
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    unordered_map<int, pipe> pipes;
    unordered_map<int, KS> kompres;
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
            KS NewKS;
            int NewID = ++NewKS.MaxId;
            cin >> NewKS;
            kompres.insert({ NewID, NewKS });
            break;
        }
        case 3: {
            if (pipes.size() == 0)
                cout << "Трубы не были добавлены, выводить нечего" << endl;
            else
                ShowAllPipes(pipes);
            cout << endl;
            if (kompres.size() == 0)
                cout << "Компрессорные станции не были добавлены, выводить нечего" << endl;
            else
                ShowAllKompres(kompres);
            break;
        }
        case 4: {
            if (pipes.size() > 0) {
                ShowAllPipes(pipes);
                EditAllPipes(pipes);
            }
            else
                cout << "Трубопроводы не были добавлены, редактировать нечего" << endl;
            break;
        }
        case 5: {
            if (kompres.size() > 0) {
                ShowAllKompres(kompres);
                EditAllKompres(kompres);
            }
            else
                cout << "Станции не были добавлены, редактировать нечего" << endl;
            break;
        }
        case 6: {
            cout << "Введите название файла: ";
            string FileName;
            getline(cin, FileName);
            if (CreateFile(pipes, kompres, FileName)) {
                cout << "Данные сохранены в файл" << endl;
            }
            else
                cout << "Не удалось создать файл" << endl;
            break;
        }
        case 7: {
            cout << "Введите название файла: ";
            string FileName;
            getline(cin, FileName);
            if (ReadFile(pipes, kompres, FileName)) {
                cout << "Данные успешно загружены" << endl;
                ShowAllPipes(pipes);
                ShowAllKompres(kompres);
            }
            else
                cout << "Файл " << FileName << " не найден" << endl;
            break;
        }
        case 8: {
            if (pipes.size() > 0) {
                ShowAllPipes(pipes);
                Delete(pipes);
                break;
            }
            else
                cout << "Трубы не были добавлены, удалять нечего" << endl;
            break;
        }
        case 9: {
            if (kompres.size() > 0) {
                ShowAllKompres(kompres);
                Delete(kompres);
                break;
            }
            else
                cout << "Станции не были добавлены, удалять нечего" << endl;
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