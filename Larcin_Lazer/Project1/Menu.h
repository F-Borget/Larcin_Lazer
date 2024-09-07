#pragma once
#ifndef Menu_H
#define Menu_H
//#include "Jeu.h"
#include <SFML/Audio.hpp>
#include "Joueur.h"
#include "Carte.h"
#include "Son.h"

class Jeu;
// Flavien s'est occupé de la partie interactive. Malo s'est occupé de la structure et des fonctionnalités des boutons et de la musique.

// Cette classe gère les différents menus (menu principal, d'options et de crédits)

class Menu
{
	Son* musique_;
	
public :
	Menu();

	string MenuTexte(sf::RenderWindow& window, Jeu jeu);

	// constructeur qui initialise la musique (recherche dans les fichiers).
	Menu(Son* bande_son); 

	 // créé le menu principal. Prends en paramètre la fenêtre et une variable de type Jeu.
	void MainMenu(sf::RenderWindow& window, Jeu& jeu);

	// créé le menu des options pour gérer le volume et la difficulté. Prends en paramètre la fenêtre et une variable de type Jeu.
	void MenuOption(sf::RenderWindow& window, Jeu& jeu);

	// créé un menu de crédits. Prends en paramètre la fenêtre.
	void MenuCredits(sf::RenderWindow& window);

	void operator=(Menu menu);

	Son* GetMusique() { return musique_; }

	void MenuEdit(sf::RenderWindow& window, Jeu& jeu);

	void DrawCarre(sf::RenderWindow& window, int i, int j);

	void drawGridEdit(sf::RenderWindow& window, Jeu& jeu, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle, float vitesseBlaser, int map[25][14], sf::Text text);

	void SetValeurMap(int x, int y, int map[25][14], bool sens);
};



#endif Menu_H