  #pragma once

#include <string>
#include <sstream>
#include <vector>

#include "Window.h"
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Lights/DirLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"

#pragma region MACROS
#define ASSERT(x) if (!(x)) __debugbreak()
#define glCall(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__))
#pragma endregion

const int MAX_POINT_LIGHTS = 2;
const int MAX_DIR_LIGHTS = 2;
const int MAX_SPOT_LIGHTS = 2;

namespace ToToEng
{
	class Renderer
	{
	private:
		struct ShaderProgramSource
		{
			std::string vertexSource;
			std::string fragmentSource;
		};

		Window* window;
		Camera* camera;
		unsigned int shader;
		unsigned int shapeShader;
		unsigned int lightShader;
		unsigned int modelShader;
		unsigned int basicModelShader;
		int u_TransformLocation;
		int u_ShapeTransformLocation;
		int u_ColorLocation;
		mat4 projection;
		mat4 view;
		vec3 cameraPos;
		
		
		PointLight* pointLights[MAX_POINT_LIGHTS];
		DirLight* dirLights[MAX_DIR_LIGHTS];
		SpotLight* spotLights[MAX_SPOT_LIGHTS];

		int pointLightCount;
		int dirLightCount;
		int spotLightCount;

		vec3 ambientLightColor;
		float ambientLightStrength;

		static unsigned int compileShader(unsigned int type, const char* source);
		static unsigned int createShader(const char* vShader, const char* fShader);
		static ShaderProgramSource parseShader(const std::string& filepath);
		static void glClearError();
		static bool glLogCall(const char* function, const char* file, int line);

	public:
		Renderer(Window* window, Camera* camera);
		~Renderer();

		void beginDraw();
		void endDraw();
		void genVertexBuffer(unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int id, unsigned int qty);
		void genVertexBuffer3D(unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int id, unsigned int qty);
		void genIndexBuffer(unsigned int& IBO,
			unsigned int indices[], unsigned int id, unsigned int qty);
		void deleteBuffers(unsigned int& VBO, unsigned int& IBO, unsigned int& EBO, unsigned int id);
		void drawEntity2D(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans, unsigned int texture);
		void drawEntity3D(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans);
		void drawLightEntity3D(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans);
		void drawModel3D(unsigned int& VAO, unsigned int indexQty, mat4 trans, std::vector<Texture> textures);
		void drawShape(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans);
		void setProjection(mat4 projection);
		void setView(mat4 view);
		unsigned int loadTexture(const char* filePath);
		void addDirLight(DirLight* dirLight);
		void addPointLight(PointLight* pointLight);
		void addSpotLight(SpotLight* spotLight);
	};
}