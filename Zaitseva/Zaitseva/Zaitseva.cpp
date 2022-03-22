﻿#include <iostream>
#include <string>
#include <conio.h>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct pipe {
    unsigned int id;
    double length, diameter;
    bool repair;
};

struct KS {
    unsigned int id;
    string Name;
    unsigned int Count, CountInWork;
    double Efficiency;
};

bool CheckDouble(string input)
{
    int length, i, point_count = 0;
    bool error = false;
    length = input.length() - 1;
    if (input.length() == 0) {
        return false;
    }
    for (i = 0; i <= length; ++i)
    {
        if ((input[i] == '.'))
        {
            point_count++;
        }
        else
        {
            if (!isdigit(input[i]))
            {
                error = true;
            }
        }
    }
    if (point_count <= 1) {
        return true;
    }
    else {
        return false;
    }
}

bool CheckInt(string input)
{
    int length, i;
    length = input.length() - 1;
    if (input.length() == 0) {
        return false;
    }
    for (i = 0; i <= length; ++i)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}

bool CheckIDPipe(vector<pipe>& pipes, int newID)
{
    int i;
    if (pipes.size() > 0)
    {
        for (i = 0; i < pipes.size(); ++i)
        {
            if (newID == pipes[i].id)
            {
                return true;
            }
        }
    }
    return false;
}

bool CheckIDKompress(vector<KS>& kompress, int newID)
{
    int i;
    if (kompress.size() > 0)
    {
        for (i = 0; i < kompress.size(); ++i)
        {
            if (newID == kompress[i].id)
            {
                return true;
            }
        }
    }
    return false;
}

void AddPipeline(vector<pipe>& pipes)
{
    system("cls");
    string input;
    cout << "Введите характеристики трубы: \nID: ";
    pipes.resize(pipes.size() + 1);
    while (true)
    {
        getline(cin, input);
        if (CheckInt(input)) {
            if (!CheckIDPipe(pipes, stoi(input))) {
                pipes[pipes.size() - 1].id = stoi(input);
                break;
            }
            else
            {
                cout << "Такой ID уже существует, попробуйте еще раз: ";
            }
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
    cout << "Длина: ";
    while (true)
    {
        getline(cin, input);
        if (CheckDouble(input)) {
            pipes[pipes.size() - 1].length = stod(input);
            break;
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
    cout << "Диаметр: ";
    while (true)
    {
        getline(cin, input);
        if (CheckDouble(input)) {
            pipes[pipes.size() - 1].diameter = stod(input);
            break;
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
    cout << "Введите 1, если труба в ремонте, или 0, если труба не в ремонте: ";
    while (true)
    {
        getline(cin, input);
        if (input == "1" || input == "0") {
            pipes[pipes.size() - 1].repair = stoi(input);
            break;
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
}

void AddKC(vector<KS>& kompress)
{
    system("cls");
    string input;
    cout << "Введите характеристики КС: \nID: ";
    kompress.resize(kompress.size() + 1);
    while (true)
    {
        getline(cin, input);
        if (CheckInt(input)) {
            if (!CheckIDKompress(kompress, stoi(input))) {
                kompress[kompress.size() - 1].id = stoi(input);
                break;
            }
            else
            {
                cout << "Такой ID уже существует, попробуйте еще раз: ";
            }
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
    cout << "Название: ";
    getline(cin, input);
    kompress[kompress.size() - 1].Name = input;
    cout << "Количество цехов: ";
    while (true)
    {
        getline(cin, input);
        if (CheckInt(input)) {
            kompress[kompress.size() - 1].Count = stoi(input);
            break;
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
    cout << "Количество цехов в работе: ";
    while (true)
    {
        getline(cin, input);
        if (CheckInt(input)) {
            if (stoi(input) <= kompress[kompress.size() - 1].Count) {
                kompress[kompress.size() - 1].CountInWork = stoi(input);
                break;
            }
            else
            {
                cout << "Количество цехов в работе не может быть больше общего кол-ва, поробуйте еще раз: ";
            }
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
    cout << "Эффективность: ";
    while (true)
    {
        getline(cin, input);
        if (CheckDouble(input)) {
            kompress[kompress.size() - 1].Efficiency = stod(input);
            break;
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: ";
        }
    }
}

void ShowPipeline(vector<pipe>& pipes, vector<KS>& kompress)
{
    system("cls");
    int i;
    cout << "Трубопроводы" << endl <<
        setw(10) << "ID" <<
        setw(20) << "Длина" <<
        setw(20) << "Диаметр" <<
        setw(20) << "В ремонте" << endl;
    if (pipes.size() > 0)
    {
        for (i = 0; i < pipes.size(); ++i)
        {
            cout << setw(10) << pipes[i].id <<
                setw(20) << pipes[i].length <<
                setw(20) << pipes[i].diameter <<
                setw(20) << pipes[i].repair << endl;
        }
    }
    else {
        cout << "Массив пустой";
    }
    cout << "Компрессорные станции" << endl <<
        setw(10) << "ID" <<
        setw(20) << "Название" <<
        setw(20) << "Кол-во цехов" <<
        setw(20) << "Цехов в работе" <<
        setw(20) << "Эффективность" << endl;
    if (kompress.size() > 0)
    {
        for (i = 0; i < kompress.size(); ++i)
        {
            cout << setw(10) << kompress[i].id <<
                setw(20) << kompress[i].Name <<
                setw(20) << kompress[i].Count <<
                setw(20) << kompress[i].CountInWork <<
                setw(20) << kompress[i].Efficiency << endl;
        }
    }
    else {
        cout << "Массив пустой";
    }
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    vector<pipe> pipes;
    vector<KS> kompress;
    char inputmenu;
    pipes.resize(0);
    kompress.resize(0);
    while (true)
    {
        system("cls");
        cout << "1. Добавить трубу " << endl <<
            "2. Добавить КС  " << endl <<
            "3. Просмотр всех объектов  " << endl <<
            "4. Редактировать трубу  " << endl <<
            "5. Редактировать КС  " << endl <<
            "6. Сохранить  " << endl <<
            "7. Загрузить  " << endl <<
            "0. Выход  " << endl;
        inputmenu = _getch();
        switch (inputmenu)
        {
        case '1':
            system("cls");
            AddPipeline(pipes);
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '2':
            system("cls");
            AddKC(kompress);
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '3':
            system("cls");
            ShowPipeline(pipes, kompress);
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '4':
            system("cls");
            cout << "4\n";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '5':
            system("cls");
            cout << "5\n";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '6':
            system("cls");
            cout << "6\n";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '7':
            system("cls");
            cout << "7\n";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '0':
            return 0;
        }
    }
    return 0;
}