#include "Bounds.h"

bool Bounds::Intersects(const Bounds& other) const
{
    //�ٸ� ������ ���� ������ ������ �ٱ����� Ȯ���ϱ�.
    if (other.GetX() > MaxX())
    {
        return false;
    }

    //�ٸ� ������ ���� ������ ���� �ٱ����� Ȯ��.
    if (other.MaxX() < x)
    {
        return false;
    }

    //�ٸ� ������ ���� ������ �Ʒ��� �ٱ����� Ȯ��.
    if (other.GetY() > MaxY())
    {
        return false;
    }

    //�ٸ� ������ ���� ������ �������� Ȯ��.
    if (other.MaxY() < y)
    {
        return false;
    }

    //�� ���ǿ� �� ���͵��� �ʴ´ٸ� ��ģ������.
    return true;
}
