#ifndef EYERLIB_EATRIX_HPP
#define EYERLIB_EATRIX_HPP

#include "EyerCore/EyerCore.hpp"
#include <math.h>
#include <algorithm>

// #define EYER_MATH_DEBUG

#ifdef EYER_MATH_DEBUG
int alloctimes = 0;
#endif

namespace Eyer
{
    template<typename T>
    class Eatrix {
    public:
        Eatrix(int _row = 0, int _col = 0) {
#ifdef EYER_MATH_DEBUG
            EyerLog("Eatrix(int, int)\n");
#endif
            Resize(_row, _col);
        }

        ~Eatrix() {
#ifdef EYER_MATH_DEBUG
            EyerLog("~Eatrix()\n");
#endif
            Free();
            if (tempArr != nullptr) {
                delete[] tempArr;
                tempArr = nullptr;
            }
            tempArrLen = 0;
        }

        Eatrix(const Eatrix & m)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("Eatrix(const Eatrix & m)\n");
#endif
            *this = m;
        }

        Eatrix(Eatrix && m)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("Eatrix && m\n");
#endif
            row = m.row;
            col = m.col;
            mat = m.mat;
            m.mat = nullptr;
        }

        const T Get(int y, int x) const
        {
            return mat[y][x];
        }

        int Set(int y, int x, T t)
        {
            mat[y][x] = t;
            return 0;
        }

        Eatrix & operator = (const Eatrix & m)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("const Eatrix & operator = (const Eatrix & m)\n");
#endif
            Resize(m.row, m.col);

            for (int i = 0; i < row; i++){
                for (int j = 0; j < col; j++){
                    mat[i][j] = m.mat[i][j];
                }
            }

            return *this;
        }

        // ====================== +++++ ======================
        friend Eatrix operator + (const Eatrix & mA, const Eatrix & mB)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("Eatrix operator + (const Eatrix & mA, const Eatrix & mB)\n");
#endif
            Eatrix res(mA.row, mA.col);
            if (mA.row == mB.row && mA.col == mB.col) {
                for (int i = 0; i < mA.row; i++) {
                    for (int j = 0; j < mA.col; j++) {
                        res.mat[i][j] = mA.mat[i][j] + mB.mat[i][j];
                    }
                }
            }
            else {
                EyerLog("Eatrix + Error, Eatrix A Shape (%d, %d) != Eatrix B Shape (%d, %d)\n", mA.row, mA.col, mB.row, mB.col);
            }

            return res;
        }

        friend Eatrix operator + (Eatrix && mA, const Eatrix & mB)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("Eatrix operator + (const Eatrix && mA, const Eatrix & mB)\n");
#endif
            Eatrix res = std::move(mA);
            if (mA.row == mB.row && mA.col == mB.col) {
                for (int i = 0; i < mA.row; i++) {
                    for (int j = 0; j < mA.col; j++) {
                        res.mat[i][j] = res.mat[i][j] + mB.mat[i][j];
                    }
                }
            }
            else {
                EyerLog("Eatrix + Error, Eatrix A Shape (%d, %d) != Eatrix B Shape (%d, %d)\n", mA.row, mA.col, mB.row, mB.col);
            }
            return res;
        }

        /**
         * 加法
         * @param m
         * @return
         */
        const Eatrix operator + (const T val) const
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] + val;
                }
            }
            return res;
        }

        /**
         * 减法
         * @param m
         * @return
         */
        friend Eatrix operator - (const Eatrix & mA, const Eatrix & mB)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("Eatrix operator - (const Eatrix & mA, const Eatrix & mB)\n");
#endif
            Eatrix res(mA.row, mA.col);
            if (mA.row == mB.row && mA.col == mB.col) {
                for (int i = 0; i < mA.row; i++) {
                    for (int j = 0; j < mA.col; j++) {
                        res.mat[i][j] = mA.mat[i][j] - mB.mat[i][j];
                    }
                }
            }
            else{
                EyerLog("Eatrix - Error, Eatrix A Shape (%d, %d) != Eatrix B Shape (%d, %d)\n", mA.row, mA.col, mB.row, mB.col);
            }
            return res;
        }

        /**
         * 减法
         * @param m
         * @return
         */
        friend Eatrix operator - (Eatrix && mA, const Eatrix & mB)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("Eatrix operator - (Eatrix && mA, const Eatrix & mB)\n");
#endif
            Eatrix res = std::move(mA);
            if (mA.row == mB.row && mA.col == mB.col) {
                for (int i = 0; i < mA.row; i++) {
                    for (int j = 0; j < mA.col; j++) {
                        res.mat[i][j] = res.mat[i][j] - mB.mat[i][j];
                    }
                }
            }
            else{
                EyerLog("Eatrix - Error, Eatrix A Shape (%d, %d) != Eatrix B Shape (%d, %d)\n", mA.row, mA.col, mB.row, mB.col);
            }
            return res;
        }

        /**
         * 减法
         * @param m
         * @return
         */
        const Eatrix operator - (const T val) const
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] - val;
                }
            }
            return res;
        }

        /**
         * 矩阵相乘
         * @param a
         * @return
         */
        friend Eatrix operator * (const Eatrix & mA, const Eatrix & mB)
        {
#ifdef EYER_MATH_DEBUG
            EyerLog("friend Eatrix operator * (const Eatrix & mA, const Eatrix & mB)\n");
#endif
            Eatrix res(mA.row, mB.col);
            for (int i = 0; i < res.row; i++) {
                for (int j = 0; j < res.col; j++) {
                    res.mat[i][j] = 0.0f;
                }
            }
            if (mB.row == mA.col) {
                for (int i = 0; i < res.row; i++) {
                    for (int j = 0; j < res.col; j++) {
                        for (int k = 0; k < res.row; k++) {
                            res.mat[i][j] += mA.mat[i][k] * mB.mat[k][j];
                        }
                    }
                }
            }
            else {
                EyerLog("Eatrix * Error, Eatrix A Shape (%d, %d) != Eatrix B Shape (%d, %d)\n", mA.row, mA.col, mB.row, mB.col);
            }
            return res;
        }

        /**
         * 矩阵数乘
         * @param a
         * @return
         */
        const Eatrix operator * (const float a) const
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] * a;
                }
            }
            return res;
        }

        /**
         * 矩阵转置
         * @param
         * @return
         */
        const Eatrix Transpose () const
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[j][i];
                }
            }
            return res;
        }

        /**
         * 矩阵转置
         * @param
         * @return
         */
        const int TransposeSelf ()
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[j][i];
                }
            }

            *this = res;

            return 0;
        }

        int SetData(T * arr, int len)
        {
            int index = 0;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++){
                    if(index < len){
                        mat[i][j] = arr[index];
                    }
                    index++;
                }
            }
            return 0;
        }

        const int PrintInfo() const
        {
            EyerLog("output:(%d,%d)\n", row, col);
            for (int i = 0; i < row; i++) {
                EyerString str = "";
                for (int j = 0; j < col; j++){
                    str += EyerString::Number(mat[i][j], " %.4f ");
                }
                EyerLog("%s\n", str.c_str());
            }
            return 0;
        }

        int GetMatLen() const
        {
            return this->col * this->row * sizeof(float);
        }

        T * GetMat(T * matBuffer) const
        {
            if(matBuffer == NULL) {
                matBuffer = (float *)malloc(GetMatLen());
            }

            int index = 0;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++){
                    matBuffer[index] = mat[i][j];
                    index++;
                }
            }
            return matBuffer;
        }

        const Eatrix Zeros()
        {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    mat[i][j] = 0.0;
                }
            }
            return *this;
        }

        const Eatrix Eye()
        {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    mat[i][j] = 0;
                    if(i == j){
                        mat[i][j] = 1;
                    }
                }
            }
            return *this;
        }



        /**
        * float矩阵的逆矩阵
        * @param
        * @return
        */
        friend Eatrix operator ! (const Eatrix & mA)
        {
            Eatrix mat = mA;
            return mat.invert();
        }

        Eatrix invert(Eatrix * tempMap = nullptr)
        {
            // https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/matrix-inverse
            Eatrix tempMat = *this;

            T ** m = tempMat.mat;

            Eatrix mat(row, row);
            int N = mat.row;

            for (int column = 0; column < N; ++column) {
                if (m[column][column] == 0) {
                    int big = column;
                    for (int row = 0; row < N; ++row) {
                        if (fabs(m[row][column]) > fabs(m[big][column])) {
                            big = row;
                        }
                    }
                    if (big == column) {
                        EyerLog("Error Singular matrix \n");
                    }
                    else {
                        for (int j = 0; j < N; ++j) {
                            std::swap(m[column][j], m[big][j]);
                            std::swap(mat.mat[column][j], mat.mat[big][j]);
                        }
                    }
                }
                for (int row = 0; row < N; ++row) {
                    if (row != column) {
                        T coeff = m[row][column] / m[column][column];
                        if (coeff != 0) {
                            for (int j = 0; j < N; ++j) {
                                m[row][j] -= coeff * m[column][j];
                                mat.mat[row][j] -= coeff * mat.mat[column][j];
                            }
                            m[row][column] = 0;
                        }
                    }
                }
            }
            for (int row = 0; row < N; ++row) {
                for (int column = 0; column < N; ++column) {
                    mat.mat[row][column] /= m[row][row];
                }
            }

            return mat;
        }

    public:
        int row = 0;
        int col = 0;
        T * * mat = nullptr;

    private:
        T * tempArr = nullptr;
        int tempArrLen = 0;

    private:

        void Alloc(int row, int col)
        {
            if (row && col) {
                mat = new T * [row];
                for (int i = 0; i < row; i++) {
                    mat[i] = new T[col];
                    for (int j = 0; j < col; j++){
                        mat[i][j] = 0;
                        if(i == j){
                            mat[i][j] = 1;
                        }
                    }
                }
            }

#ifdef EYER_MATH_DEBUG
            alloctimes++;
            EyerLog("alloctimes: %d\n", alloctimes);
#endif
        }

        void Free()
        {
            if (mat != nullptr) {
                for (int i = 0; i < row; i++){
                    if (mat[i]) {
                        delete[] mat[i];
                        mat[i] = nullptr;
                    }
                }
                if (mat){
                    delete[] mat;
                }
                mat = nullptr;
            }
        }

        int Resize(int _row, int _col)
        {
            if(row != _row || col != _col){
                Free();

                row = _row;
                col = _col;

                Alloc(row, col);
            }

            return 0;
        }
    };
}

#endif //EYERLIB_EATRIX_HPP
