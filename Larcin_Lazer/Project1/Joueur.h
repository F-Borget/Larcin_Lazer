
#ifndef Joueur_H
#define Joueur_H
#include "Carte.h"
#include<iostream>
#include <vector>
#include "Son.h"
#include <SFML/Graphics.hpp>

using namespace std;

// Classe faite par Flavien et Malo

// La classe Joueur permet de gérer les interactions entre le joueur et la carte. 

class Joueur
{
	bool etat_;
	int positionXY_ [2];
	vector <Cartes> carte_;
	int niveau_;
	int trace_[25][14] = { 0 };
	bool inGame_;
	int difficulty_;
	float posBlaserHaut_;
	float posBlaserGauche_;
	float posBlaserBas_;
	float posBlaserDroite_;
	bool invertScreen_;
public :
	Joueur();//Malo
	Joueur(int positionXY[2], int niveau, bool etat = true);//Malo
	bool GetEtat() { return etat_; }
	bool GetinGame() { return inGame_; }
	void SetinGame(bool val);//Malo
	float GetPosBlaserHaut() { return posBlaserHaut_; }
	float GetPosBlaserGauche() { return posBlaserGauche_; }
	float GetPosBlaserBas() { return posBlaserBas_; }
	float GetPosBlaserDroite() { return posBlaserDroite_; }
	bool GetInvertScreen() { return invertScreen_; }
	void SetPosBlaserHaut(float i);
	void SetPosBlaserGauche(float i);
	void SetPosBlaserBas(float i);
	void SetPosBlaserDroite(float i);
	int GetX() { return positionXY_[0]; }
	int GetY() { return positionXY_[1]; }
	int GetTrace(int i, int j) { return trace_[i][j]; }
	void SetEtat(bool etat);//Malo
	void SetNiveau(int i);//Malo
	void GemmeRecolte();//Malo //Permet de récolter la gemme et d'ouvrir la sortie du niveau
	void MortJoueur(sf::RenderWindow& window);//Malo //Réinitialise la carte (position du joueur, état de la gemme et de la sortie)
	void PorteTouche(sf::RenderWindow& window, Son* son); //Flavien // permet de passer d'un niveau à un autre
	void AjouterCarte(Cartes carte);//Malo
	void cle(int val);//Malo
	bool Update(sf::RenderWindow& window, Son* son); //Malo//Effectue les vérifications quant à la position du joueur sur la carte
	int GetValeurMap(int x, int y) { return carte_[niveau_].GetValeurMap(x,y); }
	void SetXY(int x,int y);//Malo
	int GetNiveau() { return niveau_; }
	vector<Cartes> GetCartes() { return carte_; }
	void operator=(Joueur joueur);//Malo
	void DrawPerso(sf::RenderWindow& window, int numero);//Flavien
	void Trace(int i, int j);//Flavien
	void SetDiff(int i);//Malo
	void reinitialisation();//Flavien
	void TP1(int val);//Flavien
	void TP2(int val);//Flavien
	void levierTouche(); //Malo
	void SetValeurMap(int x, int y, int val);

	void affTab();
};
#endif