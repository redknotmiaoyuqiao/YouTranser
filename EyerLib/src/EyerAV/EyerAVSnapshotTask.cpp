#include "EyerAVSnapshotTask.hpp"

namespace Eyer
{
    EyerAVSnapshotTask::EyerAVSnapshotTask()
    {

    }

    EyerAVSnapshotTask::EyerAVSnapshotTask(const EyerAVSnapshotTask & task)
    {
        *this = task;
    }

    EyerAVSnapshotTask::~EyerAVSnapshotTask()
    {

    }

    EyerAVSnapshotTask & EyerAVSnapshotTask::operator = (const EyerAVSnapshotTask & task)
    {
        path = task.path;
        pts = task.pts;

        targetWidth = task.targetWidth;
        targetHeight = task.targetHeight;

        return *this;
    }

    bool EyerAVSnapshotTask::operator == (const EyerAVSnapshotTask & task)
    {
        return pts == task.pts;
    }
}