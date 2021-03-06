﻿//SDIZO I1 212B LAB 02
// Niez


#include "pch.h"
#include <iostream>
#include <time.h>
#include<fstream>
#include <cstdlib>

using namespace std;
int X;//ilosc elementow do losowania
int Z;//argument funkcji prezentacji

struct sdizo
{
	int liczba;  //p2 klucz key
	double liczbek;
	char znaczek;
	sdizo*nastepnik;
	sdizo*poprzednik;
	sdizo();
};
sdizo::sdizo()
{
	nastepnik = nullptr;
	poprzednik = nullptr;
	znaczek = 'T';
}
sdizo*WstawEle(sdizo*&head, int klucz)
{

	sdizo*obecny = head;//wskazuje obecny element
	if (head == nullptr)
	{
		srand(time(NULL));
		head = new sdizo;
		head->liczba = klucz;
		head->liczbek = rand();
		head->znaczek = 'T';
		head->nastepnik = head;
		head->poprzednik = head;
	}
	else
	{
		if (head->poprzednik->liczba < klucz)
			obecny = head;
		else
		{
			do
			{
				if (klucz == obecny->liczba)
				{
					cout << "Ten element znajduje sie juz w liscie" << endl;
					break;
				}
				if (obecny->liczba > klucz)
				{
					srand(time(NULL));
					sdizo*newele = new sdizo;
					newele->liczba = klucz;
					newele->liczbek = rand();       
					newele->znaczek = 'T';
					sdizo*wskaznikpop = obecny->poprzednik;//2
					newele->nastepnik = obecny;//3->4
					newele->poprzednik = wskaznikpop;//wskaznik pokazuje na nastepny element,wskaznik->poprzednik na poprzedni,3->2
					wskaznikpop->nastepnik = newele;//2->3
					obecny->poprzednik = newele;
					if (newele->liczba < head->liczba)
					{
						head = newele;
					}
					break;
				}
				obecny = obecny->nastepnik;
			} while (head != obecny);
		}
	}
	return(head);
}

sdizo*Losowanko(sdizo*&head, int X)
{
	if (head == nullptr)
	{
		head = new sdizo;
		head->liczba = 9 * (rand() % 11111 + 1);
		srand(time(NULL));
		head->liczbek = rand();
		head->znaczek = (rand() % 255 + 1);
		head->poprzednik = head;
		head->nastepnik = head;
		X--;
	}
	for (int i = 0; i < X; i++)
	{
		sdizo*wylosowane = nullptr;
		int Losowanko = 9 * (rand() % 11111 + 1);
		sdizo*obecniak = head;
		do
		{
			if (Losowanko == obecniak->liczba)
			{
				obecniak = head;
				Losowanko = 9 * (rand() % 11111 + 1);
			}
			if (obecniak->liczba > Losowanko)   //obecniak wiekszy od losowanka, liczba niepowtórzona
				break;
			obecniak = obecniak->nastepnik;
		} while (head != obecniak);

		wylosowane = new sdizo; // alokacja miejsca na dane tego węzła, czyli klucz, brelok i wskaźniki
		if (Losowanko > head->poprzednik->liczba)
			obecniak = head;

		wylosowane->liczbek = rand();           
		wylosowane->liczba = Losowanko;
		wylosowane->znaczek = 'T';
		sdizo * nastepnik = obecniak;
		sdizo * poprzednik = obecniak->poprzednik;

		wylosowane->nastepnik = nastepnik;
		wylosowane->poprzednik = poprzednik;

		nastepnik->poprzednik = wylosowane;
		poprzednik->nastepnik = wylosowane;

		//wskaznik pokazuje na nastepny element,wskaznik->poprzednik na poprzedni,3->2
		if (wylosowane->liczba < head->liczba)
			head = wylosowane;
	}
	return(head);
	

}
void Wyszukaj(sdizo*head, int klucz)
{

	if (head != nullptr)
	{
		sdizo*obecny = head;//wskazuje pierwszy element - head
		do {
			if (klucz == obecny->liczba)
			{
				cout << obecny->liczba << " " << obecny->liczbek << " " << obecny->znaczek << endl;
			}
			if (klucz > obecny->liczba)
			{
				cout << "tego elementu nie ma na liscie" << endl;
				break;
			}
			obecny = obecny->nastepnik;
		} while (head != obecny);
	}
	else
		cout << "Lista jest pusta";
}
void Usuwaj(sdizo*head, int x)
{
	sdizo*obecny = head;//wskazuje obecny element
	if (x == head->liczba)
	{
		head->poprzednik->nastepnik = head->nastepnik;
		head->nastepnik->poprzednik = head->poprzednik;
		head = head->nastepnik;
	}
	else {
		do {
			if (obecny->liczba == x)
			{
				obecny->poprzednik->nastepnik = obecny->nastepnik;
				obecny->nastepnik->poprzednik = obecny->poprzednik;
				delete obecny;
				break;
			}
			else if (obecny->liczba > x)
			{
				cout << "Takiego klucza nie było w liście" << endl;
				break;
			}
			obecny = obecny->nastepnik;
		} while (head != obecny);
	}
}

void Show(sdizo*head, int Y)
{
	cout << "Wypisanie pierwszych " << X << " wartosci: " << endl;
	sdizo*obecny = head->poprzednik;//wskazuje ostatni element listy
	if (head != nullptr)
	{
		for (int i = 0; i < Y; i++)
		{
			cout << obecny->liczba << " " << obecny->liczbek << " " << obecny->znaczek << endl;
			obecny = obecny->nastepnik;
		}
	}
	else
		cout << "Lista jest pusta." << endl;
}
void Prezentacja(sdizo * head, int Z)
{
	cout << "Wypisanie ostatnich " << Z << " wartosci: " << endl;
	sdizo*obecny = head;//wskazuje obecny element
	if (head != nullptr)
	{
		for (int i = 0; i < Z; i++)
		{
			cout << obecny->liczba << " " << obecny->liczbek << " " << obecny->znaczek << endl;
			obecny = obecny->poprzednik;
		}
	}
	else
		cout << "Lista jest pusta" << endl;
}

int ListaWezlow(sdizo*head)
{
	sdizo*obecny = head;
	int Zliczanie = 0;
	if (head != nullptr)
	{
		do
		{
			obecny = obecny->nastepnik;
			Zliczanie++;
		} while (head != obecny);
	}
	return Zliczanie;
}
void UsuwankoCalosc(sdizo*&head)
{
	sdizo*obecny = head->nastepnik;
	do
	{
		delete obecny->poprzednik;
		obecny = obecny->nastepnik;

	} while (head != obecny);
	head = nullptr;
}

int main()
{
	int Z = 20;
	clock_t begin, end;
	double time_spent;
	begin = clock();
	srand(time(NULL));
	sdizo*head = nullptr;  //inicjalizacja
	int k1, k2, k3, k4, k5, losowanko;
	fstream plik;
	plik.open("inlab02.txt", ios::in);
	if (plik.good() == false)
		return -1;      ///  zabezpieczenie
	plik >> losowanko;
	plik >> k1;
	plik >> k2;
	plik >> k3;
	plik >> k4;
	plik >> k5;


	Wyszukaj(head, k1);
	head = Losowanko(head, losowanko);
	cout << "Ilosc wezlow w liscie" <<" "<<ListaWezlow(head) << endl;
	Show(head, Z);
	head = WstawEle(head, k2);
	Show(head, Z);
	head = WstawEle(head, k3);
	Show(head, Z);
	head = WstawEle(head, k4);
	Show(head, Z);
	head = WstawEle(head, k5);
	Show(head, Z);
	Usuwaj(head, k3);
	Show(head, Z);
	Usuwaj(head, k2);
	Prezentacja(head, Z);
	Usuwaj(head, k5);
	cout << "Ilosc wezlow w liscie" <<" "<<ListaWezlow(head) << endl;
	Wyszukaj(head, k5);
	Z = 11;
	Prezentacja(head, Z);
	UsuwankoCalosc(head);
	Prezentacja(head, Z);
	cout << "Ilosc wezlow w liscie" <<" "<<ListaWezlow(head) << endl;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas trwania " << time_spent << endl;
	plik.close();

	return 0;
}
