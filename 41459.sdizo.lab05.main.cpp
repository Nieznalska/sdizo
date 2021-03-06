﻿//SDIZO  LAB 05
//Niez 


#include "pch.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

int dodane;
int N1 = 10000;
int Zliczanie_listy = 0;
int Zliczanie_BST = 0;
////////////lista
int X;//ilosc elementow do losowania
int Z;//argument funkcji prezentacji

struct sdizo1
{
	int liczba;  //p2 klucz key
	sdizo1*nastepnik;
	sdizo1*poprzednik;
	sdizo1();
};
sdizo1::sdizo1()
{
	nastepnik = nullptr;
	poprzednik = nullptr;
}
sdizo1*WstawElel(sdizo1*&head, int klucz)
{

	sdizo1*obecny = head;//wskazuje obecny element
	if (head == nullptr)
	{
		srand(time(NULL));
		head = new sdizo1;
		head->liczba = klucz;
		head->nastepnik = head;
		head->poprzednik = head;
		dodane = 0;
		Zliczanie_listy++;

	}
	else
	{
		if (head->poprzednik->liczba < klucz)
		{
			obecny = head;
			//////////
			dodane = 0;
			Zliczanie_listy++;
		}
		else
		{
			do
			{
				if (klucz == obecny->liczba)
				{
					dodane = 1;
					break;
				}

				if (obecny->liczba > klucz)
				{
					srand(time(NULL));
					sdizo1*newele = new sdizo1;
					dodane = 0;
					Zliczanie_listy++;
					newele->liczba = klucz;
					sdizo1*wskaznikpop = obecny->poprzednik;//2
					newele->nastepnik = obecny;//3->4
					newele->poprzednik = wskaznikpop;//wskaznik pokazuje na nastepny element,wskaznik->poprzednik na poprzedni,3->2
					wskaznikpop->nastepnik = newele;//2->3
					obecny->poprzednik = newele;
					if (newele->liczba < head->liczba)
					{
						head = newele;
						Zliczanie_listy++;
						dodane = 0;
					}
					break;
				}
				obecny = obecny->nastepnik;
			} while (head != obecny);
		}
	}

	return(head);
}

void Wyszukajl(sdizo1*head, int klucz)
{

	if (head != nullptr)
	{
		sdizo1*obecny = head;//wskazuje pierwszy element - head
		do {

			obecny = obecny->nastepnik;
		} while (head != obecny);
		Zliczanie_listy++;
	}

}
void Usuwajl(sdizo1*head, int x)
{
	sdizo1*obecny = head;//wskazuje obecny element
	if (x == head->liczba)
	{
		head->poprzednik->nastepnik = head->nastepnik;
		head->nastepnik->poprzednik = head->poprzednik;
		head = head->nastepnik;
		Zliczanie_listy++;
	}
	else {
		do {
			if (obecny->liczba == x)
			{
				obecny->poprzednik->nastepnik = obecny->nastepnik;
				obecny->nastepnik->poprzednik = obecny->poprzednik;
				delete obecny;
				Zliczanie_listy++;
				break;
			}
			else if (obecny->liczba > x)
			{
				break;
			}
			obecny = obecny->nastepnik;
		} while (head != obecny);
	}
}

void UsuwankoCaloscl(sdizo1*&head)
{
	sdizo1*obecny = head->nastepnik;
	do
	{
		delete obecny->poprzednik;
		obecny = obecny->nastepnik;

	} while (head != obecny);
	head = nullptr;
}
///////////////BST
struct sdizo
{
	int liczba;//klucz
	sdizo*lewy;
	sdizo*prawy;
};

int Zliczanko = 0;
void wstaw_ele(sdizo*&root, int klucz)
{

	sdizo*obecny = root;//wskazuje mi obecny ele
	if (root == NULL)
	{

		root = new sdizo;
		root->lewy = root->prawy = NULL;
		root->liczba = klucz;
		Zliczanie_BST++;
		dodane = 0;

	}
	while (obecny != NULL)
	{

		if (obecny->liczba > klucz)
		{
			if (obecny->lewy == NULL)
			{
				sdizo*newele = new sdizo;
				newele->lewy = newele->prawy = NULL;
				newele->liczba = klucz;
				obecny->lewy = newele;
				Zliczanie_BST++;
				dodane = 0;
				return;

			}
			else
			{
				obecny = obecny->lewy;
			}
		}


		else if (obecny->liczba < klucz)
		{
			if (obecny->prawy == NULL)
			{
				sdizo*newele = new sdizo;
				newele->lewy = newele->prawy = NULL;
				newele->liczba = klucz;
				obecny->prawy = newele;
				dodane = 0;
				Zliczanie_BST++;
				return;
			}

			else
			{
				obecny = obecny->prawy;
			}

		}
		else if (obecny->liczba == klucz)
		{
			dodane = 1;
			return;
		}
	}
}
void poszukiwanko(sdizo*&root, int klucz)
{
	sdizo*obecny = root;//wskazuje mi obecny ele  



	while (obecny != NULL)
	{
		if (obecny->liczba < klucz)
		{
			if (obecny->prawy == NULL)
			{
				return;
			}
			obecny = obecny->prawy;

		}
		else if (obecny->liczba > klucz)
		{
			if (obecny->lewy == NULL)
			{
				return;
			}
			obecny = obecny->lewy;
		}
		else if (obecny->liczba == klucz)
		{
			Zliczanie_BST++;
			return;
		}


	}
}

void usuwanko(sdizo*&root, int klucz)
{
	sdizo*obecny = root;
	sdizo*tatus = NULL;
	while ((obecny != NULL) && (klucz != obecny->liczba))
	{
		tatus = obecny;
		if (obecny->liczba < klucz)
		{
			obecny = obecny->prawy;

		}
		else
		{
			obecny = obecny->lewy;
		}
	}if (obecny == NULL)
	{
		Zliczanie_BST++;
		return;
	}
	if ((obecny->prawy == NULL) && (obecny->lewy == NULL))
	{
		if (obecny == root)
		{
			root = NULL;
			Zliczanie_BST++;
			return;
		}
		if (tatus->prawy == obecny)
		{
			tatus->prawy = NULL;
			Zliczanie_BST++;
			return;
		}
		else
		{
			tatus->lewy = NULL;
			Zliczanie_BST++;
			return;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////
	if (obecny->prawy == NULL)
	{
		if (obecny == root)
		{
			root = obecny->lewy;//usuwamy korzonki
			Zliczanie_BST++;
			return;

		}
		else if (tatus->prawy == obecny)
		{
			tatus->prawy = obecny->lewy;
			Zliczanie_BST++;
			return;
		}
		else
		{
			tatus->lewy = obecny->lewy;
			Zliczanie_BST++;
			return;
		}
	}
	if (obecny->lewy == NULL)//wezel ma jedynie prawe poddrzewo
	{
		if (obecny = root)
		{
			root = obecny->prawy;
			Zliczanie_BST++;
			return;
		}
		else if (tatus->prawy == obecny)
		{
			tatus->prawy = obecny->prawy;
			Zliczanie_BST++;
			return;
		}
		else
		{
			tatus->lewy = obecny->prawy;
			Zliczanie_BST++;
			return;
		}
	}
	sdizo*staruszek = NULL;
	sdizo*dzidzia = NULL;
	staruszek = obecny;
	dzidzia = obecny->lewy;
	while (dzidzia->prawy != NULL)
	{
		staruszek = dzidzia;
		dzidzia = dzidzia->prawy;
		Zliczanie_BST++;
		return;
	}
	if (dzidzia == obecny->lewy)//poprzednik jest lewym potomkiem usuwanego wezla
	{
		sdizo*temp;
		if (obecny == root)//wywalamy korzen
		{
			temp = root->prawy;
			root = obecny->lewy;
			root->prawy = temp;
		}
		else if (tatus->prawy == obecny)
		{
			tatus->prawy = dzidzia;
		}
		else
		{
			tatus->lewy = dzidzia;
		}
		Zliczanie_BST++;
		return;
	}
	//poprzednik nie jest lewym potomkiem a jego wnukiem  lub dalej
	sdizo*pradzidzia = NULL;

	pradzidzia = dzidzia->lewy;//potomek poprzednika
	//adopcja
	if (staruszek->prawy == pradzidzia)
	{
		staruszek->prawy = pradzidzia;
		Zliczanie_BST++;
		return;
	}
	else
	{
		staruszek->lewy = pradzidzia;
		Zliczanie_BST++;
		return;
	}
	//adopcja poprzednika przez rodzica usuwanego wezla
	dzidzia->lewy = obecny->lewy;
	if (obecny == root)
	{
		root = dzidzia;
		Zliczanie_BST++;
		return;
	}
	else if (tatus->prawy == obecny)
	{
		tatus->prawy = dzidzia;
		Zliczanie_BST++;
		return;
	}
	else
	{
		tatus->lewy = dzidzia;
		Zliczanie_BST++;
		return;
	}

}

int main()
{

	srand(time(NULL));
	clock_t begin, end;
	double time_spent;
	sdizo1*head = nullptr;  //inicjalizacja listy
	sdizo*root = nullptr; //inicjalizacja drzewa
	/////lista generowanie kluczy losowo
	int rank;
	cout << "Generacja dla: " << N1 << endl;
	cout << "Generowanie kluczy -lista" << endl;
	srand(1);
	begin = clock();
	for (int i = 0; i < N1; i++)
	{
		rank = ((10 * rand()) % 100001);
		WstawElel(head, rank);
		if (dodane == 1)
		{
			i = i - 1;
			//i -1= dodane;
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas potrzebny do dodania: " << time_spent * 1000 << "s." << endl;
	cout << "Dodano: " << Zliczanie_listy << endl;
	Zliczanie_listy = 0;
	///////////////////////////////////////////////////////////////////////////////////////
	cout << "Wyszukiwanie kluczy -lista" << endl;
	begin = clock();
	for (int i = 0; i < N1; i++)
	{
		rank = ((10 * rand()) % 100001);
		Wyszukajl(head, rank);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas potrzebny do wyszukania: " << time_spent * 1000 << "s." << endl;
	cout << "Wyszukano: " << Zliczanie_listy << endl;
	Zliczanie_listy = 0;

	/////////////////////////////////////////////////////////////////////////////////////
	cout << "Usuwanie kluczy -lista" << endl;
	begin = clock();
	for (int i = 0; i < N1; i++)
	{
		rank = ((10 * rand()) % 100001);
		Usuwajl(head, rank);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas potrzebny do usuwania: " << time_spent * 1000 << "s." << endl;
	cout << ": " << Zliczanie_listy << endl;
	Zliczanie_listy = 0;
	////////////////////////////////////////////////////////////////// Drzewo


	/////////////////////////////////////////////////////////////////////////////

	cout << "Generowanie kluczy -bst" << endl;
	srand(1);
	begin = clock();
	for (int i = 0; i < N1; i++)
	{
		rank = ((10 * rand()) % 100001);
		wstaw_ele(root, rank);
		if (dodane == 1)
		{
			i = i - 1;
			//i -1= dodane;
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas potrzebny do dodania: " << time_spent * 1000 << "s." << endl;
	cout << "Dodano: " << Zliczanie_BST << endl;
	Zliczanie_BST = 0;
	///////////////////////////////////////////////////////////////////////////////////
	cout << "Wyszukiwanie kluczy -bst" << endl;
	srand(1);
	begin = clock();
	for (int i = 0; i < N1; i++)
	{
		rank = ((10 * rand()) % 100001);
		poszukiwanko(root, rank);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas potrzebny do wyszukiwania: " << time_spent * 1000 << "s." << endl;
	cout << "Wyszukano: " << Zliczanie_BST << endl;
	Zliczanie_BST = 0;
	/////////////////////////////////////////////////////////////////////////////////////
	cout << "Usuwanie-bst" << endl;
	srand(1);
	begin = clock();
	for (int i = 0; i < N1; i++)
	{
		rank = ((10 * rand()) % 100001);
		usuwanko(root, rank);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas potrzebny do usuwania: " << time_spent * 1000 << "s." << endl;
	cout << "Usunieto: " << Zliczanie_BST << endl;
	Zliczanie_BST = 0;
	////////////////////////////////////////////////////////////////////////////////
	////UsuwankoCaloscl(head);

	return 0;
}
