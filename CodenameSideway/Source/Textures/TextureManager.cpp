#include "TextureManager.hpp"

using namespace Graphics;

TextureManager::TextureManager() {
	m_maxTextures = 16;
    m_textureIDs.reset(new GLint[m_maxTextures]);
    for(int i=0; i < m_maxTextures; i++){
        m_textureIDs[i] = i;
    }
}

TextureManager::~TextureManager(){
    for(int i=0; i<m_allTextures.size(); i++){
        delete m_allTextures[i];
    }
}

void TextureManager::SubmitTexture(const std::string& path){
    if( !FindTexture(path).isFound ){
        m_allTextures.push_back(new Texture(path));
        m_textureMap[path] = (int)m_allTextures.size()-1;
    }
}

searchResult TextureManager::FindTexture(const std::string& path){
    searchResult result;
    result.isFound = false;
    if(m_textureMap.count(path)){
        result.isFound = true;
        result.texture = m_allTextures[m_textureMap[path]];
    }
    return result;
}

void TextureManager::EnableTextures(){
    for (int i = 0; i < m_currentTextures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_currentTextures[i]->getID());
    }
}

int TextureManager::BindTexture(const std::string& path){
	if (m_textureMap.count(path) == 0) {
		return -1;
	}

	for(int i=0;i<m_currentTextures.size(); i++){
		if (m_currentTextures[i] == m_allTextures[m_textureMap[path]]) {
			return i;
		}
	}

    if((int)m_currentTextures.size() == m_maxTextures){
        ResetCurrentTextures();
    }

    m_currentTextures.push_back(m_allTextures[m_textureMap[path]]);
    return (int)m_currentTextures.size();
}
