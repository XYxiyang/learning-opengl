#pragma once
#include<glad/glad.h>

#include<cstring>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

class Shader {
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void setBool(const string& name, bool value)const;
	void setInt(const string& name, int value)const;
	void setFloat(const string& name, float value)const;
};

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	string vertexCode;
	string fragmentCode;

	ifstream vertexFile;
	ifstream fragmentFile;

	vertexFile.open(vertexPath, ios::in);
	fragmentFile.open(fragmentPath, ios::in);

	stringstream vertexStream, fragmentStream;
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	vertexFile.close();
	fragmentFile.close();

	vertexCode = vertexStream.str();
	fragmentCode = fragmentStream.str();

	const char* cvertexCode = vertexCode.c_str();
	const char* cfragmentCode = fragmentCode.c_str();


	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &cvertexCode, &success);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "vertex shader conpile error" << infoLog << endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &cfragmentCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "fragment shader compile failed" << infoLog << endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "shaders link failed" << infoLog << endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const string& name, bool value)const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value)const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string& name, float value)const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
