#pragma once

#include <FreeImage.h>
#include <GL/glew.h>

#include <memory>
#include <string>

namespace Graphics {
    class Texture {
    public:
		Texture(const std::string& path);
        ~Texture();
        
        void bind() const;
        void unbind() const;
        
        GLuint getID() const;

	private:
		void loadTexture();

		BYTE* m_bits;

		GLuint m_texID;
		GLsizei m_width;
		GLsizei m_height;

		std::string m_filename;
    };
    
	static BYTE* load_Texture(const char* filename, GLsizei* width, GLsizei* height)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if (!dib)
			return nullptr;

		BYTE* result = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		return result;
	}
}