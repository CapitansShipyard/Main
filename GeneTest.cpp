#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
int poparray[50][5];
long double Normarray[50];
void PrintArray() //������� ������ ������� �� �����
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
void Fitness()//���������� ������� ������� ��� ������ ������
        {
            for (int i = 0; i < 50; i++)
            {
                poparray[i][4] = fabs(30 - (poparray[i][0] + poparray[i][1] + poparray[i][2] + poparray[i][3]));
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
void Randarray()//���������� ������� ���������� ������� � ��������� �� -100 �� 100
        {
            for (int j = 0; j < 50; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    poparray[j][i] = (rand() % 201)-100;
                }
            }
        }
void Normalize()//������� ������������ �� ������� �������
        {
            long double SumKoef = 0;
            for (int i = 0; i < 50; i++)
            {
                Normarray[i] = (long double)1 / (long double)poparray[i][4];
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
int main()
{
	srand(time(0));
	Randarray();
	Fitness();
    PrintArray();
    std::cin.get();
    Sort();
    cout << "Generation 0\n";
    PrintArray();
    std::cin.get();
    int flag = 0;
    for (int i = 0; i < 50; i++)//��������� ��������
    {
    	if (poparray[0][4] == 0)
    	{
    		cout <<"Solution is found on " << i << " generation\n a=" << poparray[0][0] << " b=" << poparray[0][1] << " c=" << poparray[0][2] << " d=" << poparray[0][3] << "\n";
    		std::cin.get();
    		flag = 1;
    		break;
    	}
    	else
    	{
    		Normalize();
    		Breed();
    		Mutate();
    		Fitness();
    		Sort();
    		cout << "Generation " << i+1 <<"\n";
    		PrintArray();
    		std::cin.get();
    	}
    }
    if (flag==0)
    {
    	cout << "Solution is not found\n";
    	PrintArray();
    }
    std::cin.get();
    return(0);
}
