#include "KS.h"

using namespace std;

string Name;
int Count, CountInWork;
double Efficiency;

void KS::edit(int NewCountInWork) {
    if (NewCountInWork <= Count)
        CountInWork = NewCountInWork;
}

void KS::save(ofstream& fout) const {
    fout << Name << endl
        << Count << endl
        << CountInWork << endl
        << Efficiency << endl;
}

void KS::load(ifstream& fin) {
    string input;
    getline(fin, input);
    getline(fin, input);
    Name = input;
    fin >> Count >> CountInWork >> Efficiency;
}

std::ostream& operator<<(ostream& out, const KS& k) {
    out << setw(20) << k.Name <<
        setw(20) << k.Count <<
        setw(20) << k.CountInWork <<
        setw(20) << k.Efficiency << endl;
    return out;
}

std::istream& operator>>(istream& in, KS& NewKS) {
    cout << "������� �������������� ������������� �������: " << endl << "���: " << endl;
    while (true) {
        string inputStr;
        getline(cin, inputStr);
        inputStr.erase(0, inputStr.find_first_not_of(" \n\r\t"));
        inputStr.erase(inputStr.find_last_not_of(" \n\r\t") + 1); //https://stackoverflow.com/a/33099753
        if (inputStr.length() > 0) {
            NewKS.Name = inputStr;
            break;
        }
        else
            cout << "��� �� ����� ���� ������, ���������� ��� ���: " << endl;
    }
    cout << "���-�� �����: " << endl;
    while (true) {
        int inputInt = NumberInput(0);
        if (inputInt > 0) {
            NewKS.Count = inputInt;
            break;
        }
        else
            cout << "���-�� ����� �� ����� ���� �������, ���������� ��� ���: " << endl;
    }
    cout << "���-�� ����� � ������: " << endl;
    while (true) {
        int inputInt = NumberInput(0);
        if (inputInt <= NewKS.Count) {
            NewKS.CountInWork = inputInt;
            break;
        }
        else
            cout << "���-�� ����� � ������ �� ����� ���� ������ ������ ���-�� �����: " << endl;
    }
    cout << "�������������: " << endl;
    while (true) {
        double inputDouble = NumberInput(0.);
        if (inputDouble >= 0. && inputDouble <= 1.) {
            NewKS.Efficiency = inputDouble;
            break;
        }
        else
            cout << "������������� ������ ���������� � �������� �� 0 �� 1: " << endl;
    }
    return in;
}

KS::KS() {
    Name = "";
    Count = 0;
    CountInWork = 0;
    Efficiency = 0.;
}