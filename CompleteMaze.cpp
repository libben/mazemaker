// CompleteMaze.cpp
// by Benjamin Rausch

#include <vector>
#include <cassert>
#include <iostream>
#include "Wall.h"
#include "CompleteMaze.h"
#include <stdlib.h>
#include <time.h>

// width: x
// length: y

namespace stuff {
    CompleteMaze::CompleteMaze(size_type mWidth, size_type mLength)
        : length(mLength),
          width(mWidth),
          rightWalls(mWidth, mLength),
          bottomWalls(mWidth, mLength)
    {
        srand(time(NULL));

        // add walls in 1st and last row
        for (size_type i = 1; i <= width; ++i)
        {
            bottomWalls.at(i, 0) = true;
            bottomWalls.at(i, length) = true;
        }
        // add walls in 1st and last column
        for (size_type i = 1; i <= length; ++i) {
            rightWalls.at(0, i) = true;
            rightWalls.at(width, i) = true;
        }

        std::vector<MWall> possibleWalls;

        for (size_type i = 1; i <= width; ++i)
        {
            for (size_type j = 1; j <= length; ++j)
            {
                if (j != length)
                {
                    MWall bottom = MWall(Point(i, j), MWall::Location::BOTTOM);
                    possibleWalls.push_back(bottom);
                }
                if (i != width)
                {
                    MWall right = MWall(Point(i, j), MWall::Location::RIGHT);
                    possibleWalls.push_back(right);
                }
            }
        }

        // shuffle walls (Knuth shuffle)
        size_type targetPlace;
        MWall temp;
        for (size_type i = possibleWalls.size() - 1; i > 0; --i)
        {
            targetPlace = rand() % (i + 1);
            temp = possibleWalls.at(targetPlace);
            possibleWalls.at(targetPlace) = possibleWalls.at(i);
            possibleWalls.at(i) = temp;
        }

        MWall testWall;
        while (!possibleWalls.empty()) {
            testWall = possibleWalls.back();
            possibleWalls.pop_back();
            if (testWall.getLocation() == MWall::Location::RIGHT)
            {
                rightWalls.at(testWall.getGridLocation().getX(), testWall.getGridLocation().getY()) = true;
            }
            else if (testWall.getLocation() == MWall::Location::BOTTOM)
            {
                bottomWalls.at(testWall.getGridLocation().getX(), testWall.getGridLocation().getY()) = true;
            }

            if (!canBeTraversed(testWall))
            {
                if (testWall.getLocation() == MWall::Location::RIGHT)
                {
                    rightWalls.at(testWall.getGridLocation().getX(), testWall.getGridLocation().getY()) = false;
                }
                else if (testWall.getLocation() == MWall::Location::BOTTOM)
                {
                    bottomWalls.at(testWall.getGridLocation().getX(), testWall.getGridLocation().getY()) = false;
                }
            }
        }
    }

    bool CompleteMaze::canBeTraversed(MWall newestWall)
    {
        Point origin = newestWall.getGridLocation();
        MWall::Location location = newestWall.getLocation();
        Point destination;
        Direction originFace;
        if (location == MWall::Location::BOTTOM)
        {
            destination = Point(origin.getX(), origin.getY() + 1);
            originFace = Direction::LEFT;
        } else {
            destination = Point(origin.getX() + 1, origin.getY());
            originFace = Direction::DOWN;
        }

        Point position = origin;
        Direction face = originFace;
        size_type x;
        size_type y;

        do {
            if (position == destination) {
                return true;
            }
            x = position.getX();
            y = position.getY();

            switch (face)
            {
                case UP:
                    // try to go left and point left
                    if (!rightWalls.at(x-1, y)) {
                        position = Point(x-1,y);
                        face = LEFT;
                    // if can't, go up
                    } else if (!bottomWalls.at(x,y-1)) {
                        position = Point(x,y-1);
                    // if can't, point right
                    } else {
                        face = RIGHT;
                    }
                    break;
                case RIGHT:
                    // try to go up and point up
                    if (!bottomWalls.at(x,y-1)) {
                        position = Point(x,y-1);
                        face = UP;
                    }
                    // if can't, go right
                    else if (!rightWalls.at(x,y)) {
                        position = Point(x+1,y);
                    }
                    // if can't, point down
                    else {
                        face = DOWN;
                    }
                    break;
                case DOWN:
                    // try to go right and point right
                    if (!rightWalls.at(x,y)) {
                        position = Point(x+1,y);
                        face = RIGHT;
                    }
                    // if can't, go down
                    else if (!bottomWalls.at(x,y)) {
                        position = Point(x,y+1);
                    }
                    // if can't, point left
                    else {
                        face = LEFT;
                    }
                    break;
                case LEFT:
                    // try to go down and point down
                    if (!bottomWalls.at(x,y))
                    {
                        position = Point(x,y+1);
                        face = DOWN;
                    }
                    // if can't, go left
                    else if (!rightWalls.at(x-1,y))
                    {
                        position = Point(x-1,y);
                    }
                    // if can't, point up
                    else {
                        face = UP;
                    }
            }
        }
        while (!(position == origin && face == originFace));
        return false;
    }
    
    std::ostream& operator<< (
        std::ostream& os,
        const CompleteMaze &maze
    )
    {
        // output maze
        for (CompleteMaze::size_type j = 0; j <= maze.length; ++j)
        {
            for (CompleteMaze::size_type i = 0; i <= maze.width; ++i)
            {
                os << ' ';
                os << ((maze.rightWalls.at(i,j)) ? '#' : ' ');
            }
            os << '\n';
            for (CompleteMaze::size_type i = 0; i <= maze.width; ++i)
            {
                os << ((maze.bottomWalls.at(i,j)) ? '#' : ' ');
                os << '#';
            }
            os << '\n';
        }
        return os;
    }

    //size_type length;
    //size_type width;
}
