#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Shaders/ShaderManager.hpp"
#include "../../MathFunctions/Vector.hpp"
#include "../Renderable.hpp"

class Square : public Renderable
{
public:
	Square(vec3 position, vec2 size);

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

