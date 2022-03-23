#include "KS.h"

using namespace std;

void KS::DrawHeader() {
    cout << setw(10) << "ID" << setw(20) << "��������" << setw(20) << "���-�� �����" << setw(20) << "����� � ������"
        << setw(20) << "�������������" << endl;
}

void KS::edit(int NewCountInWork) {
    if (NewCountInWork <= Count)
        CountInWork = NewCountInWork;
}

std::ostream& operator<<(ostream& out, const KS& k) {
    out << setw(20) << k.Name <<
        setw(20) << k.Count <<
        setw(20) << k.CountInWork <<
        setw(20) << k.Efficiency << endl;
    return out;
}

std::ofstream& operator<<(ofstream& fout, const KS& k)
{
    fout << k.Name << endl
        << k.Count << endl
        << k.CountInWork << endl
        << k.Efficiency << endl;
    return fout;
}

std::istream& operator>>(istream& in, KS& NewKS) {
    cout << "������� �������������� ������������� �������: " << endl << "���: " << endl;
    NewKS.Name = input::StrInput();
    cout << "���-�� �����: " << endl;
    NewKS.Count = input::NumberInput(1);
    cout << "���-�� ����� � ������: " << endl;
    NewKS.CountInWork = input::NumberInput(1, NewKS.Count);
    cout << "�������������: " << endl;
    NewKS.Efficiency = input::NumberInput(0., 1.);
    return in;
}

std::ifstream& operator>>(ifstream& fin, KS& NewKS)
{
    string input;
    getline(fin, input);
    getline(fin, input);
    NewKS.Name = input;
    fin >> NewKS.Count >> NewKS.CountInWork >> NewKS.Efficiency;
    return fin;
}

KS::KS() {
    Name = "";
    Count = 0;
    CountInWork = 0;
    Efficiency = 0.;
}