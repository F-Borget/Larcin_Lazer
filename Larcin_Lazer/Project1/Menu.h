#pragma once
#ifndef Menu_H
#define Menu_H
//#include "Jeu.h"
#include <SFML/Audio.hpp>
#include "Joueur.h"
#include "Carte.h"
#include "Son.h"

class Jeu;
// Flavien s'est occup� de la partie interactive. Malo s'est occup� de la structure et des fonctionnalit�s�des�boutons et de la musique.

// Cette classe g�re les diff�rents menus (menu principal, d'options et de cr�dits)

class Menu
{
	Son* musique_;
	
public :
	Menu();

	string MenuTexte(sf::RenderWindow& window, Jeu jeu);

	// constructeur qui initialise la musique (recherche dans les fichiers).
	Menu(Son* bande_son); 

	 // cr�� le menu principal. Prends en param�tre la fen�tre et une variable de type Jeu.
	void MainMenu(sf::RenderWindow& window, Jeu& jeu);

	// cr�� le menu des options pour g�rer le volume et la difficult�. Prends en param�tre la fen�tre et une variable de type Jeu.
	void MenuOption(sf::RenderWindow& window, Jeu& jeu);

	// cr�� un menu de cr�dits. Prends en param�tre la fen�tre.
	void MenuCredits(sf::RenderWindow& window);

	void operator=(Menu menu);

	Son* GetMusique() { return musique_; }

	void MenuEdit(sf::RenderWindow& window, Jeu& jeu);

	void DrawCarre(sf::RenderWindow& window, int i, int j);

	void drawGridEdit(sf::RenderWindow& window, Jeu& jeu, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle, float vitesseBlaser, int map[25][14], sf::Text text);

	void SetValeurMap(int x, int y, int map[25][14], bool sens);
};



#endif Menu_H