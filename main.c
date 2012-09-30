/*
main.c
------

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : menu du jeu. Permet de choisir entre l'éditeur et le jeu lui-même.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "niveau.h"


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL, *manuel = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1, afficherManuel = 0;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(408, 408, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Naruto Sokoban", NULL);

    menu = IMG_Load("menu.png");
    manuel = IMG_Load("GFX/manuel.png");
    positionMenu.x = 0;
    positionMenu.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        if (afficherManuel != 1)
                        {
                            continuer = 0;
                        }
                        else
                        {
                            afficherManuel = 0;
                        }
                        break;
                    case SDLK_1: // Demande à jouer
                        if (afficherManuel != 1)
                        {
                            menuNiveau(ecran, 1);
                        }
                        else
                        {
                            afficherManuel = 0;
                        }
                        break;
                    case SDLK_2: // Demande l'éditeur de niveaux
                        if (afficherManuel != 1)
                        {
                        menuNiveau(ecran, 0);
                        }
                        else
                        {
                            afficherManuel = 0;
                        }
                        break;
                    case SDLK_3:
                        //afficher image avec les règles
                        if (afficherManuel == 0)
                        {
                            afficherManuel = 1;
                        }
                        else
                        {
                            afficherManuel = 0;
                        }
                        break;
                }
                break;
        }

        // Effacement de l'écran
        ecran = SDL_SetVideoMode(408, 408, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        if (afficherManuel == 1)
        {
            SDL_BlitSurface(manuel, NULL, ecran, &positionMenu);
        }
        else
        {
            SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        }
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_FreeSurface(manuel);
    SDL_Quit();

    return EXIT_SUCCESS;
}





