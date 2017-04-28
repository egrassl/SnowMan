#include "floor.h"

Floor::Floor()
{

}

Floor::Floor(float size, float repeat){
    this->size = size;
    this->repeat = repeat;
    this->snowTexture1 = QString::QString("/Users/coala/Desktop/snowgrass3resized");
    this->snowTexture2 = QString::QString("/Users/coala/Desktop/snow3resized");
    this->lavaTexture = QString::QString("/Users/coala/Desktop/lava");
    this->grassTexture = QString::QString("/Users/coala/Desktop/grassSquareResized");
    this->activeTexture = QString::QString(this->snowTexture1);
    //std::cout << "Path: " << QDir::currentPath().toStdString() << std::endl;
}

// 1-default, 2-snow2, 3-lava, 4-Grama
void Floor::setActiveTexture(int textura){
    if(textura==1){
        this->activeTexture = QString::QString(this->snowTexture1);
    }else if(textura==2){
        this->activeTexture = QString::QString(this->snowTexture2);
    }else if(textura==3){
        this->activeTexture = QString::QString(this->lavaTexture);
    }else{
        this->activeTexture = QString::QString(this->grassTexture);
    }
}

void Floor::openTexture(QString textura){
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

void Floor::draw(){

    //std::cout << "Desenhando o chao" << std::endl;

    openTexture(this->activeTexture);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
        glTexCoord2f(0.0f, 0.0f);                    glVertex3f(-this->size , 0.0, -this->size);
        glTexCoord2f(0.0f, this->repeat);            glVertex3f(this->size,  0.0, -this->size);
        glTexCoord2f(this->repeat, this->repeat);    glVertex3f( this->size,  0.0, this->size);
        glTexCoord2f(this->repeat, 0.0f);            glVertex3f( -this->size, 0.0, this->size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}
