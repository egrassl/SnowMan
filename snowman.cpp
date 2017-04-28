#include "snowman.h"

SnowMan::SnowMan(){}

SnowMan::SnowMan(float bodyRadius, float headRadius, float eyesRadius, float noseRadius){
    this->bodyRadius = bodyRadius;
    this->headRadius = headRadius;
    this->eyesRadius = eyesRadius;
    this->noseRadius = noseRadius;
    this->angle = 0;
    this->snowTexture = QString::QString("/Users/coala/Desktop/snow3resized");
    this->carrotTexture = QString::QString("/Users/coala/Desktop/cenoura");
    this->lavaTexture = QString::QString("/Users/coala/Desktop/lava");
    this->grassTexture = QString::QString("/Users/coala/Desktop/grassSquareResized");
    this->activeManTexture = QString::QString(this->snowTexture);
}

void SnowMan::openTexture(QString textura){
    if (!textura.isEmpty()){
        QImage textureImg;
        GLuint texID;
        textureImg.load(textura);
        textureImg = QGLWidget::convertToGLFormat( textureImg);
        glGenTextures( (GLuint) 1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImg.width(), textureImg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImg.bits());
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BGRA);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);;
        glBindTexture(GL_TEXTURE_2D, texID);
    }
}

void SnowMan::drawSphere(float radius){
    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    gluSphere(quadric,radius,20,20);
    glPopMatrix();
}

void SnowMan::drawCylinder(float baseRadius, float topRadius){
    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluCylinder(quadric, baseRadius, topRadius, 0.5, 20, 20);
}

void SnowMan::animate(float angle){
    this->angle += angle;
}

// Seta textura, 1-Neve, 2-Lava, 3-Grama
void SnowMan::setActiveTexture(int textura){
    if(textura==1){
        this->activeManTexture = QString::QString(this->snowTexture);
    }else if(textura==2){
        this->activeManTexture = QString::QString(this->lavaTexture);
    }else{
        this->activeManTexture = QString::QString(this->grassTexture);
    }
}

void SnowMan::draw(){

    glPushMatrix();

    glRotatef(angle,0,1,0);

    openTexture(activeManTexture);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);
    drawSphere(bodyRadius);

    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    drawSphere(headRadius);

    // Desabilita textura
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    drawSphere(eyesRadius);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    drawSphere(eyesRadius);
    glPopMatrix();

    // Draw Nose
    openTexture(carrotTexture);
    glColor3f(1.0f, 1.0f , 1.0f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    drawCylinder(noseRadius, 0);

    // Desabilita textura
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glPopMatrix();

}
