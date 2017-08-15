#pragma once

#include "../Renderable.hpp"
#include "../../MathFunctions/Vector.hpp"
#include "../../Shaders/ShaderLoader.hpp"

class Square : public Renderable
{
public:
	Square(vec3 position, vec2 size) {
		shaderProgram = ShaderLoader::Load(".\\Resources\\Shaders\\vs.shader", ".\\Resources\\Shaders\\fs.shader");
		glUseProgram(shaderProgram);

		m_size = size;
		m_position = position;
		m_vbo = new Buffers::VertexBufferObject(GL_ARRAY_BUFFER); 
		m_vertices.reset(new vertex[6]);
		SetVertices();
		Setup();
	}

	~Square() {
	}

	void Setup() {
		m_vbo->bufferData(6, sizeof(vertex), m_vertices.get(), GL_STATIC_DRAW);
	}

	void Draw() {
		m_vbo->bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
		m_vbo->unbind();
	}

	void Destroy() {

	}

	void SetVertices() {
		m_vertices[0].position = vec3(m_position.x, m_position.y, m_position.z);
		m_vertices[1].position = vec3(m_position.x + m_size.x, m_position.y, m_position.z);
		m_vertices[2].position = vec3(m_position.x + m_size.x, m_position.y + m_size.y, m_position.z);
		m_vertices[3].position = vec3(m_position.x, m_position.y, m_position.z);
		m_vertices[4].position = vec3(m_position.x + m_size.x, m_position.y + m_size.y, m_position.z);
		m_vertices[5].position = vec3(m_position.x, m_position.y + m_size.y, m_position.z);
	}

private:
	unsigned int shaderProgram;
	MathFuncs::vec2 m_size;
	
protected:

};

