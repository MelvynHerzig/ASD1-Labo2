#include <iostream>
#include <vector>
#include <array>
#include "Pieces.h"


enum Orientation
{
    A, B, C, D
};
enum Cote
{
    HAUT, DROITE, BAS, GAUCHE
};

class PieceOrientee
{
public:
    PieceOrientee() = default;

    PieceOrientee(unsigned inId, Orientation inOrientation)
    {
        id = inId;
        orientation = inOrientation;
    }

    unsigned id;
    Orientation orientation;
};

const unsigned TAILLE_PUZZLE = 9;

using Puzzle = std::array<PieceOrientee, TAILLE_PUZZLE>;

Puzzle resolution(Puzzle puzzle, unsigned n)
{
    if(n == 0)
    {
        // Do something
    }
    else
    {
        for(int i = 0; i < n-1; ++i)
        {
            // Do something
        }
    }
}

int main()
{

    return EXIT_SUCCESS;
}


