#include "Material.h"

Material::Material()
{

}

Material::Material(std::string vertexSource, std::string fragmentSource)
{
	this->vertexSource = vertexSource;
	this->fragmentSource = fragmentSource;
}

Material::~Material()
{

}

Material Material::ParseShader()
{
	std::ifstream stream(shaderFilepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX,
		FRAGMENT
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Material::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

int Material::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Material::InitShader()
{
	shader = CreateShader(vertexSource, fragmentSource);	
}

void Material::DeinitShader()
{
	glDeleteProgram(shader);
}

void Material::UseShader()
{
	glUseProgram(shader);
}

void Material::SetFilepath(std::string filepath)
{
	shaderFilepath = filepath;
}

std::string Material::GetFilepath()
{
	return shaderFilepath;
}

std::string Material::GetVertexSource()
{
	std::cout << "Vertex source: " << vertexSource << std::endl;

	return vertexSource;
}

std::string Material::GetFragmentSource()
{
	return fragmentSource;
}
