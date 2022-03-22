#pragma once

#include <iostream>
#include <string>
#include "input.h"
#include <fstream>
#include <iomanip>

using namespace std;

class pipe {
public:
    string name;
    double length;
    int diameter;
    bool repair;
    int in, out;

    void link(int IdStart, int IdEnd);

    void edit();

    bool islinked() const;

    void showlink(int ID) const;

    void save(ofstream& out) const;

    void load(ifstream&);

    friend std::ostream& operator<<(ostream& out, const pipe& p);

    friend std::istream& operator>>(istream& in, pipe& NewPipe);

    pipe();
};
