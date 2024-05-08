//#version 330 core 指定版本是3.30，这个版本与OpenGL 3.3版本相对应。


//这是QOpenGLWidget中的一个重载函数，主要用于进行OpenGL的绘制操作。
//它接收模型的顶点信息（包括位置、法线以及一个误差颜色值），然后根据这些信息，投影到视空间（通过模型、视图和投影矩阵变换），计算出每个顶点在裁剪空间的位置。
//此外，它还会计算出经过模型矩阵变换后的顶点位置和法线向量，并传送给片段着色器。
//它的主要功能点如下：
//layout (location = 0) in vec3 aPos; - 这行代码定义了一个输入顶点属性，表示每个顶点的位置信息。这个信息是从顶点缓冲对象（VBO）通过OpenGL的glVertexAttribPointer函数输入到着色器中的。
//layout (location = 1) in vec3 aNormal; - 这是另一个顶点属性，表示每个顶点的法向量信息。这些法向量用于光照计算。
//layout (location = 2) in float aError; - 这是第三个顶点属性，表示一个与顶点关联的误差值。这个值可能用于调整顶点的绘制方式，比如颜色或大小。这个值在顶点着色器中没有直接被用于计算，但被传递到了片段着色器中（通过vError变量）。
//uniform mat4 model; - 这是一个uniform变量，表示模型矩阵，用于将模型的本地位置转换到世界坐标系统。
//uniform mat4 view; - 这是另一个uniform变量，表示视图矩阵，用于将世界坐标系转换到视图坐标系。
//uniform mat4 projection; - 这个uniform变量表示投影矩阵，用于将视图坐标系统转换到裁剪空间。
//void main() - 这是着色器的主函数。主要进行上述多种矩阵运算以及顶点属性传递到片段着色器等任务。



#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0
layout (location = 1) in vec3 aNormal; // 法线变量的属性位置值为 1
layout (location = 2) in float aError; // 误差颜色变量的属性位置值为 2
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out float vError;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = mat3(model) * aNormal;//用于旋转时，使得法向量一起改变
    FragPos = vec3(model * vec4(aPos, 1.0));
    vError = aError; // 传递误差值到片段着色器
}


//PaintGL函数，这是QOpenGLWidget中的一个重载函数，主要用于进行OpenGL的绘制操作。
//个函数遵循基本的OpenGL渲染流程，包括清空颜色缓冲和深度缓冲、设置并使用着色器程序、绑定并向VBO中填充数据、执行绘制操作等步骤。
//函数的主要作用是更新两个模型（model_input和model_out）的渲染。
//渲染每个模型的流程大致相似，包括以下步骤：
//首先，绑定并使用对应模型的着色器程序。
//将顶点数据、法线数据（以及模型设定要绘制误差时的误差数据）填充到相应的VBOs中，并设置着色器属性指针来使用这些数据。
//设定光照、模型变换等uniform变量。
//最后，执行绘制操作glDrawArrays。

