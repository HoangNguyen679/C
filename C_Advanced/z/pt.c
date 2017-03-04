#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;
#define DT Dathuc*

class Dathuc
{
public:
	double* Heso;
	int Baccaonhat;
	double* Nghiem;
public:
//	Dathuc()
	Dathuc (int n) : Baccaonhat(n)
	{
		this->Heso = new double[this->Baccaonhat];
		this->Nghiem = new double[this->Baccaonhat];
	}
	
	~Dathuc (){delete this->Heso;}
public:
	void Nhapdathuc();
	void Inheso()
	{
		for (int i=0; i <= this->Baccaonhat ; i++) cout << this->Heso[i] << "\t";
	}
	double Tinhgiatri(double x)
	{
		double S=0;
		for (int i=0; i <= this->Baccaonhat ; i++) S = S + pow(x,i)*this->Heso[i];
		return S;
	}
public:
	DT Daoham()
	{
		int baccaonhatdaoham = this->Baccaonhat - 1;
		DT Y1 = new Dathuc(baccaonhatdaoham);
		for (int i=0; i <= baccaonhatdaoham ; i++) Y1->Heso[i] = this->Heso[i+1]*(i+1);
		return Y1;
	}
	DT Daohambaccao();
};

void Dathuc::Nhapdathuc()
{
	for (int i=0; i <= this->Baccaonhat ; i++)
	{
		cout << "Nhap he so bac " << i << " :";
		cin >> this->Heso[i];
	}
}

int main()
{
	clock_t x,y;
	x = clock();
	DT Y=new Dathuc(1);
	Y->Heso[0] = 2;
	Y->Heso[1] = 1;
	double a = -1;
	double b = -2.7;
	double c = 0;
	double m = 1;
	while (1)
	{
		c = (a+b)/2;
		m = Y->Tinhgiatri(c);
		if (m>-0.00000001 && m<0.00000001) break;
		if (Y->Tinhgiatri(a)*m > 0) a = c; else b = c;
	}
	cout << c <<"\n";
	y = clock();
	double s = (double)(y-x)/CLOCKS_PER_SEC;
	cout << s;
	cout << "\n";
	// system("pause");
	return 0;
}
