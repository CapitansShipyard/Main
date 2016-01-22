#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
class population
{
private:
	int popnumber;
	int poparray[50][5];
	double Normarray[50];
	void Fitness()//���������� ������� ������� ��� ������ ������
	{
		for (int i = 0; i < 50; i++)
		{
			poparray[i][4] = abs(30 - (poparray[i][0] + poparray[i][1] + poparray[i][2] + poparray[i][3]));
		}
	}
	void Normalize()//������� ������������ �� ������� �������
	        {
	            double SumKoef = 0;
	            for (int i = 0; i < 50; i++)
	            {
	                Normarray[i] = (double)1 / (double)poparray[i][4];
	            }
	            for (int i = 0; i < 50; i++)
	            {
	                SumKoef = SumKoef + Normarray[i];
	            }
	            for (int i = 0; i < 50; i++)
	            {
	                Normarray[i] = Normarray[i] / SumKoef;
	            }
	            for (int i = 1; i < 50; i++)
	            {
	                Normarray[i] = Normarray[i] + Normarray[i - 1];//���� ��������� � ������� �� 0 �� 1 ������ ����� �������������� ������ �����
	            }
	        }
	void Sort() //������� ���������� ������� �� �������� ������� �������
	{
		int temparray[5]; //�������� ���������� ��������� ������
		for (int j = 49; j > 0; j--)
		{
			for (int i = 0; i < j; i++) //��� ������� ���������� ���������
			{
				if (poparray[i][4] > poparray[i + 1][4])
				{
					for (int k = 0; k < 5; k++)
					{
						temparray[k] = poparray[i][k];
					}
					for (int k = 0; k < 5; k++)
					{
						poparray[i][k] = poparray[i + 1][k];
					}
					for (int k = 0; k < 5; k++)
					{
						poparray[i + 1][k] = temparray[k];
					}
				}
			}
		}
	}
	void Mutate()//������� �������
	{
		for (int i = 1; i < 50; i++)
		{
			int mutationflag = rand()%1001;
			if (mutationflag<100)// ������ ������� �������
			{
				poparray[i][rand()%4] = (rand()%201)-100; //������ ���� �������. � ���������� ������ �������� ������ ���� ��������� ��� �� �������
			}
		}
	}
	void Breed()//������� �����������
	        {
	            int temppop [50][4]; //��������� ��������� ���������
	            for (int i = 0; i < 4; i++) //������������ ������ � ����� ��������� �� ������ �������
	            {
	                temppop[0][i] = poparray[0][i];
	            }
	            for (int k = 1; k < 50; k++)
	            {
	                long double choice = (long double)(rand()%10001) / (long double)10000; //�������� ������� �������� �� ������� 0..1 � ��������� �� ��������������
	                for (int i = 0; i < 50; i++)
	                {
	                    if (choice < Normarray[i]) //�������� �� ������� � ������� ������ ��������
	                    {
	                        for (int f = 0; f < 4; f++)
	                        {
	                            temppop[k][f] = poparray[i][f];//�������� ���������� �������� �� ��������� ���������
	                        }
	                        int d = rand()%50; //�������� ������� ��������
	                        int profile[4];
	                        for (int b = 0; b < 4; b++)
	                        {
	                            profile[b] = rand()%2; //�������� ���� ��������, ������� �������� � �������
	                        }
	                        int flag = 0;
	                        for (int g = 0; g < 4; g++)
	                        {
	                            if (profile[g]>0)
	                            {
	                                flag = 1;
	                            }
	                        }
	                        if (flag == 0)
	                        {
	                            profile[rand()%4] = 1; //����������, ��� ������ ���� ��� ������� �������� �������� � �������
	                        }
	                        for (int f = 0; f < 4; f++)
	                        {
	                            if (profile[f]>0)
	                            {
	                                temppop[k][f] = poparray[d][f]; //�������� ���� ������� �������� � �������
	                            }
	                        }
	                        break;
	                    }
	                }
	            }
	            for (int i = 0; i < 50; i++)//������������ ��������� ��������� � ��������
	            {
	                for (int j = 0; j < 4; j++)
	                {
	                    poparray[i][j] = temppop[i][j];
	                }
	            }
	        }
public:
	population():popnumber(0)
	{
		do
		{
			for (int j = 0; j < 50; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					poparray[j][i] = (rand() % 201)-100;
				}
			}
			Fitness();
			Sort();
		}
		while (poparray[0][5]==0);//����������� ������ ����������� ���, ��� � ��������� �� ����� �������
	}
	void Print() //������� ������ ������� �� �����
	{
		for (int j = 0; j < 50; j++)
		{
			for (int i = 0; i < 5; i++)
			{
				cout << setw(5) << poparray[j][i];
			}
			cout <<"\n";
		}
	}
	void Evolve()
	{
		Normalize();
		Breed();
		Mutate();
		Fitness();
		Sort();
		popnumber++;
	}
	int Flag()
	{
		if(poparray[0][5]==0)
			return(1);
		else
			return(0);
	}
	void PrintSolution()
	{
		cout<< "������� ������� �� " << popnumber << " ���������\na=" << poparray[0][0]
			<<" b=" << poparray[0][1] <<" c=" << poparray[0][2] <<" d=" << poparray[0][3];
	}
};
int main()
{
	srand(time(0));
	population a;
	a.Print();
	cin.get();
	for (int i=1; i<51; i++)
	{
		a.Evolve();
		cout <<"��������� "<<i<<'\n';
		a.Print();
		cin.get();
		if(a.Flag())
			break;
	}
	if(a.Flag())
		a.PrintSolution();
	else
		cout <<"������� �� �������";
	cin.get();
	return(0);
}

