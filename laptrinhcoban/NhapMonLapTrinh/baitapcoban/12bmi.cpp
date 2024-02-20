#include<iostream>
#include<string>
#include<typeinfo>
#include<conio.h>

using namespace std;

struct Connguoi
{
    string ten;
    int tuoi;
    float chieucao;
    char nhommau;
    int sodo3vong;
    float cannang;
    string job;
};

string chisobmi(Connguoi nguoi)
{
    float bmi = nguoi.cannang / (nguoi.chieucao * nguoi.chieucao);
    string ketqua;
    if (bmi < 18.5)
    {
        ketqua = "gay vl";
    }
    else if (bmi > 25)
    {
        ketqua = "beo vl";
    }
    else
    {
        ketqua = "dep trai vl";
    }
    cout << "Ket qua BMI cua ban " << nguoi.ten << " la: " << bmi << endl;
    return ketqua;
}

void dongthoigian(Connguoi nguoi, int namtroiqua)
{
    for (int i = 0; i < namtroiqua; i = i + 1)
    {
        nguoi.cannang = nguoi.cannang + 2;
    }
    cout << "sau " << namtroiqua << " nam ";
    string ketqua = chisobmi(nguoi);
    cout << "Ban " << nguoi.ten << " sau " << namtroiqua << " nam troi qua se " << ketqua << endl;
}

int main()
{
    int nam;
    Connguoi nguoi;
    cout << "Nhap ho va ten cua ban: ";
    getline (cin, nguoi.ten);
    cout << endl;
    cout << "Nhap can nang cua ban: ";
    cin >> nguoi.cannang;
    cout << endl;
    cout << "Nhap chieu cao cua ban: ";
    cin >>nguoi.chieucao;
    cout << endl;
    cout << "Nhap so nam can tinh: ";
    cin >> nam;
    cout << endl;
    system("cls");
    cout << "Xin chao " << nguoi.ten << endl;
    chisobmi(nguoi);
    dongthoigian(nguoi, nam);
    getch();
    system("cls");
}