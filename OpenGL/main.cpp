#include <stdio.h>
#include  <string.h>
#include <cmath>
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;
GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

float curAngle;

bool sizeDirection = true;
float curSize = .4f;
float maxSize = .8f;
float minSize = .1f;

static const char* vShader = "								        	\n\
#version 330													        \n\
																        \n\
layout (location = 0) in vec3 pos;								        \n\
																        \n\
uniform mat4 model;								        				\n\
														        		\n\
void main()												        		\n\
{																        \n\
	gl_Position = model * vec4(pos, 1.0);								\n\
}";
static const char* fShader = "									\n\
#version 330													\n\
																\n\
out vec4 colour;												\n\
																\n\
void main()														\n\
{																\n\
	colour = vec4(1.0,0.0,0.0,1.0);								\n\
}";

void CreateTriangle()
{
	GLfloat verticles[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void ComileShaders()
{
	shader = glCreateProgram();

	if (!shader)
	{
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
}

int main()
{
	if (!glfwInit())
	{
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		glfwTerminate();
		return 1;
	}

	int bufferHeight, bufferWidth;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(mainWindow);

		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);
	CreateTriangle();
	ComileShaders();
	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();
		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}


		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}
		curAngle += 1.0f;
		if (curAngle >= 360)
			curAngle -= 360;


		if (sizeDirection)
		{
			curSize += .001f;
		}
		else
		{
			curSize -= .001f;
		}
		if (curSize >= maxSize || curSize <= minSize)
		{
			sizeDirection = !sizeDirection;
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0, 1.0f));
		model = glm::translate(model, glm::vec3(triOffset, 0, 0));
		model = glm::scale(model, glm::vec3(curSize, curSize, 1));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}
