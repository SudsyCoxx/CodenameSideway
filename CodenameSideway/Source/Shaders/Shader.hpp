#pragma once

#include <string>

#include "../MathFunctions/Matrices.hpp"

using namespace MathFuncs;

namespace Graphics {
	class Shader
	{
	public:
		Shader(std::string pathVS, std::string pathFS);
		~Shader();
		
		void UseShader();

		int getUniformLocation(const char* name);

		void setUniform1f(const char* name, float value);
		void setUniform1fv(const char* name, float* value, int count);
		void setUniform1i(const char* name, int value);
		void setUniform1iv(const char* name, int* value, int count);
		void setUniform2f(const char* name, const vec2& vector);
		void setUniform3f(const char* name, const vec3& vector);
		void setUniform4f(const char* name, const vec4& vector);
		void setUniformMat4(const char* name, const mat4& matrix);

	private:
		void LoadShader();

		unsigned int m_program = -1;
		std::string m_vs, m_fs;

	protected:
	};
}
