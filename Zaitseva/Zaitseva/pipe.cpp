#include "pipe.h"

using namespace std;

int pipe::MaxId = 0;

void pipe::DrawHeader() {
    cout << setw(10) << "ID" << setw(20) << "Имя" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(20)
        << "В ремонте" << endl;
}

ostream& operator<<(std::ostream& out, const pipe& p) {
    out << setw(20) << p.Name <<
        setw(20) << p.length <<
        setw(20) << p.diameter <<
        setw(20) << ((p.repair == true) ? "Да" : "Нет") << endl;
    return out;
}

istream& operator>>(istream& in, pipe& NewPipe) {
    cout << "Введите характеристики трубы: " << endl << "Имя: " << endl;
    NewPipe.Name = StrInput();
    cout << "Длина: " << endl;
    NewPipe.length = NumberInput(0.01);
    cout << "Диаметр: " << endl;
    NewPipe.diameter = NumberInput(1);
    cout << "Введите 1, если труба в ремонте, или 0, если труба не в ремонте: " << endl;
    NewPipe.repair = (NumberInput(0, 1) == 1) ? true : false;
    return in;
}

pipe::pipe() {
    Name = "";
    length = 0.;
    diameter = 0;
    repair = false;
}