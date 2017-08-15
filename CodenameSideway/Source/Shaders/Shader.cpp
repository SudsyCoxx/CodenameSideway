#include "Shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "../Utilities/Logging.hpp"

using namespace Graphics;
using namespace Utilities;

Shader::Shader(std::string pathVS, std::string pathFS) {
	m_vs = pathVS;
	m_fs = pathFS;

	LoadShader();
}

Shader::~Shader() {

}

void Shader::UseShader() {
	if(m_program != -1)
		glUseProgram(m_program);
}

void Shader::LoadShader() {
		unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(m_vs.c_str(), std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else {
			Logging::GetInstance().Log(ID_DEBUG, -1, "Invalid Vertex Shader", "");
			return;
		}

		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(m_fs.c_str(), std::ios::in);
		if (FragmentShaderStream.is_open()) {
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		else {
			Logging::GetInstance().Log(ID_DEBUG, -1, "Invalid Fragment Shader", "");
			return;
		}

		int Result = false;
		int InfoLogLength;

		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			Logging::GetInstance().Log(ID_DEBUG, -1, std::string(&VertexShaderErrorMessage[0]), "");
		}

		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			Logging::GetInstance().Log(ID_DEBUG, -1, std::string(&FragmentShaderErrorMessage[0]), "");
		}

		m_program = glCreateProgram();
		glAttachShader(m_program, VertexShaderID);
		glAttachShader(m_program, FragmentShaderID);
		glLinkProgram(m_program);

		glGetProgramiv(m_program, GL_LINK_STATUS, &Result);
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(m_program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			Logging::GetInstance().Log(ID_DEBUG, -1, std::string(&ProgramErrorMessage[0]), "");
		}

		glDetachShader(m_program, VertexShaderID);
		glDetachShader(m_program, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
}
