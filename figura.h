#ifndef FIGURA_H
#define FIGURA_H

#include <iostream>
using namespace std;

class Figura // Figury nie mają zmiennej Pole, jest ono wyliczane z rozmiaru
{

public:
    Figura();
    Figura(float x_, float y_); 
    virtual ~Figura();
    enum {KOLO, KWADRAT, TROJKAT, KOLO_KWADRAT, KOLO_TROJKAT, KWADRAT_TROJKAT, KWADRAT_KOLO, TROJKAT_KOLO, TROJKAT_KWADRAT};
    float odleglosc();
    float odleglosc(Figura *druga);
    void ustawKolor(float red, float green, float blue, float alpha);
    void ustawPredkoscX(float vx);
    void ustawPredkoscY(float vy);
    void ustawOmega(float v);
    float zwrocPredkoscX();
    float zwrocPredkoscY();
    float zwrocOmega();
    void zmienPolozenie(float dx, float dy);
    void zmienAlpha(float da);
    float zwrocPolozenieX();
    float zwrocPolozenieY();
    float zwrocAlpha();
    void ustawSpecjalnym(int);
    virtual void rysuj() = 0;
    virtual bool czyNalezydoFigury(float x, float y) = 0; // do zmieniena na virtual i dokladniej
    virtual float zwrocRozmiar() = 0; // Rozmiar: Kolo-2*r, kwadrat - a, trojkat - a;
    virtual bool czyKolizja(Figura * druga) = 0; // zle
    virtual void zmienRozmiar(float) = 0;
    virtual float zwrocPole()=0;
    virtual void zmienPole(float) = 0;
    virtual int zwrocTyp()=0;
  //  virtual float

protected:
    float x,y;
    float kolor[4];
    float predkosc[2];
    float omega, alpha;
    int typ;
    int specjalny;



};

#endif // FIGURA_H
