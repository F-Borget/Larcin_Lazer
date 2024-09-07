#ifndef Son_H
#define Son_H
#include <SFML/Audio.hpp>



class Son
{
	bool volume_;

	sf::Music menuTheme_; //musique de fond menu
	sf::Music menuTheme_old_; //musique de fond menu
	sf::Music mainTheme1_; //Musique de fond jeu
	sf::Music mainTheme2_; //Musique de fond jeu
	sf::Music mainTheme3_; //Musique de fond jeu
	sf::Music mainTheme4_; //Musique de fond jeu
	sf::Music mainTheme5_; //Musique de fond jeu
	sf::Music mainTheme6_; //Musique de fond jeu
	sf::Music main_theme_old_; //Musique de fond jeu


	sf::Sound death_; //Musique de la mort
	sf::SoundBuffer bufferDeath_;
	
public:
	Son();
	bool GetVolume() {return volume_; }
	void SetVolume(bool volume);

	bool GetMenuStatus() { return menuTheme_.getStatus(); }
	bool GetMainThemeStatus() { return mainTheme1_.getStatus(); }
	bool GetOldThemeStatus() { return main_theme_old_.getStatus(); }

	void PlayDeath();
	void PlayMenu();
	void PlayMenuOld();
	void PlayMainTheme1();
	void PlayMainTheme2();
	void PlayMainTheme3();
	void PlayMainTheme4();
	void PlayMainTheme5();
	void PlayMainTheme6();
	void PlayMainThemeOld();


	void StopMenu();
	void StopMenuOld();
	void StopMainTheme1();
	void StopMainTheme2();
	void StopMainTheme3();
	void StopMainTheme4();
	void StopMainTheme5();
	void StopMainTheme6();
	void StopMainThemeOld();

	void operator=(Son son);
};






#endif
