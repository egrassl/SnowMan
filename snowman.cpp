#include "snowman.h"

SnowMan::SnowMan(){}

SnowMan::SnowMan(float bodyRadius, float headRadius, float eyesRadius, float noseRadius){
    this->bodyRadius = bodyRadius;
    this->headRadius = headRadius;
    this->eyesRadius = eyesRadius;
    this->noseRadius = noseRadius;
    this->move = true;
    this->angle = 0;
    this->translateX = 0;
    this ->translateZ = 0;
    this->x = 0;
    this->z = 0;
    this->y = 0;
    this->rotate = 1.0;
    this->incrementX = false;
    this->incrementZ = false;
    this->snowTexture = QString::QString(":/textures/snow3resized");
    this->carrotTexture = QString::QString(":/textures/cenoura");
    this->lavaTexture = QString::QString(":/textures/lava");
    this->grassTexture = QString::QString(":/textures/grassSquareResized");
    this->activeManTexture = QString::QString(this->snowTexture);
}

void SnowMan::setIncrementX(float x){
    this->incrementX = x;
}

float SnowMan::getIncrementX(){
    return this->incrementX;
}

void SnowMan::setIncrementZ(float x){
    this->incrementZ = x;
}

float SnowMan::getIncrementZ(){
    return this->incrementZ;
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

void SnowMan::addRotation(float r){
    float newRotate = this->rotate + r;
    if(newRotate >= 0 && newRotate <= 1){
        this->rotate = newRotate;
    }
}

void SnowMan::animate(float angle){
    this->angle += angle * this->rotate;
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

float SnowMan::getGlobalX(){
    return this->x + this->translateX;
}

float SnowMan::getGlobalZ(){
    return this->z + this->translateZ;
}

void SnowMan::draw(float x, float y, float z){

    glPushMatrix();

    if(this->move){
        this->translateX += this->incrementX;
        this->translateZ += this->incrementZ;
    }

    this->x = x + this->translateX;
    this->z = z + this->translateZ;

    glTranslatef(this->x, this->y, this->z);
    glRotatef(angle,0,1,0);

    //-------------------

    //glRasterPos3f(this->x, 2, this->z);


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
