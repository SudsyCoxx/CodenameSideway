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

	private:
		ShaderManager();
		ShaderManager(const ShaderManager& s) = delete;
		ShaderManager& operator=(const ShaderManager& s) = delete;

		int m_nextShaderId = 0;

		std::map<int, SmartPointer<Shader>> m_shaderMap;
		std::map<std::pair<std::string, std::string>, int> m_shaderLookupMap;
		std::mutex m_lock;

	protected:
	};
}