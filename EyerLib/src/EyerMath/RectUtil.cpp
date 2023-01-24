#include "RectUtil.hpp"

namespace Eyer
{
    Eect RectUtil::OverlapRect(const Eect & rectA, const Eect & rectB) {
        Eect ret = Eect(0, 0, 0, 0);
        if(rectA.w() == 0 || rectA.h() == 0 || rectB.w() == 0 || rectB.h() == 0){
            return ret;
        }

        //p1：rectA左下角  p2：rectA右上角 p3：rectB左下角  p4：rectB右上角
        //EectorF4的x代表左上角x， y代表左上角y，z代表矩形的宽，w代表矩形的高
        float p1_x = rectA.x();
        float p1_y = rectA.y() + rectA.h();

        float p2_x = rectA.x() + rectA.w();
        float p2_y = rectA.y();

        float p3_x = rectB.x();
        float p3_y = rectB.y() + rectB.h();

        float p4_x = rectB.x() + rectB.w();
        float p4_y = rectB.y();

        if (p1_x >= p4_x || p2_x <= p3_x || p1_y <= p4_y || p2_y >= p3_y) {
            return ret;
        }

        float width = std::min(p2_x, p4_x) - std::max(p1_x, p3_x);
        float height = std::min(p1_y, p3_y) - std::max(p2_y, p4_y);

        float retLeftTop_x = std::max(p1_x, p3_x);
        float retLeftTop_y = std::max(p2_y, p4_y);

        ret.SetWH(width, height);
        ret.SetXY(retLeftTop_x, retLeftTop_y);
        return ret;
    }

    bool RectUtil::PointInRect(Eatrix4x1<float> rect, Eatrix4x1<float> point)
    {
        float rightBottom_x = rect.x() + rect.z();
        float rightBottom_y = rect.y() + rect.w();
        if(point.x() >= rect.x() && point.x() <= rightBottom_x && point.y() >= rect.y() && point.y() <= rightBottom_y){
            return true;
        } else{
            return false;
        }
    }

    bool RectUtil::PointXCrossRect(Eatrix4x1<float> rect, Eatrix4x1<float> point)
    {
        float rightBottom_x = rect.x() + rect.z();
        float rightBottom_y = rect.y() + rect.w();
        if(point.y() >= rect.y() && point.y() <= rightBottom_y){
            return true;
        } else{
            return false;
        }
    }
}