#pragma once
#include <string>
#include <iostream>

using namespace std;

class input
{
public:
    template<typename T>
    static T NumberInput(T min = T(INT_MIN), T max = T(INT_MAX));
    static string StrInput();

};

template<typename T>
T NumberInput(T min) {
    T input;
    while (!(cin >> input) || input < min || input > max){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "¬веден неверный символ, попробуйте еще раз: ";
    }
    cin.ignore(10000, '\n');
    return input;
}

