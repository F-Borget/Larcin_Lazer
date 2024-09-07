#ifndef Jeu_H
#define Jeu_H

#include <vector>
#include "Menu.h"
#include "Joueur.h"
#include "Carte.h"
#include "Son.h"
#include <SFML/Audio.hpp>

// Classe faite par Flavien et Malo

// Cette classe permet de gérer le déroulement du jeu (déplacement du joueur, volume, difficulté, ...)
// ainsi que l'aspect visuel de la fenêtre (dessiner lma carte, la grille, les lasers, ...)

class Jeu
{
	Menu menu_; //composition de la classe Menu
	Joueur joueur_; //composition de la classe joueur
	int difficulty_; //Permet de détecter la difficulté
	sf::Sound death_; //Musique de la mort
	Son* bande_son_;
	int niveauMax_;
	string nom_;

	int colorR;
	int colorG;
	int colorB;
public:

	// Constructeur de la classe qui prends en paramètre un joueur 
	// et qui initialise sa position, son niveau, son état (vie/mort) et la musique de fond.
	Jeu(Joueur joueur, Menu menu, Son* bande_son);//Flavien

	// récupère la difficulté du jeu
	int GetDifficulty() { return difficulty_; }

	int GetNiveauxMax() { return niveauMax_; }

	string GetNom() { return nom_; }

	void SetNom(string nom);

	void SetNiveauMax(int i);

	// récupère le numéro du niveau du joueur
	int GetNiveau() { return joueur_.GetNiveau(); }

	// Récupère l'info pour savoir si le joueur est dans le jeu (false signifie que le joueur est dans les menus) 
	bool GetinGame() { return joueur_.GetinGame(); }

	// Récupère le nombre total de niveaux
	int GetNombreNiveaux() { return joueur_.GetCartes().size(); }

	//permet de choisir un niveau en normal , difficile ou hardcore à partir d'un entier
	//correspondant eu numéro du niveau +1 (le niveau 0 se lance quand i=1)
	void SetNiveau(int i);//Malo

	// défini la difficulté du jeu (Test, Normale, Difficile ou Hardcore) à partir d'un entier
	void SetDifficulty(int val);//Malo

	//Prend en entrée la fenêtre et un vector de rectangle et utilise ces rectangles pour dessiner 
	// le quadrillage
	void grille(sf::RenderWindow& window, std::vector<sf::RectangleShape> lines);//Flavien

	//Prends en entrée la fenêtre, deux entier correspondant à la position de la case où se trouve le laser,
	// un vecteur de rectangle et un booléen pour savoir si les lasers doivent s'afficher.
	// La méthode affiche les lasers sur la carte.
	void drawlaser(sf::RenderWindow& window,int i, int j, std::vector<sf::RectangleShape> lines, bool visible, sf::Color color);//Flavien

	//Prends en entrée la fenêtre, deux entier correspondant à la position de la case où se trouve la porte,
	// un vecteur de rectangle et un vecteur de cercle.
	//La méthode dessine la porte lorsqu'elle est fermée.
	void DrawPorteFerme(sf::RenderWindow& window,int i, int j, std::vector<sf::RectangleShape> lines, std::vector<sf::CircleShape> circle);//Flavien
	
	//Prends en entrée la fenêtre, deux entier correspondant à la position de la case où se trouve la porte
	//et un vecteur de rectangle.
	//La méthode dessine la porte lorsqu'elle est ouverte.
	void DrawPorteOuverte(sf::RenderWindow& window, int i, int j, std::vector<sf::RectangleShape> lines);//Flavien
	
	// Prends en entrée la fenêtre, un booléen permettant de savoir si les lasers sont visibles
	// Un vecteur de cercles, un vecteur d'images et un vecteur de rectangles.
	// La méthode dessine la carte du jeu à partir d'un tableau d'entier récupéré dans la classe joueur.
	void drawGrid(sf::RenderWindow& window, bool visible, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle, float vitesseBlaser);//Flavien
	
	// Prends en paramètre la fenêtre de jeu.
	// Permet de controler le joueur, d'appeler les méthodes qui affichent la carte et celles qui gèrent les 
	// interactions entre le joueur et la carte.
	void controle(sf::RenderWindow& window);//Flavien
	
	// initialise les données utiles (position du personnage, musique, le champs setInGame_ et l'état du joueur)
	// puis appelle la méthode controle.
	void game(sf::RenderWindow& window);//Malo
	
	// Prends en entrée la fenêtre et des vecteurs de cercles, de rectangles et d'images.
	// Joue l'animation de mort avant d'appeler la méthode MortJoueur de la classe Joueur.
	void MortAnimation(sf::RenderWindow& window, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle);
	
	// Prends en entrée la fenêtre, les coordonnées du joueur (i et j) et un vecteur de rectangle.
	// Permet de dessiner la trace du joueur (difficulté Test et Normale).
	void tracejoueur(sf::RenderWindow& window, int j, int i, std::vector<sf::RectangleShape> tra);//Flavien
	
	// renvoie un nombre aléatoire entre 0 et son paramètre d'entrée
	long random_at_most(long max);//Malo
	
	// réinitialise la carte (repositionne la gemme, ferme la porte etc)
	void reinitialisation();//Flavien

	void LireNiveaux();

	//Dessine les lasers liés au levier
	void DrawLaserLevier(sf::RenderWindow& window, int i, int j, std::vector<sf::RectangleShape> lines, sf::Color color); //Malo

	// Dessine les Blasers, des lasers qui se déplacent dans la carte
	void Blaser(sf::RenderWindow& window, float progression, bool ordonne); //Flavien

	void save();
	void load(string nom);

	void AjouterCarte(Cartes carte);

	void SaveLevel();

	void ChangeTimer(int timer);
};
#endif


