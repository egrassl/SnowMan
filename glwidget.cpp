#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    snowmen = new SnowMan[SNOWMMAX];
    for(int i = 0; i < SNOWMMAX; i++){
        snowmen[i] = SnowMan::SnowMan(0.75,0.25,0.05,0.08);
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(0);

}

GLWidget::~GLWidget(){
    delete[] snowmen;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    int x = event->x();
    //int y = event->y();



    if (xOrigin >= 0) {

        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.005f;

        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }

   // std::cout << "Mouse moveu" << std::endl;

}

void GLWidget::mousePressEvent(QMouseEvent *event){
    // only start motion if the left button is pressed
    if (event->button() == Qt::LeftButton) {

        xOrigin = event->x();
        //std::cout << "Botao esquerdo pressionado" << std::endl;
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        angle += deltaAngle;
        xOrigin = -1;
        //std::cout << "Botao esquerdo solto" << std::endl;
    }

}

void GLWidget::addLuz(){
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
        GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor"
        GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
        GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

        // Capacidade de brilho do material
        GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
        GLint especMaterial = 60;

        // Habilita o modelo de colorização de Gouraud
        glShadeModel(GL_SMOOTH);

        // Define a refletância do material
        glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
        // Define a concentração do brilho
        glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

        // Ativa o uso da luz ambiente
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

        // Define os parâmetros da luz de número 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

        // Habilita a definição da cor do material a partir da cor corrente
        glEnable(GL_COLOR_MATERIAL);
        //Habilita o uso de iluminação
        glEnable(GL_LIGHTING);
        // Habilita a luz de número 0
        glEnable(GL_LIGHT0);
        // Habilita o depth-buffering
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
}


void GLWidget::keyPressEvent(QKeyEvent* event){
    switch (event->key()) {
            case Qt::Key_W : deltaMove = 1.0f; break;
            case Qt::Key_S : deltaMove = -1.0f; break;
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent* event){
    switch (event->key()) {
            case Qt::Key_W :
            case Qt::Key_S : deltaMove = 0;break;
    }
}

void GLWidget::initializeGL(){



    // angle of rotation for the camera direction
    angle = 0.0f;

    // actual vector representing the camera's direction
    lx=0.0f;
    lz=-1.0f;

    // XZ position of the camera
    x=0.0f;
    z=5.0f;

    // the key states. These variables will be zero
    //when no key is being presses
    deltaAngle = 0.0f;
    deltaMove = 0;
    xOrigin = -1;

    // Mouse drag control
    isDragging = 0; // true when dragging
    xDragStart = 0; // records the x-coordinate when dragging starts


    glEnable(GL_DEPTH_TEST);

    //glClearColor(0.0, 0.7, 1.0, 1.0);
    glClearColor(0.7, 0.7, 0.72, 1.0);


    addLuz();
}


void GLWidget::computePos(){
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
    //std::cout << "novo z: " << z << std::endl;
}

void GLWidget::drawFloor(float size,float repeat){

    QString textura = QString::QString("/Users/coala/Desktop/snowgrass3resized");



    if (!textura.isEmpty())
    {
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
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, texID);
    }



    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
        glTexCoord2f(0.0f, 0.0f);        glVertex3f(-size , 0.0, -size);
        glTexCoord2f(0.0f, repeat);      glVertex3f(size,  0.0, -size);
        glTexCoord2f(repeat, repeat);    glVertex3f( size,  0.0, size);
        glTexCoord2f(repeat, 0.0f);      glVertex3f( -size, 0.0, size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

}

void GLWidget::paintGL(){

    int j;

    if (deltaMove) computePos();

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Limpa o buffer de profundidade e o buffer de cor
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gluLookAt(	x, 1.0f, z,
          x+lx, 1.0f,  z+lz,
          0.0f, 1.0f,  0.0f);

    glColor3f(1.0, 1.0, 1.0);

    drawFloor(20.0,5.0);

    j = -(int)SNOWMMAX/2;

    for(int i = 0 ; i < SNOWMMAX ; i++){
        glPushMatrix();
        glTranslated(2*j, 0 , 0);
        snowmen[i].draw();
        if(i % 2 == 0){
            snowmen[i].animate(-1);
        } else {
            snowmen[i].animate(1);
        }
        glPopMatrix();
        j++;
    }

}

void GLWidget::resizeGL(int w, int h){
    float fAspect;
   // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(45,fAspect,0.1f, 50.0f);

    // Especifica sistema de coordenadas do modelo
   //glMatrixMode(GL_MODELVIEW);
   //Inicializa sistema de coordenadas do modelo
   //glLoadIdentity();


}
