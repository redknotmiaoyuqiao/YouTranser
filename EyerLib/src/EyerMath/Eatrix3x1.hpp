#ifndef EYERLIB_EATRIX3X1_HPP
#define EYERLIB_EATRIX3X1_HPP

#include "Eatrix.hpp"

namespace Eyer
{
    template<typename T>
    class Eatrix3x1 : public Eatrix<T> {
    public:
        Eatrix3x1() : Eatrix<T>(3, 1)
        {

        }

        Eatrix3x1(const Eatrix <T> &mat) : Eatrix3x1()
        {
            *this = mat;
        }

        Eatrix3x1(T x, T y, T z) : Eatrix3x1()
        {
            Eatrix<T>::mat[0][0] = x;
            Eatrix<T>::mat[1][0] = y;
            Eatrix<T>::mat[2][0] = z;
        }

        ~Eatrix3x1()
        {

        }

        const Eatrix3x1 &operator = (const Eatrix <T> &mat) {
            if (this == &mat) {
                return *this;
            }
            Eatrix<T>::operator=(mat);
            return *this;
        }

        float Norm()
        {
            return sqrt(x() * x() + y() * y() + z() * z());
        }

        int Normalize()
        {
            float norm = Norm();
            SetX(x() / norm);
            SetY(y() / norm);
            SetZ(z() / norm);
            return 0;
        }

        static Eatrix3x1 CrossProduct(Eatrix3x1 & u, Eatrix3x1 & v)
        {
            Eatrix3x1 res;

            res.SetX( u.y() * v.z() - v.y() * u.z() );
            res.SetY( u.z() * v.x() - v.z() * u.x() );
            res.SetZ( u.x() * v.y() - u.y() * v.x() );

            return res;
        }



        T x()
        {
            return Eatrix<T>::mat[0][0];
        }

        T y()
        {
            return Eatrix<T>::mat[1][0];
        }

        T z()
        {
            return Eatrix<T>::mat[2][0];
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
    };
}

#endif //EYERLIB_EATRIX3X1_HPP
