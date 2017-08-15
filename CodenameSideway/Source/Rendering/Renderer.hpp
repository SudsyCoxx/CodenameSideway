#pragma once

#include <map>
#include <mutex>

#include "../Utilities/SmartPointer.hpp"
#include "RenderInterface.hpp"
#include "Renderable.hpp"

class Renderer : public RenderInterface {
public:
	void Setup() {
		std::lock_guard<std::mutex> lock(m_lock);
		for (auto& obj : m_renderableObjects) {
			obj.second->Setup();
		}
	}

	void Destroy() {
		std::lock_guard<std::mutex> lock(m_lock);
		for (auto& obj : m_renderableObjects) {
			obj.second->Destroy();
		}
	}

	void Draw() {
		std::lock_guard<std::mutex> lock(m_lock);
		for (auto& obj : m_renderableObjects) {
			obj.second->Draw();
		}
	}

	const int AddOject(Utilities::SmartPointer<Renderable> obj) {
		m_renderableObjects[m_nextObjId++] = obj;
		return m_nextObjId;
	}

private:
	std::map<int, Utilities::SmartPointer<Renderable>> m_renderableObjects;
	int m_nextObjId = 0;

	std::mutex m_lock;

protected:
};