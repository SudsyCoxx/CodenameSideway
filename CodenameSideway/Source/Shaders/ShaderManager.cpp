#include "ShaderManager.hpp"

using namespace Graphics;

int ShaderManager::LoadShader(std::string PathVS, std::string PathFS) {
	if (m_shaderLookupMap.count(std::make_pair(PathVS, PathFS)) > 0) {
		return m_shaderLookupMap[std::make_pair(PathVS, PathFS)];
	}

	int shaderId = -1;
	{
		std::lock_guard<std::mutex> lock(m_lock);
		shaderId = ++m_nextShaderId;
	}

	m_shaderMap[shaderId] = SmartPointer<Shader>(new Shader(PathVS, PathFS));
	m_shaderLookupMap[std::make_pair(PathVS, PathFS)] = shaderId;

	return shaderId;
}

bool ShaderManager::UseShader(int Id) {
	if (m_shaderInUse == Id) return true;

	if (m_shaderMap.count(Id) > 0) {
		m_shaderMap[Id]->UseShader();
		m_shaderInUse = Id;
		return true;
	}
	return false;
}

ShaderManager::ShaderManager() {

}

void ShaderManager::setUniform1f(const char* name, float value) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniform1f(name, value);
	}
}

void ShaderManager::setUniform1fv(const char* name, float* value, int count) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniform1fv(name, value, count);
	}
}

void ShaderManager::setUniform1i(const char* name, int value) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniform1i(name, value);
	}
}

void ShaderManager::setUniform1iv(const char* name, int* value, int count) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniform1iv(name, value, count);
	}
}

void ShaderManager::setUniform2f(const char* name, const vec2& vector) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniform2f(name, vector);
	}
}

void ShaderManager::setUniform3f(const char* name, const vec3& vector) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniform3f(name, vector);
	}
}

void ShaderManager::setUniform4f(const char* name, const vec4& vector) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniform4f(name, vector);
	}
}

void ShaderManager::setUniformMat4(const char* name, const mat4& matrix) {
	if (m_shaderInUse != -1) {
		m_shaderMap[m_shaderInUse]->setUniformMat4(name, matrix);
	}
}