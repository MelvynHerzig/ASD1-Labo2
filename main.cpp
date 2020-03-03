#include <iostream>
#include <array>
#include "Pieces.h"

//Vérifie si une image (de gauche à droite ou de haut en bas) match entre deux pièces.
bool coteComplementaire(const AttachementType& c1, const AttachementType& c2)
{
    switch(c1)
    {
        case FILLE_HAUT      : return c2 == FILLE_BAS      ;
        case FILLE_BAS       : return c2 == FILLE_HAUT     ;
        case DAME_HAUT       : return c2 == DAME_BAS       ;
        case DAME_BAS        : return c2 == DAME_HAUT      ;
        case ARROSOIR_GAUCHE : return c2 == ARROSOIR_DROIT ;
        case ARROSOIR_DROIT  : return c2 == ARROSOIR_GAUCHE;
        case GATEAU_GAUCHE   : return c2 == GATEAU_DROIT   ;
        case GATEAU_DROIT    : return c2 == GATEAU_GAUCHE  ;
        case ARROSOIR_INVERSE: return c2 == NONE           ;
    }

    return false;
}

int main()
{

    return 0;
}