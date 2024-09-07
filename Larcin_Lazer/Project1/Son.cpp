#include "Son.h"
#include <iostream>
using namespace std;

Son::Son()
{
	volume_ = true;
	menuTheme_.openFromFile("musiques/menu_theme.ogg");
	menuTheme_.setVolume(50.f);
	menuTheme_.setLoop(true);
	menuTheme_old_.openFromFile("musiques/menu_theme_old.ogg");
	menuTheme_old_.setVolume(100.f);
	menuTheme_old_.setLoop(true);

	mainTheme1_.openFromFile("musiques/main_theme1.ogg");
	mainTheme1_.setVolume(25.f);
	mainTheme1_.setLoop(true);
	mainTheme2_.openFromFile("musiques/main_theme2.ogg");
	mainTheme2_.setVolume(25.f);
	mainTheme2_.setLoop(true);
	mainTheme3_.openFromFile("musiques/main_theme3.ogg");
	mainTheme3_.setVolume(25.f);
	mainTheme3_.setLoop(true);
	mainTheme4_.openFromFile("musiques/main_theme4.ogg");
	mainTheme4_.setVolume(25.f);
	mainTheme4_.setLoop(true);
	mainTheme5_.openFromFile("musiques/main_theme5.ogg");
	mainTheme5_.setVolume(25.f);
	mainTheme5_.setLoop(true);
	mainTheme6_.openFromFile("musiques/main_theme6.ogg");
	mainTheme6_.setVolume(25.f);
	mainTheme6_.setLoop(true);
	main_theme_old_.openFromFile("musiques/main_theme_old.ogg");
	main_theme_old_.setVolume(25.f);
	main_theme_old_.setLoop(true);

	bufferDeath_.loadFromFile("bande_son/mort_laser.wav");
	death_.setBuffer(bufferDeath_);
}

void Son::operator=(Son son)
{
	volume_ = son.GetVolume();
}

void Son::SetVolume(bool volume)
{
	volume_ = volume;
}

void Son::PlayDeath()
{
	if (volume_)
	{
		death_.play();
	}
}

void Son::PlayMenu()
{
	if (volume_)
	{
		menuTheme_.play();
	}
}

void Son::PlayMenuOld()
{
	if (volume_)
	{
		menuTheme_old_.play();
	}
}

void Son::PlayMainTheme1()
{
	if (volume_)
	{
		mainTheme1_.play();
	}
}

void Son::PlayMainTheme2()
{
	if (volume_)
	{
		mainTheme2_.play();
	}
}

void Son::PlayMainTheme3()
{
	if (volume_)
	{
		mainTheme3_.play();
	}
}

void Son::PlayMainTheme4()
{
	if (volume_)
	{
		mainTheme4_.play();
	}
}

void Son::PlayMainTheme5()
{
	if (volume_)
	{
		mainTheme5_.play();
	}
}

void Son::PlayMainTheme6()
{
	if (volume_)
	{
		mainTheme6_.play();
	}
}

void Son::PlayMainThemeOld()
{
	if (volume_)
	{
		main_theme_old_.play();
	}
}

void Son::StopMenu()
{
	menuTheme_.stop();
}

void Son::StopMenuOld()
{
	menuTheme_old_.stop();
}

void Son::StopMainTheme1()
{
	mainTheme1_.stop();
}

void Son::StopMainTheme2()
{
	mainTheme2_.stop();
}

void Son::StopMainTheme3()
{
	mainTheme3_.stop();
}

void Son::StopMainTheme4()
{
	mainTheme4_.stop();
}

void Son::StopMainTheme5()
{
	mainTheme5_.stop();
}

void Son::StopMainTheme6()
{
	mainTheme6_.stop();
}

void Son::StopMainThemeOld()
{
	main_theme_old_.stop();
}