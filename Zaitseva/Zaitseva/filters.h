#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "pipe.h"
#include "KS.h"
#include "input.h"
#include <unordered_map>
#include <set>

using namespace std;

template<typename T>
void DeleteElement(T& map, int id);

template<typename T>
bool CheckByName(const T& map, string param);

template<typename T, typename T_param>
using Filter = bool (*)(const T& map, T_param param);

void PipeFilterMenu(unordered_map<int, pipe>& pipes);

void KSFilterMenu(unordered_map<int, KS>& kompres);

template<typename T, typename T_param>
vector<int> FindByFilter(const unordered_map<int, T>& map, Filter<T, T_param> f, T_param param) {
    vector<int> res;
    for (auto& [i, m] : map)
        if (f(m, param))
            res.push_back(i);
    return res;
}

template<typename T>
void PrintFindResult(const unordered_map<int, T>& map, const vector<int>& index) {
    if (index.size() != 0) {
        cout << "Найдено " << index.size() << " элементов" << endl;
        T::DrawHeader();
        for (auto& id : index)
            cout << setw(10) << id << map.at(id);
    }
    else
        cout << "Ничего не найдено " << endl;
}

template<typename T>
vector<int> FindByName(const unordered_map<int, T>& map) {
    cout << "Введите имя, которое нужно найти: " << endl;
    vector<int> index = FindByFilter(map, CheckByName, StrInput());
    PrintFindResult(map, index);
    return index;
}

template<typename T>
void DeleteElement(T& map, int id) {
    if (map.find(id) != map.end())
        map.erase(id);
}

template<typename T>
bool CheckByName(const T& map, string param) {
    return map.Name == param;
}