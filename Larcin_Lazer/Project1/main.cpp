#include <iostream>
#include "Son.h"
#include "Joueur.h"
#include "Carte.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Jeu.h"
#include <windows.h>
#include "Menu.h"

using namespace std;



int main()
{
	srand(time(NULL));
	int pos[2] = { 1,1 };
	Son son;
	Son* bande_son;
	bande_son = &son;
	Menu menu(bande_son);
	Joueur joueur(pos, 0, true);
	Jeu jeu(joueur, menu, bande_son);

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "jeu", sf::Style::Fullscreen);

	jeu.SetNiveau(40);
	joueur.SetinGame(true);
	jeu.SetDifficulty(2);
	jeu.SetNom(menu.MenuTexte(window, jeu));
	jeu.load(jeu.GetNom());
	menu.MainMenu(window, jeu);
	jeu.save();
	return 0;
}