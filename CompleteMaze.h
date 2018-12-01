// CompleteMaze.h
// by Benjamin Rausch

#ifndef COMP_MAZE
#define COMP_MAZE

#include <iostream>
#include "CartesianPoint.h"
#include "Wall.h"
#include "Grid.h"

namespace stuff {
    class CompleteMaze {
        public:
            typedef size_t size_type;
            typedef CartesianPoint<size_type> Point;
            typedef Wall<size_type> MWall;
            enum Direction { UP, DOWN, LEFT, RIGHT };
            CompleteMaze(size_type mWidth, size_type mLength);
            friend std::ostream& operator<< (
                std::ostream& os,
                const CompleteMaze &maze
            );
        private:
            bool canBeTraversed(MWall newestWall);
            /*bool canTraverseFromTo(
                Direction previousSquare,
                Point currentSpace,
                Point destination,
                Point startingSpace,
                Direction originalPreviousSquare,
                bool isRootFunctionCall);*/
            //bool canBeVisited(Point source, Direction direction);
            size_type length;
            size_type width;
            Grid rightWalls;
            Grid bottomWalls;
    };
}

#endif
