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
	void Fitness()//вычисление фитнесс функции дл€ каждой строки
	{
		for (int i = 0; i < 50; i++)
		{
			poparray[i][4] = abs(30 - (poparray[i][0] + poparray[i][1] + poparray[i][2] + poparray[i][3]));
		}
	}
	void Normalize()//функци€ нормализации по фитнесс функции
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
	                Normarray[i] = Normarray[i] + Normarray[i - 1];//этим действием € отрезок от 0 до 1 разбил части соответсвующие каждой особи
	            }
	        }
	void Sort() //функци€ сортировки массива по значению фитнесс функции
	{
		int temparray[5]; //объ€вл€ю одномерный временный массив
		for (int j = 49; j > 0; j--)
		{
			for (int i = 0; i < j; i++) //тут обычна€ сортировка пузырьком
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
	void Mutate()//функци€ мутации
	{
		for (int i = 1; i < 50; i++)
		{
			int mutationflag = rand()%1001;
			if (mutationflag<100)// задаем частоту мутаций
			{
				poparray[i][rand()%4] = (rand()%201)-100; //задаем силу мутаций. ¬ конкретном случае мутирует только один случайный ген из четырех
			}
		}
	}
	void Breed()//функци€ скрещивани€
	        {
	            int temppop [50][4]; //объ€вл€ем временную попул€цию
	            for (int i = 0; i < 4; i++) //переписываем лидера в новую попул€цию на первую позицию
	            {
	                temppop[0][i] = poparray[0][i];
	            }
	            for (int k = 1; k < 50; k++)
	            {
	                long double choice = (long double)(rand()%10001) / (long double)10000; //выбираем первого родител€ на отрезке 0..1 с точностью до дес€титыс€чной
	                for (int i = 0; i < 50; i++)
	                {
	                    if (choice < Normarray[i]) //проходим по отрезку и находим нашего родител€
	                    {
	                        for (int f = 0; f < 4; f++)
	                        {
	                            temppop[k][f] = poparray[i][f];//записали удачливого родител€ во временную попул€цию
	                        }
	                        int d = rand()%50; //выбираем второго родител€
	                        int profile[4];
	                        for (int b = 0; b < 4; b++)
	                        {
	                            profile[b] = rand()%2; //выбираем гены родител€, которые перейдут в потомка
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
	                            profile[rand()%4] = 1; //убеждаемс€, что хот€бы один ген второго родител€ перейдет в потомка
	                        }
	                        for (int f = 0; f < 4; f++)
	                        {
	                            if (profile[f]>0)
	                            {
	                                temppop[k][f] = poparray[d][f]; //записали гены второго родител€ в потомка
	                            }
	                        }
	                        break;
	                    }
	                }
	            }
	            for (int i = 0; i < 50; i++)//переписываем временную попул€цию в основную
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
		while (poparray[0][5]==0);//конструктор класса гарантирует нам, что в попул€ции не будет решени€
	}
	void Print() //функци€ вывода массива на экран
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
		cout<< "–ешение найдено на " << popnumber << " поколении\na=" << poparray[0][0]
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
		cout <<"ѕопул€ци€ "<<i<<'\n';
		a.Print();
		cin.get();
		if(a.Flag())
			break;
	}
	if(a.Flag())
		a.PrintSolution();
	else
		cout <<"–ешение не найдено";
	cin.get();
	return(0);
}

