#pragma once

#include <iostream>

using namespace std;

template<typename T>
T NumberInput(T min) {
    T input;
    while (!(cin >> input) || input < min) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "������ �������� ������, ���������� ��� ���: ";
    }
    cin.ignore(10000, '\n');
    return input;
}

