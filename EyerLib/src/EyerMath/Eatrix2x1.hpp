#ifndef EYERLIB_EATRIX2X1_HPP
#define EYERLIB_EATRIX2X1_HPP

#include "Eatrix.hpp"

namespace Eyer
{
    template<typename T>
    class Eatrix2x1 : public Eatrix<T> {
    public:
        Eatrix2x1() : Eatrix<T>(2, 1)
        {

        }

        Eatrix2x1(float x, float y) : Eatrix<T>(2, 1)
        {
            SetX(x);
            SetY(y);
        }

        Eatrix2x1(const Eatrix <T> &mat) : Eatrix2x1()
        {
            *this = mat;
        }

        Eatrix2x1(T x, T y, T z) : Eatrix2x1()
        {
            Eatrix<T>::mat[0][0] = x;
            Eatrix<T>::mat[1][0] = y;
            Eatrix<T>::mat[2][0] = z;
        }

        ~Eatrix2x1()
        {

        }

        const Eatrix2x1 &operator = (const Eatrix <T> &mat) {
            if (this == &mat) {
                return *this;
            }
            Eatrix<T>::operator=(mat);
            return *this;
        }

        float Norm()
        {
            return sqrt(x() * x() + y() * y());
        }

        int Normalize()
        {
            float norm = Norm();
            SetX(x() / norm);
            SetY(y() / norm);
            return 0;
        }

        T x() const
        {
            return Eatrix<T>::mat[0][0];
        }

        T y() const
        {
            return Eatrix<T>::mat[1][0];
        }

        T w() const
        {
            return Eatrix<T>::mat[0][0];
        }

        T h() const
        {
            return Eatrix<T>::mat[1][0];
        }

        T width() const
        {
            return Eatrix<T>::mat[0][0];
        }

        T height() const
        {
            return Eatrix<T>::mat[1][0];
        }

        void x(T x){
            Eatrix<T>::mat[0][0] = x;
        }

        void y(T y){
            Eatrix<T>::mat[1][0] = y;
        }

        void width(T width){
            Eatrix<T>::mat[0][0] = width;
        }

        void height(T height){
            Eatrix<T>::mat[1][0] = height;
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
    };
}

#endif //EYERLIB_EATRIX2X1_HPP
