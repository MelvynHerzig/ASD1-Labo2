/*
 -----------------------------------------------------------------------------------
 Laboratoire : 02
 Fichier     : main.cpp
 Auteur(s)   : Melvyn Herzig, Forestier Quentin, Berney Alec
 Date        : 03.03.2020

 But         : Exploiter la classe Pieces et résoudre le puzzle impossible

 Remarque(s) : /

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <array>     //std::array
#include <algorithm> //std::rotate
#include <iostream>   //std::ostream, std::cout
#include "Pieces.h"  //Piece, PIECES, AttachmentType

class PieceOrientee;
const unsigned TAILLE_PUZZLE = 9;
using Puzzle = std::array<PieceOrientee, TAILLE_PUZZLE>;

enum Orientation {A, B, C, D};
enum Cote{HAUT, DROITE, BAS, GAUCHE};

class PieceOrientee
{
public:
    PieceOrientee() = default;
    PieceOrientee(const Piece& piece , const Orientation& orientation, unsigned id);

    //effecteur une rotation de 90deg vers la gauche de la piece.
    void rotationGauche();

    unsigned id;
    Piece piece;
    Orientation orientation;
};

PieceOrientee::PieceOrientee(const Piece& piece , const Orientation& orientation, unsigned id)
        : piece(piece), orientation(orientation), id(id) {}

void PieceOrientee::rotationGauche()
{
    std::rotate(piece.begin(), piece.begin()+1, piece.end() );
    orientation = Orientation (((int)orientation +1) % 4);
}

std::ostream& operator<<(std::ostream& os, const Puzzle& puzzle)
{
    for(const PieceOrientee& pieceOrientee : puzzle)
    {
        os << pieceOrientee.id << (char)('a' + pieceOrientee.orientation) << ' ';
    }

    return os << '\n';
}


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

bool verifieCorrespondance(const Puzzle& puzzle, size_t posPiece)
{
    unsigned x = posPiece % 3;
    unsigned y = posPiece / 3;

    bool droiteOk = true;
    bool basOk = true;

    if((x + 1) < 3)
    {
        droiteOk = coteComplementaire(puzzle[posPiece].piece[DROITE], puzzle[posPiece+1].piece[GAUCHE]);
    }
    if((y + 1) < 3)
    {
        basOk = coteComplementaire(puzzle[posPiece].piece[BAS], puzzle[posPiece+3].piece[HAUT]);
    }
    return basOk && droiteOk;
}

void echanger(Puzzle& puzzle, unsigned pos1, unsigned pos2)
{
    PieceOrientee tmp = puzzle[pos1];
    puzzle[pos1] = puzzle[pos2];
    puzzle[pos2] = tmp;
}

void resolution(Puzzle& puzzle, unsigned pieceRestante)
{
    if(pieceRestante == 1)
    {
        for(int r = 0; r < 4; ++r)
        {
            if(verifieCorrespondance(puzzle, 0))
            {
                std::cout << puzzle << std::endl;
            }
            puzzle[0].rotationGauche();
        }
    }
    else
    {
        for(size_t i = 0; i < pieceRestante; ++i)
        {
            echanger(puzzle, i, pieceRestante-1);
            for(int r = 0; r < 4; ++r)
            {
                if(verifieCorrespondance(puzzle, pieceRestante-1))
                {
                    resolution(puzzle, pieceRestante-1);
                }
                puzzle[pieceRestante-1].rotationGauche();
            }
            echanger(puzzle, i, pieceRestante-1);
        }
    }
}

int main()
{

    //Création du Puzzle initial.
    Puzzle puzzle;
    for(size_t i = 0; i < puzzle.size(); ++i)
    {
        puzzle[i] = PieceOrientee(PIECES[i], Orientation::A, i+1);
    }

    resolution(puzzle, puzzle.size());

    return 0;
}





