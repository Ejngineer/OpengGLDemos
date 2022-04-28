#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::fstream VertexFile(vertexPath, std::fstream::in);
	std::fstream FragmentFile(fragmentPath, std::fstream::in);

	std::ostringstream VertexOss;
	std::ostringstream FragmentOss;

	if (!VertexFile.is_open())
	{
		std::cout << "Failed to open vertex shader file" << std::endl;
	}
	
	if (!FragmentFile.is_open())
	{
		std::cout << "Failed to open fragment shader file" << std::endl;
	}
	
	/*Read contents of file into memory an store stringstream data into string 
	for vertex shader source code*/
	VertexOss << VertexFile.rdbuf();
	const std::string VertexString(VertexOss.str());


	/*Same as before for fragment shader source code*/
	FragmentOss << FragmentFile.rdbuf();
	const std::string FragmentString(FragmentOss.str());
	std::cout << FragmentString << std::endl;

	/*Store string into char pointer*/
	const char* VertexCode = VertexString.c_str();
	const char* FragmentCode = FragmentString.c_str();

	unsigned int vertexShader, fragmentShader;

	/*Create and compile vertex shader*/
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexCode, NULL);
	glCompileShader(vertexShader);

	/*Error checking vertex shader*/
	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Failed to compile vertex shader. Error: " << infoLog << std::endl;
	}
	
	/*Same for fragment shader*/
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Failed to compile fragment shader. Error: " << infoLog << std::endl;
	}

	/*create program using private data member _ID*/
	_ID = glCreateProgram();
	glAttachShader(_ID, vertexShader);
	glAttachShader(_ID, fragmentShader);
	glLinkProgram(_ID);

	/*Delete shader now that program is linked*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*Check if program linked successfully*/
	glGetProgramiv(_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_ID, 512, NULL, infoLog);
		std::cout << "Failed to link program. Error: " << infoLog << std::endl;
	}
}

void Shader::use()
{
	glUseProgram(_ID);
}