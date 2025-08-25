#include "Bounds.h"

bool Bounds::Intersects(const Bounds& other) const
{
    //다른 영역이 현재 영역의 오른쪽 바깥인지 확인하기.
    if (other.GetX() > MaxX())
    {
        return false;
    }

    //다른 영역이 현재 영역의 왼쪽 바깥인지 확인.
    if (other.MaxX() < x)
    {
        return false;
    }

    //다른 영역이 현재 영역의 아랫쪽 바깥인지 확인.
    if (other.GetY() > MaxY())
    {
        return false;
    }

    //다른 영역이 현재 영역의 윗쪽인지 확인.
    if (other.MaxY() < y)
    {
        return false;
    }

    //위 조건에 다 필터되지 않는다면 겹친상태임.
    return true;
}
