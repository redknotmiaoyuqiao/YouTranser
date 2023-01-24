#ifndef EYERLIB_EYERSUBJECT_HPP
#define EYERLIB_EYERSUBJECT_HPP

#include "EyerObserver.hpp"
#include <vector>
#include <mutex>

namespace Eyer
{
    class EyerSubject {
    public:
        EyerSubject();
        ~EyerSubject();

        int AddObserver(EyerObserver * observer);
        int RemoveObserver(EyerObserver * observer);

        int NotifyObserver();

    private:
        std::vector<EyerObserver *> observerList;
        std::mutex observerListMut;
    };
}

#endif //EYERLIB_EYERSUBJECT_HPP
