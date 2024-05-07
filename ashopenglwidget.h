#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLExtraFunctions>
#include <QVector>
#include <QStringList>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QTime>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QQuaternion>
#include <QVector2D>
#include "loadobj.h"

//class ASHOpenglWidget : public QOpenGLWidget,public QOpenGLExtraFunctions
class ASHOpenglWidget : public QOpenGLWidget,public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    ASHOpenglWidget(QWidget *parent = nullptr);

    ~ASHOpenglWidget();

    QVector<float> vertices_model;
    QVector<float> loadModel(QString filename,float ratio);//文件名和放大系数

//protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w,int h) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void initializeInputobj();
    void initializeOutobj();
    QVector<float> Position;
    QVector<float> Normal;
    QOpenGLShaderProgram shaderprogram_input,shaderprogram_out;
    QOpenGLVertexArrayObject VAO_input,VAO_out;//声明VAO顶点数组对象
    QOpenGLBuffer VBOPosition_input,VBONormal_input,VBOPosition_out,VBONormal_out;//声明VBO数组缓冲对象
    QOpenGLBuffer VBOError_input,VBOError_out;//声明VBO数组缓冲对象
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    GLfloat xtrans, ytrans, ztrans,xrot,yrot,zrot; // translation on x,y,z-axis
    QVector2D mousePos;
    QQuaternion rotation;

    LoadObj model_input=LoadObj();
    LoadObj model_out=LoadObj();

};
#endif // WIDGET_H




