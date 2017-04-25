#ifndef SNOWMAN_H
#define SNOWMAN_H

#include <QString>
#include <QGLWidget>
#include <QtOpenGL>
#include <glu.h>

class SnowMan
{
public:

    // Raios do boneco e localização das texturas
    float bodyRadius, headRadius, eyesRadius, noseRadius, angle;
    QString snowTexture,carrotTexture;

    // Construtor Default
    SnowMan();

    // Construtor do Homem de neve
    explicit SnowMan(float bodyRadius, float headRadius, float eyesRadius, float noseRadius);

    // Desenha
    void draw();

    // Carrega a textura a ser utilizada
    void openTexture(QString textura);

    // faz a animação
    void animate(float angle);

private:

    // Desenha uma esfera
    void drawSphere(float radius);

    // Desenha um cilindro
    void drawCylinder(float baseRadius, float topRadius);

};

#endif // SNOWMAN_H
