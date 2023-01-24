#ifndef EYERLIB_EATRIX4X1_HPP
#define EYERLIB_EATRIX4X1_HPP


#include "Eatrix.hpp"

namespace Eyer
{
    template<typename T>
    class Eatrix4x1 : public Eatrix<T> {
    public:
        Eatrix4x1() : Eatrix<T>(4, 1)
        {

        }

        Eatrix4x1(const Eatrix<T> & mat) : Eatrix4x1()
        {
            *this = mat;
        }

        Eatrix4x1(Eatrix<T> && mat) : Eatrix<T>(std::move(mat))
        {

        }

        Eatrix4x1(T x, T y, T z, T w) : Eatrix4x1()
        {
            Eatrix<T>::mat[0][0] = x;
            Eatrix<T>::mat[1][0] = y;
            Eatrix<T>::mat[2][0] = z;
            Eatrix<T>::mat[3][0] = w;
        }

        ~Eatrix4x1()
        {

        }

        const Eatrix4x1 &operator = (const Eatrix <T> &mat) {
            if (this == &mat) {
                return *this;
            }
            Eatrix<T>::operator = (mat);
            return *this;
        }

        T x() const
        {
            return Eatrix<T>::mat[0][0];
        }

        T y() const
        {
            return Eatrix<T>::mat[1][0];
        }

        T z() const
        {
            return Eatrix<T>::mat[2][0];
        }

        T w() const
        {
            return Eatrix<T>::mat[3][0];
        }

        int SetX(T x)
        {
            Eatrix<T>::mat[0][0] = x;
            return 0;
        }

        int SetY(T y)
        {
            Eatrix<T>::mat[1][0] = y;
            return 0;
        }

        int SetZ(T z)
        {
            Eatrix<T>::mat[2][0] = z;
            return 0;
        }

        int SetW(T w)
        {
            Eatrix<T>::mat[3][0] = w;
            return 0;
        }
    };
}

#endif //EYERLIB_EATRIX4X1_HPP
