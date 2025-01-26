
#include "GL/glew.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
//remove which is not neede at the end.
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "importShaders.h"
#include "importObj.h"

#include <iostream>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;



glm::mat4 model = glm::mat4(1.0f);

float scaleby = 0.3f;
glm::vec3 translation(0.0f);
float rotationby = 0.1f;
glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);
int normMapToggle = 1;
int texCycle = 0;

int main(int argc, char *argv[])
{
    const char *vertexShaderSource = importVertexShader(argv[2]);
    const char *fragmentShaderSource = importFragmentShader(argv[2]);
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "viewGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // glew: load all OpenGL function pointers
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


// Load Texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/brickwall.jpg", &width, &height, &nrChannels, 0); 

    //Create texture ID
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);  

    //Bind texture using ID
    glBindTexture(GL_TEXTURE_2D, texture1);  

    //Generate texture using loaded image data
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "failed to load texture" << endl;
    }

    //free image data
    stbi_image_free(data);

// //for second texture
//     data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0); 
//     glGenTextures(1, &texture2);  

//     //Bind texture using ID

//     glBindTexture(GL_TEXTURE_2D, texture2);  

//     //Generate texture using loaded image data
//     if (data) {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else {
//         cout << "failed to load texture" << endl;
//     }

//     //free image data
//     stbi_image_free(data);


//load more textures
    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0); 

    //Create texture ID
    unsigned int texture3;
    glGenTextures(1, &texture3);

    //Bind texture using ID
    glBindTexture(GL_TEXTURE_2D, texture3);

    //Generate texture using loaded image data
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "failed to load awesomeface" << endl;
    }

    //free image data
    stbi_image_free(data);

//load more more textures
    data = stbi_load("textures/gator.jpg", &width, &height, &nrChannels, 0); 

    //Create texture ID
    unsigned int texture4;
    glGenTextures(1, &texture4);

    //Bind texture using ID
    glBindTexture(GL_TEXTURE_2D, texture4);

    //Generate texture using loaded image data
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "failed to load gator" << endl;
    }

    //free image data
    stbi_image_free(data);

//Load Normal Map    
    data = stbi_load("textures/brickwall_normal.jpg", &width, &height, &nrChannels, 0); 

    //Create texture ID
    glGenTextures(1, &texture2);

    //Bind texture using ID
    glBindTexture(GL_TEXTURE_2D, texture2);

    //Generate texture using loaded image data
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "failed to load normal map" << endl;
    }

    //free image data
     stbi_image_free(data);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture3"), 2);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture4"), 3);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int* numVertices = new unsigned int;
    unsigned int* numIndices = new unsigned int;
    vector<vector3D> vertexNormal;
    vector<unsigned int> indices;
    string filename = argv[1];
    std::stringstream ss;
    ss<<"obj/"<<filename;
    int yn =0;
    int yt =0;

    float* vertices = importObj(ss.str(), numVertices, indices, vertexNormal, yn, yt, numIndices);
    float* newvertices = vertices;
    // std::cout << "Print vertices" << endl;

    // for (int i = 0; i < *numVertices/4; i++) {
    //     std::cout << vertices[i] << "\t\t";
    //     if (i%3==2) {
    //         std::cout << endl;
    //     }
    //     if (i%12==11) {
    //         std::cout << endl;
    //     }
    // }
    std::cout << "Numvertices: " << *numVertices << endl;


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, *numVertices, vertices, GL_STATIC_DRAW);
    if (yn == 1 && yt == 1) {
        // position attr
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //normal attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        //texture attribute
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }
    else if(yn == 1 || yt == 1){ //texture or normal but not both
        // position attr
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //normal OR texture attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    else{ //no texture nor normal
        // position attr
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //bind and populate
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, *numIndices, &indices[0], GL_STATIC_DRAW);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    
    long long avgFrameTime = 0;
    unsigned long numFrames = 0;
    
    long long avgFrameTimeGPU = 0;
    unsigned long numFramesGPU = 0;
    GLuint queryObject;
    glGenQueries(1, &queryObject);



    while (!glfwWindowShouldClose(window))
    {
        long long currFrametime = 0;
        GLuint currFrametimeGPU = 0;
        std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
        glBeginQuery(GL_TIME_ELAPSED, queryObject);
        // input
        // -----
        processInput(window);

        // Initialization of Model View Projection Matrix
        model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(30.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // glm::mat4 projection = glm::mat4(1.0f);
        // Transformation Operations
        model = glm::scale(model, glm::vec3(scaleby));
        model = glm::rotate(model, glm::radians(rotationby), rotationAxis);
        model = glm::translate(model, translation);
        glm::mat4 modelViewProjection = projection * view * model;
        // Providing the shader with transformed coordinates (CPU Setting) 
        // if (argv[2]  == "CPU"){
        //     for (int i = 0; i < *numVertices / 4; i += 6) {
        //         glm::vec4 vertexPosition(vertices[i], vertices[i + 1], vertices[i + 2],1.0f);
        //         vertexPosition = modelViewProjection * vertexPosition;
        //         newvertices[i] = vertexPosition.x;
        //         newvertices[i + 1] = vertexPosition.y;
        //         newvertices[i + 2] = vertexPosition.z;
        //     }
    
        //     // Update the VBO with the transformed data
        //     glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //     glBufferSubData(GL_ARRAY_BUFFER, 0,*numVertices , newvertices);
        //     glBindBuffer(GL_ARRAY_BUFFER, 0);
        // }
 
        // Providing the shader with the transformed matrix(GPU SETTING)
        // else{
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelViewProjection"), 1, GL_FALSE, glm::value_ptr(modelViewProjection));
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        // }
        glUniform1i(glGetUniformLocation(shaderProgram, "yn"), yn);
        glUniform1i(glGetUniformLocation(shaderProgram, "normMapToggle"), normMapToggle);
        glUniform1i(glGetUniformLocation(shaderProgram, "texCycle"), texCycle);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);

        // draw our first triangle;
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, *numVertices/4, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // unbind our VA no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        // Time calculation to compare CPU and GPU settings
        std::chrono::steady_clock::time_point stop = std::chrono::high_resolution_clock::now();
        glEndQuery(GL_TIME_ELAPSED);

        currFrametime =  std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        avgFrameTime = avgFrameTime + currFrametime;
        numFrames += 1;
        GLuint queryResult;
        glGetQueryObjectuiv(queryObject, GL_QUERY_RESULT, &queryResult);
        currFrametimeGPU = queryResult;
        avgFrameTimeGPU = avgFrameTimeGPU + currFrametimeGPU;
    }
        long long avg = (avgFrameTime*1.0f) / numFrames;
        cout << "Frametime CPU: " << avg << endl;
        long long avgGPU = (avgFrameTimeGPU * 1.0f) / numFrames;
        cout << "Time GPU: " << avgGPU/1000 << endl;
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteQueries(1, &queryObject);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
    
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //Scaling
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        scaleby *= 1.01f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        scaleby *= 0.99f;

    //Translation    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        translation.y += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        translation.y -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        translation.x -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        translation.x += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        translation.z -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        translation.z += 0.01f;

    //Rotation
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotationby += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotationby -= 1.0f;

    // Along X
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
        rotationby = 0;
        rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    // Along Y
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
        rotationby = 0;
        rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    // Along Z
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
        rotationby = 0;
        rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    }
    // Along XY
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
        rotationby = 0;
        rotationAxis = glm::vec3(1.0f, 1.0f, 0.0f);
    }
    // Along XZ
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS){
        rotationby = 0;
        rotationAxis = glm::vec3(1.0f, 0.0f, 1.0f);
    }
        // Along yZ
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS){
        rotationby = 0;
        rotationAxis = glm::vec3(0.0f, 1.0f, 1.0f);
    }

    //toggle normal map
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
        normMapToggle = 1;
        std::cout << "NORM-MAP: " << normMapToggle << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
        normMapToggle = 0;
        std::cout << "NORM-MAP: " << normMapToggle << std::endl;
    }

    //cycle texture
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){
        texCycle = 0;
        std::cout << "Texmap: " << texCycle << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){
        texCycle = 1;
        std::cout << "Texmap: " << texCycle << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){
        texCycle = 2;
        std::cout << "Texmap: " << texCycle << std::endl;
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

