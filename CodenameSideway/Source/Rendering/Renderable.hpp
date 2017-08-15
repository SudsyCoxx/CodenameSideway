#pragma once

#include <memory>

#include "RenderInterface.hpp"
#include "../MathFunctions/Vector.hpp"
#include "../Buffers/VertexBufferObject.hpp"
#include "../Utilities/SmartPointer.hpp"

using namespace MathFuncs;

class Renderable : public RenderInterface {
public:

	struct vertex {
		vec3 position;
	};

private:

protected:
	Buffers::VertexBufferObject* m_vbo;
	vertex m_vertices[6];
	vec3 m_position;
};
