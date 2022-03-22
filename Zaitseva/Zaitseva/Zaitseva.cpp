#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //setw
#include <fstream>  //файлы
#include <ctime> // для рандомных id
#include <unordered_map>
#include "Pipe.h"
#include "KS.h"
#include "input.h"

using namespace std;

template<typename T>
int SearchId(const T& map, int id) {
    if (map.find(id) != map.end()) return id;
    return -1;
}

template<typename T>
int CreateID(const T& map) {
    int NewID;
    do {
        srand((int)time(0));
        NewID = rand();
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

void DrawHeader(bool type) {
    if (type)
        cout << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(20)
        << "В ремонте" << endl;
    else
        cout << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Кол-во цехов" << setw(20) << "Цехов в работе"
        << setw(20) << "Эффективность" << endl;
}

void ShowAllPipes(const unordered_map<int, pipe>& pipes){
    cout << "Трубопроводы" << endl;
        DrawHeader(1); 
    for (auto& p : pipes) cout << setw(10) << p.first << p.second;
}

void ShowAllKompres(const unordered_map<int, KS>& kompres){
    cout << "Компрессорные станции" << endl;
    DrawHeader(0);
    for (auto& k : kompres) cout << setw(10) << k.first << k.second;
}

void EditAllPipes(unordered_map<int, pipe>& pipes) {
    int id;
    cout << "Введите id трубы, которую хотите изменить: " << endl;
    while (true) {
        id = NumberInput(0);
        if (SearchId(pipes, id) != -1) {
            pipes[id].edit();
            DrawHeader(1);
            cout << setw(10) << id << pipes[id];
            cout << "Успешное редактирование" << endl;
            return;
        } else
            cout << "Такого номера не существует, попробуйте еще раз: " << endl;
    }
}

void EditAllKompres(unordered_map<int, KS>& kompres) {
    int NewCountInWork, id;
    cout << "Введите id станции, которую хотите изменить: " << endl;
    while (true) {
        id = NumberInput(0);
        if (SearchId(kompres, id) != -1) {
            while (true) {
                cout << "Введите количество цехов в работе: " << endl;
                NewCountInWork = NumberInput(0);
                if (NewCountInWork <= kompres[id].Count) {
                    kompres[id].edit(NewCountInWork);
                    break;
                } else
                    cout << "Кол-во цехов в работе не может быть больше общего кол-ва цехов" << endl;
            }
            DrawHeader(0);
            cout << setw(10) << id << kompres[id];
            cout << "Успешное редактирование" << endl;
            return;
        }else
            cout << "Такого номера не существует, попробуйте еще раз: " << endl;
    }
}

bool CreateFile(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres, const string& FileName) {
    ofstream fout;
    fout.open("data.txt");
    if (!fout.is_open())
        return false;
    if (pipes.size() > 0) {
        fout << "pipe" << endl << pipes.size() << endl;
        for (auto& p : pipes) {
            fout << p.first << endl;
            p.second.save(fout);
        }
    } else {
        cout << "Трубы не были добавлены" << endl;
        fout << "nopipe" << endl;
    }
    if (kompres.size() > 0) {
        fout << "kc" << endl << kompres.size() << endl;
        for (auto& k : kompres) {
            fout << k.first << endl;
            k.second.save(fout);
        }
    } else {
        cout << "КС не были добавлены" << endl;
        fout << "nokc" << endl;
    }
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
            NewPipe.load(fin);
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
            NewKS.load(fin);
            kompres.insert({ id, NewKS });
        }
    }
    return true;
}

// Удаление
template<typename T>
void DeleteElement(T& map, int id) {
    if (map.find(id) != map.end()) {
        map.erase(id);
    }
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
//template<typename T>
//bool CheckByName(const T &map, string param) {
//    return map.Name == param;
//}

bool PCheckByName(const pipe& pipe, string param) {
    return pipe.name == param;
}

bool KCheckByName(const KS& kompres, string param) {
    return kompres.Name == param;
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

void PipeFilterMenu(unordered_map<int, pipe>& pipes) {
    if (pipes.size() == 0) {
        cout << "Трубы не добавлены " << endl;
        return;
    }
    cout << endl << "Фильтр/редактирование труб" << endl << "1. Поиск труб по названию" << endl
        << "2. Поиск труб по признаку в ремонте " << endl << "3. Ввести id вручную " << endl;
    int FilterCase = NumberInput(0);
    switch (FilterCase) {
    case 1: {
        cout << "Введите имя, которое нужно найти: " << endl;
        string inputName;
        getline(cin, inputName);
        inputName.erase(0, inputName.find_first_not_of(" \n\r\t"));
        inputName.erase(inputName.find_last_not_of(" \n\r\t") + 1);
        vector<int> index = FindByFilter(pipes, PCheckByName, inputName);
        if (index.size() != 0) {
            cout << "Найдено " << index.size() << " труб" << endl;
            DrawHeader(1);
            for (auto& id : index)
                cout << setw(10) << id << pipes[id];
            cout << "Редактировать найденые? (1-да)" << endl;
            if (NumberInput(0) == 1) {
                for (auto& id : index)
                    pipes[id].edit();
            }
        }else
            cout << "Ничего не найдено " << endl;
        return;
    }
    case 2: {
        cout << "Какие трубы нужно искать (1 - в ремонте, 0 - не в ремонте): " << endl;
        char inputChar = getchar();
        cin.ignore(10000, '\n');
        if (inputChar == '1' || inputChar == '0') {
            vector<int> index = FindByFilter(pipes, CheckByRepair, (inputChar == '1') ? true : false);
            if (index.size() != 0) {
                cout << "Найдено " << index.size() << " труб" << endl;
                DrawHeader(1);
                for (auto& id : index)
                    cout << setw(10) << id << pipes[id];
                cout << "Редактировать найденые? (1-да)" << endl;
                if (NumberInput(0) == 1)
                    for (auto& id : index)
                        pipes[id].edit();
            } else
                cout << "Ничего не найдено " << endl;
        } else
            cout << "Ошибка ввода " << endl;
        return;
    }
    case 3: {
        cout << "Введите ID труб, которые нужно отредактировать: " << endl;
        int input;
        vector<int> edit_id;
        do {
            input = NumberInput(0);
            if (SearchId(pipes, input) != -1)
                edit_id.push_back(input);
        } while (input != 0);
        if (edit_id.size() != 0) {
            cout << "Успешное редактирование " << endl;
            DrawHeader(1);
            for (auto& id : edit_id) {
                pipes[id].edit();
                cout << setw(10) << id << pipes[id];
            }
        }
        return;
    }
    default:
        cout << "Такого пункта не существует" << endl;
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
    int FilterCase = NumberInput(0);
    if (FilterCase == 1) {
        cout << "Введите название, которое нужно найти: " << endl;
        string inputName;
        getline(cin, inputName);
        inputName.erase(0, inputName.find_first_not_of(" \n\r\t"));
        inputName.erase(inputName.find_last_not_of(" \n\r\t") + 1);
        vector<int> index = FindByFilter(kompres, KCheckByName, inputName);
        if (index.size() != 0) {
            cout << "Найдено " << index.size() << " КС" << endl;
            DrawHeader(0);
            for (auto& id : index) {
                cout << setw(10) << id << kompres[id];
            }
        }else
            cout << "Ничего не найдено " << endl;
    } else if (FilterCase == 2) {
        cout << "Введите процент нерабочих цехов: " << endl;
        double percent = NumberInput(0.);
        if (percent <= 100 && percent >= 0) {
            vector<int> index = FindByFilter(kompres, CheckByPercent, percent);
            if (index.size() != 0) {
                cout << "Найдено " << index.size() << " труб" << endl;
                DrawHeader(0);
                for (auto& id : index) {
                    cout << setw(10) << id << kompres[id];
                }
            }else
                cout << "Ничего не найдено " << endl;
        }else
            cout << "Ошибка ввода " << endl;
    }
    return;
}

int main(){
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
                if (pipeId != -1 && pipes[pipeId].in == 0 && pipes[pipeId].out == 0 && in != -1 && out != -1 && in != out) {
                    pipes[pipeId].link(in, out);
                    cout << "Объекты соединены " << endl;
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
                for (auto& p : pipes)
                    if (p.second.islinked())
                        p.second.showlink(p.first);
            }
            else
                cout << "Ошибка " << endl;
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