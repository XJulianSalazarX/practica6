#include "planet.h"

Planet::Planet(QString name_)
{
    name = name_;
    //setPixmap(QPixmap(name));
}

void Planet::Tamanio()
{
    setPixmap(QPixmap(name).scaled(radio*2,radio*2));
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

QString Planet::getName() const
{
    return name;
}

double Planet::getAc_x() const
{
    return ac_x;
}

void Planet::setAc_x(double value)
{
    ac_x = value;
}

double Planet::getAc_y() const
{
    return ac_y;
}

void Planet::setAc_y(double value)
{
    ac_y = value;
}
