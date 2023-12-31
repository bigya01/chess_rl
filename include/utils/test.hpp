#include "logic/engine.hpp"
#include "ui/board.hpp"
#define DEPTH 4

/*
 * A class used for peft tests
 */
class Test
{
public:
    void standardPerft(int a);
    void generateAllMoves(int depth, bool first);

private:
    int getNumberOfMoves(int depth, const BoardState &state, bool first);
};
