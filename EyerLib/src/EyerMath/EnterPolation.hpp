#ifndef EYERLIB_ENTERPOLATION_HPP
#define EYERLIB_ENTERPOLATION_HPP

#include "Eatrix.hpp"

namespace Eyer
{
    template<typename T>
    class EnterPolation {
    public:
        EnterPolation(Eatrix<T> & _a, Eatrix<T> & _b, long long _start, long long _end)
        {
            a = _a;
            b = _b;
            start = _start;
            end = _end;
        }

        ~EnterPolation()
        {

        }

        Eatrix<T> Get(long long time)
        {
            if(time <= start){
                time = start;
            }
            if(time >= end){
                time = end;
            }

            double r = (time - start) * 1.0 / (end - start);
            Eatrix<T> res = a;

            if(a.col == b.col && a.row == b.row){
                int row = a.row;
                int col = a.col;
                for(int i = 0; i < row; i++){
                    for(int j = 0; j < col; j++){
                        res.mat[i][j] = (b.mat[i][j] - a.mat[i][j]) * r + a.mat[i][j];
                    }
                }
            }

            return res;
        }

    private:
        Eatrix<T> a;
        Eatrix<T> b;

        long long start = 0;
        long long end = 0;
    };
}

#endif //EYERLIB_ENTERPOLATION_HPP
