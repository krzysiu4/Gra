#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QPointF>
#include <kolo.h>
#include <kwadrat.h>
#include <trojkat.h>
#include <QList>
#include <QTimer>
#include <poziomy.h>
#include <odcinek.h>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    enum {KOLO, KWADRAT, TROJKAT};
    explicit MyGLWidget(QWidget *parent = 0);
    virtual ~MyGLWidget();
    void dodajKwadrat(float,float,float);
    void dodajKolo(float,float,float);
    void dodajTrojkat(float,float,float);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void zmienPoziom(int i);
    void animacjaPrzyblizania();
    void ruchFigur();
    void zjadanieMniejszych();
    void ruchOdrzutowy();

    int wartoscOrtho;
    int ramka;
    GLfloat tlo[4];
    QList <Figura*> listaFigur;
    QList <Odcinek*> listaOdcinkow;
    Figura* sterowana;
    Poziomy poziomy;
    QPointF lastPos;
    QTimer timer;
    int Ts;
    int aktualnyPoziom;


signals:

public slots:
    void on_timer();
    void usunFigurySlot();

};

#endif // MYGLWIDGET_H
