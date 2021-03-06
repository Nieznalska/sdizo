
//SDIZO drzewo BST
// Niez

#include "pch.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

struct sdizo
{
	int liczba;//klucz
	sdizo*lewy;
	sdizo*prawy;
	char znaczek[10];
};

int Zliczanko = 0;
void wstaw_ele(sdizo*&root, int klucz)
{

	sdizo*obecny = root;//wskazuje mi obecny ele
	if (root == NULL)
	{ // tworze nowe i wchodze pod nie zeby je oporzadzic

		root = new sdizo;
		root->lewy = root->prawy = NULL;
		root->liczba = klucz;
		sprintf_s(root->znaczek, "%d", klucz);
		
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
				sprintf_s(newele->znaczek, "%d", klucz);
				
				obecny->lewy = newele;
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
				sprintf_s(newele->znaczek, "%d", klucz);
				obecny->prawy = newele;
				
				return;
			}
			else
			{
				obecny = obecny->prawy;
			}

		}
		else if (obecny->liczba == klucz)
		{
			cout << "TEN KLUCZ JUZ JEST" << endl;
		}

	}
}
void Dodawanko_losowe(sdizo*&root, int ilosc)
{

	int i = 0;
	while (i < ilosc)
	{
		int a = rand() % 1000000 + 10;
		wstaw_ele(root, a);
		i++;

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
				cout << "Tego klucza nie ma" << endl;
				break;
			}
			obecny = obecny->prawy;

		}
		else if (obecny->liczba > klucz)
		{
			if (obecny->lewy == NULL)
			{
				cout << "Tego klucza nie ma" << endl;
				break;
			}
			obecny = obecny->lewy;
		}
		else if (obecny->liczba == klucz)
		{
			cout << "Dany klucz znajduje sie w drzewie" << endl;
			break;
		}


	}
}

void przejscie_inorder(sdizo*&root)
{

	if (root != NULL)
	{
		przejscie_inorder(root->lewy);
		cout << root->liczba << " " << root->znaczek << endl;
		przejscie_inorder(root->prawy);
		Zliczanko++;
	}

}
void przejscie_postorder(sdizo*&root)
{

	if (root != NULL)
	{
		przejscie_postorder(root->lewy);
		przejscie_postorder(root->prawy);
		cout << root->liczba << " " << root->znaczek << endl;
		Zliczanko++;
	}

}
void przejscie_preorder(sdizo*&root)
{

	if (root != NULL)
	{
		cout << root->liczba << " " << root->znaczek << endl;
		przejscie_preorder(root->lewy);
		przejscie_preorder(root->prawy);
		Zliczanko++;
	}

}
void usuwanko(sdizo*&root, int klucz)
{
	sdizo*obecny = root;
	sdizo*tatus = NULL;
	if (obecny == NULL)
	{
		cout << "Drzewko puste" << endl;
	}
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
		cout << "Takiego klucza nie bylo" << endl;
		return;
	}
	if ((obecny->prawy == NULL) && (obecny->lewy == NULL))//mamy listek
	{
		if (obecny == root)
		{
			root = NULL;//listek jako korzen 
			return;
		}
		if (tatus->prawy == obecny)
		{
			tatus->prawy = NULL;
			return;
		}
		else
		{
			tatus->lewy = NULL;
			return;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////
	if (obecny->prawy == NULL)//ma jedyniie tylko lewe poddrzewo ... tak twierdzi Chocian
	{
		if (obecny == root)
		{
			root = obecny->lewy;//usuwamy korzonki
			return;

		}
		else if (tatus->prawy == obecny)
		{
			tatus->prawy = obecny->lewy;
			return;
		}
		else
		{
			tatus->lewy = obecny->lewy;
			return;
		}
	}
	if (obecny->lewy == NULL)//wezel ma jedynie prawe poddrzewo
	{
		if (obecny = root)
		{
			root = obecny->prawy;
			return;
		}
		else if (tatus->prawy == obecny)
		{
			tatus->prawy = obecny->prawy;
			return;
		}
		else
		{
			tatus->lewy = obecny->prawy;
			return;
		}
	}
	///usuwany wezelek ma dwa poddrzewa, poprzednik:wezel maxi w lewym poddrzewie; mini w prawym;
	//poprzednik
	sdizo*staruszek = NULL;
	sdizo*dzidzia = NULL;
	staruszek = obecny;
	dzidzia = obecny->lewy;
	while (dzidzia->prawy != NULL)
	{
		staruszek = dzidzia;
		dzidzia = dzidzia->prawy;
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
		return;
	}
	//poprzednik nie jest lewym potomkiem a jego wnukiem  lub dalej
	sdizo*pradzidzia = NULL;

	pradzidzia = dzidzia->lewy;//potomek poprzednika
	//adopcja
	if (staruszek->prawy == pradzidzia)
	{
		staruszek->prawy = pradzidzia;
		return;
	}
	else
	{
		staruszek->lewy = pradzidzia;
		return;
	}
	//adopcja poprzednika przez rodzica usuwanego wezla
	dzidzia->lewy = obecny->lewy;
	if (obecny == root)
	{
		root = dzidzia;
		return;
	}
	else if (tatus->prawy == obecny)
	{
		tatus->prawy = dzidzia;
		return;
	}
	else
	{
		tatus->lewy = dzidzia;
		return;
	}

}


int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	int k1, k2, k3, k4, losowanko;
	fstream plik;
	plik.open("inlab03.txt", ios::in);
	if (plik.good() == false)
		return -1;      ///  zabezpieczenie
	plik >> losowanko;
	plik >> k1;
	plik >> k2;
	plik >> k3;
	plik >> k4;


	sdizo*root = nullptr;

	///////////////////////////////////funkcje drzewka
	usuwanko(root, k1);
	wstaw_ele(root, k1);
	Dodawanko_losowe(root, losowanko);
	przejscie_inorder(root);
	przejscie_preorder(root);
	wstaw_ele(root, k2);
	przejscie_inorder(root);
	wstaw_ele(root, k3);
	wstaw_ele(root, k4);
	usuwanko(root, k1);
	przejscie_preorder(root);
	poszukiwanko(root, k1);
	usuwanko(root, k2);
	przejscie_inorder(root);
	usuwanko(root, k3);
	usuwanko(root, k4);


	////////////////////////////////koniec funkcji
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Czas trwania: %f", time_spent);
	plik.close();

	return 0;
}
