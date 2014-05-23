#include "myglwidget.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTextStream>
#include <GL/glut.h>
#include <QWheelEvent>
#include <cmath>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
   //listaOdcinkow.append(new Odcinek(-30,-30,30,30));
   listaOdcinkow.append(new Odcinek(-10,-10,10,-40));
    tlo[0] = 0.3;
    tlo[1]  = 0.2;
    tlo[2] = 0.4;
    tlo[3] = 1;
    Ts=20;
    zmienPoziom(0);
    wartoscOrtho = 500; // cos ulepszyc z animacja przyblizania
    timer.start(Ts);
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timer()));

}

MyGLWidget::~MyGLWidget()
{
    for (int i=0; i<listaFigur.length(); i++)
    {
        delete listaFigur.at(i);
    }
}


void MyGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);                                            // obiekty w głębi się przysłaniają
    glClearColor(tlo[0],tlo[1],tlo[2],tlo[3]);
}

void MyGLWidget::resizeGL(int w, int h)
{
    int s = qMin(w,h);
    glViewport((w-s)/2, (h-s)/2, s, s);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    static QPoint sterowanaLastPos; // pozycja sterowanej tuz przed wartoscOrho<ramka
    if(wartoscOrtho <= ramka)
    {
        float x = sterowana->zwrocPolozenieX(), y = sterowana->zwrocPolozenieY();
        glOrtho(-wartoscOrtho+x, wartoscOrtho+x, -wartoscOrtho+y, wartoscOrtho+y, -1 ,1 );
    }
    else
    {
        glOrtho(-wartoscOrtho, wartoscOrtho, -wartoscOrtho, wartoscOrtho, -1 ,1 );
    }
    glMatrixMode(GL_MODELVIEW);



}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(tlo[0],tlo[1],tlo[2],tlo[3]);
    //    glTranslatef(xMove,yMove,-zMove);
    //    glRotatef(xRot,1,0,0);
    //    glRotatef(yRot,0,1,0);
    //    glRotatef(zRot,0,0,1);


    poziomy.rysuj(0);
    for (int i=0; i<listaOdcinkow.size();i++)
    {
        listaOdcinkow.at(i)->rysuj();
    }

    for (int i=0; i<listaFigur.length(); i++)
    {
        listaFigur.at(i)->rysuj();
    }


}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (sterowana != 0)
    {
        float sVx = sterowana->zwrocPredkoscX();
        float sVy = sterowana->zwrocPredkoscY();

        // tworzenie odrzutu

        Figura *nowa = 0;
        switch(sterowana->zwrocTyp())
        {
        case KWADRAT:
        {
            nowa = new Kwadrat(sterowana->zwrocPolozenieX(),sterowana->zwrocPolozenieY(),1);
            break;
        }
        case KOLO:
        {
            nowa = new Kolo(sterowana->zwrocPolozenieX(),sterowana->zwrocPolozenieY(),1);
            break;
        }
        case TROJKAT:
        {
            nowa = new Trojkat(sterowana->zwrocPolozenieX(),sterowana->zwrocPolozenieY(),1);
            break;
        }
        }

        if( key == Qt::Key_Up || key ==Qt::Key_Down || key == Qt::Key_Left || key == Qt::Key_Right)
        {
            float dPole = sterowana->zwrocPole()*0.05; // 5% figury
            sterowana->zmienPole(-dPole);
            nowa->zmienPole(-(nowa->zwrocPole() - dPole)); // domyślnie nowa ma rozmiar 1, a chce żeby miała pole dPole // można dopisać funkcje ustawPole
        }

        switch(key)
        {
        case Qt::Key_Up:

            sterowana->ustawPredkoscY(sVy-5); // kolejnosc
            nowa->zmienPolozenie(0,sterowana->zwrocRozmiar());
            nowa->ustawPredkoscX(sVx);
            nowa->ustawPredkoscY(sVy + 40); //sc kolejno // stala prędkość wzgl sterowanej

            listaFigur.append(nowa);
            break;

        case Qt::Key_Down:

            sterowana->ustawPredkoscY(sVy+5);
            nowa->zmienPolozenie(0,-sterowana->zwrocRozmiar());
            nowa->ustawPredkoscX(sVx);
            nowa->ustawPredkoscY(sVy-40);
            listaFigur.append(nowa);

            break;
        case Qt::Key_Right:
            sterowana->ustawPredkoscX(sVx-5);
            nowa->zmienPolozenie(sterowana->zwrocRozmiar(),0);
            nowa->ustawPredkoscX(sVx+40);
            nowa->ustawPredkoscY(sVy);
            listaFigur.append(nowa);

            break;
        case Qt::Key_Left:
            sterowana->ustawPredkoscX(sVx+5);
            nowa->zmienPolozenie(-sterowana->zwrocRozmiar(),0);
            nowa->ustawPredkoscX(sVx-40);
            nowa->ustawPredkoscY(sVy);
            listaFigur.append(nowa);

            break;
        case Qt::Key_Plus:
            wartoscOrtho-=2;
            resizeGL(width(),height());
            break;
        case Qt::Key_Minus:
            wartoscOrtho+=2;
            resizeGL(width(),height());
            break;
        }
    }
    updateGL();


}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    QTextStream out(stdout);
    float h = (float) height()/(wartoscOrtho*2);
    float w = (float) width()/(wartoscOrtho*2);
    lastPos.setX(event->pos().x()/h-wartoscOrtho); // -wartoscOrtho, bo uklad wspolrzednych jest na srodku
    lastPos.setY((event->pos().y()/w-wartoscOrtho)*-1);
    out << lastPos.x() << " " << lastPos.y() << endl;

}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{

    //        if (event->buttons() & Qt::LeftButton)
    //        {
    //            float rx = event->pos().rx();
    //            wartoscOrtho+=rx;
    //            resizeGL(width(),height());

    //        }
    //        lastPos = event->pos();
    //        updateGL();
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    int x = event->delta();
    resizeGL(width(),height());
}

void MyGLWidget::dodajKwadrat(float x, float y, float a)
{
    listaFigur.append(new Kwadrat(x,y,a));
}

void MyGLWidget::dodajKolo(float x,float y,float r)
{
    listaFigur.append(new Kolo(x,y,r));
}

void MyGLWidget::dodajTrojkat(float x, float y, float a)
{
    listaFigur.append(new Trojkat(x,y,a));
}

void MyGLWidget::on_timer()
{
    animacjaPrzyblizania();
    ruchFigur();
    zjadanieMniejszych();
if(wartoscOrtho <= ramka) // jesli trzeba to aktualizuje
    resizeGL(width(),height());



    listaOdcinkow.at(0)->czyKolizja2(listaFigur.at(0));
 //   listaOdcinkow.at(1)->czyKolizja2(listaFigur.at(0));


    updateGL();
}

void MyGLWidget::usunFigurySlot()
{
    for (int i=0; i<listaFigur.length(); i++)
    {
        delete listaFigur.at(i);
    }
    listaFigur.clear();
}
void MyGLWidget::zmienPoziom(int i)
{
    usunFigurySlot();
    listaFigur = poziomy.inicjalizuj(i,ramka);
    aktualnyPoziom = i;
    sterowana = listaFigur.at(0); // sterowana figura to pierwszy element listy
}

void MyGLWidget::animacjaPrzyblizania()
{
    static bool j = 1;
    //animacja przyblizania
    if( j && wartoscOrtho > 50)
    {
        wartoscOrtho -= 10;

        if( wartoscOrtho < 61)
        {
            j = 0;
            wartoscOrtho = ramka+2;
        }
        resizeGL(width(), height());
    }

}

void MyGLWidget::ruchFigur()
{
    for(int i=0; i<listaFigur.length(); i++)
    {
        Figura *tmp = listaFigur.at(i);
        tmp->zmienPolozenie(Ts*tmp->zwrocPredkoscX()/1000,Ts*tmp->zwrocPredkoscY()/1000);
        tmp->zmienAlpha(Ts*tmp->zwrocOmega()/1000);
        QTextStream out(stdout);


        //        // jesli wyjdzie za pole renderingu
        //        float x=tmp->zwrocPolozenieX(), y=tmp->zwrocPolozenieY(), d = tmp->zwrocRozmiar()/2;
        //        if(x>=ramka+d || x<=-ramka-d || y>=ramka+d || y<=-ramka-d )// ??
        //        {
        //            tmp->zmienPolozenie(int(-2)*(x)+x/wartoscOrtho,int(-2)*y+y/wartoscOrtho); // zle, jesli jest tylko 1 skladowa predkosci, // x/wartoscOrtho - oznacza +-1 (zeby nie blokowalo sie przy przejsciu)
        //        }



        //odbicie od ściany
        float x=tmp->zwrocPolozenieX(), y=tmp->zwrocPolozenieY(), d = tmp->zwrocRozmiar()/2;
        if(tmp->zwrocTyp() == KWADRAT)
        {
            d *= 1.15;
        }
        else if(tmp->zwrocTyp() == TROJKAT)
        {
            d *= 0.866;
        }
        if(x>=ramka-d || x<=-ramka+d )
        {
            tmp->ustawPredkoscX(-tmp->zwrocPredkoscX());
            tmp->ustawPredkoscY(tmp->zwrocPredkoscY());
            //   tmp->zmienPolozenie(int(-2)*(x)+x/wartoscOrtho,int(-2)*y+y/wartoscOrtho); // zle, jesli jest tylko 1 skladowa predkosci, // x/wartoscOrtho - oznacza +-1 (zeby nie blokowalo sie przy przejsciu)
        }
        if( y>=ramka-d || y<=-ramka+d)
        {
            tmp->ustawPredkoscX(tmp->zwrocPredkoscX());
            tmp->ustawPredkoscY(-tmp->zwrocPredkoscY());
        }

    }
}


void MyGLWidget::zjadanieMniejszych()
{
    // zjadanie mniejszych
    int k=1;
    if(listaFigur.length()>1)
    {
        for(int i=0; i<listaFigur.length()-1; i++)
        {
            Figura *tmp1 = listaFigur.at(i);
            for (int j=k;j<listaFigur.length();j++)
            {
                Figura *tmp2 = listaFigur.at(j);
                if(tmp1->czyKolizja(tmp2))
                {
                    if(tmp1->zwrocPole() >= tmp2->zwrocPole())
                    {
                        // if(tmp1->zwrocRozmiar() < 30) // maksymalny rozmiar
                        tmp1->zmienPole(+tmp2->zwrocPole()/4); // szybkosc zjadania
                        tmp2->zmienPole(-tmp2->zwrocPole()/4);
                    }
                    else
                    {
                        tmp1->zmienPole(-tmp1->zwrocPole()/4);
                        //if(tmp2->zwrocRozmiar() < 30)
                        tmp2->zmienPole(+tmp1->zwrocPole()/4);

                    }
                }

            }
            k++;

        }
        // jeśli Cię zjadło

        //        if (listaFigur.at(0)->zwrocRozmiar() < 0.5)
        //        {
        //            listaFigur.clear();
        //            usunFigurySlot();
        //            sterowana = new Kwadrat(-30,20,10);
        //            listaFigur.append(sterowana);

        //        }

        //osobna petla do usuwania
        for (int i=1; i < listaFigur.length(); i++)
        {
            if (listaFigur.at(i)->zwrocRozmiar() <= 0.8) // rozmiar, czy pole?
            {
                delete listaFigur.at(i);
                listaFigur.removeAt(i);
            }
        }

    }
}


void MyGLWidget::ruchOdrzutowy()
{

}
