#pragma once

#include <iostream>
#include <string>

using namespace std;

template<typename T>
T NumberInput(T min = T(INT_MIN), T max = T(INT_MAX));

string StrInput();

template<typename T>
T NumberInput(T min, T max) {
    T input;
    while (!(cin >> input) || input < min || input > max) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "¬веден неверный символ, попробуйте еще раз: ";
    }
    cin.ignore(10000, '\n');
    return input;
}