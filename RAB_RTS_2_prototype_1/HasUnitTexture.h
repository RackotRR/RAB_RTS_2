#pragma once
#include "HasTexture.h"
#include "GameIO.h"
#include "Direction.h"
// ����� ��� ������ �� ��������� ��� ������
class HasUnitTexture :
    public HasTexture
{
public:
    HasUnitTexture() : HasTexture(), direction(Direction::right) {} 

    // ���������� ����������� ������� 
    virtual void SetDirection(Direction direction) = 0;

    // �������� ���� �������� ��������
    virtual double GetAngle() const = 0;

    // ��������� ��������
    virtual DrawFlip GetDrawFlip() const = 0;
     
    Direction GetDirection() const {
        return direction;
    }
protected:
    Direction direction;
};

