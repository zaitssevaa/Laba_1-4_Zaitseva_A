#include "KS.h"

using namespace std;

int KS::MaxId = 0;

void KS::DrawHeader() {
    cout << setw(10) << "ID" << setw(20) << "��������" << setw(20) << "���-�� �����" << setw(20) << "����� � ������"
        << setw(20) << "�������������" << endl;
}

void KS::createLink()
{
    if (!connected)
        connected = true;
}

void KS::ClearLink()
{
    connected = false;
}

bool KS::linked()
{
    return connected;
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

std::ofstream& operator<<(ofstream& fout, const KS& k) {
    fout << k.Name << endl
        << k.Count << endl
        << k.CountInWork << endl
        << k.Efficiency << endl
        << (k.connected == true ? '1' : '0') << endl;
    return fout;
}

std::istream& operator>>(istream& in, KS& NewKS) {
    cout << "������� �������������� ������������� �������: " << endl << "���: " << endl;
    NewKS.Name = StrInput();
    cout << "���-�� �����: " << endl;
    NewKS.Count = NumberInput(1);
    cout << "���-�� ����� � ������: " << endl;
    NewKS.CountInWork = NumberInput(1, NewKS.Count);
    cout << "�������������: " << endl;
    NewKS.Efficiency = NumberInput(0., 1.);
    return in;
}

std::ifstream& operator>>(ifstream& fin, KS& NewKS) {
    fin >> ws;
    getline(fin, NewKS.Name);
    fin >> NewKS.Count >> NewKS.CountInWork >> NewKS.Efficiency >> NewKS.connected;
    return fin;
}

KS::KS() {
    Name = "";
    Count = 0;
    CountInWork = 0;
    Efficiency = 0.;
}