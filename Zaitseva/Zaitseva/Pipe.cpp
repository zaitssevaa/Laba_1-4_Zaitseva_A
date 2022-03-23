#include "pipe.h"

using namespace std;

int pipe::MaxId = 0;

void pipe::DrawHeader() {
    cout << setw(10) << "ID" << setw(20) << "��������" << setw(20) << "�����" << setw(20) << "�������" << setw(20)
        << "� �������" << endl;
}

void pipe::link(int newIn, int newOut) {
    if (in == 0 && out == 0 && newOut != newIn) {
        out = newOut;
        in = newIn;
    }
    else
        cout << "������" << endl;
}

void pipe::ClearLink() {
    out = 0;
    in = 0;
}

void pipe::edit() {
    repair = !repair;
}

bool pipe::linked() const {
    return in > 0 && out > 0;
}

bool pipe::CanBeUsed() const {
    return in > 0 && out > 0 && repair == false;
}

void pipe::showlink(int ID) const {
    cout << "�� " << out << " -> ����� " << ID << " -> �� " << in << ((repair == true) ? " � ������� " : " �������� ")
        << endl;
}

ostream& operator<<(std::ostream& out, const pipe& p) {
    out << setw(20) << p.Name <<
        setw(20) << p.length <<
        setw(20) << p.diameter <<
        setw(20) << ((p.repair == true) ? "��" : "���") << endl;
    return out;
}

istream& operator>>(istream& in, pipe& NewPipe) {
    cout << "������� �������������� �����: " << endl << "���: " << endl;
    NewPipe.Name = StrInput();
    cout << "�����: " << endl;
    NewPipe.length = NumberInput(0.01);
    cout << "�������: " << endl;
    NewPipe.diameter = NumberInput(1);
    cout << "������� 1, ���� ����� � �������, ��� 0, ���� ����� �� � �������: " << endl;
    NewPipe.repair = (NumberInput(0, 1) == 1) ? true : false;
    return in;
}

ofstream& operator<<(ofstream& fout, const pipe& p) {
    fout << p.Name << endl
        << p.length << endl
        << p.diameter << endl
        << p.repair << endl
        << p.in << endl
        << p.out << endl;
    return fout;
}

ifstream& operator>>(ifstream& fin, pipe& NewPipe) {
    fin >> ws;
    getline(fin, NewPipe.Name);
    fin >> NewPipe.length >> NewPipe.diameter >> NewPipe.repair >> NewPipe.in >> NewPipe.out;
    return fin;
}

pipe::pipe() {
    Name = "";
    length = 0.;
    diameter = 0;
    repair = false;
    in = 0;
    out = 0;
}