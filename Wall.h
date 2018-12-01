// Wall.h
// by Benjamin Rausch

#ifndef WALL
#define WALL

#include "CartesianPoint.h"

namespace stuff {
    template<class T> class Wall {
        public:
            enum Location { RIGHT, BOTTOM };
            Wall(CartesianPoint<T> mGridLocation, Location mLocation)
                : gridLocation(mGridLocation), location(mLocation) {}
            Wall() {}
            CartesianPoint<T> getGridLocation() const
            {
                return gridLocation;
            }
            Location getLocation() const
            {
                return location;
            }
            Wall<T> &operator=(const Wall<T> &source)
            {
                if (this == &source) return *this;
                gridLocation = source.gridLocation;
                location = source.location;
                return *this;
            }
            bool operator==(const Wall<T> &other) const
            {
                return (gridLocation == other.getGridLocation()
                    && location == other.getLocation());
            }
            // we treat X like a 10's place in (x,y) pairs
            bool operator<(const Wall<T> &other) {
                if (gridLocation.getX() < other.getX()
                        || (gridLocation.getX() == other.getX() && gridLocation.getY() < other.getY())
                    )
                {
                    return true;
                }
                return false;
            }
        private:
            CartesianPoint<T> gridLocation;
            Location location;
    };
}
#endif
