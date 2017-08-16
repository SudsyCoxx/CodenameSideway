//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#include "TextureManager.hpp"

using namespace Graphics;

TextureManager::TextureManager() {
	// call this ONLY when linking with FreeImage as a static library
	//#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	//#endif

	glEnable(GL_TEXTURE_2D);
}
	
TextureManager::~TextureManager() {
	// call this ONLY when linking with FreeImage as a static library
	//#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	//#endif

	UnloadAllTextures();
}

unsigned int TextureManager::LoadTexture(std::string filename, GLenum image_format, GLint internal_format, GLint level, GLint border) {
	if (m_stringToTexIDMap.count(filename) > 0) 
		return m_stringToTexIDMap[filename];

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = nullptr;
	BYTE* bits = nullptr;
	
	unsigned int width = 0, height = 0;

	GLuint gl_texID;
	unsigned int internalTexId;

	std::lock_guard<std::mutex> lock(m_lock);
	m_stringToTexIDMap[filename] = internalTexId = m_nextTexID++;;

	fif = FreeImage_GetFileType(filename.c_str(), 0);
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
	if(fif == FIF_UNKNOWN)
		return false;

	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename.c_str());
	if(!dib)
		return false;

	bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	if((bits == 0) || (width == 0) || (height == 0))
		return false;

	glGenTextures(1, &gl_texID);
	m_texID[internalTexId] = gl_texID;
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		border, image_format, GL_UNSIGNED_BYTE, bits);

	FreeImage_Unload(dib);

	return internalTexId;
}

bool TextureManager::UnloadTexture(const unsigned int texID) {
	if(m_texID.find(texID) == m_texID.end())
		return false;

	glDeleteTextures(1, &(m_texID[texID]));
	m_texID.erase(texID);
	return true;
}

bool TextureManager::BindTexture(const unsigned int texID) {
	if (m_texID.find(texID) == m_texID.end())
		return false;
	
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	return true;
}

void TextureManager::UnloadAllTextures() {
	std::lock_guard<std::mutex> lock(m_lock);
	for (auto& texture : m_texID) {
		UnloadTexture(texture.second);
	}

	m_texID.clear();
	m_stringToTexIDMap.clear();
	m_nextTexID = 0;
}