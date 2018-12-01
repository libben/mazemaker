// Grid.cpp
// by Benjamin Rausch

#include "Grid.h"
#include <vector>
#include <assert.h>

// starts counting at 1 in column and row when determining width, length, and which boxes ought to be marked.

namespace stuff {
    Grid::Grid(size_type mWidth, size_type mLength)
        : length(mLength), width(mWidth)
    {
        assert( width >= 1 && length >= 1);
        data = new bool[(width + 1)*(length + 1)];
        clear();
    }

    // deallocate dynamic memory
    Grid::~Grid()
    {
        delete [] data;
    }
    
    bool &Grid::at(Grid::size_type x, Grid::size_type y)
    {
        assert(x <= width && y <= length);
        return data[index(x,y)];
    }

    bool Grid::at(Grid::size_type x, Grid::size_type y) const
    {
        assert(x <= width && y <= length);
        return data[index(x,y)];
    }


    void Grid::clear()
    {
        for (size_type i = 0; i <= width; ++i)
        {
            for (size_type j = 0; j <= length; ++j)
            {
                at(i,j) = false;
            }
        }
    }

    std::ostream& operator<< (
        std::ostream& os,
        const Grid &grid
    )
    {
        for (Grid::size_type i = 0; i <= grid.length; ++i)
        {
            for (Grid::size_type j = 0; j <= grid.width; ++j)
            {
                os << ((grid.at(i,j)) ? '*' : '-');
            }
            os << '\n';
        }
        return os;
    }


    bool Grid::isCompletelyMarked() const
    {
        for (size_type i = 1; i <= width; ++i) {
            for (size_type j = 1; j <= length; ++j) {
                if (!at(i,j)) return false;
            }
        }
        return true;
    }


    Grid::size_type Grid::index(size_type x, size_type y) const
    {
        return (x*(length+1) + y);
    }
    
    //size_type length;
    //size_type width;
    //std::vector<std::vector<bool> data;
}
