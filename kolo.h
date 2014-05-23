#ifndef KOLO_H
#define KOLO_H
#include <QGLWidget>
#include "figura.h"

class Kolo : public Figura
{
public:
    Kolo();
    Kolo(float x_, float y_, float r_);
    ~Kolo();
    virtual void rysuj();
    virtual float zwrocRozmiar();
    virtual bool czyNalezydoFigury(float x, float y);
    virtual bool czyKolizja(Figura *druga);
    virtual void zmienRozmiar(float);
    virtual float zwrocPole();
    virtual void zmienPole(float);
    virtual int zwrocTyp();



protected:
    float r;
};

#endif // KOLO_H
