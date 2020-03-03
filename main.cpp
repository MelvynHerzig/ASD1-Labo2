#include <iostream>
#include <vector>
#include <array>
#include "Pieces.h"


enum Orientation{A,B,C,D};
enum Cote{HAUT,DROITE,BAS,GAUCHE};

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

using Puzzle = std::array<PieceOrientee, 9>;
using PieceRestante = std::vector<Piece>;

Puzzle resolution(Puzzle puzzle, )

int main()
{

    return EXIT_SUCCESS;
}


