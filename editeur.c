/*
editeur.c
---------

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : gestion de l'éditeur de niveaux.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"
#include "niveau.h"

void editeur(SDL_Surface* ecran, int niveauChoisi)
{
    SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL, *caisseOk = NULL, *info = NULL;
    SDL_Rect position;
    SDL_Event event;

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE + 150, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    //int niveauChoisi = 0;

    // Chargement des objets et du niveau
    mur = IMG_Load("GFX/mur.jpg");
    caisse = IMG_Load("GFX/caisse.jpg");
    objectif = IMG_Load("GFX/objectif.png");
    mario = IMG_Load("GFX/PositionDeDepart.png");
    caisseOk = IMG_Load("GFX/caisse_ok.jpg");
    info = IMG_Load("GFX/tableauEdition.png");

    if (!chargerNiveau(carte, niveauChoisi))
        exit(EXIT_FAILURE);

    // Boucle infinie de l'éditeur
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    //empecher de mettre deux position de départ
                    if (objetActuel == MARIO)
                    {
                        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                        {
                            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                            {
                                position.x = i * TAILLE_BLOC;
                                position.y = j * TAILLE_BLOC;

                                switch(carte[i][j])
                                {
                                    case MARIO:
                                        // Si une case est la position de départ on la met vide
                                        carte[i][j] = VIDE;
                                        break;
                                }
                            }
                        }
                    }
                    // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                    clicGaucheEnCours = 1; // On active un booléen pour retenir qu'un bouton est enfoncé
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) // Le clic droit sert à effacer
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            case SDL_MOUSEMOTION:
                if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                }
                else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte, niveauChoisi);
                        break;
                    case SDLK_c:
                        chargerNiveau(carte, niveauChoisi);
                        break;
                    case SDLK_1:
                        objetActuel = MUR;
                        break;
                    case SDLK_2:
                        objetActuel = CAISSE;
                        break;
                    case SDLK_3:
                        objetActuel = OBJECTIF;
                        break;
                    case SDLK_4:
                        objetActuel = MARIO;
                        break;
                    case SDLK_5:
                        objetActuel = CAISSE_OK;
                        break;
                }
                break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        // Placement des objets à l'écran
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;
                    case MARIO:
                        SDL_BlitSurface(mario, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOk, NULL, ecran, &position);
                        break;
                }
            }
        }
        //placement des informations de l'éditeur
        position.x = 480;
        position.y = 0;
        SDL_BlitSurface(info, NULL, ecran, &position);
               //placement de l'objet sélectionné
                position.x = 520;
                position.y = 120;
                switch(objetActuel)
                {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;
                    case MARIO:
                        SDL_BlitSurface(mario, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOk, NULL, ecran, &position);
                        break;
                }
        // Mise à jour de l'écran
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);
    SDL_FreeSurface(info);
    SDL_FreeSurface(caisseOk);
}
