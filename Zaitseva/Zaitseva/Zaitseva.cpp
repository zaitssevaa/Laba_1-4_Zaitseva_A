#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //setw
#include <fstream>  //файлы
#include <ctime> // для рандомных id
#include <unordered_map>
#include <set>
#include "Pipe.h"
#include "KS.h"
#include "input.h"
#include "Gts.h"

using namespace std;

template<typename T>
int SearchId(const T& map, int id) {
    if (map.find(id) != map.end()) return id;
    return -1;
}

bool SearchIdInVector(const vector<int>& vec, int id) {
    for (auto& v : vec)
        if (v == id)
            return 1;
    return 0;
}

template<typename T>
int CreateID(const T& map) {
    int NewID;
    do {
        srand((int)time(0));
        NewID = 1 + rand() % 1000;
    } while (SearchId(map, NewID) != -1);
    return NewID;
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
        "12. Показать связи " << endl <<
        "0. Выход  " << endl <<
        "Выберите пункт меню: ";
}

void ShowAllPipes(const unordered_map<int, pipe>& pipes){
    cout << "Трубопроводы" << endl;
    pipe::DrawHeader(); 
    for (auto& p : pipes) cout << setw(10) << p.first << p.second;
}

void ShowAllKompres(const unordered_map<int, KS>& kompres){
    cout << "Компрессорные станции" << endl;
    KS::DrawHeader();
    for (auto& k : kompres) cout << setw(10) << k.first << k.second;
}

void EditAllPipes(unordered_map<int, pipe>& pipes) {
    cout << "Введите id трубы, которую хотите изменить: " << endl;
    int id = input::NumberInput(0);
    if (SearchId(pipes, id) != -1) {
        pipes[id].edit();
        pipe::DrawHeader();
        cout << setw(10) << id << pipes[id] << "Успешное редактирование" << endl;
        return;
    } else
        cout << "Такого id не существует " << endl;
}

void EditAllKompres(unordered_map<int, KS>& kompres) {
    int NewCountInWork, id = input::NumberInput(0);
    cout << "Введите id станции, которую хотите изменить: " << endl;
    if (SearchId(kompres, id) != -1) {
        cout << "Введите количество цехов в работе: " << endl;
        NewCountInWork = input::NumberInput(0, kompres[id].Count);
        kompres[id].edit(NewCountInWork);
        KS::DrawHeader();
        cout << setw(10) << id << kompres[id] << "Успешное редактирование" << endl;
        return;
    }else
        cout << "Такого id не существует " << endl;
}

bool CreateFile(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres, const string& FileName) {
    ofstream fout;
    fout.open(FileName);
    if (!fout.is_open())
        return false;
    if (pipes.size() > 0) {
        fout << "pipe" << endl << pipes.size() << endl;
        for (auto& p : pipes) {
            fout << p.first << endl;
            fout << p.second;
        }
    }else
        fout << "nopipe" << endl;
    if (kompres.size() == 0) {
        fout << "kc" << endl << kompres.size() << endl;
        for (auto& k : kompres) {
            fout << k.first << endl;
            fout << k.second;
        }
    }else
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
        fin >> n;
        for (int i = 0; i < n; ++i) {
            pipe NewPipe;
            int id;
            fin >> id;
            fin >> NewPipe;
            pipes.insert({ id, NewPipe });
        }
    }
    kompres.clear();
    fin >> input;
    if (input != "nokc") {
        int n;
        fin >> n;
        for (int i = 0; i < n; ++i) {
            KS NewKS;
            int id;
            fin >> id;
            fin >> NewKS;
            kompres.insert({ id, NewKS });
        }
    }
    return true;
}

// Удаление
template<typename T>
void DeleteElement(T& map, int id) {
    if (map.find(id) != map.end()) 
        map.erase(id);
}

template<typename T>
void Delete(T& map) {
    cout << endl << "Введите id элемента, который хотите удалить (или 0 чтобы вернуться в меню): ";
    while (true) {
        int id = NumberInput(0);
        if (id == 0) return;
        if (SearchId(map, id) != -1) {
            DeleteElement(map, id);
            cout << "Элемент с id " << id << " удален";
            return;
        } else
            cout << "ID не найден, попробуйте еще раз: ";
    }
}

// Фильтры
template<typename T>
bool CheckByName(const T& map, string param) {
    return map.Name == param;
}

bool CheckByRepair(const pipe& pipe, bool param) {
    return pipe.repair == param;
}

bool CheckByPercent(const KS& kompres, double param) {
    return round(100 * (1. * (kompres.Count - kompres.CountInWork) / kompres.Count)) == param;
}

template<typename T, typename T_param>
using Filter = bool (*)(const T& map, T_param param);

template<typename T, typename T_param>
vector<int> FindByFilter(const unordered_map<int, T>& map, Filter<T, T_param> f, T_param param) {
    vector<int> res;
    for (auto& m : map)
        if (f(m.second, param))
            res.push_back(m.first);
    return res;
}

template <typename T>
void PrintFindResult(const unordered_map<int, T>& map, const vector<int>& index) {
    if (index.size() != 0) {
        cout << "Найдено " << index.size() << " элементов" << endl;
        T::DrawHeader();
        for (auto& id : index)
            cout << setw(10) << id << map.at(id);
    }else
        cout << "Ничего не найдено " << endl;
}

template <typename T>
vector<int> FindByName(const unordered_map<int, T>& map) {
    cout << "Введите имя, которое нужно найти: " << endl;
    vector<int> index = FindByFilter(map, CheckByName, input::StrInput());
    PrintFindResult(map, index);
    return index;
}

vector<int> FindByRepair(const unordered_map<int, pipe>& pipes) {
    cout << "Какие трубы нужно искать (1 - в ремонте, 0 - не в ремонте): " << endl;
    vector<int> index = FindByFilter(pipes, CheckByRepair, bool(NumberInput(0, 1)));
    PrintFindResult(pipes, index);
    return index;
}

vector<int> FindByPercent(const unordered_map<int, KS> kompres) {
    cout << "Введите процент нерабочих цехов: " << endl;
    vector<int> index = FindByFilter(kompres, CheckByPercent, input::NumberInput(0., 100.));
    PrintFindResult(kompres, index);
    return index;
}

void EditingAfterFind(unordered_map<int, pipe>& pipes, vector<int> index) {
    cout << "1. Редактировать найденые " << endl << "2. Выбрать и редактировать " << endl << "3. Удалить найденные"
        << endl << "4. Выбрать и удалить" << endl << "0. Выход" << endl;
    int casemenu = NumberInput(0, 4);
    if (casemenu == 1) {
        for (auto& id : index)
            pipes[id].edit();
    } else if (casemenu == 2) {
        cout << "Введите Id (0-конец ввода) " << endl;
        int input;
        set<int> edit_id;
        do {
            input = NumberInput(0);
            if (SearchIdInVector(index, input) == 1)
                edit_id.insert(input);
        } while (input != 0);
        for (auto& id : edit_id)
            pipes[id].edit();
    } else if (casemenu == 3) {
        for (auto& id : index)
            DeleteElement(pipes, id);
    } else if (casemenu == 4) {
        cout << "Введите Id (0-конец ввода) " << endl;
        int input;
        set<int> edit_id;
        do {
            input = NumberInput(0);
            if (SearchIdInVector(index, input) == 1)
                edit_id.insert(input);
        } while (input != 0);
        for (auto& id : edit_id)
            DeleteElement(pipes, id);
    }
}

void PipeFilterMenu(unordered_map<int, pipe>& pipes) {
    if (pipes.size() == 0) {
        cout << "Трубы не добавлены " << endl;
        return;
    }
    cout << endl << "Фильтр/редактирование труб" << endl << "1. Поиск труб по названию" << endl
        << "2. Поиск труб по признаку в ремонте " << endl << "0. Выход" << endl;
    int FilterCase = NumberInput(0, 2);
    if (FilterCase == 1) {
        vector<int> index = FindByName(pipes);
        if (index.size() != 0)
            EditingAfterFind(pipes, index);
        return;
    } else if (FilterCase == 2) {
        vector<int> index = FindByRepair(pipes);
        if (index.size() != 0)
            EditingAfterFind(pipes, index);
        return;
    }
}

void KSFilterMenu(unordered_map<int, KS>& kompres) {
    if (kompres.size() == 0) {
        cout << "Трубы не добавлены " << endl;
        return;
    }
    cout << endl << "Фильтр по КС" << endl << "1. Поиск КС по названию" << endl
        << "2. Поиск КС по проценту незадействованных цехов" << endl;
    int FilterCase = input::NumberInput(1, 2);
    if (FilterCase == 1) {
        FindByName(kompres);
    } else if (FilterCase == 2) {
        FindByPercent(kompres);
    }
    return;
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
            int NewID = CreateID(pipes);
            pipe NewPipe;
            cin >> NewPipe;
            pipes.insert({ NewID, NewPipe });
            break;
        }
        case 2: {
            int NewID = CreateID(kompres);
            KS NewKS;
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
            FileName = "./saves/" + FileName;
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
            FileName = "./saves/" + FileName;
            if (ReadFile(pipes, kompres, FileName)) {
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
            if (pipes.size() > 0 && kompres.size() > 1) {
                cout << "Введите ID трубы, которую нужно связать: " << endl;
                int pipeId = SearchId(pipes, NumberInput(0));
                cout << "Введите ID КС, откуда выходит труба: " << endl;
                int out = SearchId(kompres, NumberInput(0));
                cout << "Введите ID КС, куда входит труба: " << endl;
                int in = SearchId(kompres, NumberInput(0));
                if (pipeId != -1) {
                    pipes[pipeId].link(in, out);
                }
                else
                    cout << "Ошибка" << endl;
            }
            else
                cout << "Необходимые элементы не были добавлены " << endl;
            break;
        }
        case 12: {
            if (pipes.size() > 0 && kompres.size() > 1) {
                for (auto& [i, p] : pipes)
                    if (p.islinked())
                        p.showlink(i);
            }
            else
                cout << "Ошибка " << endl;
            break;
        }
               //case 13:
               //{
               //    set<int> vertices;
               //    for (const auto& [i, p] : pipes)
               //        if (p.CanBeUsed() && kompres.count(p.in) && kompres.count(p.out))
               //        {
               //            vertices.insert(p.out);
               //            vertices.insert(p.in);
               //        }
               //    unordered_map<int, int> VerticesIndex, VerticesIndexReverse;
               //    int i = 0;
               //    for (const int& v : vertices) {
               //        VerticesIndex.insert({ i, v });
               //        VerticesIndexReverse.insert({ v,i++ });
               //    }
               //    vector<vector<int>> r;
               //    r.resize(vertices.size());
               //    for (const auto& p : pipes)
               //        if (p.second.CanBeUsed())
               //            r[VerticesIndexReverse[p.second.out]].push_back(VerticesIndexReverse[p.second.in]);
               //    Gts ESG(r);
               //    if (ESG.Cyclical() == false)
               //        cout << "no";
               //    else cout << "yes";
               //    break;
               //}
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
