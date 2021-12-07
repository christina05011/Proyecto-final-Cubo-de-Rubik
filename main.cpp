//Nombre: Christina Chacón
//Curso: Computación gráfica

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Estructura + camera
#include "shader_s.h"
#include "Rubik_Cube.h"
#include "camera.h"
//
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
using std::this_thread::sleep_for;
//Solver
#include "Cube.h"
#include "Cross.h"
#include "Corners.h"
#include "Edges.h"
#include "OLL.h"
#include "PLL.h"

//Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void menu();

//Solver functions
std::string Solver_string(std::string argString);
void solver_(std::vector<int>& movements);
void sol_movs();

//Tamaño ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Timing
float deltaTime = 0.0f;	// time between current frame and last frame //actualizar moves de teclado y mouse
float lastFrame = 0.0f;

//Cubo Rubik
std::string images[] = { "S.png","U.png","P.png","C.png","G.png","C.png" };

//Rotations 
int clockwise = 0;
int counter_clockwise = 0;

//Solver variables
std::vector<int> movements;
bool resolver = 0;
int current_sol = 0;
std::string sol = "";
std::string teclado_mov = "";

int main()
{
    glfwInit();
    //Para todas las caras
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubik's cube", NULL, NULL);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("D:\\UCSP\\CG\\ProjectBaseOpenGL\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\CuboRubik2\\lighting.vs",
        "D:\\UCSP\\CG\\ProjectBaseOpenGL\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\CuboRubik2\\lighting.fs");
    Shader lampShader("D:\\UCSP\\CG\\ProjectBaseOpenGL\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\CuboRubik2\\lamp.vs",
        "D:\\UCSP\\CG\\ProjectBaseOpenGL\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\CuboRubik2\\lamp.fs");

    //Texturas del cubo: letras U C S P C G
    unsigned int texture[6];
    int width, height, nrChannels;
    for (int i = 0; i < 6; i++) {
        std::string FilePath = "D://UCSP//CG//ProjectBaseOpenGL//GLFW_GLAD_GLUT_GLEW_cmake_project//src//CuboRubik2//" + images[i];
        unsigned char* LocalBuffer = nullptr;
        glGenTextures(1, &texture[i]);
        glBindTexture(GL_TEXTURE_2D, texture[i]);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        stbi_set_flip_vertically_on_load(1);

        LocalBuffer = stbi_load(FilePath.c_str(), &width, &height, &nrChannels, 0);
        if (LocalBuffer) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, LocalBuffer);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(LocalBuffer);
    }

    Big_Cube* My_Rubik_Cube = new Big_Cube();
    menu();

    float angy = 0.0, angx = 0.0;
    bool light_orbit = 0;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        glfwSetKeyCallback(window, key_callback);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        //LIGHTING //be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        glm::vec3 lightPos;
        //Animation de luz orbitando el cubo en el eje Y
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) light_orbit = 1;
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) light_orbit = 0;
        if (light_orbit) lightPos = glm::vec3(1.0f * sin(glfwGetTime()), 0.0f, 1.0f * cos(glfwGetTime()));
        else  lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // light properties
        lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        lightingShader.setFloat("material.shininess", 32.0f);

        // view/projection transformations // pass projection matrix to shader (note that in this case it could change every frame)
        //An object will appear to have the same size no matter where the camera is positioned
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
        // camera/view transformation //To look the scene
        glm::mat4 view = camera.GetViewMatrix();

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);

        //Para rotar el cubo en eje X y Y
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            angy -= 0.1;
            view = glm::rotate(view, glm::radians(angy), glm::vec3(1.0f, 0.0f, 0.0f));
            sleep_for(std::chrono::milliseconds(1));
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            angy += 0.1;
            view = glm::rotate(view, glm::radians(angy), glm::vec3(1.0f, 0.0f, 0.0f));
            sleep_for(std::chrono::milliseconds(1));
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            angx -= 0.1;
            view = glm::rotate(view, glm::radians(angx), glm::vec3(0.0f, 1.0f, 0.0f));
            sleep_for(std::chrono::milliseconds(1));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            angx += 0.1;
            view = glm::rotate(view, glm::radians(angx), glm::vec3(0.0f, 1.0f, 0.0f));
            sleep_for(std::chrono::milliseconds(1));
        }

        //Graficar cubos pequeños
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    glBindVertexArray(My_Rubik_Cube->small_cubes[i][j][k]->cubeVAO);
                    model = My_Rubik_Cube->small_cubes[i][j][k]->model;
                    lightingShader.setMat4("model", model);

                    for (int l = 0; l < 6; l++) {
                        //Partición de la textura para cada mini cubo
                        glBindTexture(GL_TEXTURE_2D, texture[l]);
                        glDrawArrays(GL_TRIANGLES, l * 6, 6);
                    }
                }
            }
        }
        //Graficar de nuevo cubo de en medio para la lámpara, para que gire alrededor 
        glBindVertexArray(My_Rubik_Cube->small_cubes[1][1][1]->cubeVAO);
        model = My_Rubik_Cube->small_cubes[1][1][1]->model;
        lightingShader.setMat4("model", model);
        for (int l = 0; l < 6; l++) {
            glBindTexture(GL_TEXTURE_2D, texture[l]);
            glDrawArrays(GL_TRIANGLES, l * 6, 6);
        }
        unsigned int VBO, lightCubeVAO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(My_Rubik_Cube->small_cubes[1][1][1]->vertices), My_Rubik_Cube->small_cubes[1][1][1]->vertices, GL_STATIC_DRAW);
        //light cube (lamp)
        glGenVertexArrays(1, &lightCubeVAO);
        glBindVertexArray(lightCubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // note that we update the lamp's position attribute's stride to reflect the updated buffer data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // also draw the lamp object (lámpara)
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.4f)); // a smaller cube
        lampShader.setMat4("model", model);
        //Dibujando lámpara: cubo blanco para la luz (orbita o no)
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Para el cubo: Rotaciones y solver
        lightingShader.use();

        if (resolver) { //Si está resolviendo, la cámara rota en forma de espiral
            sol_movs(); //Contador de cuántos movimientos faltan para terminar de resolver el Cubo
            //Combinación de teclas Up y Left
            angy -= 0.1; //Para hacer un UP
            view = glm::rotate(view, glm::radians(angy), glm::vec3(1.0f, 0.0f, 0.0f));
            sleep_for(std::chrono::nanoseconds(1000));
            angx -= 0.1; //Para hacer un LEFT
            view = glm::rotate(view, glm::radians(angx), glm::vec3(0.0f, 1.0f, 0.0f));
            sleep_for(std::chrono::nanoseconds(1000));
        }
        lightingShader.setMat4("view", view);
        //Rotaciones
        if ((clockwise >> 0) & 1) {
            My_Rubik_Cube->front_back_animation_hor(clockwise, 0); //Front F
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }
        if ((counter_clockwise >> 0) & 1) {
            My_Rubik_Cube->front_back_animation_anthor(counter_clockwise, 0); //Front' J
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }

        if ((clockwise >> 1) & 1) {
            My_Rubik_Cube->front_back_animation_hor(clockwise, 2); //Back B
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }
        if ((counter_clockwise >> 1) & 1) {
            My_Rubik_Cube->front_back_animation_anthor(counter_clockwise, 2); //Back' K
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }

        if ((clockwise >> 2) & 1) {
            My_Rubik_Cube->left_right_animation_hor(clockwise, 0); //Left L 
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }
        if ((counter_clockwise >> 2) & 1) {
            My_Rubik_Cube->left_right_animation_anthor(counter_clockwise, 0); //Left' Y
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }

        if ((clockwise >> 3) & 1) {
            My_Rubik_Cube->left_right_animation_hor(clockwise, 2); //Right R  
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }
        if ((counter_clockwise >> 3) & 1) {
            My_Rubik_Cube->left_right_animation_anthor(counter_clockwise, 2); //Right' H
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }

        if ((clockwise >> 4) & 1) {
            My_Rubik_Cube->up_down_animation_hor(clockwise, 0); //Up U
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }
        if ((counter_clockwise >> 4) & 1) {
            My_Rubik_Cube->up_down_animation_anthor(counter_clockwise, 0); //Up' I
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }

        if ((clockwise >> 5) & 1) {
            My_Rubik_Cube->up_down_animation_hor(clockwise, 2); //Down O
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }
        if ((counter_clockwise >> 5) & 1) {
            My_Rubik_Cube->up_down_animation_anthor(counter_clockwise, 2); //Down' P
            if (!clockwise && resolver && !counter_clockwise) current_sol++;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_J && action == GLFW_PRESS) { //Front F
        if (!clockwise && !counter_clockwise) {
            counter_clockwise = 1 << 0;
            teclado_mov += "F";
        }
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) { //Front' J
        if (!counter_clockwise && !clockwise) {
            clockwise = 1 << 0;
            teclado_mov += "FFF";
        }
    }
    if (key == GLFW_KEY_K && action == GLFW_PRESS) { //Back B 
        if (!clockwise && !counter_clockwise) {
            counter_clockwise = 1 << 1;
            teclado_mov += "BBB";
        }
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS) { //Back' K
        if (!counter_clockwise && !clockwise) {
            clockwise = 1 << 1;
            teclado_mov += "B";
        }
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS) { //Left L
        if (!clockwise && !counter_clockwise) {
            clockwise = 1 << 2;
            teclado_mov += "L";
        }
    }
    if (key == GLFW_KEY_Y && action == GLFW_PRESS) { //Left' Y
        if (!counter_clockwise && !clockwise) {
            counter_clockwise = 1 << 2;
            teclado_mov += "LLL";
        }
    }
    if (key == GLFW_KEY_H && action == GLFW_PRESS) { //Right R
        if (!clockwise && !counter_clockwise) {
            counter_clockwise = 1 << 3;
            teclado_mov += "R";
        }
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) { //Right' H
        if (!counter_clockwise && !clockwise) {
            clockwise = 1 << 3;
            teclado_mov += "RRR";
        }
    }
    if (key == GLFW_KEY_U && action == GLFW_PRESS) { //Up U
        if (!clockwise && !counter_clockwise) {
            clockwise = 1 << 4;
            teclado_mov += "UUU";
        }
    }
    if (key == GLFW_KEY_I && action == GLFW_PRESS) { //Up' I
        if (!counter_clockwise && !clockwise) {
            counter_clockwise = 1 << 4;
            teclado_mov += "U";
        }
    }
    if (key == GLFW_KEY_O && action == GLFW_PRESS) { //Down O
        if (!clockwise && !counter_clockwise) {
            clockwise = 1 << 5;
            teclado_mov += "D";
        }
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) { //Down' P
        if (!counter_clockwise && !clockwise) {
            counter_clockwise = 1 << 5;
            teclado_mov += "DDD";
        }
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) { //Solver
        if (!resolver) {
            sol = Solver_string(teclado_mov);
            if (!sol.empty()) solver_(movements), resolver = true;
        }
    }
}

void menu() {
    std::cout << "-----Rubik's Cube-----" << std::endl;
    std::cout << "J : Giro Cara Frontal (horario)" << std::endl;
    std::cout << "F : Giro Cara Frontal (antihorario)" << std::endl;
    std::cout << "B : Giro cara Back (horario)" << std::endl;
    std::cout << "K : Giro cara Back (antihorario)" << std::endl;
    std::cout << "L : Giro cara Left (horario)" << std::endl;
    std::cout << "Y : Giro cara Left (antihorario)" << std::endl;
    std::cout << "H : Giro cara Right (horario)" << std::endl;
    std::cout << "R : Giro cara Right (antihorario)" << std::endl;
    std::cout << "U : Giro cara Up (horario)" << std::endl;
    std::cout << "I : Giro cara Up (antihorario)" << std::endl;
    std::cout << "O : Giro cara Down (horario)" << std::endl;
    std::cout << "P : Giro cara Down (antihorario)" << std::endl;
    std::cout << std::endl;
    std::cout << "-----Camera-----" << std::endl;
    std::cout << "W : Zoom Out" << std::endl;
    std::cout << "S : Zoom In" << std::endl;
    std::cout << "D : Movimiento a la derecha " << std::endl;
    std::cout << "A : Movimiento a la izquierda " << std::endl;
    std::cout << "2 : Movimiento a arriba" << std::endl;
    std::cout << "0 : Movimiento a abajo" << std::endl;
    std::cout << "UP : Girar hacia arriba" << std::endl;
    std::cout << "DOWN : Girar hacia abajo" << std::endl;
    std::cout << "LEFT : Girar hacia la izquierda" << std::endl;
    std::cout << "RIGHT : Girar hacia la derecha" << std::endl;
    std::cout << std::endl;
    std::cout << "-----Solver-----" << std::endl; 
    std::cout << "4 : Ordenar el Cubo de Rubik" << std::endl;
    std::cout << std::endl;
    std::cout << "-----Luz orbitando-----" << std::endl;
    std::cout << "Q : Luz orbita alrededor del Cubo de Rubik" << std::endl;
    std::cout << "Z : Luz para de orbitar alrededor del Cubo de Rubik" << std::endl;
    std::cout << std::endl;
    return;
}

std::string Solver_string(std::string moves) {
    if (!moves.size()) {
        std::cout << "No hubo movimientos = No se resuelve.\n";
        return "";
    }
    else {
        std::cout << "Secuencia a resolver: " << moves << std::endl;
        Cube myCube;
        myCube.moves(moves);
        //Para resolver la cadena
        myCube.xd = true;
        Cross::solveCross(myCube);
        Corners::solveCorners(myCube);
        Edges::solveEdges(myCube);
        OLL::solveOLL(myCube);
        PLL::solvePLL(myCube);
        std::cout << "Solution: " << myCube.mov << std::endl << std::endl;
        return myCube.mov;
    }
}

void solver_(std::vector<int>& moves) {
    std::vector<std::string> tokens;
    moves.clear();
    for (auto i = strtok(&sol[0], " "); i != NULL; i = strtok(NULL, " "))
        tokens.push_back(i);
    sol.clear();
    int r;
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "R")
            r = -1 * (1 << 3);
        if (tokens[i] == "L")
            r = 1 << 2;
        if (tokens[i] == "U")
            r = -1 * (1 << 4);
        if (tokens[i] == "D")
            r = 1 << 5;
        if (tokens[i] == "F")
            r = -1 * (1 << 0);
        if (tokens[i] == "B")
            r = 1 << 1;
        if (tokens[i] == "R'")
            r = 1 << 3;
        if (tokens[i] == "L'")
            r = -1 * (1 << 2);
        if (tokens[i] == "U'")
            r = 1 << 4;
        if (tokens[i] == "D'")
            r = -1 * (1 << 5);
        if (tokens[i] == "F'")
            r = 1 << 0;
        if (tokens[i] == "B'")
            r = -1 * (1 << 1);
        if (tokens[i] == "R2") {
            r = -1 * (1 << 3);
            moves.push_back(r);
        }
        if (tokens[i] == "L2") {
            r = 1 << 2;
            moves.push_back(r);
        }
        if (tokens[i] == "U2") {
            r = -1 * (1 << 4);
            moves.push_back(r);
        }
        if (tokens[i] == "D2") {
            r = 1 << 5;
            moves.push_back(r);
        }
        if (tokens[i] == "F2") {
            r = -1 * (1 << 0);
            moves.push_back(r);
        }
        if (tokens[i] == "B2") {
            r = 1 << 1;
            moves.push_back(r);
        }
        moves.push_back(r);
    }
    tokens.clear();
}

void sol_movs() {
    if (current_sol < movements.size()) {
        if (movements[current_sol] >= 0) clockwise = movements[current_sol];
        else counter_clockwise = (-1) * (movements[current_sol]);
    }
    else {
        resolver = false;
        teclado_mov.clear();
        current_sol = 0;
        return;
    }
}