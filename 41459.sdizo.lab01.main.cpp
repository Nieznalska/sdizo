//SDIZO LAB 01
//Niez


#include "stdafx.h"
#include<iostream>
#include<time.h>
#include <stdlib.h>//malloc
#include<fstream>

using namespace std;

struct sdizo**tab = NULL;

int i;

struct sdizo
{
	int liczba;
	char znaczek;
	float cos;

};

struct sdizo** losowanie(int N)
{

	srand(time(NULL));

	tab = (struct sdizo**) calloc(N, sizeof(struct sdizo*));
	int zmienna = rand() % 10001 - 1000;
	for (i = 0; i < N; i++)
	{
		tab[i] = (struct sdizo*)malloc(sizeof(struct sdizo));
		tab[i]->liczba = zmienna;
		tab[i]->znaczek = rand() % 23 + 66;
		tab[i]->cos = 1001 + i;
		zmienna = rand() % 10001 - 1000;
		for (int j = 0; j < N; j++)
		{
			if (tab[i]->liczba == zmienna)
			{
				zmienna = rand() % 10001 - 1000;
				j = 0;
			}
		}

	}
	return (tab);
}
void kasowanie(int N, struct sdizo** lol)
{
	for (i = 0; i < N; i++)
	{
		free(lol[i]);
	}
	free(lol);
}
void zliczanie(struct sdizo**tab, int N, char znak)
{
	int zliczak = 0;
	for (i = 0; i < N; i++)
	{
		if (znak == tab[i]->znaczek) zliczak++;
	}
	cout << "Zliczanie znaku " << zliczak << endl;
}

void sortowanie_babelkowe(int N, struct sdizo** lol)
{
	sdizo * git = NULL;
	for (int z = 1; z<N - 1; z++)
	{
		int flag = 0;
		for (i = 1; i <N - z; i++)
		{
			if (lol[i]->liczba > lol[i + 1]->liczba)
			{
				git = lol[i];
				lol[i] = lol[i + 1];
				lol[i + 1] = git;
				flag = 1;
			}
			if (flag = 0)
			{
				break;
			}
		}

	}

	for (int j = 0; j < 20; j++)
	{
		cout << tab[j]->liczba << "  " << tab[j]->znaczek << " " << tab[j]->cos << endl;

	}
	cout << "Tablica jest posortowana" << endl;

}

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	int wczytaj;
	char znak;
	fstream plik;
	plik.open("inlab01.txt", ios::in);
	plik >> wczytaj;
	plik >> znak;
	cout << wczytaj << "  " << znak << endl;
	losowanie(wczytaj);
	sortowanie_babelkowe(wczytaj, tab);
	zliczanie(tab, wczytaj, znak);
	kasowanie(wczytaj, tab);

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;



	getchar();
	return 0;
}
