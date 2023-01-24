#include "EyerSubject.hpp"

namespace Eyer
{
    EyerSubject::EyerSubject()
    {

    }

    EyerSubject::~EyerSubject()
    {
        std::lock_guard<std::mutex> lg(observerListMut);
        observerList.clear();
    }

    int EyerSubject::AddObserver(EyerObserver * observer)
    {
        std::lock_guard<std::mutex> lg(observerListMut);
        observerList.push_back(observer);
        return 0;
    }

    int EyerSubject::RemoveObserver(EyerObserver * observer)
    {
        std::lock_guard<std::mutex> lg(observerListMut);
        for(std::vector<EyerObserver *>::iterator it=observerList.begin(); it!=observerList.end();) {
            if (*it == observer) {
                it = observerList.erase(it);
            } else {
                ++it;
            }
        }
        return 0;
    }

    int EyerSubject::NotifyObserver()
    {
        std::lock_guard<std::mutex> lg(observerListMut);
        for(std::vector<EyerObserver *>::iterator it=observerList.begin(); it!=observerList.end(); ++it) {
            (*it)->Update();
        }
        return 0;
    }
}

