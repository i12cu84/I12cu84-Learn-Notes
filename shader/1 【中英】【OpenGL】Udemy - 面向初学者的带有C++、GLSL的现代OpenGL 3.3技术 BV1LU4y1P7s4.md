https://www.udemy.com/course/modern-opengl/
Learn OpenGL through C++ to handle your Application or Game Engine.
Modern OpenGL 3.3 with C++/GLSL for beginners
OpenGL Shading Language

p3

download glfw/glew

设置上的链接
![](../assets/2022-04-22-15-42-39.png)
绝对路径变成相对路径
![](../assets/2022-04-22-15-44-32.png)
预处理设定
![](../assets/2022-04-22-15-45-46.png)
常规链路附加库
![](../assets/2022-04-22-15-47-28.png)
依赖附加
![](../assets/2022-04-22-15-49-48.png)
![](../assets/2022-04-22-15-55-51.png)

出现x86程序与x64库的冲突
LNK4272: 库计算机类型“x64”与目标计算机类型“x86”冲突
解决方法:
![](../assets/2022-04-22-16-06-18.png)
又出现
LNK1112: 模块计算机类型“x86”与目标计算机类型“x64”冲突
解决方法:
![](../assets/2022-04-22-16-20-55.png)

测试code
<pre><code>
//#include <GL/glew.h>//顺序不能错
#include <GLFW/glfw3.h>
int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
</code></pre>

p4

<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
    //#ifdef __APPLE__
    //    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* game loop*/
    while (!glfwWindowShouldClose(window))
    {
        /* update */

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    */
    return 0;
}
</code></pre>

p6

<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
float vertices[] =
{
    /* position */
    -0.5f,-0.5f ,0.0f, // botoom left
     0.5f,-0.5f, 0.0f, // bottom right
     0.0f, 0.5f, 0.0f, // up center
};
int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* buffers */
    unsigned int VBO;

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),&vertices,GL_STATIC_DRAW);

    /* position attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    /* game loop */
    while (!glfwWindowShouldClose(window))
    {
        /* update */

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/
    return 0;
}
</code></pre>

p7

绘制三角形
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
float vertices[] =
{
    /* position */
    -0.5f,-0.5f ,0.0f, // botoom left
     0.5f,-0.5f, 0.0f, // bottom right
     0.0f, 0.5f, 0.0f, // up center
};
int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* buffers */
    unsigned int VBO,VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),&vertices,GL_STATIC_DRAW);

    /* position attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    /* game loop */
    while (!glfwWindowShouldClose(window))
    {
        /* update */

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);
        
        //线组描绘
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/
    return 0;
}
</code></pre>

p8

绘制正方形
分割成两个三角形 绘制两个三角形
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
float vertices[] =
{
    /* position */
    -0.5f,-0.5f ,0.0f, // botoom left
     0.5f,-0.5f, 0.0f, // bottom right
     0.5f, 0.5f, 0.0f, // up right

     0.5f, 0.5f, 0.0f, // up right
    -0.5f, 0.5f, 0.0f, // up left
    -0.5f,-0.5f, 0.0f, // button left
};
int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* buffers */
    unsigned int VBO,VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),&vertices,GL_STATIC_DRAW);

    /* position attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    /* game loop */
    while (!glfwWindowShouldClose(window))
    {
        /* update */

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        //线组描绘
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/
    return 0;
}
</code></pre>

p9

改为索引点序列indecie相连
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
float vertices[] =
{
    /* position */
    -0.5f,-0.5f ,0.0f, // botoom left
     0.5f,-0.5f, 0.0f, // bottom right
     0.5f, 0.5f, 0.0f, // up right
    -0.5f, 0.5f, 0.0f, // up left
};

int indecies[] =
{
    0,1,2,
    2,3,0
};

int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* buffers */
    unsigned int VBO,VAO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), &indecies, GL_STATIC_DRAW);

    /* position attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    /* game loop */
    while (!glfwWindowShouldClose(window))
    {
        /* update */

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        //线组描绘
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/
    return 0;
}
</code></pre>

P11

<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
float vertices[] =
{
    /* position */
    -0.5f,-0.5f ,0.0f, // botoom left
     0.5f,-0.5f, 0.0f, // bottom right
     0.5f, 0.5f, 0.0f, // up right

     0.5f, 0.5f, 0.0f, // up right
    -0.5f, 0.5f, 0.0f, // up left
    -0.5f,-0.5f ,0.0f, // botoom left
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 1) in vec3 aPos;\n"
"void main()\n"
"{"
"   gl_Position = vec4(aPos, 1.0f);"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(1.0f,0.5f,0.31f,1.0f);\n"
"}\0";

int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* buffers */
    unsigned int VBO,VAO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    /* position attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    /* game loop */
    while (!glfwWindowShouldClose(window))
    {
        /* update */

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        //线组描绘
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/
    return 0;
}
</code></pre>

p12

const char*文本改变颜色
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
float vertices[] =
{
    /* position */
    -0.5f,-0.5f ,0.0f, // botoom left
     0.5f,-0.5f, 0.0f, // bottom right
     0.5f, 0.5f, 0.0f, // up right

     0.5f, 0.5f, 0.0f, // up right
    -0.5f, 0.5f, 0.0f, // up left
    -0.5f,-0.5f ,0.0f, // botoom left
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{"
"   gl_Position = vec4(aPos, 1.0f);"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(1.0f,0.5f,0.31f,1.0f);\n"
"}\0";

int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* shader */
    /* vertex */
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex, 1, &VertexShaderData, NULL);
    glCompileShader(vertex);

    int success;
    char infolog[1024];

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex, 1024, NULL, infolog);
        std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
    }

    /* fragment */
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment, 1, &FragmentShaderData, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment, 1024, NULL, infolog);
        std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
    }

    /* program */
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infolog);
        std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    /* buffers */
    unsigned int VBO,VAO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    /* position attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    /* game loop */
    while (!glfwWindowShouldClose(window))
    {
        /* update */

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,6);

        //线组描绘
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/
    return 0;
}
</code></pre>

p13

uniforms 内部update重新改色
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
float vertices[] =
{
    /* position */
    -0.5f,-0.5f ,0.0f, // botoom left
     0.5f,-0.5f, 0.0f, // bottom right
     0.5f, 0.5f, 0.0f, // up right

     0.5f, 0.5f, 0.0f, // up right
    -0.5f, 0.5f, 0.0f, // up left
    -0.5f,-0.5f ,0.0f, // botoom left
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{"
"   gl_Position = vec4(aPos, 1.0f);"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform float xColor;\n"
"uniform float yColor;\n"
"uniform float zColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(xColor,yColor,zColor,1.0f);\n"
"}\0";

int main(void)
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //mac if
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create a window 窗口大小
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

    //check window 检查
    if (!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
    }

    /* the most inportant part */
    glfwMakeContextCurrent(window);

    /* check glew*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialize glew\n";
        glfwTerminate();
    }

    /* shader */
    /* vertex */
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex, 1, &VertexShaderData, NULL);
    glCompileShader(vertex);

    int success;
    char infolog[1024];

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex, 1024, NULL, infolog);
        std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
    }

    /* fragment */
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment, 1, &FragmentShaderData, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment, 1024, NULL, infolog);
        std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
    }

    /* program */
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infolog);
        std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    /* buffers */
    unsigned int VBO,VAO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    /* position attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    /* game loop */
    while (!glfwWindowShouldClose(window))
    {
        /* update */
        //变更颜色
        glUniform1f(glGetUniformLocation(program, "xColor"), 1.0f);//r
        glUniform1f(glGetUniformLocation(program, "yColor"), 1.0f);//g
        glUniform1f(glGetUniformLocation(program, "zColor"), 0.1f);//b

        /* render */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,6);

        //线组描绘
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* display */
        glfwSwapBuffers(window);

        /* pollevents */
        //glfwPollEvents();

    }

    /* clear */
    glfwDestroyWindow(window);
    glfwTerminate();


    /*
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/
    return 0;
}
</code></pre>

p14

sin cos 渐变颜色
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
float vertices[] =
{
	/* position */
	-0.5f,-0.5f ,0.0f, // botoom left
	 0.5f,-0.5f, 0.0f, // bottom right
	 0.5f, 0.5f, 0.0f, // up right

	 0.5f, 0.5f, 0.0f, // up right
	-0.5f, 0.5f, 0.0f, // up left
	-0.5f,-0.5f ,0.0f, // botoom left
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{"
"   gl_Position = vec4(aPos, 1.0f);"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform float xColor;\n"
"uniform float yColor;\n"
"uniform float zColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(xColor,yColor,zColor,1.0f);\n"
"}\0";

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* shader */
	/* vertex */
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &VertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}

	/* fragment */
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &FragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	/* program */
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	/* buffers */
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		//变更颜色
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;//正弦值使得颜色不断渐变 0.0f - 1.0f
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		glUniform1f(glGetUniformLocation(program, "xColor"), xValue);//动态渐变
		glUniform1f(glGetUniformLocation(program, "yColor"), yValue);//动态渐变
		glUniform1f(glGetUniformLocation(program, "zColor"), zValue);//动态渐变
		//glUniform1f(glGetUniformLocation(program, "xColor"), 1.0f);//r
		//glUniform1f(glGetUniformLocation(program, "yColor"), 1.0f);//g
		//glUniform1f(glGetUniformLocation(program, "zColor"), 0.1f);//b

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//线组描绘
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		//glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();


	/*
	GLFWwindow* window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();*/
	return 0;
}
</code></pre>

p15

七彩渐变
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   outColor = aColor;\n"
"   gl_Position = vec4(aPos, 1.0f);\n"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(outColor.x,outColor.y,outColor.z,1.0f);\n"
"}\0";

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* shader */
	/* vertex */
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &VertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}

	/* fragment */
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &FragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	/* program */
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	/* buffers */
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//线组描绘
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		//glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();


	/*
	GLFWwindow* window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();*/
	return 0;
}
</code></pre>

p16

七彩渐变
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   ourColor = aColor;\n"
"   gl_Position = vec4(aPos, 1.0f);\n"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(ourColor.x,ourColor.y,ourColor.z,1.0f);\n"
"}\0";

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* shader */
	/* vertex */
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &VertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}

	/* fragment */
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &FragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	/* program */
	GLuint program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		//glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
</code></pre>

p17

着色器类
shader.h
<pre><code>
#pragma once

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
private:
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	const char* vertexShaderData, * fragmentShaderData;
	unsigned int vertex, fragment;
public:
	unsigned int ID;

	//constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	//utility uniforms
	void setFloat(const std::string& name, float value)const;
	void setInt(const std::string& name, float value)const;
};
</code></pre>
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   ourColor = aColor;\n"
"   gl_Position = vec4(aPos, 1.0f);\n"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(ourColor.x,ourColor.y,ourColor.z,1.0f);\n"
"}\0";

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* shader */
	/* vertex */
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &VertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}

	/* fragment */
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &FragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	/* program */
	GLuint program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		glUniform1f(glGetUniformLocation(program, "xColor"), xValue);



		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		//glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
</code></pre>

p18

shader.cpp
<pre><code>
#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open the files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// read the files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// close the files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// read as a string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	};
	catch (std::ifstream::failure e)
	{
		std::cout << "FAILED::FILES::TO_READ\n";
		glfwTerminate();
		return;
	}
}
</code></pre>
shader.h
<pre><code>
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
private:
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	std::stringstream vertexShaderStream, fragmentShaderStream;
	const char* vertexShaderData, * fragmentShaderData;
	unsigned int vertex, fragment;
public:
	unsigned int ID;

	//constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	//utility uniforms
	void setFloat(const std::string& name, float value)const;
	void setInt(const std::string& name, int value)const;
};
</code></pre>
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

const char* VertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   ourColor = aColor;\n"
"   gl_Position = vec4(aPos, 1.0f);\n"
"}\0";

const char* FragmentShaderData =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(ourColor.x,ourColor.y,ourColor.z,1.0f);\n"
"}\0";

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* shader */
	/* vertex */
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &VertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}

	/* fragment */
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &FragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	/* program */
	GLuint program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		glUniform1f(glGetUniformLocation(program, "xColor"), xValue);



		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		//glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
</code></pre>

//注:p18与p19中丢失了shader class3 p19内容可能存在一定差异

p19

渐变颜色动效三角形
fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform float xColor;

void main()
{
	FragColor = vec4(xColor * ourColor.x, ourColor.y, ourColor.z, 1.0f);
}
</code></pre>
vertexShader.glsl
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
	ourColor = aColor;
	gl_Position = vec4(aPos, 1.0f);
}
</code></pre>
Shader.h
<pre><code>
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
private:
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	std::stringstream vertexShaderStream, fragmentShaderStream;
	const char* vertexShaderData, * fragmentShaderData;
	unsigned int vertex, fragment;
public:
	unsigned int ID;

	//constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	//use
	void use();

	//utility uniforms
	void setFloat(const std::string& name, float value)const;
	void setInt(const std::string& name, int value)const;
};
</code></pre>
Shader.cpp
<pre><code>
#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open the files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// read the files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// close the files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// read as a string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "FAILED::FILES::TO_READ\n";
		glfwTerminate();
		return;
	}

	//read as a const char
	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();

	//vertex
	this->vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog   << std::endl;
	}
	//fragment
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog <<">"<< std::endl;
	}

	//program
	this->ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	if (!success)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setFloat(const std::string& name, float value)const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value)const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
</code></pre>
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "src/Shader.h"
float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		myShader.setFloat("xColor", xValue);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}
</code></pre>
相对位置
![](../assets/2022-04-22-22-41-15.png)

p20

无级调节
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "src/Shader.h"

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		myShader.setFloat("xColor", xValue);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
</code></pre>

p21

输入
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "src/Shader.h"

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype


int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		myShader.setFloat("xColor", xValue);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		std::cout << "w has been pressed \n";
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
</code></pre>

p22

鼠标响应 报光标位置
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "src/Shader.h"

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		myShader.setFloat("xColor", xValue);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		std::cout << "w has been pressed \n";
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "mouse cursor has been moved\n";
	std::cout << "positon :" << xpos << " " << ypos << std::endl;
}
</code></pre>

p23

鼠标滚轮
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "src/Shader.h"

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		myShader.setFloat("xColor", xValue);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		std::cout << "w has been pressed \n";
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "mouse cursor has been moved\n";
	std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << "scroll has been\n";
	std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>

p24

GLM
![](../assets/2022-04-23-14-32-43.png)

p25

添加GLM库 且改为相对路径
![](../assets/2022-04-23-14-41-34.png)
![](../assets/2022-04-23-14-44-16.png)
<pre><code>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
</code></pre>

p28

GLM vector应用
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		//glUniform3f(glGetUniformLocation(myShader.ID, "colors"), 1.0f, 0.5f, 0.31f);
		glUniform3fv(glGetUniformLocation(myShader.ID, "colors"), 1, glm::value_ptr(myVector));

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>
fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform vec3 colors;

void main()
{
	FragColor = vec4(colors, 1.0f);
}
</code></pre>

set up shader class 应用
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);
		//glUniform3f(glGetUniformLocation(myShader.ID, "colors"), 1.0f, 0.5f, 0.31f);
		//glUniform3fv(glGetUniformLocation(myShader.ID, "colors"), 1, glm::value_ptr(myVector));

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>
Shader.h
<pre><code>
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	std::stringstream vertexShaderStream, fragmentShaderStream;
	const char* vertexShaderData, * fragmentShaderData;
	unsigned int vertex, fragment;
public:
	unsigned int ID;

	//constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	//use
	void use();

	//utility uniforms
	void setFloat(const std::string& name, float value)const;
	void setInt(const std::string& name, int value)const;
	void setVec3(const std::string& name, float x, float y, float z);
	void setVec3(const std::string& name, const glm::vec3& value);
};
</code></pre>
Shader.cpp
<pre><code>
#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open the files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// read the files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// close the files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// read as a string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "FAILED::FILES::TO_READ\n";
		glfwTerminate();
		return;
	}

	//read as a const char
	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();

	//vertex
	this->vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog   << std::endl;
	}
	//fragment
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog <<">"<< std::endl;
	}

	//program
	this->ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	if (!success)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setFloat(const std::string& name, float value)const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value)const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}

</code></pre>

p29

matrix
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,

	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,

};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);
		//glUniform3f(glGetUniformLocation(myShader.ID, "colors"), 1.0f, 0.5f, 0.31f);
		//glUniform3fv(glGetUniformLocation(myShader.ID, "colors"), 1, glm::value_ptr(myVector));

		//matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
		myShader.setMat4("model", model);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>
Shader.h
<pre><code>
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	std::stringstream vertexShaderStream, fragmentShaderStream;
	const char* vertexShaderData, * fragmentShaderData;
	unsigned int vertex, fragment;
public:
	unsigned int ID;

	//constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	//use
	void use();

	//utility uniforms
	void setFloat(const std::string& name, float value)const;
	void setInt(const std::string& name, int value)const;
	void setVec3(const std::string& name, float x, float y, float z);
	void setVec3(const std::string& name, const glm::vec3& value);

	void setMat4(const std::string& name, const glm::mat4& value);
};
</code></pre>
Shade.cpp
<pre><code>
#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open the files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// read the files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// close the files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// read as a string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "FAILED::FILES::TO_READ\n";
		glfwTerminate();
		return;
	}

	//read as a const char
	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();

	//vertex
	this->vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}
	//fragment
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	//program
	this->ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	if (!success)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setFloat(const std::string& name, float value)const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value)const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
</code></pre>
vertexShader
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 model;

void main()
{
	ourColor = aColor;
	gl_Position = model * vec4(aPos, 1.0f);
}
</code></pre>
fragmentShader
<pre><code>
#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform vec3 colors;

void main()
{
	FragColor = vec4(colors, 1.0f);
}
</code></pre>

p30

translate
mian.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,

	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,

};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

glm::mat4 model;
glm::vec3 myPos = glm::vec3(1.0f);

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);

		//matrix
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		//model = glm::translate(model, glm::vec3(xValue,yValue,0.0f));//移动
		model = glm::translate(model, glm::vec3(myPos));//移动
		myShader.setMat4("model", model);


		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
		
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)
		myPos.y += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
		myPos.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
		myPos.x += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
		myPos.x -= 0.005f;
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>

p31

rotate
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,

	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,

};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

glm::mat4 model;
glm::vec3 myPos = glm::vec3(1.0f);

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);

		//matrix
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		//model = glm::translate(model, glm::vec3(xValue,yValue,0.0f));//移动
		model = glm::translate(model, glm::vec3(myPos));//移动
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)
		myPos.y += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
		myPos.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
		myPos.x += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
		myPos.x -= 0.005f;
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>

p32

描绘两个图形
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,

	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,

};

void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

glm::mat4 model;
glm::vec3 myPos = glm::vec3(1.0f);

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);

		//matrix
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		model = glm::translate(model, glm::vec3(myPos));//移动
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		model = glm::translate(model, glm::vec3(-0.5f, -0.2f, 0.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)
		myPos.y += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
		myPos.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
		myPos.x += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
		myPos.x -= 0.005f;
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>

p33

setup stb_image
![](../assets/2022-04-23-23-38-08.png)
![](../assets/2022-04-23-23-38-31.png)
github -> stb_image.h

stb_image.cpp
<pre><code>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
</code></pre>

p34

fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;

void main()
{
	FragColor = vec4(colors, 1.0f);
}
</code></pre>
vertexShader.glsl
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec3 ourColor;
out vec2 TexCoords;

uniform mat4 model;

void main()
{
	TexCoords = aTexCoords;
	ourColor = aColor;
	gl_Position = model * vec4(aPos, 1.0f);
}
</code></pre>
main.cpp 开头
<pre><code>

float vertices[] =
{
	/* position */		/* color */			/* TexCoords */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f,0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,		1.0f,0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f,1.0f,

	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f,1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,		0.0f,1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f,0.0f,

};

</code></pre>

p35

texture
![](../assets/2022-04-24-15-29-06.png)
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"
#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */			/* TexCoords */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
												  
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,		0.0f, 1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,

};



void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype

glm::mat4 model;
glm::vec3 myPos = glm::vec3(1.0f);

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* texture attribute */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);

		//matrix
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		model = glm::translate(model, glm::vec3(myPos));//移动
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		model = glm::translate(model, glm::vec3(-0.5f, -0.2f, 0.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)
		myPos.y += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
		myPos.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
		myPos.x += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
		myPos.x -= 0.005f;
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}
</code></pre>

p36

加载图片
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"
#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */			/* TexCoords */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
												  
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,		0.0f, 1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,

};



void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype


unsigned int load_texture(const char* texture_path);//protype


glm::mat4 model;
glm::vec3 myPos = glm::vec3(0.0f);

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* texture attribute */
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* texture */
	GLuint texture = load_texture("res/Texture/container.jpg");

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	myShader.use();
	myShader.setInt("texture1", 0);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);

		//matrix
		model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		model = glm::translate(model, glm::vec3(myPos));//移动
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		//model = glm::translate(model, glm::vec3(-0.5f, -0.2f, 0.0f));
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		//myShader.setMat4("model", model);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)
		myPos.y += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
		myPos.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
		myPos.x += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
		myPos.x -= 0.005f;
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	/* filters */
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
</code></pre>
fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoords);
}
</code></pre>

p37

正常显示PNG图(若无指令会镜像)
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"
#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */			/* TexCoords */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
												  
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,		0.0f, 1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,

};



void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype


unsigned int load_texture(const char* texture_path);//protype


glm::mat4 model;
glm::vec3 myPos = glm::vec3(0.0f);

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* texture attribute */
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* texture */
	stbi_set_flip_vertically_on_load(true);
	GLuint texture = load_texture("res/Texture/awesomeface.png");

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	myShader.use();
	myShader.setInt("texture1", 0);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		myVector.x = 1.0f;
		myVector.y = 0.5f;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);

		//matrix
		model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		model = glm::translate(model, glm::vec3(myPos));//移动
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		//model = glm::translate(model, glm::vec3(-0.5f, -0.2f, 0.0f));
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		//myShader.setMat4("model", model);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)
		myPos.y += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
		myPos.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
		myPos.x += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
		myPos.x -= 0.005f;
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	/* filters */
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
</code></pre>

p38

png jpg 混动效果
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "src/Shader.h"
#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] =
{
	/* position */		/* color */			/* TexCoords */
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f, 0.0f,	0.0f,1.0f,0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
												  
	 0.5f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f ,0.0f,	1.0f,0.0f,1.0f,		0.0f, 1.0f,
	-0.5f,-0.5f ,0.0f,	1.0f,0.0f,0.0f,		0.0f, 0.0f,

};



void framebuffers_size_callback(GLFWwindow* window, int width, int height);//protype
void userInput(GLFWwindow* window);//protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);//protyepe
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);//protype


unsigned int load_texture(const char* texture_path);//protype


glm::mat4 model;
glm::vec3 myPos = glm::vec3(0.0f);

int main(void)
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//mac if
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//create a window 窗口大小
	GLFWwindow* window = glfwCreateWindow(1000, 800, "OpenGL 3.3", NULL, NULL);

	//check window 检查
	if (!window)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
	}

	/* the most inportant part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffers_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	/* check glew*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		glfwTerminate();
	}

	/* buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* texture attribute */
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* texture */
	stbi_set_flip_vertically_on_load(true);
	//GLuint texture = load_texture("res/Texture/awesomeface.png"); // png
	GLuint texture = load_texture("res/Texture/container.jpg"); // jpg

	/* shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	myShader.use();
	myShader.setInt("texture1", 0);

	/* game loop */
	while (!glfwWindowShouldClose(window))
	{
		/* update */
		userInput(window);
		float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		//vector
		glm::vec3 myVector;
		//myVector.x = 1.0f;
		//myVector.y = 0.5f;
		myVector.x = xValue;
		myVector.y = yValue;
		myVector.z = 0.31f;

		myShader.setVec3("colors", myVector);

		//matrix
		model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		model = glm::translate(model, glm::vec3(myPos));//移动
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		myShader.setMat4("model", model);

		/* render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);//0.0f - 1.0f
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//scale
		//model = glm::translate(model, glm::vec3(-0.5f, -0.2f, 0.0f));
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(xValue, yValue, 0.0f));
		//myShader.setMat4("model", model);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		/* display */
		glfwSwapBuffers(window);

		/* pollevents */
		glfwPollEvents();

	}

	/* clear */
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffers_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	std::cout << "w has been pressed \n";
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)
		myPos.y += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
		myPos.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
		myPos.x += 0.005f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
		myPos.x -= 0.005f;
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "mouse cursor has been moved\n";
	//std::cout << "positon :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll has been\n";
	//std::cout << "positon :" << xoffset << " " << yoffset << std::endl;
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	/* filters */
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // png
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // jpg
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
</code></pre>
fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoords)*vec4(ourColor*colors,1.0f);
}
</code></pre>

p39

format 后续代码不再传入 仅做笔记
GLenum format
format=GL_RED
format=GL_RGB;//jpg
format=GL_RGBA;//png
传入glTexImage2D函数 不需要修改参数可以直接定义图片的不同类型

p40

split texture
修改TexCoords矩阵 变更图片的展示样式

p41

修改TexCoords矩阵 变更图片的展示个数样式

p42

f.glsl的texture函数实现翻转

p43

mipmaps

p44

filter options 过滤器 应该是滤波
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
GL_TEXTURE_WRAP_S,GL_REPEAT
GL_TEXTURE_WRAP_T,GL_REPEAT
GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST
GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST

p45

mix texture 混合
(f.glsl)FragColor=mix(texture(container_texture,TexCorrds),texture(facee_texture,TexCoords),0.2);

p46

slmple quiz
(f.glsl)FragColor=mix(texture(container_texture,TexCorrds),texture(facee_texture,TexCoords*2),0.2);
乘上系数之后变得展示矩阵
(f.glsl)FragColor=mix(texture(container_texture,TexCorrds),texture(facee_texture,TexCoords*2),-alpha);
阴间..

p47

triangle texture
(f.glsl)FragColor=mix(texture(container_texture,TexCorrds),texture(facee_texture,TexCoords*2),alpha)*vec4(outColor,1.0f);
改变矩阵数量和读取数即可

p48

coordinate system坐标系
normalized device coordinates=NDC
1.local space
2.world space
3.view space
4.clip space
5.screen space

matrices
1.model
2.projection
3.view

![](../assets/2022-04-24-19-43-16.png)
![](../assets/2022-04-24-19-44-40.png)
V clip=M projection M view M model V local

p49

jumping to 3d coordinate
(v.glsl)gl_Position=projection*view*model*vec4(aPos,1.0f);
main.cpp
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;
glm::vec3 myPos=glm::vec3(0.0f);
//projection
projection=glm::perspective(glm::radians(45.0f),float(1000)/float(800),0.1f,100.f);
myShader.setMat4("projection",projection);

//view
view=glm::mat(1.0f);
view=glm::translate(view,glm::vec(0.0f,0.0f,-3.0f));
my.Shader.setMat("view",view);

//model
model=glm::mat4(1.0f);
model=glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f,0.0f,0.0f));
model=glm::translate(model,glm::vec3(myPos));
myShader.setMat4("model",model);

p50

cube
main.cpp
vertices[]定义
// options
glEnable(GL_DEPTH_TEST);

//清除缓存
glClear(GL_DEPTH_BUFFER_BIT);

p51

pyramid 锥体
main.cpp
vertices[]定义
读取图片 渲染
f.glsl 相应修改

p52

line width
glPolygonMode(GL_FLOAT_AND_BACK,GL_LINE);
glDrawArrays(GL_TRIANGLE_FAN,0,36);
//GL_LINE_ + LOOP/STRIP

p53

多目标
glm::vec3 pro[]={}
glm::translate移动
glm::rotate旋转

p54

glm::lookat观式朝向

p55

walk around
glm::normalize(glm::cross(cameraFront,cameraUP))*camera_speed;

p56

smooth moving
平滑移动可以依靠
float deltaTime=0.0f,lastFrame=0.0f;
deltaTime=time-lastFrame;
lastFrame=time;

p57

look around
平滑观察
float pitch=0.0f,yaw=-90.0f,lastX=float(SCR_WIDTH)/2.0f,lastY=float(SCR_HEIGHT)/2.0f;
bool isFirstMouse=true;
void moust_cursor_position(GLFWwindow* window,double xpos,double ypos){
	if(isFirstMouse){
		lastX=xpos;
		lastY=ypos;
		isFirstMouse=false;
	}
	float xoffset=xpos-lastX;
	float yoffset=lastY-ypos;
	lastX=xpos;
	lastY=ypos;

	float sensitivity=0.1f;

	xoffset*=sensitivity;
	yoffset*=sensitivity;

	yaw+=xoffset;
	pitch+=yoffset;
	if(pitch>=89.0f)
		pitch=89.0f;
	if(pitch<=-89.0f)
		pitch=-89.0f;

	glm::vec3 direction;
	direction.x=std::cos(glm::radians(yaw))*std::cos(glm::radians(pitch));
	direction.y=std::sin(glm::radians(pitch));
	direction.z=std::sin(glm::radians(yaw))*std::cos(glm::radians(pitch));
	cameraFrong=glm::normalize(direction);
}
glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

p58

zoom
float zoom=45.0f;
void mouse_scroll_position(GLFWwindow* window,double xoffset,doule yoffset){
	zoom-=folat(yoffset);
	if(zoom>=45.0f)
		zoom=45.0f;
	if(zoom<=20.0f)
		zoom=20.0f;
}

p59

camera class
set
Camera.hpp
<pre><code>
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Directions
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = -0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

using namespace glm;
using namespace std;

class Camera {
public:
	//Camera Attributes
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 WorldUp;
	vec3 Right;

	// Eular Angles
	float Yaw;
	float Pitch;
	//Camera Options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// constructor with vectors
	Camera(vec3 position = vec3(0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		updateCameraVectors();
	}

	mat4 GetViewMatrix()
	{
		return lookAt(this->Position, this->Position + this->Front, this->Up);
	}

	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		if (this->Pitch >= 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch <= -89.0f)
			this->Pitch = -89.0f;

		updateCameraVectors();
	}
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		const float velocity = this->MovementSpeed * deltaTime;
		if (direction == FORWARD)
			this->Position += this->Front * velocity;
		if (direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == UP)
			this->Position += this->Up * velocity;
		if (direction == DOWN)
			this->Position -= this->Up * velocity;
	}
	void ProcessMouseScroll(float yoffset)
	{
		this->Zoom -= float(yoffset);
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
		if (Zoom <= 20.0f)
			Zoom = 20.0f;
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 direction;
		direction.x = std::cos(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		direction.y = std::sin(glm::radians(this->Pitch));
		direction.z = std::sin(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(direction);

		// Alsom re-calculate for Right and Up vectors
		this->Right = normalize(cross(this->Front, this->WorldUp));
		this->Up = normalize(cross(this->Right, this->Front));
	}
};
</code></pre>

p62

setup dear imgui
同前几lib方式

p63

first GUI
/* Render */
glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* Start new frame for Dear ImGui */
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();

myShader.use();

// Render your GUI
ImGui::Begin("Its My First GUI"); // Note: it's better not to use ' (quotes) inside the double quotes
ImGui::Text("Hello ppl wassup");
ImGui::End();

// Render to screen
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//Display
glfwSwapBuffers(window);
//Pollevents
glfwPollEvents();

/* Clear */
ImGui_ImplGlfw_Shutdown();
ImGui_ImplOpenGL3_Shutdown();
ImGui::DestroyContext();
glfwDestroyWindow(window);
glfwTerminate();
// Render your GUI
ImGui::Begin("Its My First GUI"); // Note: it's better not to use ' (quotes) inside the double quotes
ImGui::Text("Hello ppl wassup");
ImGui::End();

p64

demo gui window
// ShowDemo
bool ShowDemo = true;

if (ShowDemo)
	ImGui::ShowDemoWindow(&ShowDemo);

p65

gragfloat

// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::DragFloat("Scale", &scale_value, 0.1f,  0.01f, 5.0f);
ImGui::End();

// Model
static float scale_value = 1.2f;
model = glm::mat4(1.0f);
model = glm::scale(model, glm::vec3(scale_value));
myShader.setMat4("model", model);

p66

DF 2-3

// Model
static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
model = glm::mat4(1.0f);
model = glm::scale(model, glm::vec3(scale_value[0], scale_value[1], scale_value[2]));
myShader.setMat4("model", model);

// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::End();

p67

silderfloat
// GUI Variables
static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
static float color_value[3] = { 1.0f ,1.0f , 1.0f };
myShader.setVec3("colors", color_value[0], color_value[1], color_value[2]);

/* Render */
glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* Start new frame for Dear ImGui */
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();

// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::SliderFloat3("Color", color_value,0.0f, 1.0f);
ImGui::End();

p68

color edit
// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::ColorEdit3("Color", color_value);
ImGui::End();

p69

checkbox
fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;

uniform sampler2D container_texture;
uniform sampler2D face_texture;

uniform float alpha;

void main()
{
	FragColor = vec4(colors,1.0f);
}
</code></pre>

// GUI Variables
static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
static float color_value[3] = { 1.0f ,1.0f , 1.0f };
static bool isTexture = false;
myShader.setVec3("colors", color_value[0], color_value[1], color_value[2]);
myShader.setBool("isTexture", isTexture);

// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::ColorEdit3("Color", color_value);
ImGui::Checkbox("Texture", &isTexture);
ImGui::End();


p70

checkbox2 颜色修正等

fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform bool isTexture;
uniform bool isColor;

uniform vec3 colors;

uniform sampler2D container_texture;
uniform sampler2D face_texture;

uniform float alpha;

void main()
{
	if (isTexture && isColor)
		FragColor = texture(container_texture, TexCoords) * vec4(colors,1.0f);
	else if(isTexture && !isColor)
		FragColor = texture(container_texture, TexCoords);
	else if(!isTexture && isColor)
		FragColor = vec4(colors,1.0f);
	else
		FragColor = vec4(1.0f);
}
</code></pre>
// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::Checkbox("Texture", &isTexture);
ImGui::Checkbox("Color", &isColor);
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::ColorEdit3("Color", color_value);
ImGui::End();

p71

add alpha
f-glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform bool isTexture;
uniform bool isColor;

uniform vec3 colors;

uniform sampler2D container_texture;
uniform sampler2D face_texture;

uniform float alpha;

void main()
{
	if (isTexture && isColor)
		FragColor = mix(texture(container_texture, TexCoords), texture(face_texture, TexCoords), alpha) * vec4(colors,1.0f);
	else if(isTexture && !isColor)
		FragColor = mix(texture(container_texture, TexCoords), texture(face_texture, TexCoords), alpha);
	else if(!isTexture && isColor)
		FragColor = vec4(colors,1.0f);
	else
		FragColor = vec4(1.0f);
}
</code></pre>

// Gui Variables
static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
static float color_value[3] = { 1.0f,1.0f,1.0f };
static bool isTexture = false;
static float alpha = 0.2f;

static bool isColor = false;
myShader.setVec3("colors", color_value[0], color_value[1], color_value[2]);
myShader.setBool("isColor", isColor);
myShader.setBool("isTexture", isTexture);
myShader.setFloat("alpha", alpha);

// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::Checkbox("Color", &isColor);
ImGui::Checkbox("Texture", &isTexture);
ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::ColorEdit3("Color", color_value);
ImGui::End();

p72

slider angle 滑动块
// Gui Variables
static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
static float color_value[3] = { 1.0f,1.0f,1.0f };
static float rotate_value[3] = { 1.0f,1.0f,1.0f };
static float angle = -55.0f;
static bool isTexture = false;
static float alpha = 0.2f;

static bool isColor = false;
myShader.setVec3("colors", color_value[0], color_value[1], color_value[2]);
myShader.setBool("isColor", isColor);
myShader.setBool("isTexture", isTexture);
myShader.setFloat("alpha", alpha);

// Model
model = glm::mat4(1.0f);
model = glm::scale(model, glm::vec3(scale_value[0], scale_value[1], scale_value[2]));
model = glm::rotate(model, glm::radians(-55.0f) * angle  ,glm::vec3(rotate_value[0], rotate_value[1], rotate_value[2]));
myShader.setMat4("model", model);

// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::Checkbox("Color", &isColor);
ImGui::Checkbox("Texture", &isTexture);
ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::SliderFloat3("Rotate", rotate_value, 0.01f, 1.0f);
ImGui::SliderAngle("Angle", &angle);
ImGui::ColorEdit3("Color", color_value);
ImGui::End();

p73

ini file
ini设置文件
/* ImGui */
// Setup Dear ImGui context
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO();
io.IniFilename="ini_file.ini";//io存储ini文件

p74

button
// Render your GUI
ImGui::Begin("It's My First GUI");
ImGui::Text("Hello ppl wassup");
ImGui::Checkbox("Color", &isColor);
ImGui::Checkbox("Texture", &isTexture);
ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::SliderFloat3("Rotate", rotate_value, 0.01f, 1.0f);
ImGui::SliderAngle("Angle", &angle);
ImGui::ColorEdit3("Color", color_value);
if (ImGui::Button("Hey press me"))
{
	ShowDemo = true;
}
ImGui::End();

p75

button2
// Some window
bool ShowDemo = false;
bool mySecondWindow = false;

if (mySecondWindow)
{
	ImGui::Begin("GUI 2");
	ImGui::Text("Hey im a window here.");
	if (ImGui::Button("close me"))
		mySecondWindow = false;
	ImGui::End();
}

// Render your GUI
ImGui::Begin("GUI");
ImGui::Text("Hello ppl wassup");
ImGui::Checkbox("Texture", &isTexture);
ImGui::Checkbox("Color", &isColor);
ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::SliderFloat3("Rotate", rotate_value, 0.01f, 1.0f);
ImGui::SliderAngle("Angle", &angle);
ImGui::ColorEdit3("Color", color_value);
if (ImGui::Button("Demo"))
{
	ShowDemo = true;
}
if (ImGui::Button("Window"))
{
	mySecondWindow = true;
}
ImGui::End();

p76

fps
// Render your GUI
float FPS = ImGui::GetIO().Framerate;
ImGui::Begin("GUI");
ImGui::Text("FPS = %f", FPS);
ImGui::Checkbox("Texture", &isTexture);
ImGui::Checkbox("Color", &isColor);
ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::SliderFloat3("Rotate", rotate_value, 0.01f, 1.0f);
ImGui::SliderAngle("Angle", &angle);
ImGui::ColorEdit3("Color", color_value);
if (ImGui::Button("Demo"))
{
	ShowDemo = true;
}
if (ImGui::Button("Window"))
{
	mySecondWindow = true;
}
ImGui::End();

p77

sameline
// Render your GUI
float FPS = ImGui::GetIO().Framerate;
ImGui::Begin("GUI");
ImGui::Text("FPS = %f", FPS);
ImGui::Checkbox("Texture", &isTexture);
ImGui::SameLine();
ImGui::Checkbox("Color", &isColor);
ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);
ImGui::DragFloat3("Scale", scale_value, 0.1f, 0.01f, 5.0f);
ImGui::SliderFloat3("Rotate", rotate_value, 0.01f, 1.0f);
ImGui::SliderAngle("Angle", &angle);
ImGui::ColorEdit3("Color", color_value);
if (ImGui::Button("Demo"))
{
	ShowDemo = true;
}
ImGui::SameLine();
if (ImGui::Button("Window"))
{
	mySecondWindow = true;
}
ImGui::End();

// Setup style 颜色风格
ImGui::StyleColorsDark();

p79

code clean up
main
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1000
#define SCR_HEIGHT 800
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

float vertices[] =
{
	/* Top Position */		/* Color */				/* TexCoords */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Bottom Position */	/* Color */				/* TexCoords */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Left Position */		/* Color */				/* TexCoords */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Right Position */	/* Color */				/* TexCoords */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 /* Back Position */	/* Color */				/* TexCoords */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	/* Front Position */	/* Color */				/* TexCoords */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,

};

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype
unsigned int load_texture(const char* texture_path); // Protype

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;


/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* Color Attribute*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Texture Attribute */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* Texture */
	stbi_set_flip_vertically_on_load(true);
	

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	myShader.use();

	// Some window
	

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 5.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables
		

		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		// Model
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f) , glm::vec3(1.0f, 0.0f, 0.0f));
		myShader.setMat4("model", model);

		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		
		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Render your GUI

		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
</code></pre>
f-glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

void main()
{
	FragColor = vec4(1.0f, 0.4f, 0.31f ,1.0f);
}
</code></pre>

p80

light cube shader

/* Light Buffers */
GLuint lightCubeVBO, lightCubeVAO;

glGenVertexArrays(1, &lightCubeVAO);
glGenBuffers(1, &lightCubeVBO);

glBindVertexArray(lightCubeVAO);
glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

/* Light Position Attribute */
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

/* Shader */
Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
Shader lightCubeShader("res/Shader/vertexShader.glsl", "res/Shader/LightCube.frag");
myShader.use();

lightCube.frag
<pre><code>
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f);
}
</code></pre>


// Second Object
lightCubeShader.use();
lightCubeShader.setMat4("projection", projection);
lightCubeShader.setMat4("view", view);

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);

// Model
model = glm::mat4(1.0f);
model = glm::translate(model, lightPos);
model = glm::scale(model, glm::vec3(0.3f));
lightCubeShader.setMat4("model", model);
glBindVertexArray(lightCubeVAO);
glDrawArrays(GL_TRIANGLES, 0, 36);

// View
view = glm::mat4(1.0f);
view = camera.GetViewMatrix();
myShader.setMat4("view", view);

p81

light and object color
f-glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	vec3 result = lightColor * objectColor;
	FragColor = vec4(result,1.0f);
}
</code></pre>
LightCube.vert
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{	
	gl_Position = projection * view * model * vec4(aPos , 1.0f);
}
</code></pre>

// First Object
myShader.use();
myShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
myShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);

/* Shader */
Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
myShader.use();

p82

normals常量
ambient环境
diffuse扩散
Specular镜面反射
Shininess光照
Moving Around Object环绕
Transpose and Inverse转置和逆
<pre><code>#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float shininess;

void main()
{
	// Ambient
	float ambientStrength = 0.2f;
	vec3 ambient = lightColor * ambientStrength;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos-fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = lightColor * diff;

	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), shininess);
	vec3 specular = lightColor * spec * specularStrength;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result,1.0f);
}
</code></pre>
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
	ourColor = aColor;
	fragPos = vec3(model * vec4(aPos,1.0f));
	gl_Position = projection * view * model  * vec4(aPos, 1.0f);
}
</code></pre>
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1000
#define SCR_HEIGHT 800
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

float vertices[] =
{
	/* Top Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	/* Bottom Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	/* Left Position */		/* Color */			/* TexCoords */	    	/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	/* Right Position */		/* Color */			/* TexCoords */	   	 /* Normals */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 /* Back Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f,
	/* Front Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,

};
/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype
unsigned int load_texture(const char* texture_path); // Protype

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);


/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Cube Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position Attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Attribute 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Normals Attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	/* Light Buffers */
	GLuint lightCubeVBO, lightCubeVAO;

	glGenVertexArrays(1, &lightCubeVAO);
	glGenBuffers(1, &lightCubeVBO);

	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Light Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/* Texture */

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
	myShader.use();

	// Some window
	bool ShowDemo = false;
	bool mySecondWindow = false;

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 3.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables
		static float shininess = 32.0f;



		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// First Object
		myShader.use();

		// Light
		myShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		myShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		myShader.setVec3("lightPos", lightPos);
		myShader.setVec3("viewPos", camera.Position);
		myShader.setFloat("shininess", shininess);

		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		// Model
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(0.7f, 1.0f, 0.0f));
		myShader.setMat4("model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Second Object
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		// Model
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.3f));
		lightCubeShader.setMat4("model", model);
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Render your GUI
		ImGui::Begin("Light test");
		ImGui::SliderFloat("shininess", &shininess, 0.0f, 600.0f);
		ImGui::End();

		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
</code></pre>

p90

materials struct
f-glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};

uniform Material material;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// Ambient
	vec3 ambient = lightColor * material.ambient;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos-fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = lightColor * (diff * material.diffuse);

	// Specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	vec3 specular = lightColor * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0f);
}
</code></pre>

// Material
myShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
myShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
myShader.setVec3("material.specular", glm::vec3(0.5f));
myShader.setFloat("material.shininess", 64.0f);

p91

light struct
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	// Ambient
	vec3 ambient = light.ambient * material.ambient;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position-fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// Specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0f);
}
</code></pre>

// Light
myShader.setVec3("light.position", lightPos);
myShader.setVec3("viewPos", camera.Position);
myShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
myShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
myShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

p92

material and light with gui

// Gui Variables
static float material_ambient[3] = { 1.0f, 0.5f, 0.31f };
static float material_diffuse[3] = { 1.0f, 0.5f, 0.31f };
static float material_specular[3] = { 0.5f, 0.5f, 0.5f };
static float material_shininess = 64.0f;
static float light_ambient[3] = { 0.2f ,0.2f, 0.2f };
static float light_diffuse[3] = { 0.5f ,0.5f, 0.5f };
static float light_specular[3] = { 1.0f ,1.0f, 1.0f };

// Light
myShader.setVec3("light.position", lightPos);
myShader.setVec3("viewPos", camera.Position);
myShader.setVec3("light.ambient", light_ambient[0], light_ambient[1], light_ambient[2]);
myShader.setVec3("light.diffuse", light_diffuse[0], light_diffuse[1], light_diffuse[2]);
myShader.setVec3("light.specular", light_specular[0], light_specular[1], light_specular[2]);

// Material
myShader.setVec3("material.ambient", material_ambient[0], material_ambient[1], material_ambient[2]);
myShader.setVec3("material.diffuse", material_diffuse[0], material_diffuse[1], material_diffuse[2]);
myShader.setVec3("material.specular", material_specular[0], material_specular[1], material_specular[2]);
myShader.setFloat("material.shininess", material_shininess);

// Render your GUI
ImGui::Begin("Light test");
ImGui::SliderFloat3("Material Ambient", material_ambient, 0.0f, 1.0f);
ImGui::SliderFloat3("Material Diffuse", material_diffuse, 0.0f, 1.0f);
ImGui::SliderFloat3("Material Specular", material_specular, 0.0f, 1.0f);
ImGui::SliderFloat("Material Shininess", &material_shininess, 0.0f, 600);
ImGui::SliderFloat3("Light Ambient", light_ambient, 0.0f, 1.0f);
ImGui::SliderFloat3("Light Diffuse", light_diffuse, 0.0f, 1.0f);
ImGui::SliderFloat3("Light Specular", light_specular, 0.0f, 1.0f);

ImGui::End();

p93

diffuse maps
v-glsl
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
	ourColor = aColor;
	fragPos = vec3(model * vec4(aPos,1.0f));
	gl_Position = projection * view * model  * vec4(aPos, 1.0f);
}
</code></pre>
f-glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{
	sampler2D diffuse;
	vec3 specular;

	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	// Ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords);

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position-fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);

	// Specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0f);
}
</code></pre>

// Material
myShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
myShader.setFloat("material.shininess", 64.0f);

/* Texture */
GLuint diffuseMap = load_texture("res/Texture/container2.png");

/* Shader */
Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
myShader.use();
myShader.setInt("material.diffuse", 0);

// Model
model = glm::mat4(1.0f);
//model = glm::rotate(model, glm::radians(-55.0f) * time , glm::vec3(0.0f, 1.0f, 0.0f));
myShader.setMat4("model", model);
glBindVertexArray(VAO);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, diffuseMap);
glDrawArrays(GL_TRIANGLES, 0, 36);

p94

specular map
fragmentShader.glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{
	
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	// Ambient
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position-fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);

	// Specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0f);
}
</code></pre>

/* Texture */
GLuint diffuseMap = load_texture("res/Texture/container2.png");
GLuint specularMap = load_texture("res/Texture/container2_specular.png");

/* Shader */
Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
myShader.use();
myShader.setInt("material.diffuse", 0);
myShader.setInt("material.specular", 1);

// Model
model = glm::mat4(1.0f);
//model = glm::rotate(model, glm::radians(-55.0f) * time , glm::vec3(0.0f, 1.0f, 0.0f));
myShader.setMat4("model", model);
glBindVertexArray(VAO);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, diffuseMap);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, specularMap);
glDrawArrays(GL_TRIANGLES, 0, 36);

p95

directional lights
Point Lights
Spot Light
Soft Spot Light
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1000
#define SCR_HEIGHT 800
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

float vertices[] =
{
	/* Top Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	/* Bottom Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	/* Left Position */		/* Color */			/* TexCoords */	    	/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	/* Right Position */		/* Color */			/* TexCoords */	   	 /* Normals */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 /* Back Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f,
	/* Front Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,

};
/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype

unsigned int load_texture(const char* texture_path); // Protype

glm::vec3 cubePositions[] =
{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);


/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Cube Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position Attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Attribute 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Normals Attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	/* Light Buffers */
	GLuint lightCubeVBO, lightCubeVAO;

	glGenVertexArrays(1, &lightCubeVAO);
	glGenBuffers(1, &lightCubeVBO);

	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Light Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/* Texture */
	GLuint diffuseMap = load_texture("res/Texture/container2.png");
	GLuint specularMap = load_texture("res/Texture/container2_specular.png");

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
	myShader.use();
	myShader.setInt("material.diffuse", 0);
	myShader.setInt("material.specular", 1);

	// Some window
	bool ShowDemo = false;
	bool mySecondWindow = false;

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 3.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables



		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// First Object
		myShader.use();

		//  Flashlights
		myShader.setVec3("light.position", camera.Position);
		myShader.setVec3("light.direction", camera.Front);
		myShader.setVec3("viewPos", camera.Position);
		myShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		myShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		myShader.setVec3("light.specular", 1.0f, 1.0f, 1.0);
		myShader.setFloat("light.constant", 1.0f);
		myShader.setFloat("light.linear", 0.09f);
		myShader.setFloat("light.quadratic", 0.032f);
		myShader.setFloat("light.cutOff", glm::cos(glm::radians(13.0f)));
		myShader.setFloat("light.outerCutOff", glm::cos(glm::radians(15.5f)));

		// Material
		myShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		myShader.setFloat("material.shininess", 64.0f);


		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		for (int i = 0; i < 10; i++)
		{
			// Model
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(cubePositions[i]));
			model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(0.0f, 1.0f, 0.0f));

			myShader.setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}


		// Second Object
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		// Model
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.3f));
		lightCubeShader.setMat4("model", model);
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Render your GUI
		ImGui::Begin("Light test");

		ImGui::End();

		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}

</code></pre>
f-glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{
	
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

struct Light{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float quadratic;
	float linear;
	float constant;

	float cutOff;
	float outerCutOff;

};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{

	
	
	// Ambient
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);

	// Specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);

	// Soft Edges
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	diffuse *= intensity;
	specular *= intensity;

	// Attenuation
	float Distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance,2));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0f);
	
}
</code></pre>
v-glsl
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
	ourColor = aColor;
	fragPos = vec3(model * vec4(aPos,1.0f));
	gl_Position = projection * view * model  * vec4(aPos, 1.0f);
}
</code></pre>

p102

render multiple lights
f-glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{
	
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

// Directional Light
struct DirLight{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};
// Point Light
struct PointLight{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float linear;
	float constant;
	float quadratic;
};
// Spot Light
struct SpotLight{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float linear;
	float constant;
	float quadratic;

	float cutOff;
	float outerCutOff;
};

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight spotLight;
uniform vec3 viewPos;

vec3 CalDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 CalPointLight(PointLight light, vec3 norm, vec3 fragpos, vec3 viewDir);
vec3 CalSpotLight(SpotLight light, vec3 norm, vec3 fragpos, vec3 viewDir);

void main()
{
	//Properties
	// NOTE: all lights have the same norm and viewDir that's why it's both here
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	// Directional Light 
	vec3 result = CalDirLight(dirLight, norm, viewDir);
	// Point Light 
	for(int i = 0; i < 4; i++)
		result += CalPointLight(pointLights[i], norm ,fragPos, viewDir);
	// Spot Light 
	result += CalSpotLight(spotLight,norm ,fragPos,viewDir);

	FragColor = vec4(result, 1.0f);

}

vec3 CalDirLight(DirLight light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// Diffuse Shading
	float diff = max(dot(norm,lightDir),0.0f);
	// Specular Shading
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	// Combine results
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);


	return ambient + diffuse + specular;
}

vec3 CalPointLight(PointLight light, vec3 norm, vec3 fragpos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragpos);
	// Diffuse Shading
	float diff = max(dot(norm,lightDir),0.0f);
	// Specular Shading
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	// Attenuation
	float Distance = length(light.position - fragpos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance ,2));
	// Combine results
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;


	return ambient + diffuse + specular;
}

vec3 CalSpotLight(SpotLight light, vec3 norm, vec3 fragpos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragpos);
	// Diffuse Shading
	float diff = max(dot(norm,lightDir),0.0f);
	// Specular Shading
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	// Attenuation
	float Distance = length(light.position - fragpos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance ,2));
	// Spotlight intensity
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0f,1.0f);

	// Combine results
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;


	return ambient + diffuse + specular;
}
</code></pre>
main.cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1000
#define SCR_HEIGHT 800
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

float vertices[] =
{
	/* Top Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	/* Bottom Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	/* Left Position */		/* Color */			/* TexCoords */	    	/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	/* Right Position */		/* Color */			/* TexCoords */	   	 /* Normals */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 /* Back Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f,
	/* Front Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,

};

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype

unsigned int load_texture(const char* texture_path); // Protype

glm::vec3 cubePositions[] =
{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);


/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Cube Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position Attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Attribute 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Normals Attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	/* Light Buffers */
	GLuint lightCubeVBO, lightCubeVAO;

	glGenVertexArrays(1, &lightCubeVAO);
	glGenBuffers(1, &lightCubeVBO);

	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Light Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/* Texture */
	GLuint diffuseMap = load_texture("res/Texture/container2.png");
	GLuint specularMap = load_texture("res/Texture/container2_specular.png");

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
	myShader.use();
	myShader.setInt("material.diffuse", 0);
	myShader.setInt("material.specular", 1);

	// Some window
	bool ShowDemo = false;
	bool mySecondWindow = false;

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 3.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables



		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// First Object
		myShader.use();

		// Directional Lights
		myShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.5f);
		myShader.setVec3("dirLight.ambient",  glm::vec3(0.2f));
		myShader.setVec3("dirLight.diffuse",  glm::vec3(0.4f));
		myShader.setVec3("dirLight.specular",  glm::vec3(0.5f));

		// Point Lights
		for (int i = 0; i < 4; i++)
		{
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].position").c_str(), pointLightPositions[i]);
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].ambient").c_str(), glm::vec3(0.2f));
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), glm::vec3(0.4f));
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].specular").c_str(), glm::vec3(0.9f));
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), 1.0f);
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].linear").c_str(), 0.09f);
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), 0.032f);
		}

		// Spot Lights
		myShader.setVec3("spotLight.position", camera.Position);
		myShader.setVec3("spotLight.direction", camera.Front);
		myShader.setVec3("viewPos", camera.Position);
		myShader.setVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
		myShader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
		myShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0);
		myShader.setFloat("spotLight.constant", 1.0f);
		myShader.setFloat("spotLight.linear", 0.09f);
		myShader.setFloat("spotLight.quadratic", 0.032f);
		myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(13.0f)));
		myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.5f)));

		// Material
		myShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		myShader.setFloat("material.shininess", 64.0f);


		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		for (int i = 0; i < 10; i++)
		{
			// Model
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(cubePositions[i]));
			model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(0.0f, 1.0f, 0.0f));

			myShader.setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}


		// Second Object
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		

		for (int i = 0; i < 4; i++)
		{
			// Model
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			lightCubeShader.setMat4("model", model);
			glBindVertexArray(lightCubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Render your GUI
		ImGui::Begin("Light test");

		ImGui::End();

		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
</code></pre>

p103

project right now
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1000
#define SCR_HEIGHT 800
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

float vertices[] =
{
	/* Top Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	/* Bottom Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f,-1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,-1.0f,
	/* Left Position */		/* Color */			/* TexCoords */	    	/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
	/* Right Position */		/* Color */			/* TexCoords */	   	 /* Normals */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	 /* Back Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f,
	/* Front Position */		/* Color */			/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f,-1.0f, 0.0f,

};

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype

unsigned int load_texture(const char* texture_path); // Protype

glm::vec3 to_vec3(float arr[])
{
	glm::vec3 result;

	result.x = arr[0];
	result.y = arr[1];
	result.z = arr[2];

	return result;
}

glm::vec3 cubePositions[] =
{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] =
{
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);


/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Cube Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position Attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Attribute 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Normals Attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	/* Light Buffers */
	GLuint lightCubeVBO, lightCubeVAO;

	glGenVertexArrays(1, &lightCubeVAO);
	glGenBuffers(1, &lightCubeVBO);

	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Light Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/* Texture */
	GLuint diffuseMap = load_texture("res/Texture/container2.png");
	GLuint specularMap = load_texture("res/Texture/container2_specular.png");

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");
	myShader.use();
	myShader.setInt("material.diffuse", 0);
	myShader.setInt("material.specular", 1);

	// Some window
	bool ShowDemo = false;
	bool mySecondWindow = false;
	bool helpWindow = false; // Extra things

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 3.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables
		// Directional Light
		static float dir_direction[3] = { -0.2f, -1.0f, -0.5f };
		static float dir_ambient[3] = { 0.2f, 0.2f ,0.2f };
		static float dir_diffuse[3] = { 0.4f, 0.4f ,0.4f };
		static float dir_specular[3] = { 0.6f, 0.6f ,0.6f };

		// Point Light
		//static float point_position
		static float point_ambient[3] = { 0.2f, 0.2f, 0.2f };
		static float point_diffuse[3] = { 0.5f, 0.5f, 0.5f };
		static float point_specular[3] = { 1.0f, 1.0f, 1.0f };
		static float point_constant = 1.0f;
		static float point_linear = 0.09f;
		static float point_quadratic = 0.032f;

		// Spot Light
		static float spot_ambient[3] = { 0.2f, 0.2f, 0.2f };
		static float spot_diffuse[3] = { 1.0f, 1.0f, 1.0f };
		static float spot_specular[3] = { 1.0f, 1.0f, 1.0f };
		static float spot_constant = 1.0f;
		static float spot_linear = 0.09f;
		static float spot_quadratic = 0.032f;
		static float spot_cutOff = 12.5f;
		static float spot_outerCutOff = 18.5f;

		static float cubeMapPos[3] = { 0.0f, 0.0f, 0.0f };


		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (helpWindow) // Extra things
		{
			ImGui::Begin("How to play ?");
			ImGuiStyle* style = &ImGui::GetStyle();
			style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
			ImGui::Text("HELLO There !");
			ImGui::PopStyleColor();

			ImGui::Text("Move Around with (W-A-S-D-UP-DOWN) key.");
			ImGui::Text("Look Around  with Mouse Button Right and Cursor.");
			ImGui::Text("Turn on Flashlights with Mouse Button Left.");
			ImGui::Text("Zoom out/in with Mouse Scroll.");
			if (ImGui::Button("Thanks!"))
				helpWindow = false;
			ImGui::End();
		}

		// First Object
		myShader.use();

		// Directional Light
		myShader.setVec3("dirLight.direction", to_vec3(dir_direction));
		myShader.setVec3("dirLight.ambient", to_vec3(dir_ambient));
		myShader.setVec3("dirLight.diffuse", to_vec3(dir_diffuse));
		myShader.setVec3("dirLight.specular", to_vec3(dir_specular));

		// Point Lights
		for (int i = 0; i < 4; i++)
		{
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].position").c_str(), pointLightPositions[i] * xValue);
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].ambient").c_str(), to_vec3(point_ambient));
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), to_vec3(point_diffuse));
			myShader.setVec3(("pointLights[" + std::to_string(i) + "].specular").c_str(), to_vec3(point_specular));
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), point_constant);
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].linear").c_str(), point_linear);
			myShader.setFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), point_quadratic);
		}

		// Spot Light
		myShader.setVec3("spotLight.position", camera.Position);
		myShader.setVec3("spotLight.direction", camera.Front);
		myShader.setVec3("viewPos", camera.Position);
		myShader.setVec3("spotLight.ambient", to_vec3(spot_ambient));
		myShader.setVec3("spotLight.diffuse", to_vec3(spot_diffuse));
		myShader.setVec3("spotLight.specular", to_vec3(spot_specular));
		myShader.setFloat("spotLight.constant", spot_constant);
		myShader.setFloat("spotLight.linear", spot_linear);
		myShader.setFloat("spotLight.quadratic", spot_quadratic);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(spot_cutOff)));
			myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spot_outerCutOff)));
		}
		else
		{
			myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(0.0f)));
			myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(0.0f)));

		}

		// Material
		myShader.setFloat("material.shininess", 64.0f);


		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		
		// We Draw a map with three loop cuz we are rendering in 3D so each axies need a loop like (x -> i, y -> j, z -> k).
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					// We will set blocks like minecraft and we wannna make it to a hollow huge Maps with 10x10x10 cubes
					if (i == 0 || i == 9 || j == 0 || j == 9 || k == 9)
					{
						// Model
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(i + cubeMapPos[0], j + cubeMapPos[1], k + cubeMapPos[2]));
						//model = glm::rotate(model, glm::radians(-55.0f) * time, glm::vec3(0.0f, 1.0f, 0.0f));

						myShader.setMat4("model", model);
						glBindVertexArray(VAO);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}
				}
			}
		}


		// Second Object
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		lightCubeShader.setVec3("light.ambient", to_vec3(point_ambient));
		lightCubeShader.setVec3("light.diffuse", to_vec3(point_diffuse));

		for (int i = 0; i < 4; i++)
		{
			// Model
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i] * xValue);
			model = glm::scale(model, glm::vec3(0.3f));
			lightCubeShader.setMat4("model", model);
			glBindVertexArray(lightCubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		// Render your GUI
		ImGui::Begin("Light test");

		// Extra things
		ImGuiStyle* style = &ImGui::GetStyle();
		style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
		if (ImGui::Button("Need Helps ?"))	helpWindow = true;
		ImGui::PopStyleColor();

		ImGui::SliderFloat3("Map Position", cubeMapPos, -10.0f, 10.0f);
		ImGui::Text("Directional Light");
		ImGui::SliderFloat3("Directional Direction", dir_direction, -2.0f, 2.0f);
		ImGui::SliderFloat3("Directional Ambient", dir_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Directional Diffuse", dir_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Directional Specular", dir_specular, 0.0f, 1.0f);
		ImGui::Text("Point Light");
		ImGui::SliderFloat3("Point Ambient", point_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Point Diffuse", point_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Point Specular", point_specular, 0.0f, 1.0f);
		ImGui::SliderFloat("Point Constant", &point_constant, -1.0f, 1.0f);
		ImGui::SliderFloat("Point Linear", &point_linear, -1.0f, 1.0f);
		ImGui::SliderFloat("Point Quadratic", &point_quadratic, -1.0f, 1.0f);
		ImGui::Text("Spot Light");
		ImGui::SliderFloat3("Spot Ambient", spot_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Spot Diffuse", spot_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Spot Specular", spot_specular, 0.0f, 1.0f);
		ImGui::SliderFloat("Spot Constant", &spot_constant, -1.0f, 1.0f);
		ImGui::SliderFloat("Spot Linear", &spot_linear, -1.0f, 1.0f);
		ImGui::SliderFloat("Spot Quadratic", &spot_quadratic, -1.0f, 1.0f);
		ImGui::SliderFloat("Spot CutOff", &spot_cutOff, 0.0f, 100.0f);
		ImGui::SliderFloat("Spot OuterCutOff", &spot_outerCutOff, 0.0f, 100.0f);
		ImGui::End();



		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}
</code></pre>

p104

setup assimp on windows
方式同前

p105

meshe class
mesh.hpp
<pre><code>
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

using namespace std;
using namespace glm;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh {
public:
	// Mesh Data 
	vector<Vertex> vertices;
	vector<unsigned int> indecies;
	vector<Texture> textures;

	// Constructors
	Mesh(vector<Vertex> vertices, vector<unsigned int> indecies, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indecies = indecies;
		this->textures = textures;

		this->setupMesh();
	}

	void Draw(Shader& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		for (int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			string name = textures[i].type;
			string number;

			if (name == "texture_diffuse")
				number = to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = to_string(specularNr++);

			shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		glActiveTexture(GL_TEXTURE0);

		// Draw Mesh
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

private:
	// Render Data
	unsigned int VAO, VBO, EBO;

	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(unsigned int), &indecies[0], GL_STATIC_DRAW);

		// Position Attribute 
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// Normals Attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		// Texture Attribute 
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glEnableVertexAttribArray(0);
	}

};


</code></pre>

p107

model
model class 
<pre><code>
#pragma once

#include "Mesh.hpp"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory);

class Model {
public:

	Model(const char* path)
	{
		this->loadModel(path);
	}

	void Draw(Shader& shader)
	{
		for (auto mesh : meshes)
			mesh.Draw(shader);
	}

private:

	// Model Data
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;

	void loadModel(const string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
			return;
		}

		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);

	}
	void processNode(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		// Then do the same for each of its children
		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Data
		vector<Vertex> vertices;
		vector<unsigned int> indecies;
		vector<Texture> textures;

		// Vertex
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			// Position
			Vertex vertex;
			glm::vec3 vector3;

			vector3.x = mesh->mVertices[i].x;
			vector3.y = mesh->mVertices[i].y;
			vector3.z = mesh->mVertices[i].z;

			vertex.Position = vector3;

			// Normals 
			if (mesh->HasNormals())
			{
				vector3.x = mesh->mNormals[i].x;
				vector3.y = mesh->mNormals[i].y;
				vector3.z = mesh->mNormals[i].z;

				vertex.Normal = vector3;
			}

			// Texture Coordinate
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vector2;

				vector2.x = mesh->mTextureCoords[0][i].x;
				vector2.y = mesh->mTextureCoords[0][i].y;

				vertex.TexCoords = vector2;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f);

			vertices.push_back(vertex);
		}

		// Indices
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indecies.push_back(face.mIndices[j]);
		}

		// Texture
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// Diffuse Map
		vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// Specular Map
		vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		return Mesh(vertices, indecies, textures);
	}

	vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;

		for (int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (int j = 0; j < textures_loaded.size(); j++)
			{
				if (strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}

			if (!skip)
			{
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), directory);
				texture.path = str.C_Str();
				texture.type = typeName;
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}

		return textures;
	}

};

unsigned int TextureFromFile(const char* path, const string& directory)
{
	string fileName = string(path);
	fileName = directory + '/' + fileName;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return textureID;
}

</code></pre>

p113

render model 渲染模型

p114

sponza model 空间模型

p116

Light Testing for Model 模型光照测试
fragmentShader glsl
<pre><code>
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material{
	sampler2D texture_diffuse;
	sampler2D texture_specular;
};

struct Light{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

vec3 direction = vec3(-0.2f,-1.0f,-0.5f);


float constant = 1.0f;
float linear = 0.092f;
float quadratic = 0.032f;
float cutOff = cos(radians(12.5f));
float outerCutOff = cos(radians(17.5f));

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	// ambient
	vec3 ambient = light.ambient * texture(material.texture_diffuse, TexCoords).rgb;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(lightDir, norm) ,0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse, TexCoords);

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0f) , 64.0f);
	vec3 specular = light.specular * spec * texture(material.texture_specular, TexCoords);

	// Intensity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = cutOff - outerCutOff;
	float intensity = clamp((theta-outerCutOff)/epsilon, 0.0f, 1.0f);


	// Attenuation
	float Distance = length(light.position - FragPos);
	float attenuation = 1.0f / (constant + linear * Distance + quadratic * pow(Distance ,2));

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	// Directional Light
	// ambient
	vec3 ambient2 = light.ambient * texture(material.texture_diffuse, TexCoords).rgb;

	// diffuse
	vec3 lightDir2 = normalize(-direction);
	float diff2 = max(dot(lightDir2, norm) ,0.0f);
	vec3 diffuse2 = light.diffuse * diff * texture(material.texture_diffuse, TexCoords);

	// specular
	vec3 reflectDir2 = reflect(-lightDir2, norm);
	float spec2 = pow(max(dot(viewDir, reflectDir),0.0f) , 64.0f);
	vec3 specular2 = light.specular * spec2 * texture(material.texture_specular, TexCoords);

	vec3 result = (ambient + ambient2) + (diffuse + diffuse2) + (specular + specular2);

	FragColor =  vec4(result, 1.0f);
}

</code></pre>
LightCube frag
<pre><code>
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f);
}
</code></pre>
LightCube vert
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{	
	gl_Position = projection * view * model * vec4(aPos , 1.0f);
}
</code></pre>
vertexShader glsl
<pre><code>
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
	FragPos = vec3(model * vec4(aPos,1.0f));
	gl_Position = projection * view * model  * vec4(aPos, 1.0f);
}
</code></pre>
camera.hpp
<pre><code>
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Directions
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = -0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

using namespace glm;
using namespace std;

class Camera {
public:
	//Camera Attributes
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 WorldUp;
	vec3 Right;

	// Eular Angles
	float Yaw;
	float Pitch;
	//Camera Options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// constructor with vectors
	Camera(vec3 position = vec3(0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		updateCameraVectors();
	}

	mat4 GetViewMatrix()
	{
		return lookAt(this->Position, this->Position + this->Front, this->Up);
	}

	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		if (this->Pitch >= 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch <= -89.0f)
			this->Pitch = -89.0f;

		updateCameraVectors();
	}
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		const float velocity = this->MovementSpeed * deltaTime;
		if (direction == FORWARD)
			this->Position += this->Front * velocity;
		if (direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == UP)
			this->Position += this->Up * velocity;
		if (direction == DOWN)
			this->Position -= this->Up * velocity;
	}
	void ProcessMouseScroll(float yoffset)
	{
		this->Zoom -= float(yoffset);
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
		if (Zoom <= 20.0f)
			Zoom = 20.0f;
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 direction;
		direction.x = std::cos(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		direction.y = std::sin(glm::radians(this->Pitch));
		direction.z = std::sin(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(direction);

		// Alsom re-calculate for Right and Up vectors
		this->Right = normalize(cross(this->Front, this->WorldUp));
		this->Up = normalize(cross(this->Right, this->Front));
	}
};

</code></pre>
Mesh.hpp
<pre><code>
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

using namespace std;
using namespace glm;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh {
public:
	// Mesh Data 
	vector<Vertex> vertices;
	vector<unsigned int> indecies;
	vector<Texture> textures;

	// Constructors
	Mesh(vector<Vertex> vertices, vector<unsigned int> indecies, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indecies = indecies;
		this->textures = textures;

		this->setupMesh();
	}

	void Draw(Shader& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		for (int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			string name = textures[i].type;
			string number;

			if (name == "texture_diffuse")
				number = to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = to_string(specularNr++);

			shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		glActiveTexture(GL_TEXTURE0);

		// Draw Mesh
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

private:
	// Render Data
	unsigned int VAO, VBO, EBO;

	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(unsigned int), &indecies[0], GL_STATIC_DRAW);

		// Position Attribute 
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// Normals Attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		// Texture Attribute 
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glEnableVertexAttribArray(0);
	}

};

</code></pre>
Model hpp
<pre><code>
#pragma once

#include "Mesh.hpp"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory);

class Model {
public:

	Model(const char* path)
	{
		this->loadModel(path);
	}

	void Draw(Shader& shader)
	{
		for (auto mesh : meshes)
			mesh.Draw(shader);
	}

private:

	// Model Data
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;

	void loadModel(const string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
			return;
		}

		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);

	}
	void processNode(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		// Then do the same for each of its children
		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Data
		vector<Vertex> vertices;
		vector<unsigned int> indecies;
		vector<Texture> textures;

		// Vertex
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			// Position
			Vertex vertex;
			glm::vec3 vector3;

			vector3.x = mesh->mVertices[i].x;
			vector3.y = mesh->mVertices[i].y;
			vector3.z = mesh->mVertices[i].z;

			vertex.Position = vector3;

			// Normals 
			if (mesh->HasNormals())
			{
				vector3.x = mesh->mNormals[i].x;
				vector3.y = mesh->mNormals[i].y;
				vector3.z = mesh->mNormals[i].z;

				vertex.Normal = vector3;
			}

			// Texture Coordinate
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vector2;

				vector2.x = mesh->mTextureCoords[0][i].x;
				vector2.y = mesh->mTextureCoords[0][i].y;

				vertex.TexCoords = vector2;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f);

			vertices.push_back(vertex);
		}

		// Indices
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indecies.push_back(face.mIndices[j]);
		}

		// Texture
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// Diffuse Map
		vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// Specular Map
		vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		return Mesh(vertices, indecies, textures);
	}

	vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;

		for (int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (int j = 0; j < textures_loaded.size(); j++)
			{
				if (strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}

			if (!skip)
			{
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), directory);
				texture.path = str.C_Str();
				texture.type = typeName;
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}

		return textures;
	}

};

unsigned int TextureFromFile(const char* path, const string& directory)
{
	string fileName = string(path);
	fileName = directory + '/' + fileName;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return textureID;
}

</code></pre>
Shader cpp
<pre><code>
#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open The Files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// Read The Files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// Close The Files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Read as a string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "FAILED::FILES::TO_READ\n";
		glfwTerminate();
		return;
	}

	// Read as a const char
	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();

	// vertex
	this->vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::VERTEX::<" << infolog << std::endl;
	}
	//fragment
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		std::cout << "FAILED::SHADER::FRAGMENT::<" << infolog << ">" << std::endl;
	}

	//Program
	this->ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infolog);
		std::cout << "FAILED::PROGRAM::<" << infolog << ">" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) 
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

</code></pre>
Shader h
<pre><code>
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Reading Files
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
private:
    std::string vertexCode, fragmentCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;
    std::stringstream vertexShaderStream, fragmentShaderStream;
    const char* vertexShaderData, * fragmentShaderData;
    unsigned int vertex, fragment;
public:
    unsigned int ID;

    // Constructor
    Shader(const char* vertexPath, const char* fragmentPath);

    // use
    void use();
    // utility uniform functions
    
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec3(const std::string& name, const glm::vec3 &value);
    void setMat4(const std::string& name, const glm::mat4& value);
};
</code></pre>
main cpp
<pre><code>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.hpp"
#include "Model.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

float vertices[] =
{
	/* Top Position */		/* Color */				/* TexCoords */		/* Normals */
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f, 0.0f, 1.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,			0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f, 0.0f, 1.0f,
	/* Bottom Position */	/* Color */				/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f, 0.0f,-1.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f, 0.0f,-1.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f, 0.0f,-1.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,			0.0f, 0.0f,-1.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f, 0.0f,-1.0f,
	/* Left Position */		/* Color */				/* TexCoords */	    /* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		   -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		   -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		   -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		   -1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		   -1.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		   -1.0f, 0.0f, 0.0f,
	/* Right Position */	/* Color */				/* TexCoords */	    /* Normals */
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			1.0f, 0.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,			1.0f, 0.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			1.0f, 0.0f, 0.0f,
	 /* Back Position */	/* Color */				/* TexCoords */		/* Normals */
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f, 1.0f, 0.0f,
	 0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,			0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 		0.0f, 1.0f, 0.0f,
	/* Front Position */	/* Color */				/* TexCoords */		/* Normals */
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f,-1.0f, 0.0f,
	 0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,			0.0f,-1.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f,-1.0f, 0.0f,

};

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Protype
void userInput(GLFWwindow* window); // protype
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); // Protype
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset); // Protype

unsigned int load_texture(const char* texture_path); // Protype

glm::vec3 cubePositions[] =
{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] =
{
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);


/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

int main()
{
	/* Initialize GLFW */
	glfwInit();

	/* Initialize Version 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a window */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);

	// Check window
	if (!window)
	{
		std::cout << "Failed to Create a window\n";
		glfwTerminate();
	}

	/* The most important part */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);
	//glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	// check Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize Glew\n";
		glfwTerminate();
	}

	/* Options */
	glEnable(GL_DEPTH_TEST);

	/* ImGui */
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Setup style
	ImGui::StyleColorsDark();


	/* Cube Buffers */
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position Attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Attribute 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Normals Attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	/* Light Buffers */
	GLuint lightCubeVBO, lightCubeVAO;

	glGenVertexArrays(1, &lightCubeVAO);
	glGenBuffers(1, &lightCubeVBO);

	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Light Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/* Texture */
	stbi_set_flip_vertically_on_load(true);

	/* Model */
	Model myBackPack("res/Object/Sponza/sponza.obj");

	/* Shader */
	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	Shader lightCubeShader("res/Shader/LightCube.vert", "res/Shader/LightCube.frag");



	// Some window
	bool ShowDemo = false;
	bool mySecondWindow = false;

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{

		/* Update */
		userInput(window);
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 5.0f;
		float camX = std::sin(time) * radius;
		float camZ = std::cos(time) * radius;

		// Gui Variables



		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // 0.0 - 1.0
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// First Object
		myShader.use();

		lightPos = glm::vec3(camX, camZ, 0.0f);
		myShader.setVec3("light.position", camera.Position);
		myShader.setVec3("light.direction", camera.Front);
		myShader.setVec3("light.ambient", glm::vec3(0.2f));
		myShader.setVec3("light.diffuse", glm::vec3(0.4f));
		myShader.setVec3("light.specular", glm::vec3(0.5f));
		myShader.setVec3("viewPos", camera.Position);

		/* Coordinates */
		// Projection
		projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		// Model
		model = glm::mat4(1.0f);
		myShader.setMat4("model", model);

		// Draw your model
		myBackPack.Draw(myShader);


		// Second Object
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		lightCubeShader.setMat4("model", model);

		//glBindVertexArray(lightCubeVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	const float camera_speed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // To exit the program
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

}
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	if (isFirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Filter Options */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	return texture;
}

</code></pre>