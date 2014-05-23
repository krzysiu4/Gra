#ifndef TROJKAT_H
#define TROJKAT_H
#include "figura.h"
#include <QGLWidget>

class Trojkat : public Figura
{
public:
    Trojkat();
    Trojkat(float x_, float y_, float a_);
    ~Trojkat();
    virtual void rysuj();
    virtual float zwrocRozmiar();
    virtual bool czyNalezydoFigury(float x, float y);
    virtual bool czyKolizja(Figura *druga);
    virtual void zmienRozmiar(float);
    virtual float zwrocPole();
    virtual void zmienPole(float);
    virtual int zwrocTyp();

private:
    float a;
};

#endif // TROJKAT_H
