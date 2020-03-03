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
#include <ostream>   //std::ostream, std::cout
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
        os << pieceOrientee.id << pieceOrientee.orientation << ' ';
    }

    return os << '\n';
}

void resolution(Puzzle puzzle, unsigned pieceRestante)
{
    if(pieceRestante == 1)
    {
        //Do something
    }
    else
    {
        for(size_t i = 1; i <= pieceRestante - 1; ++i)
        {
            //Do something
        }
    }
    /*Si piece restante == 1
        Pour chaque rotation de la pièce
            si correspondance afficherPuzzle
            sinon return

      Sinon
        Pour chaque piece de 1 a 8,
            la placer en dernière position
            pour chaque orientation (donc 4 appels à rotationGauche)
                si correspondance avec la/les précédete
                    appel recursif
                fin si

            replacer la piece à se position
        Pour chaque rotation de la derniere pièce
            appel recursif
        fin si */
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





