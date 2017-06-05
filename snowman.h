#ifndef SNOWMAN_H
#define SNOWMAN_H

#include <QString>
#include <QGLWidget>
#include <QtOpenGL>
#include <glu.h>
#include <iostream>

class SnowMan
{
public:

    // Raios do boneco e localização das texturas
    float bodyRadius, headRadius, eyesRadius, noseRadius, angle, x, y, z, rotate;
    QString snowTexture,carrotTexture,lavaTexture,grassTexture,activeManTexture;
    bool move;

    // Construtor Default
    SnowMan();

    // Construtor do Homem de neve
    explicit SnowMan(float bodyRadius, float headRadius, float eyesRadius, float noseRadius);

    // Desenha
    void draw(float x, float y, float z);

    // Faz a animação
    void animate(float angle);

    // Define as texturas
    void setActiveTexture(int textura);

    void setIncrementX(float x);

    float getIncrementX();

    void setIncrementZ(float x);

    float getIncrementZ();

    float getGlobalX();

    float getGlobalZ();

    void addRotation(float r);

private:

    float translateX, translateZ, incrementX, incrementZ;

    // Desenha uma esfera
    void drawSphere(float radius);

    // Desenha um cilindro
    void drawCylinder(float baseRadius, float topRadius);

    // Carrega a textura a ser utilizada
    void openTexture(QString textura);
};

#endif // SNOWMAN_H
