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
	Utilities::SmartPointer<Buffers::VertexBufferObject> m_vbo;
	std::unique_ptr<vertex[]> m_vertices;
	vec3 m_position;
};
