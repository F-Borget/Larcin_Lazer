#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Jeu.h"
#include "joueur.h"
#include "Menu.h"
#include "Carte.h"
#include <fstream>
#include "Windows.h"
#include <SFML/Audio.hpp>
#include <stdlib.h> // For random(), RAND_MAX
#include <random>
#include <sstream>
using namespace std;

void Jeu::DrawLaserLevier(sf::RenderWindow& window, int i, int j, std::vector<sf::RectangleShape> lines, sf::Color color)
{
	int t = lines.size();
	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 73)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 73)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 73)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 73)));
	
	lines[t].setPosition(25 + j * 75,  i * 75);
	lines[t + 1].setPosition(50 + j * 75, i * 75);
	lines[t + 2].setPosition( (j+1) * 75, 25 + i * 75);
	lines[t + 3].setPosition( (j+1) * 75, 50 + i * 75);
	lines[t + 2].rotate(90);
	lines[t + 3].rotate(90);

	lines[t].setFillColor(color);
	lines[t + 1].setFillColor(color);
	lines[t + 2].setFillColor(color);
	lines[t + 3].setFillColor(color);
	for (i = 0; i < 4; i++)//tracer les lignes
		window.draw(lines[t + i]);
}

void Jeu::grille(sf::RenderWindow& window,std::vector<sf::RectangleShape> lines)
{
	
	int i = 0;

	for (i = 0; i < 24; i++)
	{
		lines.push_back(sf::RectangleShape(sf::Vector2f(5, 1080)));// Lignes verticales
	}
	
	for (i; i < 37; i++)
	{
		lines.push_back(sf::RectangleShape(sf::Vector2f(1920, 5)));// Lignes horizontales
	}
	int a = 73;

	for (i = 0; i < 24; i++)
	{
		lines[i].setPosition(a, 0); //Positionnement des lignes verticales
		a = a + 75;
	}
	a = 73;
	for (i; i < 37; i++)
	{

		lines[i].setPosition(0, a);//Positionnement des lignes horizontales
		a = a + 75;
	}
	lines.push_back(sf::RectangleShape(sf::Vector2f(50, 1080)));
	lines[37].setPosition(24*75+73, 0);
	lines.push_back(sf::RectangleShape(sf::Vector2f(1920, 50)));
	lines[38].setPosition(0, 13*75+73);

	for (size_t i = 0; i < lines.size(); i++)// couleur cadrillage
		lines[i].setFillColor(sf::Color(max(colorR - 50, 0), max(colorG - 100, 0), max(colorB - 100, 0)));
	for (size_t i = 0; i < lines.size(); i++)//tracer les lignes
		window.draw(lines[i]);
		
}

void Jeu::drawlaser(sf::RenderWindow& window,int i, int j, std::vector<sf::RectangleShape> lines, bool visible, sf::Color color)
{
	int laser1 = random_at_most(55) + 15;//4 lignes permettent aux lasers de bouger
	int laser2 =random_at_most(40) + 5;
	int laser3 =  random_at_most(30) + 30;
	int laser4 =  random_at_most(5) + 5;
	if (visible)
	{
		//placement des laser
		int t = lines.size();
		lines.push_back(sf::RectangleShape(sf::Vector2f(5, 72)));
		lines.push_back(sf::RectangleShape(sf::Vector2f(5, 76)));
		lines.push_back(sf::RectangleShape(sf::Vector2f(5, 76)));
		lines.push_back(sf::RectangleShape(sf::Vector2f(5, 85)));
		
		lines[t].setPosition(laser1 + j * 75, 2 + i * 75);
		lines[t + 1].setPosition(laser2 + j * 75, 3 + i * 75);
		lines[t + 2].setPosition(75 + j * 75, laser3 + i * 75);
		lines[t + 3].setPosition(71 + j * 75, laser4 + i * 75);
		lines[t].rotate(10);
		lines[t + 1].rotate(340);
		lines[t + 2].rotate(110);
		lines[t + 3].rotate(40);
		lines[t].setFillColor(color);
		lines[t + 1].setFillColor(color);
		lines[t + 2].setFillColor(color);
		lines[t + 3].setFillColor(color);
		for (i = 0; i < 4; i++)//tracer les lignes
			window.draw(lines[t + i]);
	}
}

void Jeu::DrawPorteFerme(sf::RenderWindow& window,int i, int j, std::vector<sf::RectangleShape> lines, std::vector<sf::CircleShape> circle)
{
	int t = lines.size();//dessine porte
	int c = circle.size();//dessine poigner
	circle.push_back(sf::CircleShape(7));
	lines.push_back(sf::RectangleShape(sf::Vector2f(35, 60)));
	lines[t].setPosition(20 + j * 75, 9 + i * 75);
	if (joueur_.GetInvertScreen())
	{
		circle[c].setPosition(38 + j * 75, 30 + i * 75);
	}
	else
	{
		circle[c].setPosition(23 + j * 75, 30 + i * 75);
	}
	lines[t].setFillColor(sf::Color(191, 75, 0));
	circle[c].setFillColor(sf::Color::Black);
	window.draw(lines[t]);
	window.draw(circle[c]);
}

void Jeu::DrawPorteOuverte(sf::RenderWindow& window, int i, int j, std::vector<sf::RectangleShape> lines)
{
	int l = lines.size();
	lines.push_back(sf::RectangleShape(sf::Vector2f(35, 60)));
	sf::ConvexShape trapeze;
	trapeze.setPointCount(4);
	if (!joueur_.GetInvertScreen())
	{
		trapeze.setPoint(0, sf::Vector2f(55 + j * 75, 9 + i * 75));
		trapeze.setPoint(1, sf::Vector2f(55 + j * 75, 69 + i * 75));
		trapeze.setPoint(2, sf::Vector2f(65 + j * 75, 75 + i * 75));
		trapeze.setPoint(3, sf::Vector2f(65 + j * 75, 3 + i * 75));
	}
	else
	{
		trapeze.setPoint(0, sf::Vector2f(20 + j * 75, 75 + i * 75));
		trapeze.setPoint(1, sf::Vector2f(20 + j * 75, 3 + i * 75));
		trapeze.setPoint(2, sf::Vector2f(30 + j * 75, 9 + i * 75));
		trapeze.setPoint(3, sf::Vector2f(30 + j * 75, 69 + i * 75));
	}
	lines[l].setPosition(20 + j * 75, 9 + i * 75);
	lines[l].setFillColor(sf::Color::Black);
	trapeze.setFillColor(sf::Color(191, 75, 0));
	window.draw(lines[l]);
	window.draw(trapeze);

}

void Jeu::drawGrid(sf::RenderWindow& window, bool visible, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle, float vitesseBlaser)
{
	vector<sf::RectangleShape> lines;//forme rectangulaire dessin
	vector<sf::CircleShape> circle;// forme circulaire dessin
	vector<sf::RectangleShape> tra;//dessine la trace du joueur

	int i;
	int j;
	int t;

	grille(window, lines);// dessine le cardillage de fond 

	if (joueur_.GetInvertScreen())
	{
		textureRectangle[0].setOrigin(sf::Vector2f(textureRectangle[0].getLocalBounds().width / 2, textureRectangle[0].getLocalBounds().height / 2));
		textureRectangle[0].rotate(180);
		textureRectangle[0].setOrigin(sf::Vector2f(textureRectangle[0].getLocalBounds().width, textureRectangle[0].getLocalBounds().height));
	}
	if (joueur_.GetInvertScreen())
	{
		textureCercle[1].setOrigin(sf::Vector2f(textureCercle[1].getLocalBounds().width / 2, textureCercle[1].getLocalBounds().height / 2));
		textureCercle[1].rotate(180);
		textureCercle[1].setOrigin(sf::Vector2f(textureCercle[1].getLocalBounds().width, textureCercle[1].getLocalBounds().height));
	}
	if (joueur_.GetInvertScreen())
	{
		textureRectangle[12].setOrigin(sf::Vector2f(textureRectangle[12].getLocalBounds().width / 2, textureRectangle[12].getLocalBounds().height / 2));
		textureRectangle[12].rotate(180);
		textureRectangle[12].setOrigin(sf::Vector2f(textureRectangle[12].getLocalBounds().width, textureRectangle[12].getLocalBounds().height));
	}

	for (i = 0; i < 14; i++)//14 = taille en ordonée
	{
		for (j = 0; j < 25; j++)//25 = taille en abcisse
		{
			if (difficulty_ > 1)//plusieur difficulté change les graphisme
			{
				switch (joueur_.GetValeurMap(j, i))
				{

				case -1://case foncé
					t = lines.size();
					lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
					lines[t].setPosition(j * 75, i * 75);
					lines[t].setFillColor(sf::Color(max(colorR - 50, 0), max(colorG - 100, 0), max(colorB - 100, 0)));
					window.draw(lines[t]);
					break;
				case 0: // case vide
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 1:// laser
					drawlaser(window, i, j, lines, visible, sf::Color::Red);
					break;
				case 2:// gemme non recolté
					textureCercle[0].setTexture(texturePng[0]);
					textureCercle[0].setPosition(4 + j * 75, 4 + i * 75);
					if (joueur_.GetInvertScreen())
					{
						textureCercle[0].setOrigin(sf::Vector2f(textureCercle[0].getLocalBounds().width / 2, textureCercle[0].getLocalBounds().height / 2));
						textureCercle[0].rotate(180);
						textureCercle[0].setOrigin(sf::Vector2f(textureCercle[0].getLocalBounds().width, textureCercle[0].getLocalBounds().height));
					}
					textureCercle[0].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[0]);
					break;
				case 3:// gemme recolté (case vide)
					tracejoueur(window, j, i, tra);
					break;
				case 4:// porte bloqué
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawPorteFerme(window, i, j, lines, circle);
					break;
				case 5:// porte ouverte
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawPorteOuverte(window, i, j, lines);
					break;
				case 6:// position de départ
					tracejoueur(window, j, i, tra);
					if (difficulty_ == 4)
					{
						textureRectangle[7].setTexture(texturePng[9]);
						if (joueur_.GetInvertScreen())
						{
							textureRectangle[7].setOrigin(sf::Vector2f(textureRectangle[7].getLocalBounds().width / 2, textureRectangle[7].getLocalBounds().height / 2));
							textureRectangle[7].rotate(180);
							textureRectangle[7].setOrigin(sf::Vector2f(textureRectangle[7].getLocalBounds().width, textureRectangle[7].getLocalBounds().height));
						}
						textureRectangle[7].setPosition(j * 75, 12 + i * 75);
						window.draw(textureRectangle[7]);//pour position du début
					}
					break;
				case 51://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 52://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 53://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 54://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 55://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 56://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 57://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 58://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 59://clef 1
					textureRectangle[0].setTexture(texturePng[1]);
					textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
					window.draw(textureRectangle[0]);
					break;
				case 61:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 62:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 63:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 64:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 65:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 66:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 67:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 68:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 69:// clef 1 recolté
					tracejoueur(window, j, i, tra);
					break;
				case 71://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 72://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 73://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 74://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 75://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 76://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 77://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 78://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;
				case 79://cadenas 1
					textureCercle[1].setTexture(texturePng[2]);
					textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureCercle[1]);
					break;

				case 81: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 82: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 83: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 84: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 85: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 86: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 87: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 88: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 89: //cadenas 1 recolté
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 21://fleche vers le bas 
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					if (!joueur_.GetInvertScreen())
					{
						textureRectangle[8].setTexture(texturePng[10]);
						textureRectangle[8].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[8]);
					}
					else
					{
						textureRectangle[9].setTexture(texturePng[11]);
						textureRectangle[9].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[9]);
					}
					break;
				case 22://fleche vers le haut
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[8].setTexture(texturePng[10]);
						textureRectangle[8].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[8]);
					}
					else
					{
						textureRectangle[9].setTexture(texturePng[11]);
						textureRectangle[9].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[9]);
					}
					break;
				case 23://fleche vers la gauche
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					if (!joueur_.GetInvertScreen())
					{
						textureRectangle[10].setTexture(texturePng[12]);
						textureRectangle[10].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[10]);
					}
					else
					{
						textureRectangle[11].setTexture(texturePng[13]);
						textureRectangle[11].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[11]);
					}
					break;
				case 24://fleche vers la droite
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[10].setTexture(texturePng[12]);
						textureRectangle[10].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[10]);
					}
					else
					{
						textureRectangle[11].setTexture(texturePng[13]);
						textureRectangle[11].setPosition(4 + j * 75, 4 + i * 75);
						window.draw(textureRectangle[11]);
					}
					break;
				case -2://décoration
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[1].setTexture(texturePng[3]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[1].setOrigin(sf::Vector2f(textureRectangle[1].getLocalBounds().width / 2, textureRectangle[1].getLocalBounds().height / 2));
						textureRectangle[1].rotate(180);
						textureRectangle[1].setOrigin(sf::Vector2f(textureRectangle[1].getLocalBounds().width, textureRectangle[1].getLocalBounds().height));
					}
					textureRectangle[1].setPosition(5 + j * 75, 5 + i * 75);
					window.draw(textureRectangle[1]);
					break;
				case -3://décoration
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[2].setTexture(texturePng[4]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[2].setOrigin(sf::Vector2f(textureRectangle[2].getLocalBounds().width / 2, textureRectangle[2].getLocalBounds().height / 2));
						textureRectangle[2].rotate(180);
						textureRectangle[2].setOrigin(sf::Vector2f(textureRectangle[2].getLocalBounds().width, textureRectangle[2].getLocalBounds().height));
					}
					textureRectangle[2].setPosition(14 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[2]);
					break;
				case -4://décoration
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[3].setTexture(texturePng[5]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[3].setOrigin(sf::Vector2f(textureRectangle[3].getLocalBounds().width / 2, textureRectangle[3].getLocalBounds().height / 2));
						textureRectangle[3].rotate(180);
						textureRectangle[3].setOrigin(sf::Vector2f(textureRectangle[3].getLocalBounds().width, textureRectangle[3].getLocalBounds().height));
					}
					textureRectangle[3].setPosition(5 + j * 75, 5 + i * 75);
					window.draw(textureRectangle[3]);
					break;
				case -5://décoration
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[4].setTexture(texturePng[6]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[4].setOrigin(sf::Vector2f(textureRectangle[4].getLocalBounds().width / 2, textureRectangle[4].getLocalBounds().height / 2));
						textureRectangle[4].rotate(180);
						textureRectangle[4].setOrigin(sf::Vector2f(textureRectangle[4].getLocalBounds().width, textureRectangle[4].getLocalBounds().height));
					}
					textureRectangle[4].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[4]);
					break;
				case -6://décoration
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[5].setTexture(texturePng[7]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[5].setOrigin(sf::Vector2f(textureRectangle[5].getLocalBounds().width / 2, textureRectangle[5].getLocalBounds().height / 2));
						textureRectangle[5].rotate(180);
						textureRectangle[5].setOrigin(sf::Vector2f(textureRectangle[5].getLocalBounds().width, textureRectangle[5].getLocalBounds().height));
					}
					textureRectangle[5].setPosition(14 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[5]);
					break;
				case -7://décoration
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[6].setTexture(texturePng[8]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[6].setOrigin(sf::Vector2f(textureRectangle[6].getLocalBounds().width / 2, textureRectangle[6].getLocalBounds().height / 2));
						textureRectangle[6].rotate(180);
						textureRectangle[6].setOrigin(sf::Vector2f(textureRectangle[6].getLocalBounds().width, textureRectangle[6].getLocalBounds().height));
					}
					textureRectangle[6].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[6]);
					break;
				case 10://teleporteur 1
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 11://teleporteur 1
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 12://teleporteur 1
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 13://teleporteur 1
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 14://teleporteur 1
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 15://teleporteur 1
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 16://receveur teleporteur 1
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 17://teleporteur 2
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 18://receveur teleporteur 2
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 19://receveur teleporteur 2
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[12].setTexture(texturePng[14]);
					textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
					window.draw(textureRectangle[12]);
					break;
				case 31://levier désactivé
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[13].setTexture(texturePng[15]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[13].setOrigin(sf::Vector2f(textureRectangle[13].getLocalBounds().width / 2, textureRectangle[13].getLocalBounds().height / 2));
						textureRectangle[13].rotate(180);
						textureRectangle[13].setOrigin(sf::Vector2f(textureRectangle[13].getLocalBounds().width, textureRectangle[13].getLocalBounds().height));
					}
					textureRectangle[13].setPosition(4 + j * 75 + 10, 4 + i * 75 + 17);
					window.draw(textureRectangle[13]);
					break;
				case 32://levier activé
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					textureRectangle[14].setTexture(texturePng[16]);
					if (joueur_.GetInvertScreen())
					{
						textureRectangle[14].setOrigin(sf::Vector2f(textureRectangle[14].getLocalBounds().width / 2, textureRectangle[14].getLocalBounds().height / 2));
						textureRectangle[14].rotate(180);
						textureRectangle[14].setOrigin(sf::Vector2f(textureRectangle[14].getLocalBounds().width, textureRectangle[14].getLocalBounds().height));
					}
					textureRectangle[14].setPosition(4 + j * 75 + 10, 4 + i * 75 + 17);
					window.draw(textureRectangle[14]);
					break;
				case 33:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);

					break;
				case 34:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 35:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 36:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);

					break;
				case 37:
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 38:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
						if (joueur_.GetX() != j || joueur_.GetY() != i)
						{
							joueur_.SetValeurMap(j, i, 39);
						}
					}
					break;
				case 39:
					tracejoueur(window, j, i, tra);
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 41://Blaser haut
					if (i == 0 && j == 0)
					{
						t = lines.size();
						lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
						lines[t].setPosition(j * 75, i * 75);
						lines[t].setFillColor(sf::Color(max(colorR - 50, 0), max(colorG - 100, 0), max(colorB - 100, 0)));
						window.draw(lines[t]);
					}
					else if (i == 13 && j == 0)
					{
						t = lines.size();
						lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
						lines[t].setPosition(j * 75, i * 75);
						lines[t].setFillColor(sf::Color(max(colorR - 50, 0), max(colorG - 100, 0), max(colorB - 100, 0)));
						window.draw(lines[t]);
					}
					else if (i == 13 && j == 24)
					{
						t = lines.size();
						lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
						lines[t].setPosition(j * 75, i * 75);
						lines[t].setFillColor(sf::Color(max(colorR - 50, 0), max(colorG - 100, 0), max(colorB - 100, 0)));
						window.draw(lines[t]);
					}
					else if (i == 0 && j == 24)
					{
						t = lines.size();
						lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
						lines[t].setPosition(j * 75, i * 75);
						lines[t].setFillColor(sf::Color(max(colorR - 50, 0), max(colorG - 100, 0), max(colorB - 100, 0)));
						window.draw(lines[t]);
					}
				case -666: // case banal
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 101:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 111:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 102:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 112:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 103:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 113:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 104:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 114:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 105:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 115:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 116:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 106:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 117:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 107:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 118:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 108:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 119:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 109:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 120:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					DrawLaserLevier(window, i, j, lines, sf::Color::Red);
					break;
				case 110:
					if (joueur_.GetTrace(j, i) == 1)
					{
						tracejoueur(window, j, i, tra);
					}
					break;
				case 121://champi inverseur
					textureRectangle[15].setTexture(texturePng[17]);
					textureRectangle[15].setPosition(4 + j * 75 + 10, 4 + i * 75 + 17);
					window.draw(textureRectangle[15]);
					break;
				case 122:
					tracejoueur(window, j, i, tra);
					break;
				}

				if (joueur_.GetValeurMap(0, 0) == 41) //Si le blaser haut existe dans cette carte
				{
					joueur_.SetPosBlaserHaut(joueur_.GetPosBlaserHaut() + vitesseBlaser);
					Blaser(window, joueur_.GetPosBlaserHaut(), true);
				}
				if (joueur_.GetValeurMap(0, 13) == 41) //Si le blaser gauche existe dans cette carte
				{
					joueur_.SetPosBlaserGauche(joueur_.GetPosBlaserGauche() + vitesseBlaser);
					Blaser(window, joueur_.GetPosBlaserGauche(), false);
				}
				if (joueur_.GetValeurMap(24, 13) == 41) //Si le blaser bas existe dans cette carte
				{
					joueur_.SetPosBlaserBas(joueur_.GetPosBlaserBas() - vitesseBlaser);
					Blaser(window, joueur_.GetPosBlaserBas(), true);
				}
				if (joueur_.GetValeurMap(24, 0) == 41) //Si le blaser droite existe dans cette carte
				{
					joueur_.SetPosBlaserDroite(joueur_.GetPosBlaserDroite() - vitesseBlaser);
					Blaser(window, joueur_.GetPosBlaserDroite(), false);
				}
			}
		}
	}
}

void Jeu::controle(sf::RenderWindow& window)
{

	float vitesseBlaser = 0;

	//différent forme pour dessin
	vector<sf::CircleShape> textureCercle;
	vector<sf::Texture*> texturePng;
	vector<sf::RectangleShape> textureRectangle;

	// charger toute les texture

	sf::Texture* diamant_png;
	diamant_png = new sf::Texture;
	(*diamant_png).loadFromFile("Images/diamant.png");
	sf::CircleShape diamant(35);
	textureCercle.push_back(diamant);
	texturePng.push_back(diamant_png);

	sf::Texture* clef_png;
	clef_png = new sf::Texture;
	(*clef_png).loadFromFile("Images/clef.png");
	sf::RectangleShape clef(sf::Vector2f(70, 30));
	textureRectangle.push_back(clef);
	texturePng.push_back(clef_png);

	sf::Texture* cadenas_png;
	cadenas_png = new sf::Texture;
	(*cadenas_png).loadFromFile("Images/cadenas.png");
	sf::CircleShape cadenas(35);
	textureCercle.push_back(cadenas);
	texturePng.push_back(cadenas_png);

	sf::Texture* arc_de_triomphe_png;
	arc_de_triomphe_png = new sf::Texture;
	(*arc_de_triomphe_png).loadFromFile("Images/arc_de_triomphe.png");
	sf::RectangleShape arc_de_triomphe(sf::Vector2f(70, 70));
	textureRectangle.push_back(arc_de_triomphe);
	texturePng.push_back(arc_de_triomphe_png);


	sf::Texture* concorde_png;
	concorde_png = new sf::Texture;
	(*concorde_png).loadFromFile("Images/concorde.png");
	sf::RectangleShape concorde(sf::Vector2f(50, 70));
	textureRectangle.push_back(concorde);
	texturePng.push_back(concorde_png);


	sf::Texture* notre_dame_png;
	notre_dame_png = new sf::Texture;
	(*notre_dame_png).loadFromFile("Images/notre_dame.png");
	sf::RectangleShape notre_dame(sf::Vector2f(70, 70));
	textureRectangle.push_back(notre_dame);
	texturePng.push_back(notre_dame_png);


	sf::Texture* louvre_png;
	louvre_png = new sf::Texture;
	(*louvre_png).loadFromFile("Images/louvre.png");
	sf::RectangleShape louvre(sf::Vector2f(70, 70));
	textureRectangle.push_back(louvre);
	texturePng.push_back(louvre_png);

	sf::Texture* tour_eiffel_png;
	tour_eiffel_png = new sf::Texture;
	(*tour_eiffel_png).loadFromFile("Images/tour_eiffel.png");
	sf::RectangleShape tour_eiffel(sf::Vector2f(45, 70));
	textureRectangle.push_back(tour_eiffel);
	texturePng.push_back(tour_eiffel_png);

	sf::Texture* pantheon_png;
	pantheon_png = new sf::Texture;
	(*pantheon_png).loadFromFile("Images/pantheon.png");
	sf::RectangleShape pantheon(sf::Vector2f(70, 70));
	textureRectangle.push_back(pantheon);
	texturePng.push_back(pantheon_png);

	sf::Texture* start_png;
	start_png = new sf::Texture;
	(*start_png).loadFromFile("Images/start.png");
	sf::RectangleShape start(sf::Vector2f(80, 50));
	textureRectangle.push_back(start);
	texturePng.push_back(start_png);

	sf::Texture* bas_png;
	bas_png = new sf::Texture;
	(*bas_png).loadFromFile("Images/bas.png");
	sf::RectangleShape bas(sf::Vector2f(70, 70));
	textureRectangle.push_back(bas);
	texturePng.push_back(bas_png);

	sf::Texture* haut_png;
	haut_png = new sf::Texture;
	(*haut_png).loadFromFile("Images/haut.png");
	sf::RectangleShape haut(sf::Vector2f(70, 70));
	textureRectangle.push_back(haut);
	texturePng.push_back(haut_png);

	sf::Texture* gauche_png;
	gauche_png = new sf::Texture;
	(*gauche_png).loadFromFile("Images/gauche.png");
	sf::RectangleShape gauche(sf::Vector2f(70, 70));
	textureRectangle.push_back(gauche);
	texturePng.push_back(gauche_png);

	sf::Texture* droite_png;
	droite_png = new sf::Texture;
	(*droite_png).loadFromFile("Images/droite.png");
	sf::RectangleShape droite(sf::Vector2f(70, 70));
	textureRectangle.push_back(droite);
	texturePng.push_back(droite_png);
	
	sf::Texture* tp2_png;
	tp2_png = new sf::Texture;
	(*tp2_png).loadFromFile("Images/tp2.png");
	sf::RectangleShape tp2(sf::Vector2f(70, 70));
	textureRectangle.push_back(tp2);
	texturePng.push_back(tp2_png);

	sf::Texture* levier_png;
	levier_png = new sf::Texture;
	(*levier_png).loadFromFile("Images/levier.png");
	sf::RectangleShape levier(sf::Vector2f(50, 50));
	textureRectangle.push_back(levier);
	texturePng.push_back(levier_png);

	sf::Texture* levier_inverse_png;
	levier_inverse_png = new sf::Texture;
	(*levier_inverse_png).loadFromFile("Images/levier_inverse.png");
	sf::RectangleShape levier_inverse(sf::Vector2f(50, 50));
	textureRectangle.push_back(levier_inverse);
	texturePng.push_back(levier_inverse_png);

	sf::Texture* champi_png;
	champi_png = new sf::Texture;
	(*champi_png).loadFromFile("Images/champi.png");
	sf::RectangleShape champi(sf::Vector2f(50, 50));
	textureRectangle.push_back(champi);
	texturePng.push_back(champi_png);

	int numero = 0;
	bool visible = true;
	int timer = 0;
	
	while (window.isOpen() && joueur_.GetinGame()==true)
	{
		if (joueur_.GetNiveau() < 7)
		{
			colorR = 255;
			colorG = 180;
			colorB = 0;
		}
		else if (joueur_.GetNiveau() < 15)
		{
			colorR = 85;
			colorG = 155;
			colorB = 64;
		}
		else if (joueur_.GetNiveau() < 23)
		{
			colorR = 237;
			colorG = 255;
			colorB = 33;
		}
		else if (joueur_.GetNiveau() < 31)
		{
			colorR = 150;
			colorG = 231;
			colorB = 250;
		}
		else if (joueur_.GetNiveau() < 39)
		{
			colorR = 81;
			colorG = 89;
			colorB = 211;
		}
		else if (joueur_.GetNiveau() < 50)
		{
			colorR = 150;
			colorG = 150;
			colorB = 150;
		}
		
		window.clear(sf::Color(colorR, colorG, colorB));// fond de couleur 
		sf::Event event;
			// tant qu'il y a des évènements à traiter
			while (window.pollEvent(event))
			{
				
				if (joueur_.GetEtat() ==true)//si joueur en vie
				{
				switch (event.type)
				{
					// fenêtre fermée
				case sf::Event::Closed:
					window.close();
					break;
					// touche pressée
				case sf::Event::KeyPressed:
					//if (!joueur_.GetInvertScreen())
					//{
						vitesseBlaser = 0.0001;
					//}
					//else
					//{
						//vitesseBlaser = -0.0001;
					//}
					window.setKeyRepeatEnabled(false);
					{
						if (event.key.code == sf::Keyboard::Escape)
						{
							
							joueur_.SetinGame(false);//on passe au menu
						}
						if (event.key.code == sf::Keyboard::O)
						{
							vitesseBlaser = 0;
							visible = true;
							joueur_.reinitialisation();
							joueur_.PorteTouche(window, bande_son_);
							timer = 0;
						}
						if (difficulty_ > 1)
						{
							if (event.key.code == sf::Keyboard::Left)//si on presse la fleche de gauche
							{
								if (!joueur_.GetInvertScreen())
								{
									if (joueur_.GetX() > 0)
									{
										window.setKeyRepeatEnabled(false);//on ne peut pas rester appuyer
										joueur_.Trace(joueur_.GetX() - 1, joueur_.GetY());//permet de ceer la trace
										if (joueur_.GetValeurMap(joueur_.GetX() - 1, joueur_.GetY()) != -1 && (joueur_.GetValeurMap(joueur_.GetX() - 1, joueur_.GetY()) < 71 || joueur_.GetValeurMap(joueur_.GetX() - 1, joueur_.GetY()) > 79))//on verifie que la case ou on se deplace ne soit pas un mur ou un cadenas
										{
											joueur_.SetXY(joueur_.GetX() - 1, joueur_.GetY());//décalle d'une case vers la gauche
											numero = random_at_most(4);//numero random pour choisir personnage
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}
											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);//on vérifie que on est pas en hardcord avant de dessiner le perso
											}
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{
												visible = joueur_.Update(window, bande_son_);//on verifie que on touche pas un laser et on met a jour
											}
											else
											{
												visible = true;//si on touche un laser
											}
										}
									}
								}
								else
								{
									if (joueur_.GetX() < 24)
									{
										window.setKeyRepeatEnabled(false);
										joueur_.Trace(joueur_.GetX() + 1, joueur_.GetY());
										if (joueur_.GetValeurMap(joueur_.GetX() + 1, joueur_.GetY()) != -1 && (joueur_.GetValeurMap(joueur_.GetX() + 1, joueur_.GetY()) < 71 || joueur_.GetValeurMap(joueur_.GetX() + 1, joueur_.GetY()) > 79))
										{
											joueur_.SetXY(joueur_.GetX() + 1, joueur_.GetY());
											numero = random_at_most(4);
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}
											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);
											}
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{

												visible = joueur_.Update(window, bande_son_);

											}
											else
											{
												visible = true;
											}
										}
									}
								}
							}
							if (event.key.code == sf::Keyboard::Right)
							{
								if (joueur_.GetInvertScreen())
								{
									if (joueur_.GetX() > 0)
									{
										window.setKeyRepeatEnabled(false);//on ne peut pas rester appuyer
										joueur_.Trace(joueur_.GetX() - 1, joueur_.GetY());//permet de ceer la trace
										if (joueur_.GetValeurMap(joueur_.GetX() - 1, joueur_.GetY()) != -1 && (joueur_.GetValeurMap(joueur_.GetX() - 1, joueur_.GetY()) < 71 || joueur_.GetValeurMap(joueur_.GetX() - 1, joueur_.GetY()) > 79))//on verifie que la case ou on se deplace ne soit pas un mur ou un cadenas
										{
											joueur_.SetXY(joueur_.GetX() - 1, joueur_.GetY());//décalle d'une case vers la gauche
											numero = random_at_most(4);//numero random pour choisir personnage
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}
											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);//on vérifie que on est pas en hardcord avant de dessiner le perso
											}
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{
												visible = joueur_.Update(window, bande_son_);//on verifie que on touche pas un laser et on met a jour
											}
											else
											{
												visible = true;//si on touche un laser
											}
										}
									}
								}
								else
								{
									if (joueur_.GetX() < 24)
									{
										window.setKeyRepeatEnabled(false);
										joueur_.Trace(joueur_.GetX() + 1, joueur_.GetY());
										if (joueur_.GetValeurMap(joueur_.GetX() + 1, joueur_.GetY()) != -1 && (joueur_.GetValeurMap(joueur_.GetX() + 1, joueur_.GetY()) < 71 || joueur_.GetValeurMap(joueur_.GetX() + 1, joueur_.GetY()) > 79))
										{
											joueur_.SetXY(joueur_.GetX() + 1, joueur_.GetY());
											numero = random_at_most(4);
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}
											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);
											}
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{

												visible = joueur_.Update(window, bande_son_);

											}
											else
											{
												visible = true;
											}
										}
									}
								}
							}
							if (event.key.code == sf::Keyboard::Up)
							{
								if (!joueur_.GetInvertScreen())
								{
									if (joueur_.GetY() > 0)
									{
										window.setKeyRepeatEnabled(false);
										joueur_.Trace(joueur_.GetX(), joueur_.GetY() - 1);

										if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() - 1) != -1 && (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() - 1) < 71 || joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() - 1) > 79))
										{
											joueur_.SetXY(joueur_.GetX(), joueur_.GetY() - 1);
											numero = random_at_most(4);
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}
											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);
											}

											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{
												visible = joueur_.Update(window, bande_son_);

											}
											else
											{
												visible = true;
											}
										}
									}
								}
								else
								{
									if (joueur_.GetY() < 13)
									{
										window.setKeyRepeatEnabled(false);
										joueur_.Trace(joueur_.GetX(), joueur_.GetY() + 1);
										if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() + 1) != -1 && (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() + 1) < 71 || joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() + 1) > 79))
										{
											joueur_.SetXY(joueur_.GetX(), joueur_.GetY() + 1);
											numero = random_at_most(4);

											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}


											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);
											}
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{
												visible = joueur_.Update(window, bande_son_);
											}
											else
											{
												visible = true;
											}
										}
									}
								}
							}
							if (event.key.code == sf::Keyboard::Down)
							{
								if (joueur_.GetInvertScreen())
								{
									if (joueur_.GetY() > 0)
									{
										window.setKeyRepeatEnabled(false);
										joueur_.Trace(joueur_.GetX(), joueur_.GetY() - 1);

										if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() - 1) != -1 && (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() - 1) < 71 || joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() - 1) > 79))
										{
											joueur_.SetXY(joueur_.GetX(), joueur_.GetY() - 1);
											numero = random_at_most(4);
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}
											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);
											}

											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{
												visible = joueur_.Update(window, bande_son_);

											}
											else
											{
												visible = true;
											}
										}
									}
								}
								else
								{
									if (joueur_.GetY() < 13)
									{
										window.setKeyRepeatEnabled(false);
										joueur_.Trace(joueur_.GetX(), joueur_.GetY() + 1);
										if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() + 1) != -1 && (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() + 1) < 71 || joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY() + 1) > 79))
										{
											joueur_.SetXY(joueur_.GetX(), joueur_.GetY() + 1);
											numero = random_at_most(4);

											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
											{
												vitesseBlaser = 0;
											}


											if (difficulty_ < 4)
											{
												joueur_.DrawPerso(window, numero);
											}
											if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) != 1)
											{
												visible = joueur_.Update(window, bande_son_);
											}
											else
											{
												visible = true;
											}
										}
									}
								}
							}
						}
					

							break;

				default:
					break;
						}
					}
				}
				else
				{
					MortAnimation(window, textureCercle, texturePng, textureRectangle);//permet au perso de "danser" quand il se prend un laser
					visible = true;
				}
			}
		// while nécessaire pour pas que sa charge infiniment 
		while (window.pollEvent(event)) {
			// Demande de fermeture de la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// On affiche la grille
		drawGrid(window, visible, textureCercle, texturePng, textureRectangle, vitesseBlaser);

		if (difficulty_ < 4)
		{
			joueur_.DrawPerso(window, numero);//dessine le personnage
		};
		// Mise à jour de la fenêtre
		timer++;
		ChangeTimer(timer);

		if (timer == 1000)
		{
			timer = 0;
		}

		window.display();
		if ((joueur_.GetX() <joueur_.GetPosBlaserGauche()+0.5 && joueur_.GetX() > joueur_.GetPosBlaserGauche() - 0.5 )|| (joueur_.GetX() > joueur_.GetPosBlaserDroite()-0.5 && joueur_.GetX() < joueur_.GetPosBlaserDroite() + 0.5) || (joueur_.GetY() <joueur_.GetPosBlaserHaut()+0.5 && joueur_.GetY() > joueur_.GetPosBlaserHaut() - 0.5) || (joueur_.GetY() > joueur_.GetPosBlaserBas() - 0.8 && joueur_.GetY() < joueur_.GetPosBlaserBas()+0.2))
		{
			joueur_.SetEtat(false);
		}



	
			if ((joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) > 19 || joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) < 10) && joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY())!=32 && joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY())!=31)
			{
				if (joueur_.GetValeurMap(joueur_.GetX(), joueur_.GetY()) == 5)
				{
					visible = true; // boucle pour afficher les laser des que l'on passe la porte
				}
				joueur_.Update(window, bande_son_);
			}
		
		if (joueur_.GetEtat() == false)
		{
			vitesseBlaser = 0;
			MortAnimation(window, textureCercle, texturePng, textureRectangle);//animation lorsque on meurt
			visible = true;
			timer = 0;
		}
	}
	if (joueur_.GetinGame() == false)//joueur retourne dans le menu
	{
		joueur_.reinitialisation();
	}
	

	delete diamant_png;
	delete clef_png;
	delete cadenas_png;
	delete louvre_png;
	delete concorde_png;
	delete arc_de_triomphe_png;
	delete tour_eiffel_png;
	delete pantheon_png;
	delete notre_dame_png;
	delete start_png;
	delete bas_png;
	delete haut_png;
	delete gauche_png;
	delete droite_png;
	delete tp2_png;

	joueur_.SetinGame(true);
}

Jeu::Jeu(Joueur joueur, Menu menu, Son* bande_son)
{
	menu_ = menu;
	bande_son_ = bande_son;
	difficulty_ = 2;
	int pos[2] = { 1 ,1};
	Joueur joueur_(pos, 0, 0);
	joueur_ = joueur;
	joueur_.SetEtat(joueur.GetEtat());

}

void Jeu::game(sf::RenderWindow& window)
{

	if (bande_son_->GetVolume())
	{
		if (joueur_.GetNiveau() < 7)
		{
			bande_son_->PlayMainTheme1();
		}
		else if (joueur_.GetNiveau() < 15)
		{
			bande_son_->PlayMainTheme2();
		}
		else if (joueur_.GetNiveau() < 23)
		{
			bande_son_->PlayMainTheme3();
		}
		else if (joueur_.GetNiveau() < 31)
		{
			bande_son_->PlayMainTheme4();
		}
		else if (joueur_.GetNiveau() < 39)
		{
			bande_son_->PlayMainTheme5();
		}
		else if (joueur_.GetNiveau() < 50)
		{
			bande_son_->PlayMainTheme6();
		}
	}
	reinitialisation();
	joueur_.SetinGame(true);
	joueur_.SetEtat(true);
	
	
	joueur_.SetXY(joueur_.GetCartes()[joueur_.GetNiveau()].GetPositionXJoueurDebut(), joueur_.GetCartes()[joueur_.GetNiveau()].GetPositionYJoueurDebut());
	
	

	controle(window);
	bande_son_->StopMainTheme1();
	bande_son_->StopMainTheme2();
	bande_son_->StopMainTheme3();
	bande_son_->StopMainTheme4();
	bande_son_->StopMainTheme5();
	bande_son_->StopMainTheme6();
	bande_son_->StopMainThemeOld();


}

void Jeu::MortAnimation(sf::RenderWindow& window, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle)
{
	//sf::SoundBuffer buffer;
	//buffer.loadFromFile("bande_son/mort_laser.wav");
	//death_.setBuffer(buffer);
	
		
		//death_.play();
	bande_son_->PlayDeath();
	

	sf::Event event;
	sf::Clock clock;
	int numero = 0;
	while (clock.getElapsedTime().asSeconds() < 2.7)
	{

		numero++;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		drawGrid(window, true, textureCercle, texturePng, textureRectangle, 0);
		joueur_.DrawPerso(window, numero);
		window.display();
		window.clear(sf::Color(colorR, colorG, colorB));
	}
	clock.restart();
	joueur_.SetEtat(true);
	
	joueur_.MortJoueur(window);
}

void Jeu::SetNiveau(int i)
{
	joueur_.SetNiveau(i);
}

void Jeu::tracejoueur(sf::RenderWindow& window, int j, int i, std::vector<sf::RectangleShape> tra)
{
	if (difficulty_ <3)
	{
		int t = tra.size();
		tra.push_back(sf::RectangleShape(sf::Vector2f(70, 70)));
		tra[t].setPosition(3 + (j) * 75, 3 + (i) * 75);
		tra[t].setFillColor(sf::Color(max(colorR -40, 0), max(colorG -40, 0), max(colorB-40, 0)));
		window.draw(tra[t]);
	}
}

void Jeu::SetDifficulty(int val)
{
	difficulty_ = val;
	joueur_.SetDiff(difficulty_);
}

long Jeu::random_at_most(long max)
{
	unsigned long
		// max <= RAND_MAX < ULONG_MAX, so this is okay.
		num_bins = (unsigned long)max + 1,
		num_rand = (unsigned long)RAND_MAX + 1,
		bin_size = num_rand / num_bins,
		defect = num_rand % num_bins;
	long x;
	do {
		x = rand();
	}
	// This is carefully written not to overflow
	while (num_rand - defect <= (unsigned long)x);
	// Truncated division is intentional
	return x / bin_size;
}

void Jeu::reinitialisation()
{
	joueur_.reinitialisation();
}

void Jeu::Blaser(sf::RenderWindow& window, float progression, bool ordonne)
{
	std::vector<sf::RectangleShape> line;
	if (ordonne)
	{
		line.push_back(sf::RectangleShape(sf::Vector2f(55, 1920)));
		line[0].rotate(270);
		line[0].setPosition(0, progression*75+57);
	}
	else
	{
		line.push_back(sf::RectangleShape(sf::Vector2f(55, 1080)));
		line[0].setPosition(progression * 75 + 10, 0);
	}
	line[0].setFillColor(sf::Color::Red);
	window.draw(line[0]);
}

void Jeu::LireNiveaux()
{
	int tab[25][14] = { 0 };
	int i = 0;
	int j = 0;
	stringstream lineStream;
	
	ifstream Levels("Niveaux/Niveaux.txt", ios::in);
	string number;
	if (Levels.is_open())
	{
		string line;
		
		while (getline(Levels, line))
		{
			lineStream << line;
			j = 0;
			while (getline(lineStream, number, ';'))
			{
				tab[j][i] = stoi(number);
				j++;
			}
			lineStream.clear();
			i++;
			if (i == 14)
			{
				Cartes carte(tab);
				joueur_.AjouterCarte(carte);
			}
			else if (i == 15)
			{
				i = 0;
			}

		}
		
	}
	else
	{
		cout << "Erreur lecture du fichier Niveaux" << endl;
	}
}

void Jeu::load(string nom)
{
	int level;

	string fichier = "Sauvegardes/" + nom + "save.txt";
	ifstream Save(fichier);
	if (Save.is_open())
	{
		string line;
		getline(Save, line);
		SetNom(line);
		getline(Save, line);
		SetNiveauMax(stoi(line));
	}
	else
	{
		string fichier = "Sauvegardes/" + nom + "save.txt";
		ofstream Save(fichier);
		if (Save.is_open())
		{
			Save << nom;
			Save << "\n";
			Save << 1;
		}
		else
		{
			cerr << "Erreur création du fichier " << fichier << endl;
		}
	}
}

void Jeu::save()
{
	string fichier = "Sauvegardes/" + nom_ + "save.txt";
	ofstream Save(fichier);
	if (Save.is_open())
	{
		Save << nom_;
		Save << "\n";
		Save << niveauMax_;
	}
	else
	{
		cerr << "Erreur création du fichier " << fichier << endl;
	}
}

void Jeu::SetNom(string nom)
{
	nom_ = nom;
}

void Jeu::SetNiveauMax(int i)
{
	niveauMax_ = i;
}

void Jeu::AjouterCarte(Cartes carte)
{
	joueur_.AjouterCarte(carte);
}

void Jeu::SaveLevel()
{
	vector<Cartes> carte = joueur_.GetCartes();
	ofstream Save("Niveaux/Niveaux.txt");
	if (Save.is_open())
	{
		for (int num = 0; num < carte.size(); num++)
		{
			for (int i = 0; i < 14; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					Save << carte[num].GetValeurMap(j, i);
					Save << ";";
				}
				Save << "\n";
			}
			Save << "\n";
		}
	}
}

void Jeu::ChangeTimer(int timer)
{
	if (timer % 50 == 0)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 101)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
				else if (joueur_.GetValeurMap(j, i) == 111)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer+5) % 50 == 0)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 102)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
				else if (joueur_.GetValeurMap(j, i) == 112)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer + 10) % 50 == 0)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 103)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
				else if (joueur_.GetValeurMap(j, i) == 113)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer + 15) % 50 == 0)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 104)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
				else if (joueur_.GetValeurMap(j, i) == 114)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer + 20) % 50 == 0)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 105)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
				else if (joueur_.GetValeurMap(j, i) == 115)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer) % 50 == 0)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 106)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
			}
		}
	}
	if ((timer) % 50 == 10)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 116)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer) % 50 == 10)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 107)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
			}
		}
	}
	if ((timer) % 50 == 20)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 117)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer) % 50 == 20)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 108)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
			}
		}
	}
	if ((timer) % 50 == 30)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 118)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer) % 50 == 30)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 109)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
			}
		}
	}
	if ((timer) % 50 == 40)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 119)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
	if ((timer) % 50 == 40)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 110)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) + 10);
				}
			}
		}
	}
	if ((timer) % 50 == 0)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (joueur_.GetValeurMap(j, i) == 120)
				{
					joueur_.SetValeurMap(j, i, joueur_.GetValeurMap(j, i) - 10);
				}
			}
		}
	}
}