#include "odcinek.h"
#include <cmath>
#include <qmath.h>
#include <QTextStream>
#include <QPoint>


Odcinek::Odcinek()
{
}

Odcinek::Odcinek(GLfloat Ax_, GLfloat Ay_, GLfloat Bx_, GLfloat By_)
{
    Ax = Ax_;
    Ay = Ay_;
    Bx = Bx_;
    By = By_;

    if(Bx-Ax != 0)
        alpha = (qAtan((By-Ay)/(Bx-Ax)));
    else
        alpha = INFINITY;

}

void Odcinek::rysuj()
{
    glLoadIdentity();
    glLineWidth(3);
    glColor4f(1,1,1,1);
    glBegin(GL_LINES);
    glVertex2f(Ax,Ay);
    glVertex2f(Bx,By);
    glEnd();
}

void Odcinek::czyKolizja2(Figura* figura)
{
    //rownanie prostej y = ax + b;
    QTextStream out2(stdout);
    GLfloat a = qTan(alpha);

    GLfloat b = By - a*Bx;
   // out2 << b;
    bool kolizja = 0;
    switch(figura->zwrocTyp())
    {
    case Figura::KOLO:
    {

        QPoint A,B; // mogą mieć kolizje
        GLfloat roz = figura->zwrocRozmiar()*0.5;

        {
        A.setX(figura->zwrocPolozenieX()+ roz* qSin(-alpha));
        A.setY(figura->zwrocPolozenieY()+roz* qCos(-alpha));
        B.setX(figura->zwrocPolozenieX()+ roz* qSin(-alpha+PI));
        B.setY(figura->zwrocPolozenieY()+roz* qCos(-alpha+PI));
        if(((qAbs(A.y() - a*A.x()-b) <3) ) || ((qAbs(B.y() - a*B.x()-b)) <3))
        {

            kolizja = 1;
             out2 << "a: " << a << " b " << b << endl;
        }
}

    }
        break;
    case Figura::KWADRAT:

        break;

    case Figura::TROJKAT:

        break;


    }
    if(kolizja == 1)
    {


        // obliczenie kata figury - beta;
        GLfloat Vx = figura->zwrocPredkoscX();
        GLfloat Vy = figura->zwrocPredkoscY();


        GLfloat modol = qSqrt(Vx*Vx + Vy*Vy);
        GLfloat cosV = Vx/modol;
        GLfloat sinV = Vy/modol;
        GLfloat beta;

        if (qAbs(Vx) == 0)
        {
            out2 << "lsldadas";
            if(Vy > 0) // w gore
                beta = PI*0.5;
            else       // w dol
                beta = 1.5*PI;
        }
        else if(Vy == 0 )
        {
            if(Vx > 0) // w prawou
                beta = 0;
            else
                beta = -PI; // w lewo
        }
        else if ( cosV > 0 &&  sinV >0 ) // I ćwiartka
            beta = qAbs(qAtan(Vy/Vx));
        else if(sinV > 0 && cosV < 0) // II ćwiartka
            beta = qAbs(qAtan(Vy/Vx))+PI*0.5;
        else if(sinV <0 && cosV < 0) // III ćwiartka
            beta = qAbs(qAtan(Vx/Vy))+PI;
        else if(sinV <0 && cosV > 0) // IV ćwiartka
            beta = qAbs(qAtan(Vx/Vy))+1.5*PI;

        //  GLfloat beta = qAtan(Vy/Vx) *180  / PI;
        GLfloat gamma = 2*(alpha-beta); // nowy kąt prędkości
        gamma += beta;
        // gamma = -90 * PI/180;
        figura->ustawPredkoscX(modol*qCos(gamma));
        figura->ustawPredkoscY(modol*qSin(gamma));
        QTextStream out(stdout);

        out << "nachylenie prostej: " << alpha*180/PI << " kat predkosci:  " << beta*180/PI << " gamma:  " << gamma*180/PI << endl;
        out << "Vx:  " << Vx << "Vy: " << Vy << endl;

    }
}
