#ifndef KWADRAT_H
#define KWADRAT_H
#include "figura.h"

class Kwadrat : public Figura
{
public:
    Kwadrat();
    Kwadrat(float x_, float y_, float a_); // srodek i dlugość boku
    ~Kwadrat();
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
   // float Ax,Ay,Bx,By,Cx,Cy,Dx,Dy; // moze nie potrzeba az tyle?
};

#endif // KWADRAT_H
