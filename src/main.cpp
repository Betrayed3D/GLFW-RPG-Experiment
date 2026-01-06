#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>
#include<fstream>
#include<string>

// function declarations
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
GLuint compile_shaders(GLuint shader_type, const std::string& shader_source);
std::string read_text_file(const std::string& filename);
float delta_time();
float normalise(float& input);
void Update();

// shape vertices
float triangle_vertices[9] = {
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
};

// globals

int main()
{
    // set error callback and init glfw
    glfwSetErrorCallback(error_callback);
    glfwInit();
    // create the main window
    GLFWwindow* main_window = glfwCreateWindow(800,800,"RPG Experiment", NULL, NULL);
    glfwMakeContextCurrent(main_window);

    // always set current context before initialising glad
    gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

    // read external shader files
    const std::string vertexSource = read_text_file("C:\\Users\\Marcus\\Documents\\Code Projects\\c++\\RPG Game Experiment\\include\\vertex.glsl");
    const std::string fragmentSource = read_text_file("C:\\Users\\Marcus\\Documents\\Code Projects\\c++\\RPG Game Experiment\\include\\fragment.glsl");

    // compile shaders
    GLuint vertexShader;
    GLuint fragmentShader;
    vertexShader = compile_shaders(GL_VERTEX_SHADER, vertexSource.c_str());
    fragmentShader = compile_shaders(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    // create shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    
    // delete the shader objects since we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // buffers
    GLuint VBO;
    GLuint VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // set callback functions
    glfwSetFramebufferSizeCallback(main_window, framebuffer_size_callback);
    glfwSetKeyCallback(main_window,key_callback);
    glfwSetMouseButtonCallback(main_window,mousebutton_callback);

    // main render loop
    while(!glfwWindowShouldClose(main_window))
    {

        glClearColor(0.5f,0.2f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // uniforms
        float timeValue = (float)glfwGetTime();
        float blueValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, blueValue, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,3);

        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void error_callback(int error, const char* description)
{
    std::cout<<"Error: "<<error<<" "<<description<<std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

void mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        std::cout<<"Right Clicked!"<<std::endl;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

GLuint compile_shaders(GLuint shader_type, const std::string& shader_source)
{
    GLuint shader_object;
    const char* source;
    int success;
    char infolog[512];

    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        shader_object = glCreateShader(GL_VERTEX_SHADER);   
        break;
    case GL_FRAGMENT_SHADER:
        shader_object = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    default:
        break;
    }

    source = shader_source.c_str();
    glShaderSource(shader_object,1,&source,NULL);
    glCompileShader(shader_object);

    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_object, 512,NULL,infolog);
        std::cout<<"Error compiling "<<shader_type<<"\n"<<infolog<<std::endl;
    }

    return shader_object;
}

std::string read_text_file(const std::string& filepath)
{
    std::string file_content = "";
    std::string line = "";
    std::ifstream file_to_read;

    file_to_read.open(filepath.c_str());
    if(file_to_read.is_open())
    {
        while(std::getline(file_to_read, line))
        {
            file_content += line + "\n";
        }
        file_to_read.close();
    }else if(!file_to_read.is_open()){
        std::cout<<"Failed to open file."<<std::endl;
        return NULL;
    }

    std::cout<<file_content<<std::endl;

    return file_content;
} 

float normalise(float& input)
{
    float normalised_data = 0.0f;

    normalised_data = ((input-0.0f)/(1.0f-0.0f));

    return normalised_data;
}

void Update()
{

}