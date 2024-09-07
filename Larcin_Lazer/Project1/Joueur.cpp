#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Carte.h"
#include "Joueur.h"
#include "windows.h"
#include <fstream>
#include "Son.h"
using namespace std;

// 1 er constructeur
Joueur::Joueur()
{
	niveau_ = 0;
}

// 2 eme constructeur
Joueur::Joueur(int positionXY[2], int niveau, bool etat)
{
	positionXY_[0] = positionXY[0];
	positionXY_[1] = positionXY[1];
	niveau_ = niveau;
	etat_ = etat;
}

// ajoute une crate a joueur en normal , difficile ou hardcord
void Joueur::AjouterCarte(Cartes carte)
{
	carte_.push_back(carte);
}

//replace le joueur sur la case du début, enlve la trace , replace les éléments tel que les clef et cadenas
void Joueur::MortJoueur(sf::RenderWindow& window)
{
	
	
	//enlve la trace
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			trace_[i][j] = 0;
		}
	}




		
	positionXY_[0] = carte_[niveau_].GetPositionXJoueurDebut();// On replace le joueur au début du niveau.
	positionXY_[1] = carte_[niveau_].GetPositionYJoueurDebut();
	reinitialisation();
}

//remplace la case diamant par case vide et ouvre la porte
void Joueur::GemmeRecolte()
{
	
	carte_[niveau_].SetValeurMap(positionXY_[0], positionXY_[1], 3);//case diamant devient vide
	carte_[niveau_].SetValeurMap(carte_[niveau_].GetPositionSortieX(), carte_[niveau_].GetPositionSortieY(), 5);//porte devient ouverte
	
}

// fait passer au niveau suivant si le joueur touche la porte
void Joueur::PorteTouche(sf::RenderWindow& window, Son* son)
{
	
	reinitialisation();
	invertScreen_ = false;

	//réinitialise la trace
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			trace_[i][j] = 0;
		}
	}

	//gere si en mode normal , difficile ou hardcord ou test pour carte suivante
		if (niveau_ < carte_.size() - 1)
		{
			niveau_++;
			positionXY_[0] = carte_[niveau_].GetPositionXJoueurDebut();
			positionXY_[1] = carte_[niveau_].GetPositionYJoueurDebut();
			if (niveau_ == 7)
			{
				son->StopMainTheme1();
				son->StopMainThemeOld();
				son->PlayMainTheme2();
			}
			else if (niveau_ == 15)
			{
				son->StopMainTheme2();
				son->StopMainThemeOld();
				son->PlayMainTheme3();
			}
			else if (niveau_ == 23)
			{
				son->StopMainTheme3();
				son->StopMainThemeOld();
				son->PlayMainTheme4();
			}
			else if (niveau_ == 31)
			{
				son->StopMainTheme4();
				son->StopMainThemeOld();
				son->PlayMainTheme5();
			}
			else if (niveau_ == 39)
			{
				son->StopMainTheme5();
				son->StopMainThemeOld();
				son->PlayMainTheme6();
			}
		}
		else
		{
			inGame_ = false;
			
		}
	
	reinitialisation();

}

//s'occupe de faire bouger le personnage lorsque il est sur des case spétial (fléche,téléporteur,clef)
bool Joueur::Update(sf::RenderWindow& window, Son* son)
{
	bool visible=false;
	int val;
	val = carte_[niveau_].GetValeurMap(positionXY_[0], positionXY_[1]);
	
	
	// 21,22,23,24 correspondent aux chiffres attirbué aux fléches qui une fois arriver sur la case vous décale d'une case 
	//selon la direction de cette dernière

	if (val == 21)//fleche vers le bas
	{
		sf::Clock clock;
		while (clock.getElapsedTime().asSeconds() < 0.02)//rajout d'un temp de latence
		{
		}
		if (invertScreen_)
		{
			positionXY_[1]--;
		}
		else
		{
			positionXY_[1]++;//change la position
		}
		trace_[GetX()][GetY()] = 1;//dessine la trace
	}
		else if (val == 22)//haut
	{
		sf::Clock clock;
		while (clock.getElapsedTime().asSeconds() < 0.02)
		{
		}
		if (!invertScreen_)
		{
			positionXY_[1]--;
		}
		else
		{
			positionXY_[1]++;//change la position
		}
		trace_[GetX()][GetY()] = 1;
	}
		else if (val == 23)//gauche
	{
		sf::Clock clock;
		while (clock.getElapsedTime().asSeconds() < 0.02)
		{
		}
		if (!invertScreen_)
		{
			positionXY_[0]--;
		}
		else
		{
			positionXY_[0]++;//change la position
		}
		trace_[GetX()][GetY()] = 1;
	}
		else if ( val == 24)//droite
	{
		sf::Clock clock;
		while (clock.getElapsedTime().asSeconds() < 0.02)
		{
		}
		if (invertScreen_)
		{
			positionXY_[0]--;
		}
		else
		{
			positionXY_[0]++;//change la position
		}
		trace_[GetX()][GetY()] = 1;
	}
	else if (val == 1 || val==39 || (val>=101 && val <=105) || (val >= 116 && val <= 120))//case du laser
	{
		visible = true;//rend revisible laser pour recommencer
		etat_ = false;//le joueur est mort
	}
	else if (val == 2)//case de la gemme
	{
		GemmeRecolte();
		visible = false;
	}
	else if (val == 5)//case porte ouverte
	{
		PorteTouche(window, son);
		visible = true;
	}
	else if (val>=51 && val<=59)//case clef
	{
		cle(val);
		visible = false;
	}
	else if (val >9 && val<15)//case téléporteur
	{
		TP1(val);
		trace_[positionXY_[0]][positionXY_[1]] = 1;
	}
	else if (val>14 && val<20)//case téléporteur
	{
		TP2(val);
		trace_[positionXY_[0]][positionXY_[1]] = 1;
		
	}
	else if (val == 31)//levier
	{
		levierTouche();
		trace_[GetX()][GetY()] = 1;//dessine la trace
	}
	else if (val == 33)
	{
		visible = true;//rend visible laser pour recommencer
		etat_ = false;//le joueur est mort
	}
	else if (val == 36)
	{
		visible = true;//rend visible laser pour recommencer
		etat_ = false;//le joueur est mort
	}
	else if (val == 37)
	{
		visible = true;//rend visible laser pour recommencer
		etat_ = false;//le joueur est mort
	}
	else if (val == 121)
	{
		if (invertScreen_)
		{
			invertScreen_ = false;
		}
		else
		{
			invertScreen_ = true;
		}
		int tab[25][14];
		int tab2[25][14];
		SetValeurMap(positionXY_[0], positionXY_[1], 122);
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				tab[j][i] = carte_[niveau_].GetValeurMap(j,  i);
				tab2[j][i] = trace_[j][i];
			}
		}
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				carte_[niveau_].SetValeurMap(24 -j, 13 - i, tab[j][i]);
				trace_[24 - j][13 - i] = tab2[j][i];
			}
		}
		carte_[niveau_].SetSortie(24 - carte_[niveau_].GetPositionSortieX(), 13 - carte_[niveau_].GetPositionSortieY());
		carte_[niveau_].SetDebut(24 - carte_[niveau_].GetPositionXJoueurDebut(), 13 - carte_[niveau_].GetPositionYJoueurDebut());
		positionXY_[0] = 24 - positionXY_[0];
		positionXY_[1] = 13 - positionXY_[1];

		float temp;

		temp = posBlaserHaut_;
		posBlaserHaut_ = 13 - posBlaserBas_;
		posBlaserBas_ = 13 - temp;

		temp = posBlaserDroite_;
		posBlaserDroite_ = 24 - posBlaserGauche_;
		posBlaserGauche_ = 24 - temp;

	}
	else if (val==-666)
	{
		son->StopMainTheme1();
		son->StopMainTheme2();
		son->StopMainTheme3();
		son->StopMainTheme4();
		son->StopMainTheme5();
		son->StopMainTheme6();
		if (!son->GetOldThemeStatus())
		{
			son->PlayMainThemeOld();
		}
	}

	return visible;
}

//met le joueur a une position de la carte (x en abscisse et y en ordonné)
void Joueur::SetXY(int x, int y)
{
	positionXY_[0] = x;
	positionXY_[1] = y;
}

void Joueur::operator=(Joueur joueur)
{
	positionXY_[0] = joueur.GetX();
	positionXY_[1] = joueur.GetY();
	carte_ = joueur.GetCartes();
	niveau_ = joueur.GetNiveau();
	etat_ = joueur.GetEtat();
}

//change les cadenas en case vide
void Joueur::cle(int val)
{	
		carte_[niveau_].SetValeurMap(positionXY_[0], positionXY_[1], val + 10);
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (carte_[niveau_].GetValeurMap(j, i) == val + 20)
				{
					carte_[niveau_].SetValeurMap(j, i, val + 30);
				}
			}
		}
}

//dessine le personnage de facon aleétoire (5 perso possible)
void Joueur::DrawPerso(sf::RenderWindow& window, int numero)
{
	int x = positionXY_[0];
	int y = positionXY_[1];

	sf::Texture* perso1_png;
	perso1_png = new sf::Texture;
	(*perso1_png).loadFromFile("Images/perso1.png");
	sf::RectangleShape perso1(sf::Vector2f(63, 85));

	sf::Texture* perso2_png;
	perso2_png = new sf::Texture;
	(*perso2_png).loadFromFile("Images/perso2.png");
	sf::RectangleShape perso2(sf::Vector2f(37, 75));

	sf::Texture* perso3_png;
	perso3_png = new sf::Texture;
	(*perso3_png).loadFromFile("Images/perso3.png");
	sf::RectangleShape perso3(sf::Vector2f(40, 82));

	sf::Texture* perso4_png;
	perso4_png = new sf::Texture;
	(*perso4_png).loadFromFile("Images/perso4.png");
	sf::RectangleShape perso4(sf::Vector2f(40, 72));

	sf::Texture* perso5_png;
	perso5_png = new sf::Texture;
	(*perso5_png).loadFromFile("Images/perso5.png");
	sf::RectangleShape perso5(sf::Vector2f(55, 65));
	switch (numero%5)
	{
	case 0:
		perso1.setTexture(perso1_png);
		if (invertScreen_)
		{
			perso1.setOrigin(sf::Vector2f(perso1.getLocalBounds().width / 2, perso1.getLocalBounds().height / 2));
			perso1.rotate(180);
			perso1.setOrigin(sf::Vector2f(perso1.getLocalBounds().width, perso1.getLocalBounds().height));
		}
		perso1.setPosition(10 + x * 75, -5 + y * 75);
		window.draw(perso1);//perso qui ecarte jambe et levre bras
		break;
	case 1:
		perso2.setTexture(perso2_png);
		if (invertScreen_)
		{
			perso2.setOrigin(sf::Vector2f(perso2.getLocalBounds().width / 2, perso2.getLocalBounds().height / 2));
			perso2.rotate(180);
			perso2.setOrigin(sf::Vector2f(perso2.getLocalBounds().width, perso2.getLocalBounds().height));
		}
		perso2.setPosition(18 + x * 75, -1 + y * 75);
		window.draw(perso2);//leve bras gauche
		break;

	case 2:
		perso3.setTexture(perso3_png);
		if (invertScreen_)
		{
			perso3.setOrigin(sf::Vector2f(perso3.getLocalBounds().width / 2, perso3.getLocalBounds().height / 2));
			perso3.rotate(180);
			perso3.setOrigin(sf::Vector2f(perso3.getLocalBounds().width, perso3.getLocalBounds().height));
		}
		perso3.setPosition(18 + x * 75, -4 + y * 75);
		window.draw(perso3);//deux bras collé corp
		break;

	case 3:
		perso4.setTexture(perso4_png);
		if (invertScreen_)
		{
			perso4.setOrigin(sf::Vector2f(perso4.getLocalBounds().width / 2, perso4.getLocalBounds().height / 2));
			perso4.rotate(180);
			perso4.setOrigin(sf::Vector2f(perso4.getLocalBounds().width, perso4.getLocalBounds().height));
		}
		perso4.setPosition(20 + x * 75, 4 + y * 75);
		window.draw(perso4);//croise jambe plus leve 2 bras
		break;

	case 4:
		perso5.setTexture(perso5_png);
		if (invertScreen_)
		{
			perso5.setOrigin(sf::Vector2f(perso5.getLocalBounds().width / 2, perso5.getLocalBounds().height / 2));
			perso5.rotate(180);
			perso5.setOrigin(sf::Vector2f(perso5.getLocalBounds().width, perso5.getLocalBounds().height));
		}
		perso5.setPosition(8 + x * 75, 8 + y * 75);
		window.draw(perso5);//leve bras droit montre bas gauche plie les jambes
		break;

	}
	delete perso1_png;
	delete perso2_png;
	delete perso3_png;
	delete perso4_png;
	delete perso5_png;
}

// savoir si le joueur est en vie (false=mort ,true= en vie)
void Joueur::SetEtat(bool etat)
{
	etat_ = etat;
}

// permet de se placer dans un niveau choisi en normal , difficile ou hardcord
void Joueur::SetNiveau(int i)
{
	niveau_ = i-1;
}

// peremt de dessiner trace
void Joueur::Trace(int i, int j)
{
	trace_[i][j] = 1;//trace_[i][j] =0 on fait rien trace_[i][j] =1 on dessine trace
}

// permet de savoir si on est dans le jeu ou menu (false=menu,true=jeu)
void Joueur::SetinGame(bool val)
{
	inGame_ = val;
}

// permet de changer la difficulté (test,normal,difficil,hardcord)
void Joueur::SetDiff(int i)
{
	difficulty_ = i;
}

//reinitialise les niveau lorsque on change entre menu et jeu
void Joueur::reinitialisation()
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (carte_.size() != 0)
			{
				if (carte_[niveau_].GetValeurMap(j, i) == 3 || carte_[niveau_].GetValeurMap(j, i) == 5  || carte_[niveau_].GetValeurMap(j, i) == 32 || carte_[niveau_].GetValeurMap(j, i) == 34 || carte_[niveau_].GetValeurMap(j, i) == 36 || carte_[niveau_].GetValeurMap(j, i) == 39 || carte_[niveau_].GetValeurMap(j, i) == 122)
				{
					carte_[niveau_].SetValeurMap(j, i, carte_[niveau_].GetValeurMap(j, i) - 1);
				}
				if ((carte_[niveau_].GetValeurMap(j, i) > 60 && carte_[niveau_].GetValeurMap(j, i) < 70) || (carte_[niveau_].GetValeurMap(j, i) > 80 && carte_[niveau_].GetValeurMap(j, i) < 90) || (carte_[niveau_].GetValeurMap(j, i) > 110 && carte_[niveau_].GetValeurMap(j, i) < 121))
				{
					carte_[niveau_].SetValeurMap(j, i, carte_[niveau_].GetValeurMap(j, i) - 10);
				}
			}
			trace_[j][i] = 0;

		}
	}
	
	if (invertScreen_)
	{
		int tab[25][14];
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				tab[j][i] = carte_[niveau_].GetValeurMap(j, i);
			}
		}
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				carte_[niveau_].SetValeurMap(24 -j, 13 - i, tab[j][i]);
			}
		}
		invertScreen_ = false;
		carte_[niveau_].SetSortie(24 - carte_[niveau_].GetPositionSortieX(), 13 - carte_[niveau_].GetPositionSortieY());
		carte_[niveau_].SetDebut(24 - carte_[niveau_].GetPositionXJoueurDebut(), 13 - carte_[niveau_].GetPositionYJoueurDebut());

		positionXY_[0] = 24 - positionXY_[0];
		positionXY_[1] = 13 - positionXY_[1];
	}


		if (carte_[niveau_].GetValeurMap(0, 0) == 41)
		{
			posBlaserHaut_ = 0;
		}
		else
		{
			posBlaserHaut_ = -10000;
		}
		if (carte_[niveau_].GetValeurMap(0, 13) == 41)
		{
			posBlaserGauche_ = 0;
		}
		else
		{
			posBlaserGauche_ = -10000;
		}
		if (carte_[niveau_].GetValeurMap(24, 13) == 41)
		{
			posBlaserBas_ = 13;
		}
		else
		{
			posBlaserBas_ = 10000;
		}
		if (carte_[niveau_].GetValeurMap(24, 0) == 41)
		{
			posBlaserDroite_ = 24;
		}
		else
		{
			posBlaserDroite_ = 10000;
		}
}

// 4 fonction gère 4 différent téléporteur
void Joueur::TP1(int val)
{
	
	int pos[2] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{

				//cherche la position du 2 eme tp 15 du niveau et note sa position
				if (carte_[niveau_].GetValeurMap(j, i) == val && positionXY_[0]!=j && positionXY_[1]!=i) 
				{
					pos[0] = j;
					pos[1] = i;

				}
		}
	}
	positionXY_[0] = pos[0];
	positionXY_[1] = pos[1];
}

void Joueur::TP2(int val)
{
	int pos[2] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
				if (carte_[niveau_].GetValeurMap(j, i) == val)
				{
					if (positionXY_[0] != j || positionXY_[1] != i)
					{
						pos[0] = j;
						pos[1] = i;
					}

				}
		}
	}
	positionXY_[0] = pos[0];
	positionXY_[1] = pos[1];
}

void Joueur::levierTouche()
{
	
		// Change la position du laser
		carte_[niveau_].SetValeurMap(positionXY_[0], positionXY_[1], carte_[niveau_].GetValeurMap(positionXY_[0], positionXY_[1])%2 +31);
		
		for (int j = 0; j < 25; j++)
		{
			for (int i = 0; i < 14; i++)
			{
				// rend visible certains lasers, et invisible d'autres
				if (carte_[niveau_].GetValeurMap(j, i) == 33 || carte_[niveau_].GetValeurMap(j, i) == 34)
				{
					carte_[niveau_].SetValeurMap(j, i, carte_[niveau_].GetValeurMap(j, i) % 2 + 33);
				}
				if (carte_[niveau_].GetValeurMap(j, i) == 35 || carte_[niveau_].GetValeurMap(j, i) == 36)
				{
					carte_[niveau_].SetValeurMap(j, i, carte_[niveau_].GetValeurMap(j, i) % 2 + 35);
				}
			}
		}
}

void Joueur::SetPosBlaserHaut(float i)
{
	posBlaserHaut_ = i;
}

void Joueur::SetPosBlaserGauche(float i)
{
	posBlaserGauche_ = i;
}

void Joueur::SetPosBlaserBas(float i)
{
	posBlaserBas_ = i;
}

void Joueur::SetPosBlaserDroite(float i)
{
	posBlaserDroite_ = i;
}

void Joueur::SetValeurMap(int x, int y, int val)
{
	carte_[niveau_].SetValeurMap(x, y, val);
}

void Joueur::affTab()
{
	cout << posBlaserHaut_ << " " << posBlaserDroite_ << endl;
	cout << posBlaserGauche_ << " " << posBlaserBas_ << endl << endl;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			cout << carte_[niveau_].GetValeurMap(j, i) << " ";
		}
		cout << endl;
	}
	cout << endl;
	
}