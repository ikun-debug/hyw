// loadobj.cpp
#include "loadobj.h"
#include <QFile>
#include <QTextStream>

LoadObj::LoadObj() {}

bool LoadObj::load(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    // Implement your obj file parsing logic here
    // Populate m_vertices, m_texCoords, and m_normals vectors
    QString line;
    QStringList parts;
    //QVector<QVector3D>m_vertices_calculate;
    QVector<QVector2D>m_texCoords_temp;
    QVector<QVector3D>m_normals_temp;
    while (!in.atEnd()) {
        line = in.readLine();
        parts = line.trimmed().split(' ');

        if (parts.isEmpty()) {
            continue;
        }

        // 解析顶点
        if (parts[0] == "v") {
            QVector3D v;
            v.setX(parts[1].toFloat());
            v.setY(parts[2].toFloat());
            v.setZ(parts[3].toFloat());
            m_vertices_calculate.append(v);
        }
        // 解析纹理坐标
        else if (parts[0] == "vt") {
            QVector2D t;
            t.setX(parts[1].toFloat());
            t.setY(parts[2].toFloat());
            m_texCoords_temp.append(t);
        }
        // 解析法线
        else if (parts[0] == "vn") {
            QVector3D n;
            n.setX(parts[1].toFloat());
            n.setY(parts[2].toFloat());
            n.setZ(parts[3].toFloat());
            m_normals_temp.append(n);
        }
        else if(parts[0] == "f")
        {
            for(int i=1;i<parts.size();i++)
            {
                QStringList indexParts = parts[i].trimmed().split("/");
                int vertexIdx = indexParts[0].toInt() - 1;
                int normalIdx = indexParts[2].toInt() - 1;
                m_vertices.append(m_vertices_calculate[vertexIdx]);
                m_normals.append(m_normals_temp[normalIdx]);
                m_vertices_index.append(vertexIdx);
            }
        }
    }
    file.close();
    isDraw=true;
    return true;
}

QVector<QVector3D> LoadObj::vertices() const {
    return m_vertices;
}

QVector<QVector2D> LoadObj::texCoords() const {
    return m_texCoords;
}

QVector<QVector3D> LoadObj::normals() const {
    return m_normals;
}

void LoadObj::calculateError(QVector<float> error)
{
    for(int i=0;i<m_vertices_index.size();i++)
    {
        m_error.append(error[m_vertices_index[i]]);
    }
}
