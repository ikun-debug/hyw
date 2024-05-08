//#version 330 core 指定版本是3.30，这个版本与OpenGL 3.3版本相对应。
//OpenGL的vertex shader代码。



#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0
layout (location = 1) in vec3 aNormal; // 颜色变量的属性位置值为 1

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = mat3(model) * aNormal;//用于旋转时，使得法向量一起改变
    FragPos = vec3(model * vec4(aPos, 1.0));
}


//layout (location = 0) in vec3 aPos; 定义一个输入顶点属性，称为aPos，表示每个顶点的位置信息。这个信息是从顶点缓冲区通过OpenGL的函数输入到shader中的。
//layout (location = 1) in vec3 aNormal; 是另一个顶点属性，这回存储了每个顶点的法向量信息。这些法向量用于之后的光照计算。


//uniform mat4 model; 是模型矩阵，它将模型本地空间位置（也称作物体空间）转换为世界空间中的位置。
//uniform mat4 view; 是视图矩阵，它将世界空间中的位置转换为观察/视图空间中的位置。
//uniform mat4 projection; 是投影矩阵，它将观察空间中的位置转换为裁剪空间的位置。


//gl_Position = projection * view * model * vec4(aPos, 1.0); 这部分代码首先将顶点的位置aPos转换为齐次坐标vec4(aPos, 1.0)，然后，依次通过模型矩阵、视图矩阵和投影矩阵的变换，最后计算并设置齐次裁剪空间的顶点位置。


//Normal = mat3(model) * aNormal; 这里将法向量通过模型矩阵（丢弃了平移部分，只保留缩放和旋转部分）进行变换，以便获取正确的朝向。


//FragPos = vec3(model * vec4(aPos, 1.0)); 这条语句计算并设置世界空间中顶点的位置。


