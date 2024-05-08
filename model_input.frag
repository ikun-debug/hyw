//#version 330 core 指定版本是3.30，这个版本与OpenGL 3.3版本相对应。


//片段着色器，负责最终渲染的像素颜色
//片段着色器接收变换后的几何顶点数据（来自顶点着色器），并针对每个像素进行光照计算。
//这个片段着色器中，基本光照模型是环境光照和漫反射光照的组合。
//这是一个简化的光照模型，因为它没有计算镜面反射来模拟闪亮的表面。

#version 330 core
//layout( location = 0 ) out vec4 FragColor;

out vec4 FragColor;
uniform vec3 objectColor;
uniform vec3 lightColor;
in vec3 FragPos;
in vec3 Normal;
uniform vec3 lightPos;

void main()
{
     float ambientStrength = 0.1;
       vec3 ambient = ambientStrength * lightColor;

       vec3 norm = normalize(Normal);
       vec3 lightDir = normalize(lightPos - FragPos);
       // float diff = max(dot(norm, lightDir), 0.0);
       float diff = abs(dot(norm, lightDir));
       vec3 diffuse = diff * lightColor;
       vec3 result = (ambient + diffuse) * objectColor;
       FragColor = vec4(result, 1.0);
       //FragColor = vec4(1.0,0.5,0.31, 1.0);
}



//在主函数main()开始，首先定义环境光的强度ambientStrength，然后得到环境光的颜色ambient。

//然后计算光源距离片段的方向lightDir，并归一化法向量和光的方向。

//然后计算两个向量的点积diff，根据其方向性决定光线照到表面的强度，并得到漫反射光的颜色diffuse。

//最后将环境光和漫反射光混合，并使用表面基础色objectColor调整光的颜色，得到最终的像素颜色FragColor。

//这个光照模型的计算漫反射光时使用的是abs(dot(norm, lightDir))而不是常见的max(dot(norm, lightDir), 0.0)。
//abs函数会取绝对值，这意味着即使光源在表面的背面，漫反射仍然会起作用。
//用abs会使成像更加直观，如果不需要注释掉即可
