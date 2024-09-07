#include "Carte.h"
#include <iostream>
using namespace std;
#pragma once




void Cartes::SetValeurMap(int x, int y, int val)
{
	map_[x][y] = val;
}

Cartes::Cartes(int map[25][14])
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			map_[j][i] = map[j][i];
			if (map[j][i] == 2)//gemme
			{
				positionGemme_[0] = j;
				positionGemme_[1] = i;
			}
			if (map[j][i] == 4)//porte ferme
			{
				positionSortie_[0] = j;
				positionSortie_[1] = i;
			}
			if (map[j][i] == 6)//depart
			{
				positionJoueurDebut_[0] = j;
				positionJoueurDebut_[1] = i;
			}
		}
	}
}

void Cartes::SetSortie(int j, int i)
{
	positionSortie_[0] = j;
	positionSortie_[1] = i;
}

void Cartes::SetDebut(int j, int i)
{
	positionJoueurDebut_[0] = j;
	positionJoueurDebut_[1] = i;
}