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

public:
	Material();
	Material(std::string vertexSource, std::string fragmentSource);
	~Material();

	static Material ParseShader(const std::string& filepath);
	static unsigned int CompileShader(unsigned int type, 
		const std::string& source);
	static int CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader);

	void SetFilepath(std::string filepath);

	std::string GetFilepath();
	std::string GetVertexSource();
	std::string GetFragmentSource();
};