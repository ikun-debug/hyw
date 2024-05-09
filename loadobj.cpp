// loadobj.cpp
//加载obj文件的类LoadObj包含功能：
//1、读取.obj文件并解析。
//2、获取解析后的顶点、纹理坐标、法向量。
//3、计算每个顶点的误差
//这个类主要针对简单的.obj文件编写，仅处理了顶点坐标、纹理坐标、顶点法线和面的基本数据解析，不处理例如材质、贴图等更复杂的情况。



#include "loadobj.h"
#include <QFile>
#include <QTextStream>


//构建函数
LoadObj::LoadObj() {}



//加载obj文件的函数（接收一个文件名作为参数）
bool LoadObj::load(const QString& filename) {

    //创建一个QFile对象，用于加载文件
    QFile file(filename);

    //以只读和文本模式打开文件
    //文件无法打开返回false
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    // 创建一个文字流，用于读取文件内容
    QTextStream in(&file);


    // 在这里实现obj文件解析逻辑
    // 填充m_vertices, m_texcoord和m_normals向量


    // 创建一个QString对象，用于暂存每行的数据
    QString line;

    // 创建一个QStringList对象，用于存储分隔后的字符串
    QStringList parts;


    //QVector<QVector3D>m_vertices_calculate;


    // 创建一个temp纹理坐标数组
    QVector<QVector2D>m_texCoords_temp;
    // 创建一个temp法向量数组
    QVector<QVector3D>m_normals_temp;



    //读取文件第一行
    //如果parts为空，对应空行，跳过此次循环
    while (!in.atEnd()) {
        //从文件流 in 中读取一行文本，并将其存储在变量 line 中
        line = in.readLine();

        //使用 trimmed() 方法去除行首和行尾的空白字符
        //使用 split(' ') 方法以空格为分隔符将文本行分割成多个部分，并将这些部分存储在 parts 中
        parts = line.trimmed().split(' ');

        if (parts.isEmpty()) {
            continue;
        }


        // 解析顶点
        //录入的时候用的局部坐标系  以模型自身中心为原点
        //wavefront的.obj文件中顶点数据的格式为：v, x, y, z
        //parts[0]代表的是v所以可以判断是否有顶点数据
        //parts[1]代表的是x的坐标
        //parts[2]代表的是y的坐标
        //parts[3]代表的是z的坐标
        if (parts[0] == "v") {
            // 创建一个QVector3D对象，用于存储这个顶点的坐标
            QVector3D v;

            // 设置顶点的x坐标
            v.setX(parts[1].toFloat());
            // 设置顶点的y坐标
            v.setY(parts[2].toFloat());
            // 设置顶点的z坐标
            v.setZ(parts[3].toFloat());

            // 把这个顶点加入到总的顶点数组中
            m_vertices_calculate.append(v);
        }


        // 解析纹理坐标
        //vt开头表示这行数据是纹理坐标
        //纹理坐标数据的存储格式是vt，u，v
        //u表示纹理坐标的u分量
        //v表示纹理坐标的v分量
        //u、v分量表示纹理在坐标上横向、纵向延伸的大小 相当于平面坐标系下的xy分量
        else if (parts[0] == "vt") {
            // 创建一个QVector2D对象，用于存储这个纹理坐标
            QVector2D t;

            // 设置纹理坐标的x坐标
            t.setX(parts[1].toFloat());
            // 设置纹理坐标的y坐标
            t.setY(parts[2].toFloat());

            // 把这个纹理坐标加入到总的纹理坐标数组中
            m_texCoords_temp.append(t);
        }


        // 解析法线
        //vn开头表示是法线的数据
        //法线数据用于计算光照效果，根据法线方向和光线方向计算出表面的明暗程度，从而呈现出真实的光照效果
        //x 分量影响着法线在模型表面的水平方向上的方向。正 x 分量表示法线向右，负 x 分量表示法线向左。
        //y 分量影响着法线在模型表面的垂直方向上的方向。正 y 分量表示法线向上，负 y 分量表示法线向下。
        //z 分量影响着法线在模型表面的深度方向上的方向。正 z 分量表示法线朝向观察者，负 z 分量表示法线背离观察者。
        else if (parts[0] == "vn") {
            // 创建一个QVector3D对象，用于存储这个法向量
            QVector3D n;

            // 设置法向量的x坐标
            n.setX(parts[1].toFloat());
            // 设置法向量的y坐标
            n.setY(parts[2].toFloat());
            // 设置法向量的z坐标
            n.setZ(parts[3].toFloat());


            // 把这个法向量加入到总的法向量数组中
            m_normals_temp.append(n);
        }

        //面数据处理
        //以f开头说明次行存放的是面数据
        //数据存放方式：f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
        //面数据行通常以字母 f 开头，后跟顶点索引、纹理坐标索引和法线索引，用来描述模型的面片结构，例如：f 1/1/1 2/2/2 3/3/3
        //顶点索引用于存放顶点之间的连接顺序，从而构成表面
        //纹理坐标索引用于指定每个顶点在纹理图像中的位置
        //纹理坐标索引通常包括 u 和 v 值，用来确定在纹理图像中的水平和垂直位置。
        //在渲染过程中，纹理坐标索引与顶点索引一起被用来确定每个顶点在纹理图像中的采样位置，从而实现纹理的贴图效果
        //法线索引用于指定每个顶点的法线方向，用于光照计算和表面法线的插值。
        //法线索引通常包括 x、y、z 分量，用来描述顶点的法线方向。
        //在光照计算和渲染过程中，法线索引与顶点索引一起被用来确定每个顶点的法线方向，以便计算光照效果和表面的明暗程度。
        else if(parts[0] == "f")
        {
            // 遍历该面上的所有索引
            for(int i=1;i<parts.size();i++)
            {
                //对每个索引，代码首先将字符串按 "/" 分割，提取出顶点索引和法线索引
                QStringList indexParts = parts[i].trimmed().split("/");

                //vertexIdx：顶点索引
                int vertexIdx = indexParts[0].toInt() - 1;
                //normalIdx：法线索引
                int normalIdx = indexParts[2].toInt() - 1;


                // 将正确的顶点和法向量添加至最终数组中
                //顶点数组 m_vertices_calculate
                m_vertices.append(m_vertices_calculate[vertexIdx]);

                //法线数组 m_normals_temp
                m_normals.append(m_normals_temp[normalIdx]);

                //顶点索引数组 m_vertices_index
                m_vertices_index.append(vertexIdx);
            }
        }
    }


    //关闭文件
    file.close();


    //.obj文件已经读取完成，可以开始绘制
    isDraw=true;

     // 读取.func文件并将其解析成功
    return true;
}



// 返回读取到的顶点数组
QVector<QVector3D> LoadObj::vertices() const {
    return m_vertices;
}



// 返回读取到的纹理坐标数组
QVector<QVector2D> LoadObj::texCoords() const {
    return m_texCoords;
}



// 返回读取到的法向量数组
QVector<QVector3D> LoadObj::normals() const {
    return m_normals;
}



// 计算每个顶点的误差
//calculateError接受一个类型为 QVector<float> 的 error 参数，用于存储每个顶点的误差值
void LoadObj::calculateError(QVector<float> error)
{
    // 遍历顶点数组index，为每个顶点计算其误差
    for(int i=0;i<m_vertices_index.size();i++)
    {
        m_error.append(error[m_vertices_index[i]]);
    }
}



//基于给定的obj文件，首先要考虑obj文件的法线等数据是否有问题
//法线等数据有问题的文件会导致显示异常等清空
//所以在一般情况下需要提前对obj文件进行检查与修改
//本课题是为了验证两个模型的误差的一种可视化的分析的可行性
//如果连法线数据都是错误的那就不能称之为误差了
//所以模型错误不在程序处理条件内
