#include "Renderer.h"

#include <fstream>
#include <vector>

#include "Mesh.h"

namespace ToToEng
{
    Renderer::Renderer(Window* window, Camera* camera)
    {
        //glfwWindowHint(GLFW_DEPTH_BITS, 24);
        this->window = window;
        this->camera = camera;

        ShaderProgramSource shaderSource = parseShader("../res/shaders/Basic.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        shader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        shaderSource = parseShader("../res/shaders/Shape.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        shapeShader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        shaderSource = parseShader("../res/shaders/Lighting.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        lightShader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        shaderSource = parseShader("../res/shaders/Model.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        modelShader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        shaderSource = parseShader("../res/shaders/BasicModel.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        basicModelShader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        glCall(u_TransformLocation = glGetUniformLocation(shader, "u_Transform"));
        _ASSERT(u_TransformLocation != -1);

        glCall(u_ShapeTransformLocation = glGetUniformLocation(shapeShader, "u_Transform"));
        _ASSERT(u_TransformLocation != -1);

        glFrontFace(GL_CCW);

        //3D
        setProjection(perspective(radians(45.f),
                                  static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()),
                                  1.f, 6000.f));
        if (camera->thirdPersonCamera)
        {
            cameraPos = vec3(0.0f, 0.0f, -10.0f);
            view = lookAt(cameraPos, {0, 0, 0}, {0, 1, 0});
        }
        else
        {
            cameraPos = vec3(0.0f, 0.0f, 0.0f);
            view = lookAt(cameraPos, {0, 0, 0}, {0, 1, 0});
        }

        //2D
        /*setProjection(ortho(0.0f, static_cast<float>(window->getWidth()), 0.0f,
            static_cast<float>(window->getHeight()), 0.1f, 500.f));
        cameraPos = vec3(0.0f, 0.0f, 1.0f);*/


        dirLights[0] = new DirLight({0.5f, 0.5f, 0.5f}, {0.4f, 0.4f, 0.4f}, {0.5f, 0.5f, 0.5f}, {-0.2f, -1.0f, -0.3f});
        pointLights[0] = new PointLight({1.0f, 1.f, 1.f}, {10.0f, 10.f, 10.f}, {10.0f, 10.f, 10.f}, {0.0f, 0.0f, 10.0f},
                                        1.0f, 0.09f, 0.032f);
        spotLights[0] = new SpotLight({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f}, {10.0f, 10.0f, 10.0f}, {0, 25, 15},
                                      {0, -1, 0}, 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(10.5f)),
                                      glm::cos(glm::radians(10.5f)));

        //dirLights[0]->isOn = false;
        //pointLights[0]->isOn = false;
        //spotLights[0]->isOn = false;

        dirLightCount = 1;
        pointLightCount = 1;
        spotLightCount = 1;
    }

    Renderer::~Renderer()
    {
        glDeleteProgram(shader);
    }

    void Renderer::beginDraw()
    {
        glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Renderer::endDraw()
    {
        glCall(glfwSwapBuffers(window->getWindow()));
    }

    void Renderer::genVertexBuffer(unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int id,
                                   unsigned int qty)
    {
        glCall(glGenVertexArrays(id, &VAO));
        glCall(glGenBuffers(id, &VBO));

        glCall(glBindVertexArray(VAO));

        glCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * qty * 9, vertices, GL_STATIC_DRAW));

        glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), static_cast<void*>(0)));
        glCall(glEnableVertexAttribArray(0));

        glCall(
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)
            )));
        glCall(glEnableVertexAttribArray(1));

        glCall(
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(7 * sizeof(float)
            )));
        glCall(glEnableVertexAttribArray(2));
    }

    void Renderer::genVertexBuffer3D(unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int id,
                                     unsigned int qty)
    {
        glCall(glGenVertexArrays(id, &VAO));
        glCall(glGenBuffers(id, &VBO));

        glCall(glBindVertexArray(VAO));

        glCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * qty * 12, vertices, GL_STATIC_DRAW));

        glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), static_cast<void*>(0)));
        glCall(glEnableVertexAttribArray(0));

        glCall(
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float
                )
            )));
        glCall(glEnableVertexAttribArray(1));

        glCall(
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), reinterpret_cast<void*>(7 * sizeof(float
                )
            )));
        glCall(glEnableVertexAttribArray(2));

        glCall(
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), reinterpret_cast<void*>(9 * sizeof(float
                )
            )));
        glCall(glEnableVertexAttribArray(3));
    }

    void Renderer::genIndexBuffer(unsigned int& IBO,
                                  unsigned int indices[], unsigned int id, unsigned int qty)
    {
        glCall(glGenBuffers(id, &IBO));
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * qty, indices, GL_STATIC_DRAW));

        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        glCall(glBindVertexArray(0));
    }

    void Renderer::deleteBuffers(unsigned int& VBO, unsigned int& IBO, unsigned int& EBO, unsigned int id)
    {
        glDeleteVertexArrays(id, &VBO);
        glDeleteBuffers(id, &IBO);
        glDeleteBuffers(id, &EBO);
        glDeleteProgram(shader);
    }

    void Renderer::drawEntity2D(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans, unsigned int texture)
    {
        mat4 pvm = projection * view * trans;

        glCall(glUseProgram(shader));
        glCall(glUniform1i(glGetUniformLocation(shader, "ourTexture"), 0));
        glCall(u_ColorLocation = glGetUniformLocation(shader, "u_Color"));

        glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));

        glCall(glActiveTexture(GL_TEXTURE0));
        glCall(glBindTexture(GL_TEXTURE_2D, texture));
        glCall(glBindVertexArray(VAO));

        glCall(glUniformMatrix4fv(u_TransformLocation, 1, GL_FALSE, glm::value_ptr(pvm)));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::drawEntity3D(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans)
    {
        mat4 pvm = projection * view * trans;

        glCall(glUseProgram(shader));
        glCall(glUniform1i(glGetUniformLocation(shader, "ourTexture"), 0));
        glCall(u_ColorLocation = glGetUniformLocation(shader, "u_Color"));

        glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));
        glCall(glBindVertexArray(VAO));

        glCall(glUniformMatrix4fv(u_TransformLocation, 1, GL_FALSE, glm::value_ptr(pvm)));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::drawLightEntity3D(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans)
    {
        mat4 pvm = projection * view * trans;

        GLint u_Model = glGetUniformLocation(lightShader, "model");
        GLint u_View = glGetUniformLocation(lightShader, "view");
        GLint u_Projection = glGetUniformLocation(lightShader, "projection");

        GLint u_LightPos = glGetUniformLocation(lightShader, "lightPos");
        GLint u_ViewPos = glGetUniformLocation(lightShader, "viewPos");
        GLint u_LightColor = glGetUniformLocation(lightShader, "lightColor");
        GLint u_ObjectColor = glGetUniformLocation(lightShader, "objectColor");

        GLint u_MaterialAmbient = glGetUniformLocation(lightShader, "material.ambient");
        GLint u_MaterialDiffuse = glGetUniformLocation(lightShader, "material.diffuse");
        GLint u_MaterialSpecular = glGetUniformLocation(lightShader, "material.specular");
        GLint u_MaterialShininess = glGetUniformLocation(lightShader, "material.shininess");

        GLint u_LightAmbient = glGetUniformLocation(lightShader, "light.ambient");
        GLint u_LightDiffuse = glGetUniformLocation(lightShader, "light.diffuse");
        GLint u_LightSpecular = glGetUniformLocation(lightShader, "light.specular");


        glCall(glUseProgram(lightShader));
        //glCall(glUniform1i(glGetUniformLocation(shader, "ourTexture"), 0));
        //glCall(u_ColorLocation = glGetUniformLocation(shader, "u_Color"));

        //glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));
        glCall(glBindVertexArray(VAO));

        glCall(glUniformMatrix4fv(u_Model, 1, GL_FALSE, glm::value_ptr(view)));
        glCall(glUniformMatrix4fv(u_View, 1, GL_FALSE, glm::value_ptr(trans)));
        glCall(glUniformMatrix4fv(u_Projection, 1, GL_FALSE, glm::value_ptr(projection)));

        glCall(glUniform3f(u_LightPos, 0.0f, 0.0f, 0.0f));
        glCall(glUniform3f(u_ViewPos, cameraPos.x, cameraPos.y, cameraPos.z));
        glCall(glUniform3f(u_LightColor, 1.0f, 1.0f, 1.0f));
        glCall(glUniform3f(u_ObjectColor, color.x, color.y, color.z));

        glCall(glUniform3f(u_LightAmbient, 0.2f, 0.2f, 0.2f));
        glCall(glUniform3f(u_LightDiffuse, 0.5f, 0.5f, 0.5f));
        glCall(glUniform3f(u_LightSpecular, 1.0f, 1.0f, 1.0f));

        //Esmeralda
        glCall(glUniform3f(u_MaterialAmbient, 0.0215f, 0.1745f, 0.0215f));
        glCall(glUniform3f(u_MaterialDiffuse, 0.07568f, 0.61424f, 0.07568));
        glCall(glUniform3f(u_MaterialSpecular, 0.633f, 0.727811f, 0.633f));
        glCall(glUniform1f(u_MaterialShininess, 0.6f));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::drawModel3D(unsigned int& VAO, unsigned int indexQty, mat4 trans, std::vector<Texture> textures)
    {
        mat4 pvm = projection * view * trans;
        GLint u_Material;

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            u_Material = glGetUniformLocation(modelShader, ("material." + name + number).c_str());
            glUniform1f(u_Material, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        //DirLights
        GLint u_DirLightDirections[MAX_DIR_LIGHTS];
        GLint u_DirLightAmbients[MAX_DIR_LIGHTS];
        GLint u_DirLightDiffuses[MAX_DIR_LIGHTS];
        GLint u_DirLightSpeculars[MAX_DIR_LIGHTS];

        //PointLights
        GLint u_PointLightPositions[MAX_POINT_LIGHTS];
        GLint u_PointLightAmbients[MAX_POINT_LIGHTS];
        GLint u_PointLightDiffuses[MAX_POINT_LIGHTS];
        GLint u_PointLightSpeculars[MAX_POINT_LIGHTS];
        GLint u_PointLightConstants[MAX_POINT_LIGHTS];
        GLint u_PointLightLinears[MAX_POINT_LIGHTS];
        GLint u_PointLightQuadratics[MAX_POINT_LIGHTS];

        //Spotlights
        GLint u_SpotLightPositions[MAX_SPOT_LIGHTS];
        GLint u_SpotLightDirections[MAX_SPOT_LIGHTS];
        GLint u_SpotLightAmbients[MAX_SPOT_LIGHTS];
        GLint u_SpotLightDiffuses[MAX_SPOT_LIGHTS];
        GLint u_SpotLightSpeculars[MAX_SPOT_LIGHTS];
        GLint u_SpotLightConstants[MAX_SPOT_LIGHTS];
        GLint u_SpotLightLinears[MAX_SPOT_LIGHTS];
        GLint u_SpotLightQuadratics[MAX_SPOT_LIGHTS];
        GLint u_SpotLightCutOffs[MAX_SPOT_LIGHTS];
        GLint u_SpotLightOuterCutOffs[MAX_SPOT_LIGHTS];

        GLint u_PointLightCount = glGetUniformLocation(modelShader, "pointLightCount");
        GLint u_DirLightCount = glGetUniformLocation(modelShader, "dirLightCount");
        GLint u_SpotLightCount = glGetUniformLocation(modelShader, "spotLightCount");

        GLint u_Model = glGetUniformLocation(modelShader, "model");
        GLint u_View = glGetUniformLocation(modelShader, "view");
        GLint u_Proj = glGetUniformLocation(modelShader, "projection");

        GLint u_MaterialShininess = glGetUniformLocation(modelShader, "material.shininess");

        for (int i = 0; i < pointLightCount; ++i)
        {
            std::string lightPrefix = "pointLights[" + std::to_string(i) + "].";
            u_PointLightPositions[i] = glGetUniformLocation(modelShader, (lightPrefix + "position").c_str());
            u_PointLightAmbients[i] = glGetUniformLocation(modelShader, (lightPrefix + "ambient").c_str());
            u_PointLightDiffuses[i] = glGetUniformLocation(modelShader, (lightPrefix + "diffuse").c_str());
            u_PointLightSpeculars[i] = glGetUniformLocation(modelShader, (lightPrefix + "specular").c_str());
            u_PointLightConstants[i] = glGetUniformLocation(modelShader, (lightPrefix + "constant").c_str());
            u_PointLightLinears[i] = glGetUniformLocation(modelShader, (lightPrefix + "linear").c_str());
            u_PointLightQuadratics[i] = glGetUniformLocation(modelShader, (lightPrefix + "quadratic").c_str());
        }

        for (int i = 0; i < dirLightCount; ++i)
        {
            std::string lightPrefix = "dirLights[" + std::to_string(i) + "].";
            u_DirLightDirections[i] = glGetUniformLocation(modelShader, (lightPrefix + "direction").c_str());
            u_DirLightAmbients[i] = glGetUniformLocation(modelShader, (lightPrefix + "ambient").c_str());
            u_DirLightDiffuses[i] = glGetUniformLocation(modelShader, (lightPrefix + "diffuse").c_str());
            u_DirLightSpeculars[i] = glGetUniformLocation(modelShader, (lightPrefix + "specular").c_str());
        }

        for (int i = 0; i < spotLightCount; ++i)
        {
            std::string lightPrefix = "spotLights[" + std::to_string(i) + "].";
            u_SpotLightPositions[i] = glGetUniformLocation(modelShader, (lightPrefix + "position").c_str());
            u_SpotLightDirections[i] = glGetUniformLocation(modelShader, (lightPrefix + "direction").c_str());
            u_SpotLightAmbients[i] = glGetUniformLocation(modelShader, (lightPrefix + "ambient").c_str());
            u_SpotLightDiffuses[i] = glGetUniformLocation(modelShader, (lightPrefix + "diffuse").c_str());
            u_SpotLightSpeculars[i] = glGetUniformLocation(modelShader, (lightPrefix + "specular").c_str());
            u_SpotLightConstants[i] = glGetUniformLocation(modelShader, (lightPrefix + "constant").c_str());
            u_SpotLightLinears[i] = glGetUniformLocation(modelShader, (lightPrefix + "linear").c_str());
            u_SpotLightQuadratics[i] = glGetUniformLocation(modelShader, (lightPrefix + "quadratic").c_str());
            u_SpotLightCutOffs[i] = glGetUniformLocation(modelShader, (lightPrefix + "cutOff").c_str());
            u_SpotLightOuterCutOffs[i] = glGetUniformLocation(modelShader, (lightPrefix + "outerCutOff").c_str());
        }

        glUseProgram(modelShader);

        glBindVertexArray(VAO);

        glUniform1f(u_MaterialShininess, 1.f);

        glUniformMatrix4fv(u_Model, 1, GL_FALSE, &trans[0][0]);
        glUniformMatrix4fv(u_View, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(u_Proj, 1, GL_FALSE, &projection[0][0]);

        glUniform1f(u_PointLightCount, pointLightCount);
        glUniform1f(u_DirLightCount, dirLightCount);
        glUniform1f(u_SpotLightCount, spotLightCount);


        for (int i = 0; i < dirLightCount; ++i)
        {
            if (dirLights[i]->isOn)
            {
                glUniform3f(u_DirLightAmbients[i], dirLights[i]->ambient.x, dirLights[i]->ambient.y,
                            dirLights[i]->ambient.z);
                glUniform3f(u_DirLightDiffuses[i], dirLights[i]->diffuse.x, dirLights[i]->diffuse.y,
                            dirLights[i]->diffuse.z);
                glUniform3f(u_DirLightSpeculars[i], dirLights[i]->specular.x, dirLights[i]->specular.y,
                            dirLights[i]->specular.z);
                glUniform3f(u_DirLightDirections[i], dirLights[i]->direction.x, dirLights[i]->direction.y,
                            dirLights[i]->direction.z);
            }
            else
            {
                glUniform3f(u_DirLightAmbients[i], 0.f, 0.f, 0.f);
                glUniform3f(u_DirLightDiffuses[i], 0.f, 0.f, 0.f);
                glUniform3f(u_DirLightSpeculars[i], 0.f, 0.f, 0.f);
                glUniform3f(u_DirLightDirections[i], 0.f, 0.f, 0.f);
            }
        }

        for (int i = 0; i < pointLightCount; ++i)
        {
            if (pointLights[i]->isOn)
            {
                glUniform3f(u_PointLightPositions[i], pointLights[i]->position.x, pointLights[i]->position.y,
                            pointLights[i]->position.z);
                glUniform3f(u_PointLightAmbients[i], pointLights[i]->ambient.x, pointLights[i]->ambient.y,
                            pointLights[i]->ambient.z);
                glUniform3f(u_PointLightDiffuses[i], pointLights[i]->diffuse.x, pointLights[i]->diffuse.y,
                            pointLights[i]->diffuse.z);
                glUniform3f(u_PointLightSpeculars[i], pointLights[i]->specular.x, pointLights[i]->specular.y,
                            pointLights[i]->specular.z);
                glUniform1f(u_PointLightConstants[i], pointLights[i]->constant);
                glUniform1f(u_PointLightLinears[i], pointLights[i]->linear);
                glUniform1f(u_PointLightQuadratics[i], pointLights[i]->quadratic);
            }
            else
            {
                glUniform3f(u_PointLightPositions[i], 0.f, 0.f, 0.f);
                glUniform3f(u_PointLightAmbients[i], 0.f, 0.f, 0.f);
                glUniform3f(u_PointLightDiffuses[i], 0.f, 0.f, 0.f);
                glUniform3f(u_PointLightSpeculars[i], 0.f, 0.f, 0.f);
                glUniform1f(u_PointLightConstants[i], 0.f);
                glUniform1f(u_PointLightLinears[i], 0.f);
                glUniform1f(u_PointLightQuadratics[i], 0.0001f);
            }
        }

        for (int i = 0; i < spotLightCount; ++i)
        {
            if (spotLights[i]->isOn)
            {
                glUniform3f(u_SpotLightPositions[i], spotLights[i]->position.x, spotLights[i]->position.y,
                            spotLights[i]->position.z);
                glUniform3f(u_SpotLightDirections[i], spotLights[i]->direction.x, spotLights[i]->direction.y,
                            spotLights[i]->direction.z);
                glUniform3f(u_SpotLightAmbients[i], spotLights[i]->ambient.x, spotLights[i]->ambient.y,
                            spotLights[i]->ambient.z);
                glUniform3f(u_SpotLightDiffuses[i], spotLights[i]->diffuse.x, spotLights[i]->diffuse.y,
                            spotLights[i]->diffuse.z);
                glUniform3f(u_SpotLightSpeculars[i], spotLights[i]->specular.x, spotLights[i]->specular.y,
                            spotLights[i]->specular.z);
                glUniform1f(u_SpotLightConstants[i], spotLights[i]->constant);
                glUniform1f(u_SpotLightLinears[i], spotLights[i]->linear);
                glUniform1f(u_SpotLightQuadratics[i], spotLights[i]->quadratic);
                glUniform1f(u_SpotLightCutOffs[i], spotLights[i]->cutOff);
                glUniform1f(u_SpotLightOuterCutOffs[i], spotLights[i]->outerCutOff);
            }
            else
            {
                glUniform3f(u_SpotLightPositions[i], 0.f, 0.f, 0.f);
                glUniform3f(u_SpotLightDirections[i], 0.f, 0.f, 0.f);
                glUniform3f(u_SpotLightAmbients[i], 0.f, 0.f, 0.f);
                glUniform3f(u_SpotLightDiffuses[i], 0.f, 0.f, 0.f);
                glUniform3f(u_SpotLightSpeculars[i], 0.f, 0.f, 0.f);
                glUniform1f(u_SpotLightConstants[i], 0.f);
                glUniform1f(u_SpotLightLinears[i], 0.f);
                glUniform1f(u_SpotLightQuadratics[i], 0.0001f);
                glUniform1f(u_SpotLightCutOffs[i], 0.f);
                glUniform1f(u_SpotLightOuterCutOffs[i], 0.f);
            }
        }

        (glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        (glBindVertexArray(0));
        (glUseProgram(0));
    }

    void Renderer::drawShape(unsigned& VAO, unsigned indexQty, vec4 color, mat4 trans)
    {
        mat4 pvm = projection * view * trans;

        glCall(glUseProgram(shapeShader));
        glCall(u_ColorLocation = glGetUniformLocation(shapeShader, "u_Color"));

        glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));

        glCall(glBindVertexArray(VAO));

        glCall(glUniformMatrix4fv(u_ShapeTransformLocation, 1, GL_FALSE, glm::value_ptr(pvm)));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::setProjection(mat4 projection)
    {
        this->projection = projection;
    }

    void Renderer::setView(mat4 view)
    {
        this->view = view;
    }

    void Renderer::addDirLight(DirLight* dirLight)
    {
        if (dirLightCount < MAX_DIR_LIGHTS)
        {
            dirLights[dirLightCount] = dirLight;
            dirLightCount++;
        }
        else
        {
            std::cout << "Max dir lights reached" << std::endl;
        }
    }

    void Renderer::addPointLight(PointLight* pointLight)
    {
        if (pointLightCount < MAX_POINT_LIGHTS)
        {
            pointLights[pointLightCount] = pointLight;
            pointLightCount++;
        }
        else
        {
            std::cout << "Max point lights reached" << std::endl;
        }
    }

    void Renderer::addSpotLight(SpotLight* spotLight)
    {
        if (spotLightCount < MAX_SPOT_LIGHTS)
        {
            spotLights[spotLightCount] = spotLight;
            spotLightCount++;
        }
        else
        {
            std::cout << "Max spot lights reached" << std::endl;
        }
    }

    void Renderer::turnOnDirLight(int index)
    {
        dirLights[index]->isOn = true;
    }

    void Renderer::turnOffDirLight(int index)
    {
        dirLights[index]->isOn = false;
    }

    void Renderer::turnDirLight(int index)
    {
        dirLights[index]->isOn = !dirLights[index]->isOn;
    }

    void Renderer::turnPointLight(int index)
    {
        pointLights[index]->isOn = !pointLights[index]->isOn;
    }

    void Renderer::turnSpotLight(int index)
    {
        spotLights[index]->isOn = !spotLights[index]->isOn;
    }

    void Renderer::turnOnPointLight(int index)
    {
        pointLights[index]->isOn = true;
    }

    void Renderer::turnOffPointLight(int index)
    {
        pointLights[index]->isOn = false;
    }

    void Renderer::turnOnSpotLight(int index)
    {
        spotLights[index]->isOn = true;
    }

    void Renderer::turnOffSpotLight(int index)
    {
        spotLights[index]->isOn = false;
    }


    void Renderer::changeCameraMode()
    {
        camera->setThirdPersonCamera(camera->thirdPersonCamera = !camera->thirdPersonCamera);
    }

    bool Renderer::getIsThirdPerson()
    {
        return camera->getIsThirdPerson();
    }

    unsigned int Renderer::compileShader(unsigned int type, const char* source)
    {
        unsigned int id = glCreateShader(type);
        glCall(glShaderSource(id, 1, &source, nullptr));
        glCall(glCompileShader(id));

        int result;
        glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

        if (!result)
        {
            int length;
            glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = new char[length];
            glCall(glGetShaderInfoLog(id, length, &length, message));

            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" <<
                std::endl;
            std::cout << message << std::endl;

            glCall(glDeleteShader(id));
            return 0;
        }

        return id;
    }

    unsigned int Renderer::createShader(const char* vShader, const char* fShader)
    {
        glCall(unsigned int program = glCreateProgram());
        glCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vShader));
        glCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fShader));

        glCall(glAttachShader(program, vs));
        glCall(glAttachShader(program, fs));
        glCall(glLinkProgram(program));
        glCall(glValidateProgram(program));

        glCall(glDeleteShader(vs));
        glCall(glDeleteShader(fs));

        return program;
    }

    Renderer::ShaderProgramSource Renderer::parseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath);

        enum class ShaderType
        {
            None = -1,
            Vertex = 0,
            Fragment = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::None;

        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::Vertex;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::Fragment;
            }
            else
            {
                ss[static_cast<int>(type)] << line << '\n';
            }
        }

        return {ss[0].str(), ss[1].str()};
    }

    void Renderer::glClearError()
    {
        while (glGetError());
    }

    bool Renderer::glLogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            std::cout << "[OpenGL Error] (" << error << "): "
                << function << " " << file << ": " << line << std::endl;
            return false;
        }

        return true;
    }
}
