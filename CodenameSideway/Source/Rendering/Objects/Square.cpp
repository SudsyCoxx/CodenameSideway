#include "Square.hpp"

#include "../../Textures/TextureManager.hpp"
#include "../../Utilities/Logging.hpp"

using namespace Utilities;
using namespace Graphics;

Square::Square(vec3 position, vec2 size, vec3 color, std::string texture) {
	m_shaderProgram = Graphics::ShaderManager::GetInstance().LoadShader(".\\Resources\\Shaders\\vs.shader", ".\\Resources\\Shaders\\fs.shader");
	if (texture != "") {
		m_texPath = texture;
		TextureManager::GetInstance().SubmitTexture(m_texPath);
		m_textureID = TextureManager::GetInstance().BindTexture(m_texPath);
	}
	m_size = size;
	m_position = position;
	m_color = color;
	m_vbo = new Buffers::VertexBufferObject(GL_ARRAY_BUFFER);
	
	m_vertices.reset(new vertex[4]);
	m_indices.reset(new unsigned int[6]);

	SetVertices();
	Setup();
}

Square::~Square() {
}

void Square::Setup() {
	m_vbo->bufferData(4, sizeof(vertex), m_vertices.get(), GL_STATIC_DRAW);
}

void Square::Draw() {
	Graphics::ShaderManager::GetInstance().UseShader(m_shaderProgram);

	TextureManager::GetInstance().BindTexture(m_texPath);
	TextureManager::GetInstance().EnableTextures();
	ShaderManager::GetInstance().setUniform1iv("textures", TextureManager::GetInstance().GetTextureIDs(), 16);

	m_vbo->bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vertex::color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vertex::uv));
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vertex::tid));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, m_indices.get());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	m_vbo->unbind();
}

void Square::Destroy() {
}

void Square::SetVertices() {
	m_vertices[0].position = vec3(m_position.x, m_position.y, m_position.z);
	m_vertices[1].position = vec3(m_position.x + m_size.x, m_position.y, m_position.z);
	m_vertices[2].position = vec3(m_position.x + m_size.x, m_position.y + m_size.y, m_position.z);
	m_vertices[3].position = vec3(m_position.x, m_position.y + m_size.y, m_position.z);

	m_vertices[0].color = m_color;
	m_vertices[1].color = m_color;
	m_vertices[2].color = m_color;
	m_vertices[3].color = m_color;

	m_vertices[0].uv = vec2(0,0);
	m_vertices[1].uv = vec2(1,0);
	m_vertices[2].uv = vec2(1,1);
	m_vertices[3].uv = vec2(0,1);

	m_vertices[0].tid = m_textureID;
	m_vertices[1].tid = m_textureID;
	m_vertices[2].tid = m_textureID;
	m_vertices[3].tid = m_textureID;

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 2;
	m_indices[4] = 3;
	m_indices[5] = 0;
}