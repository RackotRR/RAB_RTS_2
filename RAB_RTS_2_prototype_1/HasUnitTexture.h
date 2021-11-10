#pragma once
#include "HasTexture.h"
#include "GameIO.h"
#include "Direction.h"
// класс для данных об отрисовке для юнитов
class HasUnitTexture :
    public HasTexture
{
public:
    HasUnitTexture() : HasTexture(), direction(Direction::right) {} 

    // установить направление движеня 
    virtual void SetDirection(Direction direction) = 0;

    // получить угол поворота текстуры
    virtual double GetAngle() const = 0;

    // отражение текстуры
    virtual DrawFlip GetDrawFlip() const = 0;
     
    Direction GetDirection() const {
        return direction;
    }
protected:
    Direction direction;
};

