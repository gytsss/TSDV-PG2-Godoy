#include "Renderer.h"

#include <fstream>

namespace ToToEng
{
	Renderer::Renderer(Window* window, Camera* camera)
	{
		this->window = window;

		ShaderProgramSource shaderSource = parseShader("../res/shaders/Basic.shader");
		std::cout << glGetString(GL_VERSION) << std::endl;
		shader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

		shaderSource = parseShader("../res/shaders/Shape.shader");
		std::cout << glGetString(GL_VERSION) << std::endl;
		shapeShader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glCall(u_TransformLocation = glGetUniformLocation(shader, "u_Transform"));
		_ASSERT(u_TransformLocation != -1);

		glCall(u_ShapeTransformLocation = glGetUniformLocation(shapeShader, "u_Transform"));
		_ASSERT(u_TransformLocation != -1);

		//3D
			setProjection(perspective(radians(45.f),
				static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()),
				0.1f, 6000.f));
			cameraPos = vec3(0.0f, 0.0f, 3.0f);
		
		//2D
			/*setProjection(ortho(0.0f, static_cast<float>(window->getWidth()), 0.0f,
				static_cast<float>(window->getHeight()), 0.1f, 500.f));
			cameraPos = vec3(0.0f, 0.0f, 1.0f);*/
		

		view = lookAt(cameraPos, { 0, 0, 0 }, { 0, 1, 0 });
		ambientLightColor = vec3(1.0f, 1.0f, 1.0f);
		ambientLightStrength = 0.1f;
	}

	Renderer::~Renderer()
	{
		glDeleteProgram(shader);
	}

	void Renderer::beginDraw()
	{
		glCall(glClear(GL_COLOR_BUFFER_BIT));
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

		//vec3 ambient = ambientLightStrength * ambientLightColor;
		glCall(glUseProgram(shader));
		glCall(glUniform1i(glGetUniformLocation(shader, "ourTexture"), 0));
		glCall(u_ColorLocation = glGetUniformLocation(shader, "u_Color"));

		glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));
		//glCall(glUniform4f(glGetUniformLocation(shader, "lightColor"), ambientLightColor.x, ambientLightColor.y, ambientLightColor.z, 1.0f));
		//glCall(glUniform4f(glGetUniformLocation(shapeShader, "ambientLight"), ambientLightColor.x, ambientLightColor.y, ambientLightColor.z, 1.0f));
		
		glCall(glBindVertexArray(VAO));

		glCall(glUniformMatrix4fv(u_TransformLocation, 1, GL_FALSE, glm::value_ptr(pvm)));

		glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

		glCall(glBindVertexArray(0));
		glCall(glUseProgram(0));
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

		return { ss[0].str(), ss[1].str() };
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
