#ifndef PLANET_H
#define PLANET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Planet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Planet(QString name);
    double getPosx() const;
    void setPosx(double value);

    double getPosy() const;
    void setPosy(double value);

    double getMasa() const;
    void setMasa(double value);

    double getRadio() const;
    void setRadio(double value);

    double getVelx() const;
    void setVelx(double value);

    double getVely() const;
    void setVely(double value);

private:
    double posx,posy,masa,radio,velx,vely;
    QString name;
};

#endif // PLANET_H
