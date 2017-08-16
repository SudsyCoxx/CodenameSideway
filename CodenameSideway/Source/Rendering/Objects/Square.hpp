#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Shaders/ShaderManager.hpp"
#include "../../MathFunctions/Vector.hpp"
#include "../Renderable.hpp"

namespace Graphics {
	class Square : public Renderable
	{
	public:
		Square(vec3 position, vec2 size, vec3 color = vec3(1, 1, 1));

		~Square();

		void Setup();
		void Draw();
		void Destroy();

		void SetVertices();

	private:
		unsigned int m_shaderProgram = -1;
		MathFuncs::vec2 m_size;

	protected:
	};
}
