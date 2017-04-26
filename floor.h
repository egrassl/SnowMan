#ifndef FLOOR_H
#define FLOOR_H
#include <QString>
#include <QtOpenGL>
#include <iostream>

class Floor
{
public:
    Floor();

    Floor(float size, float repeat);

    void draw();

    void setActiveTexture(int textura);

private:

    float size, repeat;
    QString activeTexture, snowTexture1, snowTexture2, lavaTexture;

    // Carrega a textura a ser utilizada
    void openTexture(QString textura);

};

#endif // FLOOR_H
