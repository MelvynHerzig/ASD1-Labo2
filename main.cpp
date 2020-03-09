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

#include <array>      //std::array
#include <algorithm>  //std::rotate
#include <iostream>   //std::ostream, std::cout
#include "Pieces.h"   //Piece, PIECES, AttachmentType

class PieceOrientee;

const unsigned TAILLE_PUZZLE = 9;
using Puzzle = std::array<PieceOrientee, TAILLE_PUZZLE>;

enum Orientation {A, B, C, D};
enum Cote{HAUT, DROITE, BAS, GAUCHE};

struct PieceOrientee
{
    /**
     * @brief Constructeur par défaut.
     */
    PieceOrientee() = default;

    /**
    * @brief Constructeur standard.
    * @param id Id de la pieceOrientee
    * @param piece Représentation de la pièce orientée.
    * @param orientation Orientation de la piece orentée.
    */
    PieceOrientee( unsigned id, const Piece& piece , const Orientation& orientation);

    /**
     * @brief Effectue une rotation d'un quart de tour sur la gauche des éléments de piece.
     */
    void rotationGauche();

    unsigned id;
    Piece piece;
    Orientation orientation;
};

/**
 * @brief Affiche l'état actuel d'un puzzle.
 * @param os Flux de sortie.
 * @param puzzle Puzzle à afficher
 * @return Retourne le flux avec les détails du puzzle.
 */
std::ostream& operator<<(std::ostream& os, const Puzzle& puzzle);

/**
 * @brief Effectue toutes les rotations de la dernière pièce.
 * @param puzzle
 * @param pieceRestante
 */
void rotateAndCallBack(Puzzle& puzzle, unsigned pieceRestante);

/**
 * @brief Vérifie si deux côté correspondent.
 * @param c1 Côté 1.
 * @param c2 Côté 2
 * @return Vrai si ils correspondent.
 */
bool coteComplementaire(const AttachementType& c1, const AttachementType& c2);

/**
 * @brief Vérifie si la pièce donnée s'aligne avec ses voisines déjà ajustées.
 * @param puzzle Puzzle dans lequel vérifier.
 * @param posPiece Position de la pièce à vérifier.
 * @return Vrai si la pièce s'ajuste.
 */
bool verifieCorrespondance(const Puzzle& puzzle, size_t posPiece);

/**
 * @brief Retourne la dernière pièce et appel les fonctions de validité.
 * @param puzzle Etat actuel du puzzle.
 * @param pieceRestante Nombre de pièce restantes à ordonner.
 */
void rotateAndCallBack(Puzzle& puzzle, unsigned pieceRestante);

/**
 * @brief Résout récursivement le puzzle impossible.
 * @param puzzle Puzzle initial.
 * @param pieceRestante Nombre de pièces dans le puzzle.
 */
void resolution(Puzzle& puzzle, unsigned pieceRestante);


PieceOrientee::PieceOrientee(unsigned id, const Piece& piece , const Orientation& orientation)
        : id(id), piece(piece), orientation(orientation){}

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

    return os;
}

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
        case NONE            : return false;
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

void rotateAndCallBack(Puzzle& puzzle, unsigned pieceRestante)
{
    for(int r = 0; r < 4; ++r)
    {
        if(verifieCorrespondance(puzzle, pieceRestante - 1))
        {
            if(pieceRestante == 1)
                std::cout << puzzle << std::endl;
            else
                resolution(puzzle, pieceRestante-1);
        }
        puzzle[pieceRestante - 1].rotationGauche();
    }
}

void resolution(Puzzle& puzzle, unsigned pieceRestante)
{

    //Cas trivial
    if(pieceRestante == 1)
    {
        rotateAndCallBack(puzzle, pieceRestante);
    }
    else
    {
        //8 premières pièces
        for(size_t i = 0; i < pieceRestante-1; ++i)
        {
            std::swap(puzzle[i], puzzle[pieceRestante - 1]);
            rotateAndCallBack(puzzle, pieceRestante);
            std::swap(puzzle[i], puzzle[pieceRestante - 1]);
        }

        //Dernière pièce sans swap inutiles
        rotateAndCallBack(puzzle, pieceRestante);
    }
}

int main()
{
    //Création du Puzzle initial.
    Puzzle puzzle;
    for(size_t i = 0; i < puzzle.size(); ++i)
    {
        puzzle[i] = PieceOrientee{i+1, PIECES[i], Orientation::A};
    }

    resolution(puzzle, puzzle.size());

    return 0;
}
