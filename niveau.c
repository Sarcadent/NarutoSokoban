/*
jeu.c
-----

Par Sarcadent

Rôle : choix des niveaux.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "jeu.h"
//#include "niveau.h"
//venue = 0 Editeur
//venue = 1 Jeu
void menuNiveau(SDL_Surface* ecran, int venue)
{
    SDL_Surface *NiveauEditeur = {NULL}, *NiveauJeu = {NULL};
    SDL_Rect position;
    SDL_Event event;

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    position.x = 0;
    position.y = 0;

    int continuer = 1;
    int niveauChoisi = 0;
    int carte[7][7] = {0};
    int clic = 1, i = 0, j = 0;

    // Chargement des sprites (décors, personnage...)
    NiveauEditeur = IMG_Load("GFX/niveauEditer.png");
    NiveauJeu = IMG_Load("GFX/niveauJouer.png");

    // Activation de la répétition des touches
    SDL_EnableKeyRepeat(100, 100);

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
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                       carte[event.button.x / 60][event.button.y / 60] = clic;
                        //clicGaucheEnCours = 1; // On retient qu'un bouton est enfoncé
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT) // Clic droit pour effacer
                    {
                        //carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                        //clicDroitEnCours = 1;
                    }
                    break;
            }

        //calcule du niveau choisi
            if (carte[1][2] == clic)        {niveauChoisi = 1;}
            else if (carte[2][2] == clic)   {niveauChoisi = 2;}
            else if (carte[3][2] == clic)   {niveauChoisi = 3;}
            else if (carte[4][2] == clic)   {niveauChoisi = 4;}
            else if (carte[5][2] == clic)   {niveauChoisi = 5;}
            else if (carte[6][2] == clic)   {niveauChoisi = 6;}
            else if (carte[1][3] == clic)   {niveauChoisi = 7;}
            else if (carte[2][3] == clic)   {niveauChoisi = 8;}
            else if (carte[3][3] == clic)   {niveauChoisi = 9;}
            else if (carte[4][3] == clic)   {niveauChoisi = 10;}
            else if (carte[5][3] == clic)   {niveauChoisi = 11;}
            else if (carte[6][3] == clic)   {niveauChoisi = 12;}
            else if (carte[1][4] == clic)   {niveauChoisi = 13;}
            else if (carte[2][4] == clic)   {niveauChoisi = 14;}
            else if (carte[3][4] == clic)   {niveauChoisi = 15;}
            else if (carte[4][4] == clic)   {niveauChoisi = 16;}
            else if (carte[5][4] == clic)   {niveauChoisi = 17;}
            else if (carte[6][4] == clic)   {niveauChoisi = 18;}
            else if (carte[1][5] == clic)   {niveauChoisi = 19;}
            else if (carte[2][5] == clic)   {niveauChoisi = 20;}
            else if (carte[3][5] == clic)   {niveauChoisi = 21;}
            else if (carte[4][5] == clic)   {niveauChoisi = 22;}
            else if (carte[5][5] == clic)   {niveauChoisi = 23;}
            else if (carte[6][5] == clic)   {niveauChoisi = 24;}
            else if (carte[1][6] == clic)   {niveauChoisi = 25;}
            else if (carte[2][6] == clic)   {niveauChoisi = 26;}
            else if (carte[3][6] == clic)   {niveauChoisi = 27;}
            else if (carte[4][6] == clic)   {niveauChoisi = 28;}
            else if (carte[5][6] == clic)   {niveauChoisi = 29;}
            else if (carte[6][6] == clic)   {niveauChoisi = 30;}

            if (niveauChoisi !=0 && venue == 1)
            {
               jouer(ecran, niveauChoisi);
               venue = 1;
               niveauChoisi = 0;
            }
            else if (niveauChoisi > 10 && venue == 0)
            {
                editeur(ecran, niveauChoisi);
                venue = 0;
                niveauChoisi = 0;
            }
            //reinitialisation du tableau
            for (i=0; i<=6; i++)
                    {
                        for (j=0; j<=6; j++)
                        {
                            carte[i][j] = 0;
                        }
                    }

         // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        // Placement des objets à l'écran
        if (venue == 0)
        {
            SDL_BlitSurface(NiveauEditeur, NULL, ecran, &position);
        }
        else
        {
            SDL_BlitSurface(NiveauJeu, NULL, ecran, &position);
        }
        SDL_Flip(ecran);
    }

    // Désactivation de la répétition des touches (remise à 0)
    SDL_EnableKeyRepeat(0, 0);

    // Libération des surfaces chargées
    SDL_FreeSurface(NiveauEditeur);
    SDL_FreeSurface(NiveauJeu);


}









