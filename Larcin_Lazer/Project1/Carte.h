#ifndef Cartes_h
#define Cartes_h

// Faite par Malo

// La classe Cartes permet de construire une carte de jeu et stocker les différentes informations liées
// à celle-ci (emplacement de la gemme, de la porte, des lasers etc)

class Cartes 
{
	int positionJoueurDebut_[2]; //Position du joueur dans la carte au début du niveau
	int positionGemme_[2]; //position de la gemme
	int positionSortie_[2]; //position de la sortie
	int map_[25][14]; //tableau d'entier correspondant à la carte du jeu
public:
	//constructeur qui permet d'avoir les 6 valeur des return ci dessous
	Cartes(int map[25][14] = { 0 });

	int GetValeurMap(int x, int y) { return map_[x][y];}
	int GetPositionXJoueurDebut() { return positionJoueurDebut_[0];}
	int GetPositionYJoueurDebut() { return positionJoueurDebut_[1]; }
	int GetPositionGemmeX() { return positionGemme_[0]; }
	int GetPositionGemmeY() { return positionGemme_[1]; }	
	int GetPositionSortieX() { return positionSortie_[0]; }
	int GetPositionSortieY() { return positionSortie_[1]; }

	void SetSortie(int j, int i);
	void SetDebut(int j, int i);

	//Prend en entré les coordonnes et une valeur qui sera attribué au tableau a ses coordonnées
	void SetValeurMap(int x, int y, int val);
};
#endif