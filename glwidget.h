#ifndef GLWIDGET_H
#define GLWIDGET_H
#define SNOWMMAX 5

#include <QGLWidget>
#include <QtOpenGL>
#include <QKeyEvent>
#include <glu.h>
#include <QTimer>
#include <iostream>
#include <QOpenGLTexture>
#include <QFileDialog>
#include <QDir>
#include <QMouseEvent>
#include <math.h>
#include "snowman.h"
#include "floor.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    ~GLWidget();

    void initializeGL();

    void paintGL();

    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent* event);

    void keyReleaseEvent(QKeyEvent* event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void setSkyColor(int i);

    void changeSnowMenTexture(int i);

    void changeFloorTexture(int i);

    void changeActiveSnowMan(int snowMan);

private:
    int i,j;
    // angle of rotation for the camera direction
    float angle;

    // actual vector representing the camera's direction
    float lx;
    float lz;

    // XZ position of the camera
    float x;
    float z;

    // the key states. These variables will be zero
    //when no key is being presses
    float deltaAngle;
    float deltaMove;
    int xOrigin;

    // Mouse drag control
    int isDragging; // true when dragging
    int xDragStart; // records the x-coordinate when dragging starts

    int clearColor, activeSnowMan;

    SnowMan *snowmen;

    Floor terreno;

    void computePos();

    void registraTextura(QString filePath, int posText);

    void addLuz();

    void addNearbySnowmen();

    float distanciaEntreSnowmen(SnowMan s1, SnowMan s2);

    bool canSnowManMove(int snowman);

protected:


signals:

public slots:
};

#endif // GLWIDGET_H
