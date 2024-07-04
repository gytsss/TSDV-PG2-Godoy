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
        cameraPos = vec3(0.0f, 0.0f, 0.0f);

        //2D
        /*setProjection(ortho(0.0f, static_cast<float>(window->getWidth()), 0.0f,
            static_cast<float>(window->getHeight()), 0.1f, 500.f));
        cameraPos = vec3(0.0f, 0.0f, 1.0f);*/


        view = lookAt(cameraPos, {0, 0, 0}, {0, 1, 0});
        //ambientLightColor = vec3(1.0f, 1.0f, 1.0f);
        //ambientLightStrength = 0.1f;

        dirLights[0] = new DirLight({0.5f, 0.5f, 0.5f}, {0.4f, 0.4f, 0.4f}, {0.5f, 0.5f, 0.5f}, {-0.2f, -1.0f, -0.3f});
        pointLights[0] = new PointLight({10.0f, 10.f, 10.f}, {10.0f, 10.f, 10.f}, {10.0f, 10.f, 10.f}, {0.0f, 0.0f, 3.0f}, 1.0f, 0.09f, 0.032f);
        spotLights[0] = new SpotLight({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {camera->pos.x, camera->pos.y, camera->pos.z},{camera->pos.x, camera->pos.y, camera->pos.z}, 1.0f, 0.09f, 0.032f, 45.0f, 45.0f);
        
        
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

        GLint u_DirLightDirection = glGetUniformLocation(modelShader, "dirLight.direction");
        GLint u_DirLightAmbient = glGetUniformLocation(modelShader, "dirLight.ambient");
        GLint u_DirLightDiffuse = glGetUniformLocation(modelShader, "dirLight.diffuse");
        GLint u_DirLightSpecular = glGetUniformLocation(modelShader, "dirLight.specular");
        GLint u_Model = glGetUniformLocation(modelShader, "model");
        GLint u_View = glGetUniformLocation(modelShader, "view");
        GLint u_Proj = glGetUniformLocation(modelShader, "projection");

        GLint u_MaterialShininess = glGetUniformLocation(modelShader, "material.shininess");

        
        GLint u_PointLightPosition = glGetUniformLocation(modelShader, "pointLights[0].position");
        GLint u_PointLightAmbient = glGetUniformLocation(modelShader, "pointLights[0].ambient");
        GLint u_PointLightDiffuse = glGetUniformLocation(modelShader, "pointLights[0].diffuse");
        GLint u_PointLightSpecular = glGetUniformLocation(modelShader, "pointLights[0].specular");
        GLint u_PointLightConstant = glGetUniformLocation(modelShader, "pointLights[0].constant");
        GLint u_PointLightLinear = glGetUniformLocation(modelShader, "pointLights[0].linear");
        GLint u_PointLightQuadratic = glGetUniformLocation(modelShader, "pointLights[0].quadratic");

        GLint u_PointLightPosition1 = glGetUniformLocation(modelShader, "pointLights[1].position");
        GLint u_PointLightAmbient1 = glGetUniformLocation(modelShader, "pointLights[1].ambient");
        GLint u_PointLightDiffuse1 = glGetUniformLocation(modelShader, "pointLights[1].diffuse");
        GLint u_PointLightSpecular1 = glGetUniformLocation(modelShader, "pointLights[1].specular");
        GLint u_PointLightConstant1 = glGetUniformLocation(modelShader, "pointLights[1].constant");
        GLint u_PointLightLinear1 = glGetUniformLocation(modelShader, "pointLights[1].linear");
        GLint u_PointLightQuadratic1 = glGetUniformLocation(modelShader, "pointLights[1].quadratic");

        GLint u_SpotLightPosition = glGetUniformLocation(modelShader, "spotLights[0].position");
        GLint u_SpotLightDirection = glGetUniformLocation(modelShader, "spotLights[0].direction");
        GLint u_SpotLightAmbient = glGetUniformLocation(modelShader, "spotLights[0].ambient");
        GLint u_SpotLightDiffuse = glGetUniformLocation(modelShader, "spotLights[0].diffuse");
        GLint u_SpotLightSpecular = glGetUniformLocation(modelShader, "spotLights[0].specular");
        GLint u_SpotLightConstant = glGetUniformLocation(modelShader, "spotLights[0].constant");
        GLint u_SpotLightLinear = glGetUniformLocation(modelShader, "spotLights[0].linear");
        GLint u_SpotLightQuadratic = glGetUniformLocation(modelShader, "spotLights[0].quadratic");
        GLint u_SpotLightCutoff = glGetUniformLocation(modelShader, "spotLights[0].cutOff");
        GLint u_SpotLightOuterCutoff = glGetUniformLocation(modelShader, "spotLights[0].outerCutOff");

        GLint u_SpotLightPosition1 = glGetUniformLocation(modelShader, "spotLights[1].position");
        GLint u_SpotLightDirection1 = glGetUniformLocation(modelShader, "spotLights[1].direction");
        GLint u_SpotLightAmbient1 = glGetUniformLocation(modelShader, "spotLights[1].ambient");
        GLint u_SpotLightDiffuse1 = glGetUniformLocation(modelShader, "spotLights[1].diffuse");
        GLint u_SpotLightSpecular1 = glGetUniformLocation(modelShader, "spotLights[1].specular");
        GLint u_SpotLightConstant1 = glGetUniformLocation(modelShader, "spotLights[1].constant");
        GLint u_SpotLightLinear1 = glGetUniformLocation(modelShader, "spotLights[1].linear");
        GLint u_SpotLightQuadratic1 = glGetUniformLocation(modelShader, "spotLights[1].quadratic");
        GLint u_SpotLightCutoff1 = glGetUniformLocation(modelShader, "spotLights[1].cutOff");
        GLint u_SpotLightOuterCutoff1 = glGetUniformLocation(modelShader, "spotLights[1].outerCutOff");

        glUseProgram(modelShader);

        glBindVertexArray(VAO);

        glUniform1f(u_MaterialShininess, 1.f);

        glUniformMatrix4fv(u_Model, 1, GL_FALSE, &trans[0][0]);
        glUniformMatrix4fv(u_View, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(u_Proj, 1, GL_FALSE, &projection[0][0]);

        glUniform3f(u_DirLightAmbient, 0.5f, 0.5f, 0.5f);
        glUniform3f(u_DirLightDiffuse, 0.4f, 0.4f, 0.4f);
        glUniform3f(u_DirLightSpecular, 0.5f, 0.5f, 0.5f);
        glUniform3f(u_DirLightDirection, -0.2f, -1.0f, -0.3f);

        //point light 1
        glUniform3f(u_PointLightAmbient, 1.f, 1.f, 1.f);
        glUniform3f(u_PointLightDiffuse, 10.f, 10.f, 10.f);
        glUniform3f(u_PointLightSpecular, 10.f, 10.f, 10.f);
        glUniform3f(u_PointLightPosition, 0.0f, 0.0f, 10.0f);
        glUniform1f(u_PointLightConstant, 1.0f);
        glUniform1f(u_PointLightLinear, 0.09f);
        glUniform1f(u_PointLightQuadratic, 0.032f);

        // point light 2
        glUniform3f(u_PointLightAmbient1, 1.f, 1.f, 1.f);
        glUniform3f(u_PointLightDiffuse1, 10.f, 10.f, 10.f);
        glUniform3f(u_PointLightSpecular1, 10.f, 10.f, 10.f);
        glUniform3f(u_PointLightPosition1, 0, 0, 20);
        glUniform1f(u_PointLightConstant1, 1.0f);
        glUniform1f(u_PointLightLinear1, 0.09f);
        glUniform1f(u_PointLightQuadratic1, 0.032f);
        
        // // point light 3
        // lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        // lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        // lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        // lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        // lightingShader.setFloat("pointLights[2].constant", 1.0f);
        // lightingShader.setFloat("pointLights[2].linear", 0.09f);
        // lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
        // // point light 4
        // lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        // lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        // lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        // lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        // lightingShader.setFloat("pointLights[3].constant", 1.0f);
        // lightingShader.setFloat("pointLights[3].linear", 0.09f);
        // lightingShader.setFloat("pointLights[3].quadratic", 0.032f);

          //spotLight 1
        (glUniform3f(u_SpotLightAmbient, 0.0f, 0.0f, 0.0f));
        (glUniform3f(u_SpotLightDiffuse, 10.0f, 10.0f, 10.0f));
        (glUniform3f(u_SpotLightSpecular, 10.0f, 10.0f, 10.0f));
        (glUniform3f(u_SpotLightPosition, 0, 25, 15));
        (glUniform3f(u_SpotLightDirection, 0, -1, 0));
        (glUniform1f(u_SpotLightConstant, 1.0f));
        (glUniform1f(u_SpotLightLinear, 0.09f));
        (glUniform1f(u_SpotLightQuadratic, 0.032f));
        (glUniform1f(u_SpotLightCutoff, glm::cos(glm::radians(10.5f))));
        (glUniform1f(u_SpotLightOuterCutoff, glm::cos(glm::radians(15.0f))));
 //spotLight 2
        (glUniform3f(u_SpotLightAmbient1, 0.0f, 0.0f, 0.0f));
        (glUniform3f(u_SpotLightDiffuse1, 10.0f, 10.0f, 10.0f));
        (glUniform3f(u_SpotLightSpecular1, 10.0f, 10.0f, 10.0f));
        (glUniform3f(u_SpotLightPosition1, 10, 25, 15));
        (glUniform3f(u_SpotLightDirection1, 0, -1, 0));
        (glUniform1f(u_SpotLightConstant1, 1.0f));
        (glUniform1f(u_SpotLightLinear1, 0.09f));
        (glUniform1f(u_SpotLightQuadratic1, 0.032f));
        (glUniform1f(u_SpotLightCutoff1, glm::cos(glm::radians(10.5f))));
        (glUniform1f(u_SpotLightOuterCutoff1, glm::cos(glm::radians(15.0f))));

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

    void Renderer::addSpotLight(SpotLight *spotLight)
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
