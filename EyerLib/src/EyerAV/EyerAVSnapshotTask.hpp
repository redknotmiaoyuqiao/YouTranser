#ifndef EYERLIB_EYERAVSNAPSHOTTASK_HPP
#define EYERLIB_EYERAVSNAPSHOTTASK_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVSnapshotTask
    {
    public:
        EyerAVSnapshotTask();
        EyerAVSnapshotTask(const EyerAVSnapshotTask & task);
        ~EyerAVSnapshotTask();

        EyerAVSnapshotTask & operator = (const EyerAVSnapshotTask & task);

        bool operator == (const EyerAVSnapshotTask & task);

        EyerString path = "";
        double pts;
        int targetWidth = 0;
        int targetHeight = 0;
    };
}

#endif //EYERLIB_EYERAVSNAPSHOTTASK_HPP
