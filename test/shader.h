#pragma once
#include<glad/glad.h>
#include<D:\vcpkg\vcpkg\installed\x86-windows\include\glm\glm.hpp>
#include<D:\vcpkg\vcpkg\installed\x86-windows\include\glm/gtc/matrix_transform.hpp>
#include<D:\vcpkg\vcpkg\installed\x86-windows\include\glm/gtc/type_ptr.hpp>
#include<cstring>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
using namespace glm;

class Shader {
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void setBool(const string& name, bool value)const;
	void setInt(const string& name, int value)const;
	void setFloat(const string& name, float value)const;
	void setVec2(const string& name, const vec2& value) const;
	void setVec2(const string& name, float x, float y)const ;
	void setVec3(const string& name, const vec3& value)const;
	void setVec3(const string& name, float x, float y, float z)const;
	void setVec4(const string& name, const vec4& value) const;
	void setVec4(const string& name, float x, float y, float z, float w)const;
	void setMat2(const string& name, const mat2& mat) const;
	void setMat3(const string& name, const mat3& mat) const;
	void setMat4(const string& name, const mat4& mat) const;
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
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setVec2(const string& name, const vec2& value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const  string& name, float x, float y)const{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const string& name, const vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const string& name, const vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const string& name, float x, float y, float z, float w)const{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const  string& name, const  mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const  string& name, const  mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const  string& name, const  mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}