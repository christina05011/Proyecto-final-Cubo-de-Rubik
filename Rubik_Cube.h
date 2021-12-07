#ifndef RUBIK_CUBE_H
#define RUBIK_CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

float PI = 3.1415926536;

class Small_Cube {
public:
    float vertices[396]; //396 = 6 caras * 11 valores * 6 vértices
    unsigned int cubeVAO, VBO;
    glm::mat4 model;
    Small_Cube() {
        cubeVAO = 0;
        VBO = 0;
        model = glm::mat4(1.0f);
        float vertices_[] = {
            //coordenadas(x,y,z)  //colores RGB      //texturas   //Normal(lighting)
            //CARA DE ATRÁS
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,//A
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,//B
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,//C
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,//D
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,//E
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,//F

            //CARA DE ADELANTE
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

            //CARA IZQUIERDA
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,

            //CARA DERECHA
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

             //CARA DE ABAJO
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

            //CARA ARRIBA
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f
        };
        //Igualar y normalizar
        for (int i = 0; i < 396; i += 11) {
            vertices[i + 0] = vertices_[i + 0] / 5;
            vertices[i + 1] = vertices_[i + 1] / 5;
            vertices[i + 2] = vertices_[i + 2] / 5;
            vertices[i + 3] = vertices_[i + 3];
            vertices[i + 4] = vertices_[i + 4];
            vertices[i + 5] = vertices_[i + 5];
            vertices[i + 6] = vertices_[i + 6];
            vertices[i + 7] = vertices_[i + 7];
            vertices[i + 8] = vertices_[i + 8];
            vertices[i + 9] = vertices_[i + 9];
            vertices[i + 10] = vertices_[i + 10];
        }
    }
    void set_position(glm::vec3 p)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, p);
    }
    void rotation_animation(glm::vec3 dimension, float angle, glm::vec3 p) {
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(angle), dimension);
        model = glm::translate(model, p);
    }
    //Graficar datos del big_cube: color, position, texture y normal.
    void set_vertex_vao() {
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // normal attribute
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }
    void rotation_x(int n, float a, int r) {
        float y, z;
        for (int i = 0; i < n; i += r) {
            y = vertices[i + 1] * cos(a * PI / 180) - sin(a * PI / 180) * vertices[i + 2];
            z = vertices[i + 1] * sin(a * PI / 180) + cos(a * PI / 180) * vertices[i + 2];
            vertices[i + 1] = y;
            vertices[i + 2] = z;
        }
    }
    void rotation_y(int n, float a, int r) {
        float x, z;
        for (int i = 0; i < n; i += r) {
            x = vertices[i] * cos(a * PI / 180) + sin(a * PI / 180) * vertices[i + 2];
            z = -1.0 * vertices[i] * sin(a * PI / 180) + cos(a * PI / 180) * vertices[i + 2];
            vertices[i] = x;
            vertices[i + 2] = z;
        }
    }
    void rotation_z(int n, float a, int r) {
        float x, y;
        for (int i = 0; i < n; i += r) {
            x = vertices[i] * cos(a * PI / 180) - sin(a * PI / 180) * vertices[i + 1];
            y = vertices[i] * sin(a * PI / 180) + cos(a * PI / 180) * vertices[i + 1];
            vertices[i] = x;
            vertices[i + 1] = y;
        }
    }
};

class Big_Cube {
public:
    std::vector<std::vector<Small_Cube*> > small_cubes[3];
    std::vector<std::vector<glm::vec3> > initial_positions[3]; //Actualizar posiciones a estas posiciones iniciales, para que el cubo vuelva a la normalidad
    int n_animation;
    float angle;

    Big_Cube() {
        n_animation = 0;
        angle = 0.75;
        //Crear los 27 mini cubos
        for (int i = 0; i < 3; ++i) {
            small_cubes[i] = std::vector<std::vector<Small_Cube*> >(3, std::vector< Small_Cube* >(3, nullptr));
            initial_positions[i] = std::vector<std::vector<glm::vec3> >(3, std::vector<glm::vec3>(3, glm::vec3(0.f, 0.f, 0.f)));
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k)
                    small_cubes[i][j][k] = new Small_Cube();
            }
        }
        //Transformar sus posiciones a cada mini cubo para formar el cubo grande
        float y = 0.2, x, z;
        for (int i = 0; i < 3; ++i) {
            x = -0.2;
            for (int j = 0; j < 3; ++j) {
                z = 0.2;
                for (int k = 0; k < 3; ++k) {
                    initial_positions[i][j][k] = glm::vec3(x, y, z);
                    small_cubes[i][j][k]->set_position(glm::vec3(x, y, z));
                    z -= 0.20;
                }
                x += 0.20;
            }
            y -= 0.20;
        }

        Vcolor();
        Ttextura();
        //Actualizar los datos de los mini cubos
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k)
                    small_cubes[i][j][k]->set_vertex_vao();
            }
        }
    }

    void Vcolor() {
        //Posiciones de colores
        //COLOR DETRÁS          //ORANGE
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 66; k += 11) {
                    small_cubes[i][j][2]->vertices[k + 3] = 1.0f;
                    small_cubes[i][j][2]->vertices[k + 4] = 0.5f;
                }
            }
        }

        //COLOR ADELANTE        //RED
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 66; k < 132; k += 11)
                    small_cubes[i][j][0]->vertices[k + 3] = 1.0f;
            }
        }

        //COLOR IZQUIERDA       //GREEN
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 132; k < 198; k += 11)
                    small_cubes[i][0][j]->vertices[k + 4] = 1.0f;
            }
        }

        //COLOR DERECHA         //BLUE
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 198; k < 264; k += 11) {
                    small_cubes[i][2][j]->vertices[k + 5] = 1.0f;
                }
            }
        }

        //COLOR ABAJO           //YELLOW
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 264; k < 330; k += 11) {
                    small_cubes[2][i][j]->vertices[k + 3] = 1.0f;
                    small_cubes[2][i][j]->vertices[k + 4] = 1.0f;
                }
            }
        }

        //COLOR ARRIBA          //WHITE
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 330; k < 396; k += 11) {
                    small_cubes[0][i][j]->vertices[k + 3] = 1.0f;
                    small_cubes[0][i][j]->vertices[k + 4] = 1.0f;
                    small_cubes[0][i][j]->vertices[k + 5] = 1.0f;
                }
            }
        }
    }

    void Ttextura() {
        //Posiciones de textura //Delimitadores de cada mini cubo
        //Para que cada cara tenga la textura de 9 mini cubos
        //CARA DE ATRÁS         //ORANGE
        float y = 0, x;
        float y1 = 0.333333, x1;
        for (int i = 0; i < 3; ++i) {
            x = 0;
            x1 = 0.333333;
            for (int j = 0; j < 3; ++j) {
                //A
                small_cubes[i][j][2]->vertices[6] = x;
                small_cubes[i][j][2]->vertices[7] = y1;

                //F
                small_cubes[i][j][2]->vertices[61] = x;
                small_cubes[i][j][2]->vertices[62] = y1;

                //B
                small_cubes[i][j][2]->vertices[17] = x1;
                small_cubes[i][j][2]->vertices[18] = y1;

                //C
                small_cubes[i][j][2]->vertices[28] = x1;
                small_cubes[i][j][2]->vertices[29] = y;

                //D
                small_cubes[i][j][2]->vertices[39] = x1;
                small_cubes[i][j][2]->vertices[40] = y;

                //E
                small_cubes[i][j][2]->vertices[50] = x;
                small_cubes[i][j][2]->vertices[51] = y;
                x += 0.3333333;
                x1 += 0.333333;
                if (x1 >= 0.9) x1 = 1;
            }
            y += 0.3333333;
            y1 += 0.3333333;
            if (y1 >= 0.9) y1 = 1;
        }

        // CARA DE ADELANTE         //RED
        y = 0;
        y1 = 0.333333;
        for (int i = 0; i < 3; ++i) {
            x = 0;
            x1 = 0.333333;
            for (int j = 0; j < 3; ++j) {
                //A
                small_cubes[i][j][0]->vertices[6 + 66] = x;
                small_cubes[i][j][0]->vertices[7 + 66] = y1;

                //F
                small_cubes[i][j][0]->vertices[61 + 66] = x;
                small_cubes[i][j][0]->vertices[62 + 66] = y1;

                //B
                small_cubes[i][j][0]->vertices[17 + 66] = x1;
                small_cubes[i][j][0]->vertices[18 + 66] = y1;

                //C
                small_cubes[i][j][0]->vertices[28 + 66] = x1;
                small_cubes[i][j][0]->vertices[29 + 66] = y;

                //D
                small_cubes[i][j][0]->vertices[39 + 66] = x1;
                small_cubes[i][j][0]->vertices[40 + 66] = y;

                //E
                small_cubes[i][j][0]->vertices[50 + 66] = x;
                small_cubes[i][j][0]->vertices[51 + 66] = y;
                x += 0.3333333;
                x1 += 0.333333;
                if (x1 >= 0.9) x1 = 1;
            }
            y += 0.3333333;
            y1 += 0.3333333;
            if (y1 >= 0.9) y1 = 1;
        }

        // CARA DE IZQUIERDA        //GREEN
        y = 0;
        y1 = 0.333333;
        for (int i = 0; i < 3; ++i) {
            x = 0.0;
            x1 = 0.3333333;
            for (int j = 0; j < 3; ++j) {
                //A
                small_cubes[i][0][j]->vertices[132 + 6] = x;
                small_cubes[i][0][j]->vertices[132 + 7] = y;

                //F
                small_cubes[i][0][j]->vertices[132 + 61] = x;
                small_cubes[i][0][j]->vertices[132 + 62] = y;

                //B
                small_cubes[i][0][j]->vertices[132 + 17] = x1;
                small_cubes[i][0][j]->vertices[132 + 18] = y;

                //C         
                small_cubes[i][0][j]->vertices[132 + 28] = x1;
                small_cubes[i][0][j]->vertices[132 + 29] = y1;

                //D
                small_cubes[i][0][j]->vertices[132 + 39] = x1;
                small_cubes[i][0][j]->vertices[132 + 40] = y1;

                //E
                small_cubes[i][0][j]->vertices[132 + 50] = x;
                small_cubes[i][0][j]->vertices[132 + 51] = y1;
                x += 0.3333333;
                x1 += 0.3333333;
                if (x1 >= 0.9) x1 = 1;
            }
            y += 0.3333333;
            y1 += 0.3333333;
            if (y1 >= 0.9) y1 = 1;
        }

        // CARA DERECHA         //BLUE
        y = 0;
        y1 = 0.333333;
        for (int i = 0; i < 3; ++i) {
            x = 0.0;
            x1 = 0.3333333;
            for (int j = 0; j < 3; ++j) {
                //A
                small_cubes[i][2][j]->vertices[198 + 6] = x;
                small_cubes[i][2][j]->vertices[198 + 7] = y;

                //F
                small_cubes[i][2][j]->vertices[198 + 61] = x;
                small_cubes[i][2][j]->vertices[198 + 62] = y;

                //B
                small_cubes[i][2][j]->vertices[198 + 17] = x1;
                small_cubes[i][2][j]->vertices[198 + 18] = y;

                //C         
                small_cubes[i][2][j]->vertices[198 + 28] = x1;
                small_cubes[i][2][j]->vertices[198 + 29] = y1;

                //D
                small_cubes[i][2][j]->vertices[198 + 39] = x1;
                small_cubes[i][2][j]->vertices[198 + 40] = y1;

                //E
                small_cubes[i][2][j]->vertices[198 + 50] = x;
                small_cubes[i][2][j]->vertices[198 + 51] = y1;
                x += 0.3333333;
                x1 += 0.3333333;
                if (x1 >= 0.9) x1 = 1;
            }
            y += 0.3333333;
            y1 += 0.3333333;
            if (y1 >= 0.9) y1 = 1;
        }

        // CARA DE ABAJO            //YELLOW
        x = 0;
        x1 = 0.333333;
        for (int i = 0; i < 3; ++i) {
            y = 0.0;
            y1 = 0.3333333;
            for (int j = 0; j < 3; ++j) {
                //A
                small_cubes[2][i][j]->vertices[264 + 6] = x;
                small_cubes[2][i][j]->vertices[264 + 7] = y1;

                //F
                small_cubes[2][i][j]->vertices[264 + 61] = x;
                small_cubes[2][i][j]->vertices[264 + 62] = y1;

                //B
                small_cubes[2][i][j]->vertices[264 + 17] = x1;
                small_cubes[2][i][j]->vertices[264 + 18] = y1;

                //C         
                small_cubes[2][i][j]->vertices[264 + 28] = x1;
                small_cubes[2][i][j]->vertices[264 + 29] = y;

                //D
                small_cubes[2][i][j]->vertices[264 + 39] = x1;
                small_cubes[2][i][j]->vertices[264 + 40] = y;

                //E
                small_cubes[2][i][j]->vertices[264 + 50] = x;
                small_cubes[2][i][j]->vertices[264 + 51] = y;
                y += 0.3333333;
                y1 += 0.3333333;
                if (y1 >= 0.9) y1 = 1;
            }
            x += 0.3333333;
            x1 += 0.3333333;
            if (x1 >= 0.9) x1 = 1;
        }

        // CARA DE ARRIBA           //WHITE
        x = 0;
        x1 = 0.333333;
        for (int i = 0; i < 3; ++i) {
            y = 0.0;
            y1 = 0.3333333;
            for (int j = 0; j < 3; ++j) {
                //A
                small_cubes[0][i][j]->vertices[330 + 6] = x;
                small_cubes[0][i][j]->vertices[330 + 7] = y1;

                //F
                small_cubes[0][i][j]->vertices[330 + 61] = x;
                small_cubes[0][i][j]->vertices[330 + 62] = y1;

                //B
                small_cubes[0][i][j]->vertices[330 + 17] = x1;
                small_cubes[0][i][j]->vertices[330 + 18] = y1;

                //C         
                small_cubes[0][i][j]->vertices[330 + 28] = x1;
                small_cubes[0][i][j]->vertices[330 + 29] = y;

                //D
                small_cubes[0][i][j]->vertices[330 + 39] = x1;
                small_cubes[0][i][j]->vertices[330 + 40] = y;

                //E
                small_cubes[0][i][j]->vertices[330 + 50] = x;
                small_cubes[0][i][j]->vertices[330 + 51] = y;
                y += 0.3333333;
                y1 += 0.3333333;
                if (y1 >= 0.9) y1 = 1;
            }
            x += 0.3333333;
            x1 += 0.3333333;
            if (x1 >= 0.9)  x1 = 1;
        }
    }

    void Nnormal(int x, int anm, bool hor) {
        //Cambiar vectores normal respecto a las animaciones y sentido
        if (!anm) { //ANIMATION BACK_FRONT
            if (hor) { //sentido horario
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 66; k += 11) { //Cara de atrás = Cara de izquierda
                            small_cubes[i][j][x]->vertices[k + 8] = -1.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 66; k < 132; k += 11) { //Cara de adelante = Cara de derecha
                            small_cubes[i][j][x]->vertices[k + 8] = 1.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 132; k < 198; k += 11) { //Cara de izquierda = Cara de adelante
                            small_cubes[i][j][x]->vertices[k + 8] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = 1.0f;
                        }
                        for (int k = 198; k < 264; k += 11) { //Cara de derecha = Cara de atrás
                            small_cubes[i][j][x]->vertices[k + 8] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = -1.0f;
                        }
                    }
                }
            }
            else { //sentido anti horario
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 66; k += 11) { //Cara de atrás = Cara de derecha
                            small_cubes[i][j][x]->vertices[k + 8] = 1.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 66; k < 132; k += 11) { //Cara de adelante = Cara de izquierda
                            small_cubes[i][j][x]->vertices[k + 8] = -1.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 132; k < 198; k += 11) { //Cara de izquierda = Cara de atrás
                            small_cubes[i][j][x]->vertices[k + 8] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = -1.0f;
                        }
                        for (int k = 198; k < 264; k += 11) { //Cara de derecha = Cara de adelante
                            small_cubes[i][j][x]->vertices[k + 8] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 9] = 0.0f;
                            small_cubes[i][j][x]->vertices[k + 10] = 1.0f;
                        }
                    }
                }
            }
        }
        else if (anm == 1) { //ANIMATION LEFT_RIGHT 
            if (hor) { //sentido horario
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 66; k += 11) { //Cara de atrás = Cara de izquierda
                            small_cubes[i][x][j]->vertices[k + 8] = -1.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 66; k < 132; k += 11) { //Cara de adelante = Cara de derecha
                            small_cubes[i][x][j]->vertices[k + 8] = 1.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 132; k < 198; k += 11) { //Cara de izquierda = Cara de adelante
                            small_cubes[i][x][j]->vertices[k + 8] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = 1.0f;
                        }
                        for (int k = 198; k < 264; k += 11) { //Cara de derecha = Cara de atrás
                            small_cubes[i][x][j]->vertices[k + 8] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = -1.0f;
                        }
                    }
                }
            }
            else { //sentido anti horario
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 66; k += 11) { //Cara de atrás = Cara de derecha
                            small_cubes[i][x][j]->vertices[k + 8] = 1.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 66; k < 132; k += 11) { //Cara de adelante = Cara de izquierda
                            small_cubes[i][x][j]->vertices[k + 8] = -1.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 132; k < 198; k += 11) { //Cara de izquierda = Cara de atrás
                            small_cubes[i][x][j]->vertices[k + 8] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = -1.0f;
                        }
                        for (int k = 198; k < 264; k += 11) { //Cara de derecha = Cara de adelante
                            small_cubes[i][x][j]->vertices[k + 8] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 9] = 0.0f;
                            small_cubes[i][x][j]->vertices[k + 10] = 1.0f;
                        }
                    }
                }
            }
        }
        else if (anm == 2) { //ANIMATION UP_DOWN
            if (hor) { //sentido horario
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 66; k += 11) { //Cara de atrás = Cara de izquierda
                            small_cubes[x][i][j]->vertices[k + 8] = -1.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 66; k < 132; k += 11) { //Cara de adelante = Cara de derecha
                            small_cubes[x][i][j]->vertices[k + 8] = 1.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 132; k < 198; k += 11) { //Cara de izquierda = Cara de adelante
                            small_cubes[x][i][j]->vertices[k + 8] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = 1.0f;
                        }
                        for (int k = 198; k < 264; k += 11) { //Cara de derecha = Cara de atrás
                            small_cubes[x][i][j]->vertices[k + 8] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = -1.0f;
                        }
                    }
                }
            }
            else { //sentido anti horario
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 66; k += 11) { //Cara de atrás = Cara de derecha
                            small_cubes[x][i][j]->vertices[k + 8] = 1.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 66; k < 132; k += 11) { //Cara de adelante = Cara de izquierda
                            small_cubes[x][i][j]->vertices[k + 8] = -1.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = 0.0f;
                        }
                        for (int k = 132; k < 198; k += 11) { //Cara de izquierda = Cara de atrás
                            small_cubes[x][i][j]->vertices[k + 8] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = -1.0f;
                        }
                        for (int k = 198; k < 264; k += 11) { //Cara de derecha = Cara de adelante
                            small_cubes[x][i][j]->vertices[k + 8] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 9] = 0.0f;
                            small_cubes[x][i][j]->vertices[k + 10] = 1.0f;
                        }
                    }
                }
            }
        }
    }

    //ANIMATION BACK_FRONT // ROTATION Z
    void update_pointer_front_back_hor(int x) {
        Small_Cube* tmp1 = nullptr;
        Small_Cube* tmp2 = nullptr;
        //Esquinas
        tmp1 = small_cubes[0][0][x]; // 0
        small_cubes[0][0][x] = small_cubes[0][2][x]; // 0->2
        tmp2 = small_cubes[2][0][x]; // 6
        small_cubes[2][0][x] = tmp1; // 6->0
        tmp1 = small_cubes[2][2][x]; // 8
        small_cubes[2][2][x] = tmp2; // 8->6
        small_cubes[0][2][x] = tmp1; // 2->8

        //Nodos
        tmp1 = small_cubes[0][1][x]; // 1
        small_cubes[0][1][x] = small_cubes[1][2][x]; // 1->5
        tmp2 = small_cubes[1][0][x]; // 3
        small_cubes[1][0][x] = tmp1; // 3->1
        tmp1 = small_cubes[2][1][x]; // 7
        small_cubes[2][1][x] = tmp2; // 7->3
        small_cubes[1][2][x] = tmp1; // 5->7
    }
    void update_pointer_front_back_anthor(int x) {
        Small_Cube* tmp1 = nullptr;
        Small_Cube* tmp2 = nullptr;
        //Esquinas
        tmp1 = small_cubes[0][0][x]; // 0
        small_cubes[0][0][x] = small_cubes[2][0][x]; // 0->6
        tmp2 = small_cubes[0][2][x]; // 2
        small_cubes[0][2][x] = tmp1; // 2->0
        tmp1 = small_cubes[2][2][x]; // 8
        small_cubes[2][2][x] = tmp2; // 8->2
        small_cubes[2][0][x] = tmp1; // 6->8

        //Nodos
        tmp1 = small_cubes[1][0][x]; // 3
        small_cubes[1][0][x] = small_cubes[2][1][x]; // 3->7
        tmp2 = small_cubes[0][1][x]; // 1
        small_cubes[0][1][x] = tmp1; // 1->3
        tmp1 = small_cubes[1][2][x]; // 5
        small_cubes[1][2][x] = tmp2; // 5->1
        small_cubes[2][1][x] = tmp1; // 7->5
    }
    void front_back_animation_hor(int& activation, int x) {
        //Visualizar rotation
        if (n_animation < 121) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->rotation_animation(glm::vec3(0.0, 0.0, 1.0), angle * n_animation, initial_positions[i][j][x]);
            }
            n_animation++;
        }
        else {
            //PASO 1. CAMBIAR LOS PUNTEROS, cuando termina la rotation.
            activation = 0;
            n_animation = 0;
            update_pointer_front_back_hor(x);
            //1.2 ACTUALIZAR POSICIONES INICIALES, para que vuelva a ser el mismo static cubo. //Un solo cubo.
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->set_position(initial_positions[i][j][x]);
            }
            //PASO 2. CAMBIAR LOS VERTICES originales
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->rotation_z(396, 90.0, 11);
            }
            //PASO 3. Actualizar los vectores NORMAL
            Nnormal(x, 0, 1);
            //PASO 4. Actualizar los vao
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->set_vertex_vao();
            }
        }
    }
    void front_back_animation_anthor(int& activation, int x) {
        //Visualizar rotation
        if (n_animation < 121) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->rotation_animation(glm::vec3(0.0, 0.0, 1.0), angle * n_animation * -1, initial_positions[i][j][x]);
            }
            n_animation++;
        }
        else {
            //PASO 1. CAMBIAR LOS PUNTEROS
            activation = 0;
            n_animation = 0;
            update_pointer_front_back_anthor(x);
            //1.2 ACTUALIZAR POSICIONES INICIALES
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->set_position(initial_positions[i][j][x]);
            }
            //PASO 2. CAMBIAR LOS VERTICES originales
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->rotation_z(396, -90.0, 11);
            }
            //PASO 3. Actualizar los vectores NORMAL
            Nnormal(x, 0, 0);
            //PASO 4. Actualizar los vao
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][j][x]->set_vertex_vao();
            }
        }
    }

    //ANIMATION LEFT_RIGHT //ROTATION X
    void update_pointer_left_right_hor(int x) {
        Small_Cube* tmp1 = nullptr;
        Small_Cube* tmp2 = nullptr;
        //Esquinas
        tmp1 = small_cubes[0][x][0]; // 0
        small_cubes[0][x][0] = small_cubes[0][x][2]; // 0->2
        tmp2 = small_cubes[2][x][0]; // 6
        small_cubes[2][x][0] = tmp1; // 6->0
        tmp1 = small_cubes[2][x][2]; // 8
        small_cubes[2][x][2] = tmp2; // 8->6
        small_cubes[0][x][2] = tmp1; // 2->8

        //Nodos
        tmp1 = small_cubes[1][x][0]; // 3
        small_cubes[1][x][0] = small_cubes[0][x][1]; // 3->1
        tmp2 = small_cubes[2][x][1]; // 7
        small_cubes[2][x][1] = tmp1; // 7->3
        tmp1 = small_cubes[1][x][2]; // 5
        small_cubes[1][x][2] = tmp2; // 5->7
        small_cubes[0][x][1] = tmp1; // 1->5 
    }
    void update_pointer_left_right_anthor(int x) {
        Small_Cube* tmp1 = nullptr;
        Small_Cube* tmp2 = nullptr;
        //Esquinas
        tmp1 = small_cubes[0][x][0]; // 0
        small_cubes[0][x][0] = small_cubes[2][x][0]; // 0->6
        tmp2 = small_cubes[0][x][2]; // 2
        small_cubes[0][x][2] = tmp1; // 2->0
        tmp1 = small_cubes[2][x][2]; // 8
        small_cubes[2][x][2] = tmp2; // 8->2
        small_cubes[2][x][0] = tmp1; // 6->8

        //Nodos
        tmp1 = small_cubes[1][x][0]; // 3
        small_cubes[1][x][0] = small_cubes[2][x][1]; // 3->7
        tmp2 = small_cubes[0][x][1]; // 1
        small_cubes[0][x][1] = tmp1; // 1->3
        tmp1 = small_cubes[1][x][2]; // 5
        small_cubes[1][x][2] = tmp2; // 5->1
        small_cubes[2][x][1] = tmp1; // 7->5
    }
    void left_right_animation_hor(int& activation, int x) {
        //Visualizar rotation
        if (n_animation < 121) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->rotation_animation(glm::vec3(1.0, 0.0, 0.0), angle * n_animation, initial_positions[i][x][j]);
            }
            n_animation++;
        }
        else {
            //PASO 1. CAMBIAR LOS PUNTEROS
            activation = 0;
            n_animation = 0;
            update_pointer_left_right_hor(x);
            //1.2 ACTUALIZAR POSICIONES INICIALES
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->set_position(initial_positions[i][x][j]);
            }
            //PASO 2. CAMBIAR LOS VERTICES originales
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->rotation_x(396, 90.0, 11);
            }
            //PASO 3. Actualizar los vectores NORMAL
            Nnormal(x, 1, 1);
            //PASO 4. Actualizar los vao
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->set_vertex_vao();
            }
        }
    }
    void left_right_animation_anthor(int& activation, int x) {
        //Visualizar rotation
        if (n_animation < 121) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->rotation_animation(glm::vec3(1.0, 0.0, 0.0), angle * n_animation * -1, initial_positions[i][x][j]);
            }
            n_animation++;
        }
        else {
            //PASO 1. CAMBIAR LOS PUNTEROS
            activation = 0;
            n_animation = 0;
            update_pointer_left_right_anthor(x);
            //1.2 ACTUALIZAR POSICIONES INICIALES
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->set_position(initial_positions[i][x][j]);
            }
            //PASO 2. CAMBIAR LOS VERTICES originales
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->rotation_x(396, -90.0, 11);
            }
            //PASO 3. Actualizar los vectores NORMAL
            Nnormal(x, 1, 0);
            //PASO 4. Actualizar los vao
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[i][x][j]->set_vertex_vao();
            }
        }
    }

    //ANIMATION UP_DOWN //ROTATION Y
    void update_pointer_up_down_hor(int x) {
        Small_Cube* tmp1 = nullptr;
        Small_Cube* tmp2 = nullptr;
        //Esquinas
        tmp1 = small_cubes[x][0][0]; // 0;
        small_cubes[x][0][0] = small_cubes[x][0][2]; // 0->2
        tmp2 = small_cubes[x][2][0]; // 6
        small_cubes[x][2][0] = tmp1; // 0->6
        tmp1 = small_cubes[x][2][2]; // 8
        small_cubes[x][2][2] = tmp2; // 0->8
        small_cubes[x][0][2] = tmp1; // 2->8

        //Nodos
        tmp1 = small_cubes[x][1][0]; // 3
        small_cubes[x][1][0] = small_cubes[x][0][1]; // 3->1
        tmp2 = small_cubes[x][2][1]; // 7
        small_cubes[x][2][1] = tmp1; // 7->3
        tmp1 = small_cubes[x][1][2]; // 5
        small_cubes[x][1][2] = tmp2; // 5->7
        small_cubes[x][0][1] = tmp1; // 1->5
    }
    void update_pointer_up_down_anthor(int x) {
        Small_Cube* tmp1 = nullptr;
        Small_Cube* tmp2 = nullptr;
        //Esquinas
        tmp1 = small_cubes[x][0][0]; // 0;
        small_cubes[x][0][0] = small_cubes[x][2][0]; // 0->6
        tmp2 = small_cubes[x][0][2]; // 2
        small_cubes[x][0][2] = tmp1; // 2->0
        tmp1 = small_cubes[x][2][2]; // 8
        small_cubes[x][2][2] = tmp2; // 8->2
        small_cubes[x][2][0] = tmp1; // 6->8

        //Nodos
        tmp1 = small_cubes[x][1][0]; // 3
        small_cubes[x][1][0] = small_cubes[x][2][1]; // 3->7
        tmp2 = small_cubes[x][0][1]; // 1
        small_cubes[x][0][1] = tmp1; // 1->3
        tmp1 = small_cubes[x][1][2]; // 5
        small_cubes[x][1][2] = tmp2; // 5->1
        small_cubes[x][2][1] = tmp1; // 7->5
    }
    void up_down_animation_hor(int& activation, int x) {
        //Visualizar rotation
        if (n_animation < 121) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->rotation_animation(glm::vec3(0.0, 1.0, 0.0), angle * n_animation, initial_positions[x][i][j]);
            }
            n_animation++;
        }
        else {
            //PASO 1. CAMBIAR LOS PUNTEROS
            activation = 0;
            n_animation = 0; 
            update_pointer_up_down_hor(x);
            //1.2 ACTUALIZAR POSICIONES INICIALES
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->set_position(initial_positions[x][i][j]);
            }
            //PASO 2. CAMBIAR LOS VERTICES originales
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->rotation_y(396, 90.0, 11);
            }
            //PASO 3. Actualizar los vectores NORMAL
            Nnormal(x, 2, 1);
            //PASO 4. Actualizar los vao
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->set_vertex_vao();
            }
        }
    }
    void up_down_animation_anthor(int& activation, int x) {
        //Visualizar rotation
        if (n_animation < 121) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->rotation_animation(glm::vec3(0.0, 1.0, 0.0), angle * n_animation * -1, initial_positions[x][i][j]);
            }
            n_animation++;
        }
        else {
            //PASO 1. CAMBIAR LOS PUNTEROS
            activation = 0;
            n_animation = 0;
            update_pointer_up_down_anthor(x);
            //1.2 ACTUALIZAR POSICIONES INICIALES
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->set_position(initial_positions[x][i][j]);
            }
            //PASO 2. CAMBIAR LOS VERTICES originales
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->rotation_y(396, -90.0, 11);
            }
            //PASO 3. Actualizar los vectores NORMAL
            Nnormal(x, 2, 0);
            //PASO 4. Actualizar los vao
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    small_cubes[x][i][j]->set_vertex_vao();
            }
        }
    }
};

#endif

