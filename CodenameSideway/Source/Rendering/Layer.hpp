#pragma once

#include <map>
#include <vector>
#include <mutex>

#include "../Utilities/SmartPointer.hpp"

#include "RenderInterface.hpp"
#include "Renderer.hpp"

class Layer : public RenderInterface {
public:

	enum RenderableLayers {
		ID_UI = 0,
		ID_PARTICLES = 1,
		ID_FOREGROUND = 2,
		ID_MIDDLE = 3,
		ID_BACKGROUND = 4
	};

	void Setup() {
		std::lock_guard<std::mutex> lock(m_lock);
		for (auto& layerObj : m_renderObjs) {
			for (auto& renderer : layerObj.second) {
				renderer->Setup();
			}
		}
	}

	void Destroy() {
		std::lock_guard<std::mutex> lock(m_lock);
		for (auto& layerObj : m_renderObjs) {
			for (auto& renderer : layerObj.second) {
				renderer->Destroy();
			}
		}
	}

	void Draw() {
		std::lock_guard<std::mutex> lock(m_lock);
		for (auto& layerObj : m_renderObjs) {
			for (auto& renderer : layerObj.second) {
				renderer->Draw();
			}
		}
	}

	void ClearLayer(RenderableLayers LayerId) {
		std::lock_guard<std::mutex> lock(m_lock);
		m_renderObjs[LayerId].clear();
	}

	void AddItemToLayer(RenderableLayers LayerId, Utilities::SmartPointer<Renderer> object) {
		std::lock_guard<std::mutex> lock(m_lock);
		m_renderObjs[LayerId].push_back(object);
	}

private:
	std::map<RenderableLayers, std::vector<Utilities::SmartPointer<Renderer>>> m_renderObjs;

	std::mutex m_lock;

protected:
};
