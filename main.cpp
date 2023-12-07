//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"//assignment e ai camera niye kaj kra lagbe
#include "basic_camera.h"//aita diye kaj kra jabena


#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);//mouse diye kaj krar jnno
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
//void drawchairTable(unsigned int VAO, Shader ourShader, glm::mat4 sm);

void table(unsigned int VAO, Shader ourShader, glm::mat4 sm);
void chair(unsigned int VAO, Shader ourShader, glm::mat4 sm);
void ground(unsigned int VAO, Shader ourShader, glm::mat4 sm);
void ground1(unsigned int VAO, Shader ourShader, glm::mat4 sm);
void barDesk(unsigned int VAO, Shader ourShader, glm::mat4 sm);
void roundChair(Shader ourShader, glm::mat4 moveMatrix);
void roundlamp(Shader ourShader, glm::mat4 moveMatrix);
void element(Shader ourShader, glm::mat4 moveMatrix, glm::mat4 scale);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform.//global variable 
float rotateAngle_X = 0.0f;//45.0;
float rotateAngle_Y = 0.0f;//45.0;
float rotateAngle_Z = 0.0f;//45.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

float r = 0.0;
float p = 0.0;
bool fanOn = false;
bool turnOn = false;
bool bothOn = false;

// camera.h er jnno
Camera camera(glm::vec3(-3.0f, 0.0f, 3.0f));//camera er location change kra jayw
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//basic camera.h er jnno
float eyeX = 0.0, eyeY = 0.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing //sob pc te jeno processing time eki ney aijnno eti set kre deya hoice
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse //camera.h er jnno mouse er kaj 
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);//z buffer , z axis e kto depth e object thakbe eti decide kra jay

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    /*float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 0.3f, 0.8f, 0.5f,
        0.5f, 0.0f, 0.0f, 0.5f, 0.4f, 0.3f,
        0.5f, 0.5f, 0.0f, 0.2f, 0.7f, 0.3f,
        0.0f, 0.5f, 0.0f, 0.6f, 0.2f, 0.8f,
        0.0f, 0.0f, 0.5f, 0.8f, 0.3f, 0.6f,
        0.5f, 0.0f, 0.5f, 0.4f, 0.4f, 0.8f,
        0.5f, 0.5f, 0.5f, 0.2f, 0.3f, 0.6f,
        0.0f, 0.5f, 0.5f, 0.7f, 0.5f, 0.4f
    };*/
    /*float cube_vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f
    };*/
    float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    /*unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        1, 2, 6,
        6, 5, 1,

        5, 6, 7,
        7 ,4, 5,

        4, 7, 3,
        3, 0, 4,

        6, 2, 3,
        3, 7, 6,

        1, 5, 4,
        4, 0, 1
    };*/
    /*float cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };*/
    // world space positions of our cubes
    /*glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };*/
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        ourShader.setMat4("view", view);

        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.8f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.0f, -2.7f, -20.0f));
        element(ourShader, translateMatrix, scaleMatrix);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.8f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.0f, -2.7f, -7.0f));
        element(ourShader, translateMatrix, scaleMatrix);

        //roundlamp(ourShader, identityMatrix);
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.8f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.0f, -2.7f, -1.0f));
        element(ourShader, translateMatrix, scaleMatrix);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.8f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.02f, -2.7f, -4.0f));
        element(ourShader, translateMatrix, scaleMatrix);


        



        translateMatrix = identityMatrix;
        roundlamp(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -2.0f));
        roundlamp(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -4.0f));
        roundlamp(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -4.0f));
        roundlamp(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -6.0f));
        roundlamp(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -8.0f));
        roundlamp(ourShader, translateMatrix);

        translateMatrix = identityMatrix;
        roundChair(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -2.0f));
        roundChair(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -4.0f));
        roundChair(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -4.0f));
        roundChair(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -6.0f));
        roundChair(ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -8.0f));
        roundChair(ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = translateMatrix * rotateYMatrix * identityMatrix;
        chair(VAO, ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -1.0f));
        table(VAO, ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -1.0f));
        chair(VAO, ourShader, translateMatrix);

        glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
        translateMatrix1 = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0f, -2.80f));
        rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix1 = translateMatrix1 * rotateYMatrix1 * identityMatrix;
        chair(VAO, ourShader, translateMatrix1);

        glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -4.0f));
        table(VAO, ourShader, translateMatrix2);
        //translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -1.0f));

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -4.2f));
        chair(VAO, ourShader, translateMatrix);

        //glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
        translateMatrix1 = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0f, -6.0f));
        rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix1 = translateMatrix1 * rotateYMatrix1 * identityMatrix;
        chair(VAO, ourShader, translateMatrix1);

        //glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -6.95f));
        table(VAO, ourShader, translateMatrix2);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -7.2f));
        chair(VAO, ourShader, translateMatrix);
        translateMatrix = identityMatrix;
        barDesk(VAO, ourShader, identityMatrix);

        //-------------------------------------------------------------------------------------------------------
        translate_Z = -0.5f;
        translate_X = 1.0f;
        //ground(VAO, ourShader,identityMatrix);

        translateMatrix = identityMatrix;

        for (int i = 0; i < 10; i++)
        {
            translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-translate_X, 0.0f, 0.0f));

            ground(VAO, ourShader, translateMatrix);



        }

        for (int i = 0; i < 10; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, translate_Z));

            for (int i = 0; i < 10; i++)
            {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-translate_X, 0.0f, 0.0f));

                ground1(VAO, ourShader, translateMatrix);

            }
            translate_Z -= 0.5f;

            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, translate_Z));

            for (int i = 0; i < 10; i++)
            {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-translate_X, 0.0f, 0.0f));

                ground(VAO, ourShader, translateMatrix);
            }
            translate_Z -= 0.5f;

        }



        //right wall

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.0f, 12.0f, 21.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.918f, 0.949f, 0.999f, 1.0f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //dag

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.2f, 21.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.475f, 1.7f, -9.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, 12.0f, 0.05f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.475f, -1.0f, 0.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 12.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2f, -1.0f, -4.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, 12.0f, 0.05f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.475f, -1.0f, -7.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        



        //back wall
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(20.0f, 12.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.5f, -1.0f, -9.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.831f, 0.584f, 0.804f, 0.831f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 5.0f, 0.02f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-7.5f, -0.25f, -9.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.91f, 0.949f, 0.999f, 1.0f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 3.5f, 0.02f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.5f, 0.55f, -9.0f));
        model = translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.91f, 0.949f, 0.999f, 1.0f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //left wall
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.0f, 12.0f, 21.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
        translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
        model = translateMatrix1 * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        ourShader.setVec4("color", glm::vec4(0.91f, 0.949f, 0.999f, 1.0f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //top wall

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(20.0f, 0.0f, 21.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 5.0f, -9.0f));
        //translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
        model = translateMatrix1 * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
        //ourShader.setVec4("color", glm::vec4(0.91f, 0.949f, 0.999f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);





        //fan1

         if (fanOn)
        {
            //fan er pakha1
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -1.0f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -0.93f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            /*
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0f));

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.0f, .5f));

            model = glm::rotate(identityMatrix, glm::radians(-90+r), glm::vec3(0.0f, 1.0f, 0.0f))* translateMatrix * scaleMatrix ;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0f));

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.0f, .5f));

            model = glm::rotate(identityMatrix, glm::radians(-180 + r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



            */


            r = (r + 10.0);

            //fan er pakha1
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -4.5f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians( 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -4.43f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        

       
        //fan2


        else if (turnOn)
        {
            //fan er pakha1
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -4.5f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -4.43f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));
           // ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            /*
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0f));

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.0f, .5f));

            model = glm::rotate(identityMatrix, glm::radians(-90+r), glm::vec3(0.0f, 1.0f, 0.0f))* translateMatrix * scaleMatrix ;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0f));

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.0f, .5f));

            model = glm::rotate(identityMatrix, glm::radians(-180 + r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



            */


            r = (r + 10.0);

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -1.0f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians( 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -0.93f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        else if (bothOn)
        {
            //fan er pakha1
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -4.5f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -4.43f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));
            // ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            /*
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0f));

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.0f, .5f));

            model = glm::rotate(identityMatrix, glm::radians(-90+r), glm::vec3(0.0f, 1.0f, 0.0f))* translateMatrix * scaleMatrix ;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0f));

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.0f, .5f));

            model = glm::rotate(identityMatrix, glm::radians(-180 + r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



            */
            r = (r + 10.0);

            //fan er pakha1
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -1.0f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(p), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(p + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -0.93f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            p = (p + 10.0);

            
            }


        else
        {
            //fan er pakha1
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -4.5f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -4.43f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));
            //ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha1
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.1f, .5f));
            translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, -0.125f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, -0.5f, 0.125f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-3.0f, 4.2f, -1.0f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //pakha2
            //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.5f, 0.125f));

            //translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.5f, -0.125f));

            model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
            ourShader.setMat4("model", model);
            //ourShader.setVec4("color", glm::vec4(0.0196, 0.0157f, 0.4f, 1.0f));
            ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //rode
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.6f, .1f));
            translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-2.3f, 4.2f, -0.93f));

            model = translateMatrix3 * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);




        }


       

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);

        ////////


                // render boxes
                //for (unsigned int i = 0; i < 10; i++)
                //{
                //    // calculate the model matrix for each object and pass it to shader before drawing
                //    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                //    model = glm::translate(model, cubePositions[i]);
                //    float angle = 20.0f * i;
                //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                //    ourShader.setMat4("model", model);

                //    glDrawArrays(GL_TRIANGLES, 0, 36);
                //}

                // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
                // -------------------------------------------------------------------------------

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


void element(Shader ourShader, glm::mat4 moveMatrix, glm::mat4 scale) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.658, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7, 0.6, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", scale* moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.0f,0.0f,0.0f,1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {


        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.833, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", scale * moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.933, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", scale * moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.0333, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", scale * moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.133, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.4, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", scale * moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.333, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", scale * moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.631f, 0.484f, 0.104f, 0.431f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }


}

void roundlamp(Shader ourShader, glm::mat4 moveMatrix) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //rope
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.98, 0.0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 2.0, 0.2));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0));
    //glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.733, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7, 0.45, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.833, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.933, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.0333, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.133, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.233, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.2, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 3.688, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7, 0.09, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.85, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.001, 0.3, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        //ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
}

void roundChair(Shader ourShader, glm::mat4 moveMatrix) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //rope
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 0.05, 0.0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, -2.25, 0.2));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0));
    //glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 0.05, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.45, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }

    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, -1.0, 0.0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.06, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", moveMatrix * model);
        ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
        //glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }
}

void barDesk(unsigned int VAO, Shader ourShader, glm::mat4 sm) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, translateMatrix1, translateMatrix2, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //box
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 3.5f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    model = translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //boxer upr
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.02f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 1.75f, 0.0f));
    model = translateMatrix2 * translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);




    //1st self
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.3f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 2.2f, 0.0f));
    model = translateMatrix2 * translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.439f, 0.4f, 0.361f, 0.471f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.02f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 2.19f, 0.0f));
    model = translateMatrix2 * translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.023f, 0.013f, 0.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



    //2nd self
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.3f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 2.9f, 0.0f));
    model = translateMatrix2 * translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.439f, 0.4f, 0.361f, 0.471f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.02f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 2.89f, 0.0f));
    model = translateMatrix2 * translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.023f, 0.013f, 0.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //3d self
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.3f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 4.0f, 0.0f));
    model = translateMatrix2 * translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.439f, 0.4f, 0.361f, 0.471f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.02f, 19.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, -9.0f));
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, 0.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 3.99f, 0.0f));
    model = translateMatrix2 * translateMatrix1 * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.023f, 0.013f, 0.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



}

void chair(unsigned int VAO, Shader ourShader, glm::mat4 sm) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //sofa
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, -1.0f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 1.5f, 0.9f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);




    //backside of sofa
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.025f, -1.0f, -0.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.1f, 2.75f, 0.2f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //r11
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.01f, 0.16f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //r12
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 0.16f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //r13
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.51f, 0.16f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //r14
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.77f, 0.16f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //r21
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.01f, -0.18f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //r22
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.18f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //r23

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.51f, -0.18f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //r24
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.77f, -0.18f, -0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.42f, 0.42f, 0.02f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.631f, 0.086f, 0.043f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}



void table(unsigned int VAO, Shader ourShader, glm::mat4 sm) {


    //table body
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .2f, 2.0f));
    model = sm * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.949f, 0.702f, 0.42f, 0.831f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //menucard
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.4f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.04f, 0.4f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left back leg

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, 0.0f, 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -2.0f, 0.2f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //left front leg
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, 0.0f, 0.85f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -2.0f, 0.2f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //front right leg
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, 0.0f, 0.85f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -2.0f, 0.2f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right back  leg

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, 0.0f, 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -2.0f, 0.2f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left bottom 
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.2f, 1.4f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05f, -0.80f, 0.15f));

    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.918f, 0.949f, 0.757f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right bottom 
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.2f, 1.4f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, -0.80f, 0.15f));

    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.918f, 0.949f, 0.757f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //middle
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 0.2f, 0.2f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f, -0.80f, 0.5f));

    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.918f, 0.949f, 0.757f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void ground(unsigned int VAO, Shader ourShader, glm::mat4 sm) {

    //white
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -1.0f, 1.0f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.918f, 0.949f, 0.999f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, 1.0f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //black



}

void ground1(unsigned int VAO, Shader ourShader, glm::mat4 sm) {

    //white
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -1.0f, 1.0f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    //ourShader.setVec4("color", glm::vec4(0.918f, 0.949f, 0.999f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, -1.0f, 1.0f));
    model = sm * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.502f, 0.208f, 0.18f, 0.012f));
    //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.918f, 0.949f, 0.999f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //black



}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }


    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        camera.ProcessKeyboard(YAW_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        camera.ProcessKeyboard(YAW_L, deltaTime);
    }


    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 1;
        else if (rotateAxis_Y) rotateAngle_Y -= 1;
        else rotateAngle_Z -= 1;
    }
    //A(+x scale),B(+y scale),C,D,E(y eye-),F(x eye-),G(x eye+),H(x eye+),I(+y trans),J(-x trans),K(-y trans),L(+x trans),M(+z scale),N(-y scale),
    // O(+z trans),P(-z trans)
    //    Q(y eye+),R,S,T(z eye+),v(-x scale),W,
    // X(rotate x),Y(rotate y),Z(rotate z)
    // 1(lookat x+),2(lookat x-),3(lookat y+),4(lookat y-),5(lookat z+),6(lookat z-)
    //
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.01;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.01;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.01;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.01;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.01;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.01;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.01;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (fanOn)
            fanOn = false;
        else
            fanOn = true;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (turnOn)
            turnOn = false;
        else
            turnOn = true;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (bothOn)
            bothOn = false;
        else
            bothOn = true;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) 
    {
        lookAtX += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        lookAtX -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        lookAtY += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        lookAtY -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        lookAtZ += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        lookAtZ -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 0.0f, 1.0f));
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


