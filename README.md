Larcin Lazer game replica in C++

The goal of the game is to get the diamond and to move to the door to pass to the next level.
You need to memorize where the lasers are before moving and avoid them.
If you want to pass a level, you can press "o".
There is also some other functionality as you advance, but there is a level to help you understand them.

To launch the game, if it does not work, just click on Larcin_Lazer.sln:

1. Download the Visual C++ 15(2017) - 64 bits version on the official website
2. Download and unzip the SFML-2.5.1 folder to the root of your C drive:
3. In the top left-hand corner, to the left of the Local Windows Debugger button, check that you are
Debug and x64 configuration
4. Open the properties page in Project -> Properties of < project name >.
5. At the very top, check that the configuration is Debug and platform x64
6. In the C/C++ -> General tab, in the Other include directories field, enter C:\SFML-2.5.1\include
7. In the Link Editor -> General tab, in the Additional library directories field, enter directories, specify C:\SFML-2.5.1\lib
8. In the Link Editor -> Input tab, click on Additional dependencies then on the down arrow then <Edit...>.
9. In the text box, enter sfml-system-d.lib, sfml-window-d.lib, sfml-graphics-d.lib, sfml-audio-d.lib separated by line breaks.
10. Validate the changes

In the game, the first thing you need to do is enter your name ("Veuillez entrer votre nom") to save your progression.
After that, you are on the main menu, and you can play by clicking on Play ("Jouer") but before that, you can choose your settings in "Options" 
If you want music or not with "Volume" and the Difficulty ("Difficulté") of the game with Normal("Normale"), Difficult ("Difficile") or Hardcore 
After that, you can click on ("Menu Principale") to go back to the main menu.
With the - and + next to ("Choix des niveaux") you can select the level that you want.

Author : 
Malo GALABERT DE CLERCQ / Flavien BORGET
