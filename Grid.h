// Grid.h
// by Benjamin Rausch

#ifndef GRID
#define GRID
#include <iostream>

namespace stuff {
    class Grid {
        public:
            typedef unsigned long size_type;
            Grid(size_type mWidth, size_type mLength);
            ~Grid();
            bool &at(size_type x, size_type y);
            bool at(size_type x, size_type y) const;
            bool isCompletelyMarked() const;
            void clear();
            friend std::ostream& operator<< (
                std::ostream& os,
                const Grid &grid
            );

        private:
            size_type index(size_type x, size_type y) const;
            // store data sequentially in columns
            bool *data;
            size_type length;
            size_type width;
    };
}

#endif
