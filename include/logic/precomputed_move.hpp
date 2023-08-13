#pragma once

struct Move
{
    int from;
    int to;
}

class MoveData
{
public:
    int[] directionOffsets;
    int[][] numSquaresToEdge;
private:
    // static precomputeMove();
}