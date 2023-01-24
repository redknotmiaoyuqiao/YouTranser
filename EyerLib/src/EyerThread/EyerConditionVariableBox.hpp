#ifndef EYERLIB_EYERCONDITIONVARIABLEBOX_HPP
#define EYERLIB_EYERCONDITIONVARIABLEBOX_HPP

#include <thread>
#include <condition_variable>

namespace Eyer
{
    class EyerConditionVariableBox
    {
    public:
        std::mutex mtx;
        std::condition_variable cv;
    };
}


#endif //EYERLIB_EYERCONDITIONVARIABLEBOX_HPP
