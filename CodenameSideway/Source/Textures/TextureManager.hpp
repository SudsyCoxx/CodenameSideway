#pragma once

#include "../Utilities/Singleton.hpp"
#include "Texture.hpp"

#include <vector>
#include <string>
#include <map>
#include <memory>

using namespace Utilities;

namespace Graphics {
    
    typedef std::map<std::string, int> textureMap;
    
    struct searchResult {
        bool isFound;
		Texture* texture;
    };
    
    class TextureManager : public Singleton<TextureManager> {
		friend class Singleton<TextureManager>;
    public:
        ~TextureManager();

        void EnableTextures();
        void SubmitTexture(const std::string& path);
        int BindTexture(const std::string& path);
        inline GLint* GetTextureIDs() const { return m_textureIDs.get(); }
	
	private:
		TextureManager();
		TextureManager(const TextureManager& s) = delete;
		TextureManager& operator=(const TextureManager& s) = delete;

		searchResult FindTexture(const std::string& path);
        inline void ResetCurrentTextures(){ m_currentTextures.clear(); }
		
		int m_maxTextures;

		std::vector<Texture*> m_allTextures;	
		std::vector<Texture*> m_currentTextures;
		std::unique_ptr<GLint[]> m_textureIDs;	

		textureMap m_textureMap;

	};

}