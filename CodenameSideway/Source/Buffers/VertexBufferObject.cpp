#include "VertexBufferObject.hpp"
#include <gl/glew.h>

using namespace Buffers;

VertexBufferObject::VertexBufferObject(unsigned int BufferType) 
	: m_buffer(0), m_type(BufferType), m_enabled(0)
{
	genBuffer();
}

VertexBufferObject::~VertexBufferObject() {
	glDeleteBuffers(1, &m_buffer);
}

void VertexBufferObject::bind() {
	if (!m_enabled) {
		glBindBuffer(m_type, m_buffer);
		m_enabled != m_enabled;
	}
}

void VertexBufferObject::unbind() {
	if (m_enabled) {
		glBindBuffer(m_type, m_buffer);
		m_enabled != m_enabled;
	}
}

void VertexBufferObject::bufferData(int Count, int SizeOfElement, void* Elements, unsigned int DrawType) {
	bind();
	glBufferData(m_type, Count*SizeOfElement, Elements, DrawType);
	unbind();
}

void VertexBufferObject::genBuffer() {
	glGenBuffers(1, &m_buffer);
}
