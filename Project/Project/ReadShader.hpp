#ifndef READSHADER_HPP
#define READSHADER_HPP

#include <string>
#include <fstream>
#include <GL\glew.h>

std::string readShader(const char *filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		fprintf(stderr, "Could not open file %s", filePath);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

bool CreateProgram(GLuint &programID, std::string shadernames[], GLenum shaderType[], int numberOfShaders)
{
	programID = glCreateProgram();

	bool success = true;

	for (int i = 0; i < numberOfShaders && success; i++)
	{
		std::string shaderStr = readShader(shadernames[i].c_str());
		const char *shaderChar = shaderStr.c_str();
		GLuint shader = glCreateShader(shaderType[i]);
		glShaderSource(shader, 1, &shaderChar, nullptr);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			success = false;
			fprintf(stderr, "Failed to compile shader %s\n", shadernames[i].c_str());

			GLchar log[10240];
			GLsizei length;
			glGetShaderInfoLog(shader, 10239, &length, log);
			fprintf(stderr, "Compiler log:\n%s\n", log);
		}
		glAttachShader(programID, shader);
		glDeleteShader(shader);

	}

	// if we can link all shaders
	glLinkProgram(programID);

	GLint linked;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if (linked != GL_TRUE)
	{
		success = false;
		fprintf(stderr, "Failed to link shader program %d\n", programID);
	}

	if (success)
	{
		return true;
	}
	else
	{
		glDeleteProgram(programID);
		programID = 0;
		return false;
	}
}
#endif