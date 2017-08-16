//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#pragma once 

#include <windows.h>
#include <gl/gl.h>
#include "FreeImage.h"
#include <map>
#include <string>
#include <mutex>

#include "../Utilities/Singleton.hpp"

namespace Graphics {
	class TextureManager : public Utilities::Singleton<TextureManager> {
		friend class Utilities::Singleton<TextureManager>;
	public:
		virtual ~TextureManager();

		unsigned int LoadTexture(std::string filename,	//where to load the file from
			GLenum image_format = GL_RGB,				//format the image is in
			GLint internal_format = GL_RGB,				//format to store the image in
			GLint level = 0,							//mipmapping level
			GLint border = 0);							//border size

		bool BindTexture(const unsigned int texID);

		void UnloadAllTextures();
		bool UnloadTexture(const unsigned int texID);

	private:
		TextureManager();
		TextureManager(const TextureManager& tm) = delete;
		TextureManager& operator=(const TextureManager& tm) = delete;

		std::map<unsigned int, GLuint> m_texID;
		std::map<std::string, int> m_stringToTexIDMap;
		unsigned int m_nextTexID = 0;

		std::mutex m_lock;

	protected:
	};
}