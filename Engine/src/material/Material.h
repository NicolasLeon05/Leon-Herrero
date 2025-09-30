#pragma once

#include "GL/glew.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Material
{
private:
	std::string vertexSource;
	std::string fragmentSource;

	std::string shaderFilepath;

	unsigned int shader;

public:
	Material();
	Material(std::string vertexSource, std::string fragmentSource);
	~Material();

	Material ParseShader();
	unsigned int CompileShader(unsigned int type, 
		const std::string& source);
	int CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader);

	void InitShader();
	void DeinitShader();

	void UseShader();

	unsigned int GetShader();

	void SetFilepath(std::string filepath);	

	std::string GetFilepath();
	std::string GetVertexSource();
	std::string GetFragmentSource();
};