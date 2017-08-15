#include "ShaderManager.hpp"

using namespace Graphics;

int ShaderManager::LoadShader(std::string PathVS, std::string PathFS) {
	if (m_shaderLookupMap.count(std::make_pair(PathVS, PathFS)) > 0) {
		return m_shaderLookupMap[std::make_pair(PathVS, PathFS)];
	}

	int shaderId;
	{
		std::lock_guard<std::mutex> lock(m_lock);
		shaderId = ++m_nextShaderId;
	}

	m_shaderMap[shaderId] = SmartPointer<Shader>(new Shader(PathVS, PathFS));
	m_shaderLookupMap[std::make_pair(PathVS, PathFS)] = shaderId;
}

bool ShaderManager::UseShader(int Id) {
	if (m_shaderInUse == Id) return true;

	if (m_shaderMap.count(Id) > 0) {
		m_shaderMap[Id]->UseShader();
		return true;
	}
	return false;
}

ShaderManager::ShaderManager() {

}