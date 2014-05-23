#include "poziomy.h"
#include <QGLWidget>

Poziomy::Poziomy()
{
    aktualnaRamka = 50;// dla pierwszego levelu
}

QList <Figura*> Poziomy::inicjalizuj(int i,int &ramka_) // tworzy figury itd.
{
    ramka_ = aktualnaRamka;
    QList <Figura*> list;
    switch(i)
    {
    case 0:
    {
        list.append(new Kolo(10,-10,5)); // pierwsza to sterowana
        for (int j=-aktualnaRamka+5; j<aktualnaRamka-5; j+=10)
        {
//            for(int i=-aktualnaRamka+5,k=1; i< aktualnaRamka-5; i+=10,k++)
//            {
//                list.append(new Kwadrat(i,j,1));
//                if(i%5==0)
//                {
//                    list.at(k)->ustawSpecjalnym(KWADRAT_TROJKAT);
//                }
//            }
        }

        break;
    }
    case 1:
    {
        break;
    }
    case 2:
    {
        break;
    }
    case 3:
    {
        break;
    }
    case 4:
    {
        break;
    }
    case 5:
    {
        break;
    }
    case 6:
    {
        break;
    }
    case 7:
    {
        break;
    }
    }
    list.at(0)->ustawPredkoscX(0); // sterowana
    list.at(0)->ustawPredkoscY(0); //
    list.at(0)->ustawOmega(0);     //
    return list;
}

void Poziomy::rysuj(int i) // rysuje scene, bez figur
{
    glLoadIdentity();
    glColor3f(1,1,1);
    glLineWidth(2);
    switch(i)
    {
    case 0:
    {
        //krawędzi
        aktualnaRamka = 50;

        glBegin(GL_LINE_LOOP);

        glVertex2f(-aktualnaRamka,-aktualnaRamka);
        glVertex2f(-aktualnaRamka,aktualnaRamka);
        glVertex2f(aktualnaRamka,aktualnaRamka);
        glVertex2f(aktualnaRamka,-aktualnaRamka);


        glEnd();
        break;
    }
    case 1:
    {
        break;
    }
    case 2:
    {
        break;
    }
    case 3:
    {
        break;
    }
    case 4:
    {
        break;
    }
    case 5:
    {
        break;
    }
    case 6:
    {
        break;
    }
    case 7:
    {
        break;
    }
    }
}
