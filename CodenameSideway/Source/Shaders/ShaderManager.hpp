#pragma once

#include <map>
#include <string>
#include <mutex>

#include "../Utilities/Singleton.hpp"
#include "../Utilities/SmartPointer.hpp"
#include "Shader.hpp"

using namespace Utilities;

namespace Graphics {
	class ShaderManager : public Singleton<ShaderManager> {
		friend class Singleton<ShaderManager>;
	public:
		int LoadShader(std::string PathVS, std::string PathFS);
		bool UseShader(int Id);

		void setUniform1f(const char* name, float value);
		void setUniform1fv(const char* name, float* value, int count);
		void setUniform1i(const char* name, int value);
		void setUniform1iv(const char* name, int* value, int count);
		void setUniform2f(const char* name, const vec2& vector);
		void setUniform3f(const char* name, const vec3& vector);
		void setUniform4f(const char* name, const vec4& vector);
		void setUniformMat4(const char* name, const mat4& matrix);

	private:
		ShaderManager();
		ShaderManager(const ShaderManager& s) = delete;
		ShaderManager& operator=(const ShaderManager& s) = delete;

		int m_nextShaderId = 0;
		unsigned int m_shaderInUse = -1;

		std::map<int, SmartPointer<Shader>> m_shaderMap;
		std::map<std::pair<std::string, std::string>, int> m_shaderLookupMap;
		std::mutex m_lock;

	protected:
	};
}