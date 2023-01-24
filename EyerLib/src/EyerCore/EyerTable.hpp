#ifndef EYERLIB_EYERTABLE_HPP
#define EYERLIB_EYERTABLE_HPP

#include <vector>

namespace Eyer
{
    template <typename T>
    class EyerTable {
    public:
        EyerTable() : EyerTable(0, 0)
        {

        }

        EyerTable(int _w, int _h)
        {
            Resize(_w, _h);
        }

        ~EyerTable()
        {
            vec.clear();
        }

        int Resize(int _w, int _h)
        {
            w = _w;
            h = _h;
            vec.clear();

            for(int y=0;y<h;y++){
                for(int x=0;x<w;x++){
                    T t;
                    vec.push_back(t);
                }
            }

            return 0;
        }

        int Set(int x, int y, T & t)
        {
            if(x < 0){
                return -1;
            }
            if(x >= w){
                return -1;
            }

            if(y < 0){
                return -1;
            }
            if(y >= h){
                return -1;
            }

            int index = y * w + x;
            vec[index] = t;
            return 0;
        }

        int Get(T & t, int x, int y)
        {
            if(x < 0){
                return -1;
            }
            if(x >= w){
                return -1;
            }
            if(y < 0){
                return -1;
            }
            if(y >= h){
                return -1;
            }
            int index = y * w + x;
            t = vec[index];
            return 0;
        }

        int GetW()
        {
            return w;
        }

        int GetH()
        {
            return h;
        }

    private:
        int w = 0;
        int h = 0;

        std::vector<T> vec;
    };
}

#endif //EYERLIB_EYERTABLE_HPP
