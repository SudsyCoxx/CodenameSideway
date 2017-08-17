#include "Texture.hpp"

using namespace Graphics;
    
Texture::Texture(const std::string& Filename)
: m_filename(Filename)
{
	loadTexture();
}

Texture::~Texture() {
    glDeleteTextures(GL_TEXTURE_2D, &m_texID);
}

//void Texture::loadTexture(){
//    BYTE* pixels = load_Texture(m_filename.c_str(), &m_width, &m_height);
//    
//    glGenTextures(1, &m_texID);
//    glBindTexture(GL_TEXTURE_2D, m_texID);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}

void Texture::loadTexture(){
	m_bits = load_Texture(m_filename.c_str(), &m_width, &m_height);
    
    glGenTextures(1, &m_texID);
    glBindTexture(GL_TEXTURE_2D, m_texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_bits);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID() const {
    return m_texID;
}
