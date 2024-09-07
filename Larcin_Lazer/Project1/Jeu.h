#ifndef Jeu_H
#define Jeu_H

#include <vector>
#include "Menu.h"
#include "Joueur.h"
#include "Carte.h"
#include "Son.h"
#include <SFML/Audio.hpp>

// Classe faite par Flavien et Malo

// Cette classe permet de g�rer le d�roulement du jeu (d�placement du joueur, volume, difficult�, ...)
// ainsi que l'aspect visuel de la fen�tre (dessiner lma carte, la grille, les lasers, ...)

class Jeu
{
	Menu menu_; //composition de la classe Menu
	Joueur joueur_; //composition de la classe joueur
	int difficulty_; //Permet de d�tecter la difficult�
	sf::Sound death_; //Musique de la mort
	Son* bande_son_;
	int niveauMax_;
	string nom_;

	int colorR;
	int colorG;
	int colorB;
public:

	// Constructeur de la classe qui prends en param�tre un joueur 
	// et qui initialise sa position, son niveau, son �tat (vie/mort) et la musique de fond.
	Jeu(Joueur joueur, Menu menu, Son* bande_son);//Flavien

	// r�cup�re la difficult� du jeu
	int GetDifficulty() { return difficulty_; }

	int GetNiveauxMax() { return niveauMax_; }

	string GetNom() { return nom_; }

	void SetNom(string nom);

	void SetNiveauMax(int i);

	// r�cup�re le num�ro du niveau du joueur
	int GetNiveau() { return joueur_.GetNiveau(); }

	// R�cup�re l'info pour savoir si le joueur est dans le jeu (false signifie que le joueur est dans les menus) 
	bool GetinGame() { return joueur_.GetinGame(); }

	// R�cup�re le nombre total de niveaux
	int GetNombreNiveaux() { return joueur_.GetCartes().size(); }

	//permet de choisir un niveau en normal , difficile ou hardcore � partir d'un entier
	//correspondant eu num�ro du niveau +1 (le niveau 0 se lance quand i=1)
	void SetNiveau(int i);//Malo

	// d�fini la difficult� du jeu (Test, Normale, Difficile ou Hardcore) � partir d'un entier
	void SetDifficulty(int val);//Malo

	//Prend en entr�e la fen�tre et un vector de rectangle et utilise ces rectangles pour dessiner 
	// le quadrillage
	void grille(sf::RenderWindow& window, std::vector<sf::RectangleShape> lines);//Flavien

	//Prends en entr�e la fen�tre, deux entier correspondant � la position de la case o� se trouve le laser,
	// un vecteur de rectangle et un bool�en pour savoir si les lasers doivent s'afficher.
	// La m�thode affiche les lasers sur la carte.
	void drawlaser(sf::RenderWindow& window,int i, int j, std::vector<sf::RectangleShape> lines, bool visible, sf::Color color);//Flavien

	//Prends en entr�e la fen�tre, deux entier correspondant � la position de la case o� se trouve la porte,
	// un vecteur de rectangle et un vecteur de cercle.
	//La m�thode dessine la porte lorsqu'elle est ferm�e.
	void DrawPorteFerme(sf::RenderWindow& window,int i, int j, std::vector<sf::RectangleShape> lines, std::vector<sf::CircleShape> circle);//Flavien
	
	//Prends en entr�e la fen�tre, deux entier correspondant � la position de la case o� se trouve la porte
	//et un vecteur de rectangle.
	//La m�thode dessine la porte lorsqu'elle est ouverte.
	void DrawPorteOuverte(sf::RenderWindow& window, int i, int j, std::vector<sf::RectangleShape> lines);//Flavien
	
	// Prends en entr�e la fen�tre, un bool�en permettant de savoir si les lasers sont visibles
	// Un vecteur de cercles, un vecteur d'images et un vecteur de rectangles.
	// La m�thode dessine la carte du jeu � partir d'un tableau d'entier r�cup�r� dans la classe joueur.
	void drawGrid(sf::RenderWindow& window, bool visible, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle, float vitesseBlaser);//Flavien
	
	// Prends en param�tre la fen�tre de jeu.
	// Permet de controler le joueur, d'appeler les m�thodes qui affichent la carte et celles qui g�rent les 
	// interactions entre le joueur et la carte.
	void controle(sf::RenderWindow& window);//Flavien
	
	// initialise les donn�es utiles (position du personnage, musique, le champs setInGame_ et l'�tat du joueur)
	// puis appelle la m�thode controle.
	void game(sf::RenderWindow& window);//Malo
	
	// Prends en entr�e la fen�tre et des vecteurs de cercles, de rectangles et d'images.
	// Joue l'animation de mort avant d'appeler la m�thode MortJoueur de la classe Joueur.
	void MortAnimation(sf::RenderWindow& window, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle);
	
	// Prends en entr�e la fen�tre, les coordonn�es du joueur (i et j) et un vecteur de rectangle.
	// Permet de dessiner la trace du joueur (difficult� Test et Normale).
	void tracejoueur(sf::RenderWindow& window, int j, int i, std::vector<sf::RectangleShape> tra);//Flavien
	
	// renvoie un nombre al�atoire entre 0 et son param�tre d'entr�e
	long random_at_most(long max);//Malo
	
	// r�initialise la carte (repositionne la gemme, ferme la porte etc)
	void reinitialisation();//Flavien

	void LireNiveaux();

	//Dessine les lasers li�s au levier
	void DrawLaserLevier(sf::RenderWindow& window, int i, int j, std::vector<sf::RectangleShape> lines, sf::Color color); //Malo

	// Dessine les Blasers, des lasers qui se d�placent dans la carte
	void Blaser(sf::RenderWindow& window, float progression, bool ordonne); //Flavien

	void save();
	void load(string nom);

	void AjouterCarte(Cartes carte);

	void SaveLevel();

	void ChangeTimer(int timer);
};
#endif


