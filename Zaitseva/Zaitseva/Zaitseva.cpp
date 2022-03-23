#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //setw
#include <fstream>  //файлы
#include <unordered_map>
#include "pipe.h"
#include "KS.h"
#include "input.h"
#include "Gts.h"
#include "Filter.h"

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
        "11. Соединить трубу " << endl <<
        "12. Удалить связи " << endl <<
        "13. Показать связи " << endl <<
        "14. Топологическая сортировка " << endl <<
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
        if (pipes[id].linked() && pipes[id].repair == 0) {
            cout << "Труба " << id << " включена в сеть, вы уверены, что хотите выключить ее ? (1 - да, 0 - нет)" << endl;
            if (NumberInput(0, 1) == 0) return;
        }
        pipes[id].edit();
        pipe::DrawHeader();
        cout << setw(10) << id << pipes[id] << "Успешное редактирование" << endl;
        return;
    }
    else
        cout << "Такого id не существует " << endl;
}

void EditAllKompres(unordered_map<int, KS>& kompres) {
    int NewCountInWork, id = NumberInput(0);
    cout << "Введите id станции, которую хотите изменить: " << endl;
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
void Delete(unordered_map<int, T>& map) {
    cout << endl << "Введите id элемента, который хотите удалить (или 0 чтобы вернуться в меню): ";
    while (true) {
        int id = NumberInput(0);
        if (id == 0) return;
        if (SearchId(map, id) != -1) {
            if (map.at(id).linked()) {
                cout << "Элемент находится в ГТС, сначала выключите его" << endl;
                return;
            }
            else {
                DeleteElement(map, id);
                cout << "Элемент с id " << id << " удален";
                return;
            }
        }
        else
            cout << "ID не найден, попробуйте еще раз: ";
    }
}

void ShowConnection(const unordered_map<int, pipe>& pipes) {
    for (auto& [i, p] : pipes)
        if (p.linked())
            p.showlink(i);
}

void CreateBranch(unordered_map<int, pipe>& pipes, unordered_map<int, KS>& kompres) {
    cout << "Введите ID трубы, которую нужно связать: " << endl;
    int pipeId = SearchId(pipes, NumberInput(0));
    cout << "Введите ID КС, откуда выходит труба: " << endl;
    int out = SearchId(kompres, NumberInput(0));
    cout << "Введите ID КС, куда входит труба: " << endl;
    int in = SearchId(kompres, NumberInput(0));
    if (pipeId != -1 && pipes[pipeId].in == 0 && pipes[pipeId].out == 0 && out != -1 && in != -1 && out != in) {
        pipes[pipeId].link(in, out);
        kompres[in].createLink();
        kompres[out].createLink();
    }
    else
        cout << "Ошибка" << endl;
}

void DeleteBranches(unordered_map<int, pipe>& pipes, unordered_map<int, KS>& kompres) {
    ShowConnection(pipes);
    cout << "Введите ID трубы, связь которой хотите удалить: " << endl;
    int pipeId = SearchId(pipes, NumberInput(0));
    if (pipeId != -1 && pipes[pipeId].linked()) {
        kompres[pipes[pipeId].in].ClearLink();
        kompres[pipes[pipeId].out].ClearLink();
        pipes[pipeId].ClearLink();
    }
    else
        cout << "Ошибка" << endl;
}

vector<vector<int>> CreateGraph(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres) {
    set<int> vertices;
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed() && kompres.count(p.in) && kompres.count(p.out))
        {
            vertices.insert(p.out);
            vertices.insert(p.in);
        }
    unordered_map<int, int> VerticesIndex;
    int i = 0;
    for (const int& v : vertices)
        VerticesIndex.insert({ v, i++ });
    vector<vector<int>> r;
    r.resize(vertices.size());
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed())
            r[VerticesIndex[p.out]].push_back(VerticesIndex[p.in]);
    return r;
}

int main() {
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
            if (CreateFile(pipes, kompres, "./saves/" + FileName)) {
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
            if (ReadFile(pipes, kompres, "./saves/" + FileName)) {
                cout << "Данные успешно загружены" << endl;
                ShowAllPipes(pipes);
                ShowAllKompres(kompres);
            }
            else
                cout << "Файл " << FileName.erase(0, FileName.find_last_of("/") + 1) << " не найден" << endl;
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
            cout << endl << "Меню фильтров" << endl << "1. Поиск/редактирование труб " << endl << "2. Поиск КС "
                << endl;
            int editCase = NumberInput(0);
            if (editCase == 1) {
                PipeFilterMenu(pipes);
            }
            else if (editCase == 2) {
                KSFilterMenu(kompres);
            }
            break;
        }
        case 11: {
            if (pipes.size() > 0 && kompres.size() > 1)
                CreateBranch(pipes, kompres);
            else
                cout << "Необходимые элементы не были добавлены " << endl;
            break;
        }
        case 12:
        {
            if (pipes.size() > 0 && kompres.size() > 1)
                DeleteBranches(pipes, kompres);
            else
                cout << "Ошибка " << endl;
            break;
        }
        case 13: {
            if (pipes.size() > 0 && kompres.size() > 1)
                ShowConnection(pipes);
            else
                cout << "Ошибка " << endl;
            break;
        }
        case 14:
        {
            vector<vector<int>> r = CreateGraph(pipes, kompres);
            Gts ESG(r);
            set<int> vertices;
            for (const auto& [i, p] : pipes)
                if (p.CanBeUsed() && kompres.count(p.in) && kompres.count(p.out))
                {
                    vertices.insert(p.out);
                    vertices.insert(p.in);
                }
            unordered_map<int, int> VerticesIndex;
            int i = 0;
            for (const int& v : vertices)
                VerticesIndex.insert({ i++, v });
            ESG.TopologicalSort(VerticesIndex);
            break;
        }
        case 0: {
            return 0;
        }
        default: {
            cout << "Такого пункта не существует" << endl;
            break;
        }
        }
        cout << "\n\n\n\n\n\n";
    }
    return 0;
}