#ifndef ODCINEK_H
#define ODCINEK_H
#include <QGLWidget>
#include <figura.h>
#define PI 3.14159265

class Odcinek
{
public:
    Odcinek();
    Odcinek(GLfloat,GLfloat,GLfloat,GLfloat);
    void rysuj();
    void czyKolizja2(Figura* ); // od razu odbija figure, jesli kolizja

private:
    GLfloat Ax, Ay, Bx, By;
    GLfloat alpha; // kat nachylenia
};

#endif // ODCINEK_H
