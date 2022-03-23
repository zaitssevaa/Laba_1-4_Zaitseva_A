#include "Pipe.h"

using namespace std;

void pipe::DrawHeader() {
    cout << setw(10) << "ID" << setw(20) << "��������" << setw(20) << "�����" << setw(20) << "�������" << setw(20)
        << "� �������" << endl;
}

void pipe::link(int in, int out) {
    this->out = out;
    this->in = in;
}

void pipe::edit() {
    repair = !repair;
}

bool pipe::islinked() const {
    return in > 0 && out > 0;   // && repair == false
}

void pipe::showlink(int ID) const {
    cout << "�� " << out << " -> ����� " << ID << " -> �� " << in << ((repair == false) ? " � ������� " : " �������� ")
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
    NewPipe.Name = input::StrInput();
    cout << "�����: " << endl;
    NewPipe.length = input::NumberInput(0.01);
    cout << "�������: " << endl;
    NewPipe.diameter = input::NumberInput(1);
    cout << "������� 1, ���� ����� � �������, ��� 0, ���� ����� �� � �������: " << endl;
    NewPipe.repair = (input::NumberInput(0, 1) == 1) ? true : false;
    return in;
}

ofstream& operator<<(ofstream& fout, const pipe& p)
{
    fout << p.Name << endl
        << p.length << endl
        << p.diameter << endl
        << p.repair << endl
        << p.in << endl
        << p.out << endl;
    return fout;
}

ifstream& operator>>(ifstream& fin, pipe& NewPipe)
{
    string input;
    getline(fin, input);
    getline(fin, input);
    NewPipe.Name = input;
    fin >> NewPipe.length >> NewPipe.diameter >> NewPipe.repair >> NewPipe.in >> NewPipe.out;
    return fin;
}

pipe::pipe() {
    name = "";
    length = 0.;
    diameter = 0;
    repair = false;
    in = 0;
    out = 0;
}