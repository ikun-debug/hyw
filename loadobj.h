// loadobj.h
#ifndef LOADOBJ_H
#define LOADOBJ_H

#include <QString>
#include <QVector>
#include <QVector3D>
#include <QVector2D>

class LoadObj {
public:
    LoadObj();


    bool load(const QString& filename);


    QVector<QVector3D> vertices() const;
    QVector<QVector2D> texCoords() const;
    QVector<QVector3D> normals() const;


    bool isDraw=false;


    QVector<QVector3D> m_vertices_calculate;
    QVector<int> m_vertices_index;
    QVector<float> m_error;


    bool isDrawerror=false;


    void calculateError(QVector<float> error);


private:
    QVector<QVector3D> m_vertices;
    QVector<QVector2D> m_texCoords;
    QVector<QVector3D> m_normals;

};

#endif // LOADOBJ_H
