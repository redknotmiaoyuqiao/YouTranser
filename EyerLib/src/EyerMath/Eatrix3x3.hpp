#ifndef EYERLIB_EATRIX3X3_HPP
#define EYERLIB_EATRIX3X3_HPP

#include "Eatrix.hpp"

namespace Eyer
{
    template<typename T>
    class Eatrix3x3 : public Eatrix<T> {
    public:
        Eatrix3x3() : Eatrix<T>(3, 3)
        {

        }

        Eatrix3x3(T * data) : Eatrix<T>(3, 3)
        {
            Eatrix<T>::SetData(data, 9);
        }

        Eatrix3x3(const Eatrix <T> &mat) : Eatrix3x3()
        {
            *this = mat;
        }

        ~Eatrix3x3()
        {

        }

        const Eatrix3x3 &operator = (const Eatrix <T> &mat) {
            if (this == &mat) {
                return *this;
            }
            Eatrix<T>::operator=(mat);
            return *this;
        }
    };
}

#endif //EYERLIB_EATRIX3X3_HPP
