#include "trojkat.h"
#include <cmath>

Trojkat::Trojkat()
{
    a = 0;
}

Trojkat::Trojkat(float x_, float y_, float a_)
    : Figura(x_,y_)
{
    a = a_;
    typ = TROJKAT;
}

Trojkat::~Trojkat()
{

}

void Trojkat::rysuj()
{
    glLoadIdentity();
    glTranslatef(x,y,0); // ma znaczenie
    glRotatef(alpha,0,0,1); // kolejnosc
    glColor4fv(kolor);
    glBegin(GL_POLYGON);
    glVertex2f(-a/2,-a*1.73/6);
    glVertex2f(a/2,-a*1.73/6);
    glVertex2f(0,a*1.73/3);
    glEnd();
}

//double Trojkat::pole()
//{
//    double p = 0.5*(a+b+c);
//    return sqrt(p*(p-a)*(p-b)*(p-c));
//}

//double Trojkat::obwod()
//{
//    return a+b+c;
//}
float Trojkat::zwrocRozmiar()
{
    return a;
}

bool Trojkat::czyNalezydoFigury(float x_, float y_)
{
    float dx = (x_-x)*(x_-x);
    float dy = (y_-y)*(y_-y);
    return (sqrt(dx+dy) < a*1.73/6);
}

bool Trojkat::czyKolizja(Figura *druga)
{
    if(druga->zwrocTyp() == TROJKAT)
    {
        return (odleglosc(druga) < (a+druga->zwrocRozmiar())*0.433);  //0.5 wysokosci (srednia między 2/3 i 1/3) // 0.9- korekta
    }
    return false;
}

void Trojkat::zmienRozmiar(float dr)
{
    a+=dr;
}

float Trojkat::zwrocPole()
{
    return a*a*1.73/4;
}

void Trojkat::zmienPole(float dp)
{
    float pole = zwrocPole() + dp; // tyle wynosi nowe pole
    zmienRozmiar(sqrt(pole*4/1.73) - a); // obliczenie dlugosci boku na podstawie pola
}

int Trojkat::zwrocTyp()
{
    return TROJKAT;
}


