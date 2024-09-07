#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include <vector>
#include "Jeu.h"
#include "joueur.h"
#include "Carte.h"
#include <string>
#include <fstream>
using namespace std;

Menu::Menu()
{

}

Menu::Menu(Son* son)
{
	musique_ = son;
}

void Menu::MainMenu(sf::RenderWindow& window, Jeu& jeu)
{
	int n = 0;

	jeu.LireNiveaux(); // Permet de stocker les niveaux dans les champs carte_ et carteTest_ de la classe Joueur
	//remplir le tabbleau pour bouton interactif
	int tab[190][100] = { 0 };
	for (int i = 74; i < 110; i++)//jouer
	{
		for (int j = 39; j < 57; j++)
		{
			tab[i][j] = 1;
		}
	}
	for (int i = 75; i < 111; i++) //choix du niveau
	{
		for (int j = 59; j < 77; j++)
		{
			tab[i][j] = 2;
		}
	}
	for (int i = 75; i < 112; i++)//option
	{
		for (int j = 79; j < 97; j++)
		{
			tab[i][j] = 3;
		}
	}
	for (int i = 1; i < 41; i++)//quitter
	{
		for (int j = 79; j < 99; j++)
		{
			tab[i][j] = 4;
		}
	}
	for (int i = 77; i < 83; i++)//baisser d'un niveau
	{
		for (int j = 68; j < 71; j++)
		{
			tab[i][j] = 5;
		}
	}
	for (int i = 104; i < 111; i++)//augmenter d'un niveau
	{
		for (int j = 67; j < 74; j++)
		{
			tab[i][j] = 6;
		}
	}
	for (int i = 6; i < 40; i++)//Menu Edit
	{
		for (int j = 62; j < 77; j++)
		{
			tab[i][j] = 7;
		}
	}
	for (int i = 74; i < 79; i++)//Menu Edit
	{
		for (int j = 15; j < 31; j++)
		{
			tab[i][j] = 8;
		}
	}

	//gérer les texture
	sf::Texture* noms_png;
	noms_png = new sf::Texture;
	(*noms_png).loadFromFile("Images/noms.png");
	sf::RectangleShape noms(sf::Vector2f(270, 120));

	sf::Texture* titre_png;
	titre_png = new sf::Texture;
	(*titre_png).loadFromFile("Images/titre.png");
	sf::RectangleShape titre(sf::Vector2f(800, 400));

	sf::Texture* version_wish_png;
	version_wish_png = new sf::Texture;
	(*version_wish_png).loadFromFile("Images/version_wish.png");
	sf::RectangleShape version_wish(sf::Vector2f(200, 100));

	sf::Texture* Jouer_png;
	Jouer_png = new sf::Texture;
	(*Jouer_png).loadFromFile("Images/Jouer.png");
	sf::RectangleShape Jouer(sf::Vector2f(360, 180));

	sf::Texture* options_png;
	options_png = new sf::Texture;
	(*options_png).loadFromFile("Images/options.png");
	sf::RectangleShape options(sf::Vector2f(370, 180));

	sf::Texture* quitter_png;
	quitter_png = new sf::Texture;
	(*quitter_png).loadFromFile("Images/quitter.png");
	sf::RectangleShape quitter(sf::Vector2f(400, 200));

	sf::Texture* edit_png;
	edit_png = new sf::Texture;
	(*edit_png).loadFromFile("Images/edit.png");
	sf::RectangleShape edit(sf::Vector2f(400, 200));

	sf::Texture* choix_niveaux_png;
	choix_niveaux_png = new sf::Texture;
	(*choix_niveaux_png).loadFromFile("Images/choix_niveaux.png");
	sf::RectangleShape choix_niveaux(sf::Vector2f(360, 180));

	sf::Texture* perso4_png;
	perso4_png = new sf::Texture;
	(*perso4_png).loadFromFile("Images/perso4.png");
	sf::RectangleShape perso4(sf::Vector2f(600, 1000));

	sf::Texture* diamant_png;
	diamant_png = new sf::Texture;
	(*diamant_png).loadFromFile("Images/diamant.png");
	sf::CircleShape diamant(140);

	string numeroNiveau;

	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color(255, 180, 0));//fond de couleur

		// Permet d'écrire un texte pour indiquer le niveau actuel sur le menu principal
		sf::Font font;
		font.loadFromFile("niagara_solid.ttf"); // choix de la police
		sf::Text text;
		text.setFont(font);
		
		numeroNiveau = to_string(jeu.GetNiveau()+1);
				
		text.setString(numeroNiveau);
		text.setCharacterSize(100);
		text.setPosition(9 * 75 + 12, 625);
		text.setFillColor(sf::Color(136, 0, 21));
		window.draw(text);

		// Permet de jouer la musique du menu
		if (!musique_->GetMenuStatus() && musique_->GetVolume())
		{
			musique_->PlayMenu();
		}


		while (window.pollEvent(event))
		{

			switch (event.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}

			// Permet de detecter les clics de la souris (pour rendre nos boutons fonctionnels
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
			{
				// Position de la souris dans par rapport à la fenêtre
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				// Position de la souris dans le tableau
				//cout << localPosition.x << " " << localPosition.y << std::endl;
				localPosition /= 10;
				
				//différent bouton
				if (tab[localPosition.x][localPosition.y] == 1)
				{
					musique_->StopMenu();//fin de la musique du menu
					musique_->StopMenuOld();//fin de la musique du menu
					jeu.game(window);//lancement du jeu
				}
				else if (tab[localPosition.x][localPosition.y] == 3)
				{
					MenuOption(window, jeu);// Permet d'aller dans le menu des options
				}
				else if (tab[localPosition.x][localPosition.y] == 4)
				{
					jeu.SaveLevel();
					window.close();//quitter
				}
				else if (tab[localPosition.x][localPosition.y] == 5)
				{
					
					if (jeu.GetNiveau() > 0) //On vérifie si on est pas au premier niveau
					{
						jeu.SetNiveau(jeu.GetNiveau()); //aller a niveau précédent
						jeu.reinitialisation(); // réinitialise la carte
					}
				}
				else if (tab[localPosition.x][localPosition.y] == 6 && jeu.GetNiveau()<jeu.GetNiveauxMax())
				{
					if (jeu.GetNiveau() < jeu.GetNombreNiveaux()-1)
					{
						jeu.SetNiveau(jeu.GetNiveau()+2); //aller au niveau suivant
						jeu.reinitialisation(); //réinitialise la carte
					}
				}
				else if (tab[localPosition.x][localPosition.y] == 7)
				{
					MenuEdit(window, jeu);
				}
				else if (tab[localPosition.x][localPosition.y] == 8)
				{
					musique_->StopMenu();
					musique_->PlayMenuOld();
				}

			}
		}
		while (window.pollEvent(event)) {
			// Demande de fermeture de la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (jeu.GetNiveauxMax() < jeu.GetNiveau())
		{
			jeu.SetNiveauMax(jeu.GetNiveau());
		}

		// position des différentes images
		titre.setTexture(titre_png);
		titre.setPosition(7.5 * 75, 20);
		window.draw(titre);

		version_wish.setTexture(version_wish_png);
		version_wish.setPosition(8 * 75, 290);
		window.draw(version_wish);

		noms.setTexture(noms_png);
		noms.setPosition(10, 10);
		window.draw(noms);

		Jouer.setTexture(Jouer_png);
		Jouer.setPosition(10*75, 400);//750->1110 400->580
		window.draw(Jouer);

		choix_niveaux.setTexture(choix_niveaux_png);
		choix_niveaux.setPosition(10 * 75 +12 , 600);//760->1120 600->780
		window.draw(choix_niveaux);

		options.setTexture(options_png);
		options.setPosition(10 * 75 +12, 800); //760 ->1130 800->980
		window.draw(options);

		quitter.setTexture(quitter_png);
		quitter.setPosition(20, 800);//20->420 800->1000
		window.draw(quitter);

		edit.setTexture(edit_png);
		edit.setPosition(20, 600);//20->420 800->1000
		window.draw(edit);

		perso4.setTexture(perso4_png);
		perso4.setPosition(17 * 75, 600);
		window.draw(perso4);

		// Animation du diamant
		if (n < 400)
		{
			diamant.setTexture(diamant_png);
			diamant.setPosition(18.85 * 75 + 10, 410);
			window.draw(diamant);
		}
		else if (n < 800)
		{
			diamant.setTexture(diamant_png);
			diamant.setPosition(18.85 * 75 + 10, 440);
			window.draw(diamant);
		}
		else
		{
			n = -1;
		}
		window.display();
		n++;
	}
	delete titre_png;
	delete version_wish_png;
	delete noms_png;
	delete Jouer_png;
	delete options_png;
	delete quitter_png;
	delete edit_png;
	delete perso4_png;
	delete diamant_png;
	delete choix_niveaux_png;
}

void Menu::MenuOption(sf::RenderWindow& window, Jeu& jeu)
{
	bool isInSettings = true; //permet de sortir du menu des options
	int tab[190][100] = { 0 };
	for (int i = 74; i < 110; i++)//volume
	{
		for (int j = 39; j < 57; j++)
		{
			tab[i][j] = 1;
		}
	}
	for (int i = 75; i < 111; i++) //choix difficulté
	{
		for (int j = 59; j < 77; j++)
		{
			tab[i][j] = 2;
		}
	}
	for (int i = 75; i < 112; i++)//menu principal
	{
		for (int j = 79; j < 97; j++)
		{
			tab[i][j] = 3;
		}
	}
	for (int i = 1; i < 41; i++)//crédits
	{
		for (int j = 79; j < 99; j++)
		{
			tab[i][j] = 4;
		}
	}

	//stockage des images
	sf::Texture* noms_png;
	noms_png = new sf::Texture;
	(*noms_png).loadFromFile("Images/noms.png");
	sf::RectangleShape noms(sf::Vector2f(270, 120));

	sf::Texture* titre_png;
	titre_png = new sf::Texture;
	(*titre_png).loadFromFile("Images/titre.png");
	sf::RectangleShape titre(sf::Vector2f(800, 400));

	sf::Texture* version_wish_png;
	version_wish_png = new sf::Texture;
	(*version_wish_png).loadFromFile("Images/version_wish.png");
	sf::RectangleShape version_wish(sf::Vector2f(200, 100));

	sf::Texture* volume_png;
	volume_png = new sf::Texture;
	(*volume_png).loadFromFile("Images/volume.png");
	sf::RectangleShape volume(sf::Vector2f(360, 180));

	sf::Texture* volume_off_png;
	volume_off_png = new sf::Texture;
	(*volume_off_png).loadFromFile("Images/volume_off.png");
	sf::RectangleShape volume_off(sf::Vector2f(360, 180));

	sf::Texture* difficulte_png;
	difficulte_png = new sf::Texture;
	(*difficulte_png).loadFromFile("Images/difficulte.png");
	sf::RectangleShape difficulte(sf::Vector2f(360, 180));

	sf::Texture* menu_principal_png;
	menu_principal_png = new sf::Texture;
	(*menu_principal_png).loadFromFile("Images/menu_principal.png");
	sf::RectangleShape menu_principal(sf::Vector2f(360, 180));

	sf::Texture* diffNormale_png;
	diffNormale_png = new sf::Texture;
	(*diffNormale_png).loadFromFile("Images/diffNormale.png");
	sf::RectangleShape diffNormale(sf::Vector2f(180, 90));

	sf::Texture* diffDifficile_png;
	diffDifficile_png = new sf::Texture;
	(*diffDifficile_png).loadFromFile("Images/diffDifficile.png");
	sf::RectangleShape diffDifficile(sf::Vector2f(180, 90));

	sf::Texture* diffHardcore_png;
	diffHardcore_png = new sf::Texture;
	(*diffHardcore_png).loadFromFile("Images/diffHardcore.png");
	sf::RectangleShape diffHardcore(sf::Vector2f(180, 90));

	sf::Texture* explication_png;
	explication_png = new sf::Texture;
	(*explication_png).loadFromFile("Images/explication.png");
	sf::RectangleShape explication(sf::Vector2f(500, 400));

	sf::Texture*credit_png;
	credit_png = new sf::Texture;
	(*credit_png).loadFromFile("Images/credit.png");
	sf::RectangleShape credit(sf::Vector2f(400, 200));

	while (window.isOpen() && isInSettings)
	{ 
		

		sf::Event event;
		window.clear(sf::Color(255, 180, 0));//couleur du fond

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
			{
				// Position de la souris dans par rapport à la fenêtre
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				// Position de la souris dans le tableau
				localPosition /= 10;
				// Affichage console des coordonées
				//cout << localPosition.x << " " << localPosition.y << std::endl;
				// Si on tombe sur une case vide
				
				//permet de rendre les boutons fonctionnels
				if (tab[localPosition.x][localPosition.y] == 1)
				{
					// gère le volume (on/off)
					if (musique_->GetVolume() == false)
					{
						musique_->SetVolume(true); 
						musique_->PlayMenu();
					}
					else
					{
						musique_->SetVolume(false);
						musique_->StopMenu();
					}
				}

				//gère la difficulté du jeu (Test, Normale, Difficile, Hardcore)
				else if (tab[localPosition.x][localPosition.y] == 2)
				{
					if (jeu.GetDifficulty() == 4)
					{
						jeu.SetDifficulty(2);
					}
					else
					{
						jeu.SetDifficulty(jeu.GetDifficulty() + 1);
					}
				}

				// Permet de revenir au menu principal
				else if (tab[localPosition.x][localPosition.y] == 3)
				{
					isInSettings = false;
				}

				//Permet d'aller au menu des crédits
				else if (tab[localPosition.x][localPosition.y] == 4)
				{
					MenuCredits(window);
				}

			}
		}
		while (window.pollEvent(event)) {
			// Demande de fermeture de la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Affichages des images
		titre.setTexture(titre_png);
		titre.setPosition(7.5 * 75, 20);
		window.draw(titre);

		version_wish.setTexture(version_wish_png);
		version_wish.setPosition(8 * 75, 290);
		window.draw(version_wish);

		noms.setTexture(noms_png);
		noms.setPosition(10, 10);
		window.draw(noms);

		//Affichage du bouton volume en fonction du volume
		if (musique_->GetVolume())
		{
			volume.setTexture(volume_png);
			volume.setPosition(10 * 75 + 10, 400);
			window.draw(volume);
		}
		else
		{
			volume_off.setTexture(volume_off_png);
			volume_off.setPosition(10 * 75 + 10, 400);
			window.draw(volume_off);
		}

		difficulte.setTexture(difficulte_png);
		difficulte.setPosition(10 * 75 + 10, 600);
		window.draw(difficulte);

		explication.setTexture(explication_png);
		explication.setPosition( 50, 350);
		window.draw(explication);

		credit.setTexture(credit_png);
		credit.setPosition(20, 800);//20->420 800->1000
		window.draw(credit);

		//Affichage de la difficulté
		switch (jeu.GetDifficulty())
		{
		case 2:

			diffNormale.setTexture(diffNormale_png);
			diffNormale.setPosition(15 * 75 - 10, 650);
			window.draw(diffNormale);

			break;

		case 3:

			diffDifficile.setTexture(diffDifficile_png);
			diffDifficile.setPosition(15 * 75 - 10, 650);
			window.draw(diffDifficile);

			break;

		case 4:

			diffHardcore.setTexture(diffHardcore_png);
			diffHardcore.setPosition(15 * 75 - 10, 650);
			window.draw(diffHardcore);

			break;
		}

		menu_principal.setTexture(menu_principal_png);
		menu_principal.setPosition(10* 75 + 10, 800);
		window.draw(menu_principal);


		window.display();
	}


	delete titre_png;
	delete version_wish_png;
	delete noms_png;
	delete volume_png;
	delete difficulte_png;
	delete menu_principal_png;
	delete credit_png;
}

void Menu::MenuCredits(sf::RenderWindow& window)
{
	int tab[190][100] = { 0 };
	for (int i = 0; i < 44; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			tab[i + 10][ j + 70] = 1;
		}
	}

	bool menuOuvert = true; //permet de quitter le menu

	//Stockage de l'image
	sf::Texture* credits_txt_png;
	credits_txt_png = new sf::Texture;
	(*credits_txt_png).loadFromFile("Images/credits_txt.png");
	sf::RectangleShape credits_txt(sf::Vector2f(1820, 980));

	while (window.isOpen() && menuOuvert )
	{
		sf::Event event;
		window.clear(sf::Color(255, 180, 0)); //couleur du fond

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}

			//détection des clics de la souris
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
			{
				// Position de la souris dans par rapport à la fenêtre
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				// Position de la souris dans le tableau
				localPosition /= 10;

				if (tab[localPosition.x][localPosition.y] == 1)
				{
					menuOuvert = false; // Quitter le menu
				}

			}
		}
		while (window.pollEvent(event)) {
			// Demande de fermeture de la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Affichage de l'image
		credits_txt.setTexture(credits_txt_png);
		credits_txt.setPosition(0 * 75, 0);
		window.draw(credits_txt);




		window.display();
	}

	delete credits_txt_png;
}

void Menu::operator=(Menu menu)
{
	musique_ = menu.GetMusique();
}

string Menu::MenuTexte(sf::RenderWindow& window, Jeu jeu)
{
	bool inMenu = true;
	string nom = "";
	while (window.isOpen() && inMenu)
	{
		sf::Event event;
		window.clear(sf::Color(255, 180, 0));//fond de couleur
		sf::Font font;
		font.loadFromFile("niagara_solid.ttf"); // choix de la police
		sf::Text titre;
		sf::Text name;

		titre.setFont(font);
		name.setFont(font);

		titre.setString("Veuillez entrer votre nom :");
		titre.setCharacterSize(100);
		titre.setPosition(8*75, 5*75);
		titre.setFillColor(sf::Color(136, 0, 21));

		name.setString(nom);
		name.setCharacterSize(100);
		name.setPosition(11 * 75+30, 6 * 75);
		name.setFillColor(sf::Color(136, 0, 21));

		window.draw(titre);
		window.draw(name);

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter)
				{
					inMenu = false;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					nom += "A";
				}
				if (event.key.code == sf::Keyboard::B)
				{
					nom += "B";
				}
				if (event.key.code == sf::Keyboard::C)
				{
					nom += "C";
				}
				if (event.key.code == sf::Keyboard::D)
				{
					nom += "D";
				}
				if (event.key.code == sf::Keyboard::E)
				{
					nom += "E";
				}
				if (event.key.code == sf::Keyboard::F)
				{
					nom += "F";
				}
				if (event.key.code == sf::Keyboard::G)
				{
					nom += "G";
				}
				if (event.key.code == sf::Keyboard::H)
				{
					nom += "H";
				}
				if (event.key.code == sf::Keyboard::I)
				{
					nom += "I";
				}
				if (event.key.code == sf::Keyboard::J)
				{
					nom += "J";
				}
				if (event.key.code == sf::Keyboard::K)
				{
					nom += "K";
				}
				if (event.key.code == sf::Keyboard::L)
				{
					nom += "L";
				}
				if (event.key.code == sf::Keyboard::M)
				{
					nom += "M";
				}
				if (event.key.code == sf::Keyboard::N)
				{
					nom += "N";
				}
				if (event.key.code == sf::Keyboard::O)
				{
					nom += "O";
				}
				if (event.key.code == sf::Keyboard::P)
				{
					nom += "P";
				}
				if (event.key.code == sf::Keyboard::Q)
				{
					nom += "Q";
				}
				if (event.key.code == sf::Keyboard::R)
				{
					nom += "R";
				}
				if (event.key.code == sf::Keyboard::S)
				{
					nom += "S";
				}
				if (event.key.code == sf::Keyboard::T)
				{
					nom += "T";
				}
				if (event.key.code == sf::Keyboard::U)
				{
					nom += "U";
				}
				if (event.key.code == sf::Keyboard::V)
				{
					nom += "V";
				}
				if (event.key.code == sf::Keyboard::W)
				{
					nom += "W";
				}
				if (event.key.code == sf::Keyboard::X)
				{
					nom += "X";
				}
				if (event.key.code == sf::Keyboard::Y)
				{
					nom += "Y";
				}
				if (event.key.code == sf::Keyboard::Z)
				{
					nom += "Z";
				}
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					nom.pop_back();
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					nom += " ";
				}
				break;
			default:
				break;
			}
		}
		while (window.pollEvent(event)) {
			// Demande de fermeture de la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.display();
	}
	return nom;
}

void Menu::MenuEdit(sf::RenderWindow& window, Jeu& jeu)
{
	int map[25][14] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			map[j][i] = -1;
		}
	}

	int choix = 1;
	bool quitter = false;
	
	//différent forme pour dessin
	vector<sf::CircleShape> textureCercle;
	vector<sf::Texture*> texturePng;
	vector<sf::RectangleShape> textureRectangle;

	sf::Font font;
	font.loadFromFile("niagara_solid.ttf"); // choix de la police
	sf::Text text;
	text.setFont(font);

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

	// 849*294

	sf::Texture* oui_png;
	oui_png = new sf::Texture;
	(*oui_png).loadFromFile("Images/oui.png");
	sf::RectangleShape oui(sf::Vector2f(849, 294));
	textureRectangle.push_back(oui);
	texturePng.push_back(oui_png);

	sf::Texture* non_png;
	non_png = new sf::Texture;
	(*non_png).loadFromFile("Images/non.png");
	sf::RectangleShape non(sf::Vector2f(849, 294));
	textureRectangle.push_back(non);
	texturePng.push_back(non_png);

	sf::Texture* cancel_png;
	cancel_png = new sf::Texture;
	(*cancel_png).loadFromFile("Images/cancel.png");
	sf::RectangleShape cancel(sf::Vector2f(849, 294));
	textureRectangle.push_back(cancel);
	texturePng.push_back(cancel_png);

	bool menuOuvert = true; //permet de quitter le menu
	int x = 0;
	int y = 0;

	while (window.isOpen() && menuOuvert)
	{
		sf::Event event;
		window.clear(sf::Color(255, 180, 0)); //couleur du fond

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					quitter=true;
					bool start = false;
					bool diamant = false;
					bool porte = false;
					for (int i = 0; i < 14; i++)
					{
						for (int j = 0; j < 25; j++)
						{
							if (map[j][i] == 6)
							{
								start = true;
							}
							else if (map[j][i] == 2)
							{
								diamant = true;
							}
							else if (map[j][i] == 4)
							{
								porte = true;
							}
						}
					}
					if (start == false)
					{
						map[1][1] = 6;
					}
					if (diamant == false)
					{
						map[2][1] = 2;
					}
					if (porte == false)
					{
						map[3][1] = 4;
					}
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					if (y > 0)
					{
						y--;
					}
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					if (x > 0)
					{
						x--;
					}
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					if (y < 13)
					{
						y++;
					}
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					if (x < 24)
					{
						x++;
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					SetValeurMap(x, y, map, true);
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					SetValeurMap(x, y, map, false);
				}
				break;
			default:
				break;
			}
		}

		

		while (window.pollEvent(event)) {
			// Demande de fermeture de la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}

		drawGridEdit(window, jeu, textureCercle, texturePng, textureRectangle, 0, map, text);
		DrawCarre(window, y, x);

		while (quitter)
		{
			window.setKeyRepeatEnabled(false);
			{
				while (window.pollEvent(event))
				{
					switch (event.type)
					{
						// fenêtre fermée
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::KeyPressed:
						if (event.key.code == sf::Keyboard::Right)
						{
							if (choix < 3)
							{
								choix++;
							}
						}
						if (event.key.code == sf::Keyboard::Left)
						{
							if (choix > 1)
							{
								choix--;
							}
						}
						if (event.key.code == sf::Keyboard::Enter)
						{
							if (choix == 1)
							{
								Cartes carte(map);
								jeu.AjouterCarte(carte);
								menuOuvert = false;
								quitter = false;
							}
							if (choix == 2)
							{
								menuOuvert=false;
								quitter = false;
							}
							if (choix == 3)
							{
								quitter = false;
							}
						}
					}
				}
			}


			drawGridEdit(window, jeu, textureCercle, texturePng, textureRectangle, 0, map, text);


			if (choix == 1)
			{
				oui.setTexture(oui_png);
				oui.setPosition(6 * 75, 5 * 75);
				window.draw(oui);
			}
			else if (choix == 2)
			{
				non.setTexture(non_png);
				non.setPosition(6 * 75, 5 * 75);
				window.draw(non);
			}
			else
			{
				cancel.setTexture(cancel_png);
				cancel.setPosition(6 * 75, 5 * 75);
				window.draw(cancel);
			}

			window.display();
		}

		window.display();
	}

}

void Menu::DrawCarre(sf::RenderWindow& window, int i, int j)
{
	vector<sf::RectangleShape> lines;
	int t = lines.size();

	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 77)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 77)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 81)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(5, 77)));

	lines[t].setPosition(j * 75 - 2, i * 75);
	lines[t + 1].setPosition(75+j * 75, i * 75+73);
	lines[t + 2].setPosition(73 + j * 75, i * 75-2);
	lines[t + 3].setPosition(75 + j * 75,  i * 75-2);
	lines[t + 1].rotate(90);
	lines[t + 3].rotate(90);
	lines[t].setFillColor(sf::Color::Yellow);
	lines[t + 1].setFillColor(sf::Color::Yellow);
	lines[t + 2].setFillColor(sf::Color::Yellow);
	lines[t + 3].setFillColor(sf::Color::Yellow);

	for (i = 0; i < 4; i++)//tracer les lignes
		window.draw(lines[t + i]);
}

void Menu::drawGridEdit(sf::RenderWindow& window, Jeu& jeu, vector<sf::CircleShape> textureCercle, vector<sf::Texture*> texturePng, vector<sf::RectangleShape> textureRectangle, float vitesseBlaser, int map[25][14], sf::Text text)
{
	vector<sf::RectangleShape> lines;//forme rectangulaire dessin
	vector<sf::CircleShape> circle;// forme circulaire dessin
	vector<sf::RectangleShape> tra;//dessine la trace du joueur

	int t;

	jeu.grille(window, lines);// dessine le cardillage de fond 

	for (int i = 0; i < 14; i++)//14 = taille en ordonée
	{
		for (int j = 0; j < 25; j++)//25 = taille en abcisse
		{

			switch (map[j][i])
			{

			case -1://case foncé
				t = lines.size();
				lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
				lines[t].setPosition(j * 75, i * 75);
				lines[t].setFillColor(sf::Color(205, 80, 0));
				window.draw(lines[t]);
				break;
			case 0: // case vide
				break;
			case 1:// laser
				jeu.drawlaser(window, i, j, lines, true, sf::Color::Red);
				break;
			case 2:// gemme non recolté
				textureCercle[0].setTexture(texturePng[0]);
				textureCercle[0].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[0]);
				break;
			case 3:// gemme recolté (case vide)
				break;
			case 4:// porte bloqué
				jeu.DrawPorteFerme(window, i, j, lines, circle);
				break;
			case 5:// porte ouverte
				jeu.DrawPorteOuverte(window, i, j, lines);
				break;
			case 6:// position de départ
				textureRectangle[7].setTexture(texturePng[9]);
				textureRectangle[7].setPosition(j * 75, 12 + i * 75);
				window.draw(textureRectangle[7]);//pour position du début
				break;
			case 51://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("1");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 52://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("2");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 53://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("3");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 54://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("4");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 55://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("5");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 56://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("6");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 57://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("7");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 58://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("8");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 59://clef 1
				textureRectangle[0].setTexture(texturePng[1]);
				textureRectangle[0].setPosition(4 + j * 75, 24 + i * 75);
				window.draw(textureRectangle[0]);
				text.setString("9");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 61:// clef 1 recolté
				break;
			case 62:// clef 1 recolté
				break;
			case 63:// clef 1 recolté
				break;
			case 64:// clef 1 recolté
				break;
			case 65:// clef 1 recolté
				break;
			case 66:// clef 1 recolté
				break;
			case 67:// clef 1 recolté
				break;
			case 68:// clef 1 recolté
				break;
			case 69:// clef 1 recolté
				break;
			case 71://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("1");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 72://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("2");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 73://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("3");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 74://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("4");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 75://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("5");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 76://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("6");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 77://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("7");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 78://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("8");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 79://cadenas 1
				textureCercle[1].setTexture(texturePng[2]);
				textureCercle[1].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureCercle[1]);
				text.setString("9");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 81: //cadenas 1 recolté
				break;
			case 82: //cadenas 1 recolté
				break;
			case 83: //cadenas 1 recolté
				break;
			case 84: //cadenas 1 recolté
				break;
			case 85: //cadenas 1 recolté
				break;
			case 86: //cadenas 1 recolté
				break;
			case 87: //cadenas 1 recolté
				break;
			case 88: //cadenas 1 recolté
				break;
			case 89: //cadenas 1 recolté
				break;
			case 21://fleche vers le bas 
				textureRectangle[8].setTexture(texturePng[10]);
				textureRectangle[8].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[8]);
				break;
			case 22://fleche vers le haut
				textureRectangle[9].setTexture(texturePng[11]);
				textureRectangle[9].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[9]);
				break;
			case 23://fleche vers la gauche
				textureRectangle[10].setTexture(texturePng[12]);
				textureRectangle[10].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[10]);
				break;
			case 24://fleche vers la droite
				textureRectangle[11].setTexture(texturePng[13]);
				textureRectangle[11].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[11]);
				break;
			case -2://décoration
				textureRectangle[1].setTexture(texturePng[3]);
				textureRectangle[1].setPosition(5 + j * 75, 5 + i * 75);
				window.draw(textureRectangle[1]);
				break;
			case -3://décoration
				textureRectangle[2].setTexture(texturePng[4]);
				textureRectangle[2].setPosition(14 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[2]);
				break;
			case -4://décoration
				textureRectangle[3].setTexture(texturePng[5]);
				textureRectangle[3].setPosition(5 + j * 75, 5 + i * 75);
				window.draw(textureRectangle[3]);
				break;
			case -5://décoration
				textureRectangle[4].setTexture(texturePng[6]);
				textureRectangle[4].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[4]);
				break;
			case -6://décoration
				textureRectangle[5].setTexture(texturePng[7]);
				textureRectangle[5].setPosition(14 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[5]);
				break;
			case -7://décoration
				textureRectangle[6].setTexture(texturePng[8]);
				textureRectangle[6].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[6]);
				break;
			case 10://teleporteur 1
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("1");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 11://teleporteur 1
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("2");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 12://teleporteur 1
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("3");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 13://teleporteur 1
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("4");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 14://teleporteur 1
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("5");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 15://teleporteur 1
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("6");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 16://receveur teleporteur 1
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("7");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 17://teleporteur 2
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("8");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 18://receveur teleporteur 
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("9");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 19://receveur teleporteur 2
				textureRectangle[12].setTexture(texturePng[14]);
				textureRectangle[12].setPosition(4 + j * 75, 4 + i * 75);
				window.draw(textureRectangle[12]);
				text.setString("10");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 31://levier désactivé
				textureRectangle[13].setTexture(texturePng[15]);
				textureRectangle[13].setPosition(4 + j * 75 + 10, 4 + i * 75 + 17);
				window.draw(textureRectangle[13]);
				break;
			case 32://levier activé
				textureRectangle[14].setTexture(texturePng[16]);
				textureRectangle[14].setPosition(4 + j * 75 + 10, 4 + i * 75 + 17);
				window.draw(textureRectangle[14]);
				break;
			case 33:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Red);

				break;
			case 34:
				break;
			case 35:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color(150, 150, 150));

				break;
			case 36:
				break;
			case 37:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Yellow);
				break;
			case 38:
				jeu.tracejoueur(window, j, i, tra);
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Red);
				break;
			case 39:
				break;
			case 41://Blaser haut
				if (i == 0 && j == 0)
				{
					t = lines.size();
					lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
					lines[t].setPosition(j * 75, i * 75);
					lines[t].setFillColor(sf::Color(205, 80, 0));
					window.draw(lines[t]);
				}
				else if (i == 13 && j == 0)
				{
					t = lines.size();
					lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
					lines[t].setPosition(j * 75, i * 75);
					lines[t].setFillColor(sf::Color(205, 80, 0));
					window.draw(lines[t]);
				}
				else if (i == 13 && j == 24)
				{
					t = lines.size();
					lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
					lines[t].setPosition(j * 75, i * 75);
					lines[t].setFillColor(sf::Color(205, 80, 0));
					window.draw(lines[t]);
				}
				else if (i == 0 && j == 24)
				{
					t = lines.size();
					lines.push_back(sf::RectangleShape(sf::Vector2f(75, 75)));
					lines[t].setPosition(j * 75, i * 75);
					lines[t].setFillColor(sf::Color(205, 80, 0));
					window.draw(lines[t]);
				}
				break;
			case 101:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("1");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 102:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("2");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 103:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("3");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 104:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("4");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 105:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("5");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 106:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("6");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 107:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("7");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 108:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("8");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 109:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("9");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 110:
				jeu.DrawLaserLevier(window, i, j, lines, sf::Color::Black);
				text.setString("10");
				text.setCharacterSize(75);
				text.setPosition(35 + j * 75, -14 + i * 75);
				text.setFillColor(sf::Color(255, 255, 255));
				window.draw(text);
				break;
			case 121://champi inverseur
				textureRectangle[15].setTexture(texturePng[17]);
				textureRectangle[15].setPosition(4 + j * 75 + 10, 4 + i * 75 + 17);
				window.draw(textureRectangle[15]);
				break;
			}
			if (map[0][0] == 41) //Si le blaser haut existe dans cette carte
			{
				jeu.Blaser(window, 0, true);
			}
			if (map[0][13] == 41) //Si le blaser gauche existe dans cette carte
			{
				jeu.Blaser(window, 0, false);
			}
			if (map[24][13] == 41) //Si le blaser bas existe dans cette carte
			{
				jeu.Blaser(window, 13, true);
			}
			if (map[24][0] == 41) //Si le blaser droite existe dans cette carte
			{
				jeu.Blaser(window, 24, false);
			}
		}
	}


}

void Menu::SetValeurMap(int x, int y, int map[25][14], bool sens)
{
	if (sens)
	{
		if ((map[x][y] > -8 && map[x][y] < 2) || (map[x][y] > 9 && map[x][y] < 19) || (map[x][y] > 20 && map[x][y] < 24) || map[x][y] == 37 || (map[x][y] > 50 && map[x][y] < 59) || (map[x][y] > 70 && map[x][y] < 79) || (map[x][y] > 100 && map[x][y] < 110))
		{
			map[x][y] += 1;
		}
		else if (map[x][y] == 2 || map[x][y] == 4 || map[x][y]==31 || map[x][y] == 33 || map[x][y] == 35)
		{
			map[x][y] += 2;

		}
		else if (map[x][y] == 6)
		{
			map[x][y] = 10;

		}
		else if (map[x][y] == 19)
		{
			map[x][y] = 21;

		}
		else if (map[x][y] == 24)
		{
			map[x][y] = 31;

		}
		else if (map[x][y] == 38)
		{
			if (x == 0 && y == 0)
			{
				map[x][y] = 41;
			}
			else if (x == 0 && y == 13)
			{
				map[x][y] = 41;
			}
			else if (x == 24 && y == 13)
			{
				map[x][y] = 41;
			}
			else if (x == 24 && y == 0)
			{
				map[x][y] = 41;
			}
			else
			{
				map[x][y] = 51;
			}
		}
		else if (map[x][y] == 41)
		{
			map[x][y] = 51;
		}
		else if (map[x][y] == 59)
		{
			map[x][y] = 71;

		}
		else if (map[x][y] == 79)
		{
			map[x][y] = 101;

		}
		else if (map[x][y] == 110)
		{
			map[x][y] = 121;
		}
		else if (map[x][y] == 121)
		{
			map[x][y] = -7;
		}
	}
	else
	{
		if ((map[x][y] > -7 && map[x][y] < 3) || (map[x][y] > 10 && map[x][y] < 20) || (map[x][y] > 21 && map[x][y] < 25) || map[x][y] == 38 || (map[x][y] > 51 && map[x][y] < 60) || (map[x][y] > 71 && map[x][y] < 80) || (map[x][y] > 101 && map[x][y] < 111))
		{
			map[x][y] -= 1;
		}
		else if (map[x][y] == 6 || map[x][y] == 4 || map[x][y]==33 || map[x][y] == 37 || map[x][y] == 35)
		{
			map[x][y] -= 2;

		}
		else if (map[x][y] == 10)
		{
			map[x][y] = 6;

		}
		else if (map[x][y] == 21)
		{
			map[x][y] = 19;

		}
		else if (map[x][y] == 31)
		{
			map[x][y] = 24;

		}
		else if (map[x][y] == 51)
		{
			if (x == 0 && y == 0)
			{
				map[x][y] = 41;
			}
			else if (x == 0 && y == 13)
			{
				map[x][y] = 41;
			}
			else if (x == 24 && y == 13)
			{
				map[x][y] = 41;
			}
			else if (x == 24 && y == 0)
			{
				map[x][y] = 41;
			}
			else
			{
				map[x][y] = 38;
			}
		}
		else if (map[x][y] == 41)
		{
			map[x][y] = 38;
		}
		else if (map[x][y] == 71)
		{
			map[x][y] = 59;

		}
		else if (map[x][y] == 101)
		{
			map[x][y] = 79;
		}
		else if (map[x][y] == 121)
		{
			map[x][y] = 110;
		}
		else if (map[x][y] == -7)
		{
			map[x][y] = 121;
		}
	}
}