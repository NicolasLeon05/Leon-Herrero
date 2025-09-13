#pragma once

#include "GL/glew.h"
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

	void SetFilepath(std::string filepath);

	std::string GetFilepath();
	std::string GetVertexSource();
	std::string GetFragmentSource();
};