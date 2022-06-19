﻿#include "KS.h"

using namespace std;

int KS::MaxId = 0;

void KS::DrawHeader() {
    cout << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Кол-во цехов" << setw(20) << "Цехов в работе"
        << setw(20) << "Эффективность" << endl;
}

std::ostream& operator<<(ostream& out, const KS& k) {
    out << setw(20) << k.Name <<
        setw(20) << k.Count <<
        setw(20) << k.CountInWork <<
        setw(20) << k.Efficiency << endl;
    return out;
}

std::istream& operator>>(istream& in, KS& NewKS) {
    cout << "Введите характеристики компрессорной станции: " << endl << "Имя: " << endl;
    NewKS.Name = StrInput();
    cout << "Кол-во цехов: " << endl;
    NewKS.Count = NumberInput(1);
    cout << "Кол-во цехов в работе: " << endl;
    NewKS.CountInWork = NumberInput(1, NewKS.Count);
    cout << "Эффективность: " << endl;
    NewKS.Efficiency = NumberInput(0., 1.);
    return in;
}

KS::KS() {
    Name = "";
    Count = 0;
    CountInWork = 0;
    Efficiency = 0.;
}