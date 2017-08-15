#pragma once

#include <string>

namespace Graphics {
	class Shader
	{
	public:
		Shader(std::string pathVS, std::string pathFS);
		~Shader();
		
		void UseShader();

	private:
		void LoadShader();

		unsigned int m_program = -1;
		std::string m_vs, m_fs;

	protected:
	};
}
