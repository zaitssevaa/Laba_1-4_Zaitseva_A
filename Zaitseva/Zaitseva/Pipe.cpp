#include "Pipe.h"

using namespace std;
string name;
double length;
int diameter;
bool repair;
int in, out;

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

void pipe::save(ofstream& fout) const {
    fout << name << endl
        << length << endl
        << diameter << endl
        << repair << endl
        << in << endl
        << out << endl;
}

void pipe::load(ifstream& fin) {
    string input;
    getline(fin, input);
    getline(fin, input);
    name = input;
    fin >> length >> diameter >> repair >> in >> out;
}

ostream& operator<<(std::ostream& out, const pipe& p) {
    out << setw(20) << p.name <<
        setw(20) << p.length <<
        setw(20) << p.diameter <<
        setw(20) << ((p.repair == true) ? "��" : "���") << endl;
    return out;
}

std::istream& operator>>(istream& in, pipe& NewPipe) {
    cout << "������� �������������� �����: " << endl << "���: " << endl;
    while (true) {
        string inputStr;
        getline(in, inputStr);
        inputStr.erase(0, inputStr.find_first_not_of(" \n\r\t"));
        inputStr.erase(inputStr.find_last_not_of(" \n\r\t") + 1); //https://stackoverflow.com/a/33099753
        if (inputStr.length() > 0) {
            NewPipe.name = inputStr;
            break;
        }
        else
            cout << "��� �� ����� ���� ������, ���������� ��� ���: " << endl;
    }
    cout << "�����: " << endl;
    while (true) {
        double inputDouble = NumberInput(0.);
        if (inputDouble > 0) {
            NewPipe.length = inputDouble;
            break;
        }
        else cout << "����� �� ����� ���� �������" << endl;
    }
    cout << "�������: " << endl;
    int inputInt = NumberInput(1);
    NewPipe.diameter = inputInt;
    cout << "������� 1, ���� ����� � �������, ��� 0, ���� ����� �� � �������: " << endl;
    while (true) {
        char inputChar = getchar();
        cin.ignore(10000, '\n');
        if (inputChar == '1' || inputChar == '0') {
            NewPipe.repair = (inputChar == '1') ? true : false;
            break;
        }
        else
            cout << "������ ������������ ������, ���������� ��� ���: " << endl;
    }
    return in;
}

pipe::pipe() {
    name = "";
    length = 0.;
    diameter = 0;
    repair = false;
    in = 0;
    out = 0;
}