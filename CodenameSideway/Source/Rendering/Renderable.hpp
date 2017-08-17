#pragma once

#include <memory>

#include "RenderInterface.hpp"
#include "../MathFunctions/Vector.hpp"
#include "../Buffers/VertexBufferObject.hpp"
#include "../Utilities/SmartPointer.hpp"

using namespace MathFuncs;

namespace Graphics {
	class Renderable : public RenderInterface {
	public:
		struct vertex {
			vec3 position;
			vec3 color;
			vec2 uv;
			float tid;
		};

	private:

	protected:
		Utilities::SmartPointer<Buffers::VertexBufferObject> m_vbo;
		unsigned int m_textureID = -1;
		std::string m_texPath;
		std::unique_ptr<vertex[]> m_vertices;
		std::unique_ptr<unsigned int[]> m_indices;
		vec3 m_position;
		vec3 m_color;
	};
}