#include "filters.h"

bool SearchIdInVector(const vector<int>& vec, int id) {
    for (auto& v : vec)
        if (v == id)
            return 1;
    return 0;
}

bool CheckByRepair(const pipe& pipe, bool param) {
    return pipe.repair == param;
}

bool CheckByPercent(const KS& kompres, double param) {
    return round(100 * (1. * (kompres.Count - kompres.CountInWork) / kompres.Count)) == param;
}


vector<int> FindByRepair(const unordered_map<int, pipe>& pipes) {
    cout << "Какие трубы нужно искать (1 - в ремонте, 0 - не в ремонте): " << endl;
    vector<int> index = FindByFilter(pipes, CheckByRepair, bool(NumberInput(0, 1)));
    PrintFindResult(pipes, index);
    return index;
}

vector<int> FindByPercent(const unordered_map<int, KS> kompres) {
    cout << "Введите процент нерабочих цехов: " << endl;
    vector<int> index = FindByFilter(kompres, CheckByPercent, NumberInput(0., 100.));
    PrintFindResult(kompres, index);
    return index;
}

void EditingAfterFind(unordered_map<int, pipe>& pipes, vector<int> index) {
    cout << "1. Редактировать найденые " << endl << "2. Выбрать и редактировать " << endl << "3. Удалить найденные"
        << endl << "4. Выбрать и удалить" << endl << "0. Выход" << endl;
    int casemenu = NumberInput(0, 4);
    if (casemenu == 1) {
        for (auto& id : index) {
            cout << "Труба " << id << " включена в сеть, вы уверены, что хотите выключить ее ? (1 - да, 0 - нет)" << endl;
            if (NumberInput(0, 1) == 0) continue;
            pipes[id].edit();
        }
    }
    else if (casemenu == 2) {
        cout << "Введите Id (0-конец ввода) " << endl;
        int input;
        set<int> edit_id;
        do {
            input = NumberInput(0);
            if (SearchIdInVector(index, input) == 1)
                edit_id.insert(input);
        } while (input != 0);
        for (auto& id : edit_id) {
            cout << "Труба " << id << " включена в сеть, вы уверены, что хотите выключить ее ? (1 - да, 0 - нет)" << endl;
            if (NumberInput(0, 1) == 0) continue;
            pipes[id].edit();
        }
    }
    else if (casemenu == 3) {
        for (auto& id : index)
            DeleteElement(pipes, id);
    }
    else if (casemenu == 4) {
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
    }
    else if (FilterCase == 2) {
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
        << "2. Поиск КС по проценту незадействованных цехов" << endl << "0. Выход" << endl;
    int FilterCase = NumberInput(0, 2);
    if (FilterCase == 1) {
        FindByName(kompres);
    }
    else if (FilterCase == 2) {
        FindByPercent(kompres);
    }
    return;
}