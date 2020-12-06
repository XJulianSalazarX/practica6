#include "planet.h"

Planet::Planet(QString name)
{
    setPixmap(QPixmap(name));
}

double Planet::getPosx() const
{
    return posx;
}

void Planet::setPosx(double value)
{
    posx = value;
}

double Planet::getPosy() const
{
    return posy;
}

void Planet::setPosy(double value)
{
    posy = value;
}

double Planet::getMasa() const
{
    return masa;
}

void Planet::setMasa(double value)
{
    masa = value;
}

double Planet::getRadio() const
{
    return radio;
}

void Planet::setRadio(double value)
{
    radio = value;
}

double Planet::getVelx() const
{
    return velx;
}

void Planet::setVelx(double value)
{
    velx = value;
}

double Planet::getVely() const
{
    return vely;
}

void Planet::setVely(double value)
{
    vely = value;
}
