#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
	
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vSGaderCode = vertexCode.c_str();
	const char* fSGaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vSGaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fSGaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FLRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	std::cout << "shader file Success" << std::endl;
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x ,y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::ShaderDelete()
{
	glDeleteProgram(ID);
}

void Shader::checkCompileErrors(GLuint shader, std::string tyep)
{
}
