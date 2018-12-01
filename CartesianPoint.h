// CartesianPoint.h
// by Benjamin Rausch

#ifndef CART_POINT
#define CART_POINT

namespace stuff {
    template<class T> class CartesianPoint
    {
        public:
            CartesianPoint(T myX, T myY)
                : x(myX), y(myY) {}
            CartesianPoint() {}
            bool operator==(const CartesianPoint<T> &other) const
            {
                return (x == other.x && y == other.y);
            }
            CartesianPoint<T> &operator=(const CartesianPoint<T> &source)
            {
                if (this == &source) return *this;
                x = source.x;
                y = source.y;
                return *this;
            }
            bool operator!=(const CartesianPoint<T> &other) const
            {
                return !(*this == other);
            }
            T getX() { return x; }
            T getY() { return y; }
        private:
            T x;
            T y;
    };
}

#endif
