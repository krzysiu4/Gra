#include <cmath>
#include "figura.h"
#include <QTextStream>

using namespace std;

Figura::Figura()
{

    x = 0;
    y = 0;
    QTextStream out(stdout);
    out << "konstruktor domyslny - nie powinien";
}

Figura::Figura(float x_, float y_)
{
    x = x_;
    y = y_;
    kolor[0] = (float) (rand()%101)/100;
    kolor[1] = (float) (rand()%101)/100;
    kolor[2] = (float) (rand()%101)/100;
    kolor[3] =  1;
    predkosc[0] = rand()%41-20;
    predkosc[1] = rand()%41-20;
    omega = rand()%60-30;
    alpha = 0;
    specjalny = 0;

}

Figura::~Figura()
{
}



float Figura::odleglosc()
{
    return sqrt(x*x+y*y);
}

float Figura::odleglosc(Figura *druga)
{
    float a = (druga->x - x)*(druga->x - x) + (druga->y - y)*(druga->y - y);
    return sqrt(a);
}

void Figura::ustawKolor(float red, float green, float blue, float alpha)
{
    kolor[0] = red;
    kolor[1] = green;
    kolor[2] = blue;
    kolor[3] = alpha;
}

void Figura::ustawPredkoscX(float vx)
{
    predkosc[0] = vx;
}

void Figura::ustawPredkoscY(float vy)
{
    predkosc[1] = vy;
}

float Figura::zwrocPredkoscX()
{
    return predkosc[0];
}

float Figura::zwrocPredkoscY()
{
    return predkosc[1];
}

void Figura::zmienPolozenie(float dx, float dy)
{
    x += dx;
    y += dy;
}

float Figura::zwrocPolozenieX()
{
    return x;
}

float Figura::zwrocPolozenieY()
{
    return y;
}

void Figura::ustawOmega(float v)
{
    omega = v;
}

void Figura::zmienAlpha(float da)
{
    alpha += da;
    if(alpha > 360)
        alpha -= 360;
}

float Figura::zwrocOmega()
{
    return omega;
}

float Figura::zwrocAlpha()
{
    return alpha;
}

void Figura::ustawSpecjalnym(int typ)
{
    if(typ > 2 && typ < 10)
    specjalny = typ;
}
