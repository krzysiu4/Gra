#include <QGLWidget>
#include <cmath>
#include "kwadrat.h"


using namespace std;

Kwadrat::Kwadrat()
{
    a = 0;
}

Kwadrat::Kwadrat(float x_, float y_, float a_): Figura(x_,y_)
{
    a = a_;
    typ = KWADRAT;
    specjalny = 0;

}

Kwadrat::~Kwadrat()
{

}

void Kwadrat::rysuj()
{

    glLoadIdentity();
    glTranslatef(x,y,0);
    glRotatef(alpha,0,0,1);

    if (specjalny != 0)
    {
        glColor4f(0.3,0.2,0.4,1); // kolor tla
        switch(specjalny)
        {
        case KWADRAT_KOLO:

            break;

        case KWADRAT_TROJKAT:
            glBegin(GL_POLYGON);
            glVertex2f(-a/4,-a/4);
            glVertex2f(a/4,-a/4);
            glVertex2f(0,a/4);
            glEnd();
            break;

        }
    }
    glBegin(GL_POLYGON);
    glColor4f(kolor[0],kolor[1],kolor[2],kolor[3]);
    glVertex2f(-a/2,-a/2);
    glVertex2f(a/2,-a/2);
    glVertex2f(a/2,a/2);
    glVertex2f(-a/2,a/2);
    glEnd();



}

float Kwadrat::zwrocRozmiar()
{
    return a;
}

bool Kwadrat::czyNalezydoFigury(float x_, float y_)
{
    float dx = (x_-x)*(x_-x);
    float dy = (y_-y)*(y_-y);
    return (sqrt(dx+dy) < a/2); // nie uwzglednia rogu kwadratu
}

//bool Kwadrat::czyKolizja(Figura *druga)
//{
//    if(druga->zwrocTyp() == KWADRAT)
//    {
//    return (odleglosc(druga) < a/2+druga->zwrocRozmiar()/2);
//    }
//  return false;

//}

bool Kwadrat::czyKolizja(Figura *druga)
{
    if(druga->zwrocTyp() == KWADRAT && odleglosc(druga) < (a + druga->zwrocRozmiar())*0.72)
    {

        // Obliczanie wierzchołków
        //                float delta = alpha - druga->zwrocAlpha();
        //                while(delta > 90)
        //                    delta -= 90;
        //        float sinb = sin(beta), cosb = cos(beta);
        //        QPointF wierzcholkiA[4];
        //        wierzcholkiA[0].setX(-a*0.707*cosb);
        //        wierzcholkiA[0].setY(-a*0.707*sinb);
        //        wierzcholkiA[1].setX(a*0.707*sinb);
        //        wierzcholkiA[1].setY(-a*0.707*cosb);
        //        wierzcholkiA[2].setX(a*0.707*cosb);
        //        wierzcholkiA[2].setY(a*0.707*sinb);
        //        wierzcholkiA[3].setX(-a*0.707*sinb);
        //        wierzcholkiA[3].setY(a*0.707*cosb);
        //        if(delta> 22.5 && delta < 77.5)
        //        {
        //            return (odleglosc(druga) < (a+druga->zwrocRozmiar())*0.707);
        //        }

        //        else
        //        {
        // return(odleglosc(druga) < (a + druga->zwrocRozmiar()) * 0.707);
        return (odleglosc(druga) < ((a+druga->zwrocRozmiar())*0.5)*(1 + 0.15)); // 0.15 -  korekta - jest ok
        // }
    }
    return false;

}

void Kwadrat::zmienRozmiar(float dr)
{
    a += dr;
}

float Kwadrat::zwrocPole()
{
    return a*a;
}

void Kwadrat::zmienPole(float dp)
{
    float pole = zwrocPole() + dp;

    zmienRozmiar(sqrt(pole) - a);
}

int Kwadrat::zwrocTyp()
{
    return KWADRAT;
}


