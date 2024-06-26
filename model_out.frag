//#version 330 core 指定版本是3.30，这个版本与OpenGL 3.3版本相对应。

//这是一个片段着色器，负责计算发出Pixel颜色。
//主要工作包括基本的光照计算（环境光+漫反射），并处理从顶点着色器传过来的误差值，将误差映射到颜色上。
//光照是简化的，没有考虑镜面反射
//着色器首先定义了相应的输入/输出和uniform变量。
//输入变量（in）是从顶点着色器传过来的FragPos、Normal和vError变量。
//输出变量（out）是最终的FragColor，即每个像素的颜色。
//uniform变量是光源的颜色和位置。
//mapErrorToColor函数根据从顶点着色器传过来的误差值（vError）来计算相应的顶点颜色。
//main函数计算了基本的光照模型（环境光和漫反射光），然后将结果和之前的映射颜色相乘得到最终像素的颜色。

#version 330 core
//layout( location = 0 ) out vec4 FragColor;

out vec4 FragColor;
//uniform vec3 objectColor;
uniform vec3 lightColor;
in vec3 FragPos;
in vec3 Normal;
uniform vec3 lightPos;
in float vError; // 从顶点着色器传入的误差值


// 将误差值映射到颜色的函数
vec3 mapErrorToColor(float error)
{
    // 定义颜色映射的范围和方式
    // 假设误差值的范围是 [0.0, 1.0]
    // 可以根据实际情况调整颜色和映射函数
    if (error <= 0.0) {
        return vec3(0.0, 1.0, 0.0);
    } else if (error > 0.0 && error <= 0.1) {
        return vec3(0.1, 0.9, 0.0);
    } else if (error > 0.1 && error <= 0.2) {
        return vec3(0.2,0.8,0.0);
    } else if (error > 0.2 && error <= 0.3) {
        return vec3(0.3, 0.7, 0.0);
    } else if (error > 0.3 && error <= 0.4) {
        return vec3(0.4, 0.6, 0.0);
    } else if (error > 0.4 && error <= 0.5) {
        return vec3(0.5, 0.5, 0.0);
    } else if (error > 0.5 && error <= 0.6) {
        return vec3(0.6, 0.3, 0.0);
    } else if (error > 0.6 && error <= 0.7) {
        return  vec3(0.7, 0.3, 0.0);
    } else if (error > 0.7 && error <= 0.8) {
        return vec3(0.8, 0.2, 0.0);
    } else if (error > 0.8 && error <= 0.9) {
        return vec3(0.9, 0.1, 0.0);
    } else {
        return vec3(1.0, 0.0, 0.0);
    }
}

void main()
{
       vec3 objectColor= mapErrorToColor(vError);
       float ambientStrength = 0.1;
       vec3 ambient = ambientStrength * lightColor;

       vec3 norm = normalize(Normal);
       vec3 lightDir = normalize(lightPos - FragPos);
       float diff = max(dot(norm, lightDir), 0.0);
       vec3 diffuse = diff * lightColor;

       vec3 result = (ambient + diffuse) * objectColor;
       FragColor = vec4(result, 1.0);
}
//// 将误差值映射到颜色的函数
//vec3 mapErrorToColor(float error)
//{
//    // 定义颜色映射的范围和方式
//    // 假设误差值的范围是 [0.0, 1.0]
//    // 你可以根据实际情况调整颜色和映射函数
//    if (error <= 0.0) {
//        // 无误差或误差很小，显示为绿色
//        return vec3(0.0, 1.0, 0.0);
//    } else if (error > 0.0 && error < 0.5) {
//        // 较小误差，显示为黄色
//        return vec3(1.0, 1.0, 0.0);
//    } else {
//        // 较大误差，显示为红色
//        return vec3(1.0, 0.0, 0.0);
//    }
//}

//如果还要细分颜色误差修改参数即可

