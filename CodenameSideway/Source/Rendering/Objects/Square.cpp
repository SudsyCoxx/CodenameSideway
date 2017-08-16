#include "Square.hpp"

Square::Square(vec3 position, vec2 size) {
	m_shaderProgram = Graphics::ShaderManager::GetInstance().LoadShader(".\\Resources\\Shaders\\vs.shader", ".\\Resources\\Shaders\\fs.shader");

	m_size = size;
	m_position = position;
	m_vbo = new Buffers::VertexBufferObject(GL_ARRAY_BUFFER);
	
	m_vertices.reset(new vertex[4]);
	m_indices.reset(new unsigned int[4]);

	SetVertices();
	Setup();
}

Square::~Square() {
}

void Square::Setup() {
	m_vbo->bufferData(6, sizeof(vertex), m_vertices.get(), GL_STATIC_DRAW);
}

void Square::Draw() {
	Graphics::ShaderManager::GetInstance().UseShader(m_shaderProgram);
	Graphics::ShaderManager::GetInstance().setUniformMat4("pr_matrix", Ortho(-10, 10, -10, 10, -.1, -100));

	m_vbo->bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, m_indices.get());

	m_vbo->unbind();
}

void Square::Destroy() {

}

void Square::SetVertices() {
	m_vertices[0].position = vec3(m_position.x, m_position.y, m_position.z);
	m_vertices[1].position = vec3(m_position.x + m_size.x, m_position.y, m_position.z);
	m_vertices[2].position = vec3(m_position.x + m_size.x, m_position.y + m_size.y, m_position.z);
	m_vertices[3].position = vec3(m_position.x, m_position.y + m_size.y, m_position.z);

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 2;
	m_indices[4] = 3;
	m_indices[5] = 0;
}