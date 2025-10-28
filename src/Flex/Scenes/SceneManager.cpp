#include "Flex/Scenes/SceneManager.hpp"
#include "Flex/Core/Worlds/World.hpp"

using Flex::SceneBase;
using Flex::World;

namespace Flex {
	SceneManager::SceneManager(World* containingWorld) :
		m_containingWorld(containingWorld)
	{

	}
	SceneManager::~SceneManager() = default;

	bool SceneManager::removeScene(ID_t sceneID) {
		if (sceneID >= m_scenes.size()) return false;

		try {
			std::shared_ptr<SceneBase>& ptr = m_scenes.at(sceneID);
			ptr.reset();
		}
		catch (const std::exception&) {
			return false;
		}

		m_unusedSceneID.push(sceneID);

		return true;
	}

	void SceneManager::update(double dt) {
		if (m_activeScene.first.has_value() && m_activeScene.second != nullptr)
			m_activeScene.second->update(dt);
	}

	void SceneManager::postUpdate(double dt) {
		if (m_activeScene.first.has_value() && m_activeScene.second != nullptr)
			m_activeScene.second->postUpdate(dt);
	}

	void SceneManager::draw(Window& win) {
		if (m_activeScene.first.has_value() && m_activeScene.second != nullptr)
			m_activeScene.second->draw(win);
	}

	bool SceneManager::setActiveScene(ID_t sceneID) {
		if (sceneID >= m_scenes.size() ||
			m_activeScene.first.value_or(sceneID) == sceneID || 
			m_scenes.at(sceneID) == nullptr)
			return false;

		auto& [optID, scenePtr] = m_activeScene;
		scenePtr->deactivate();

		optID.reset();
		scenePtr.reset();

		optID = sceneID;
		scenePtr = m_scenes.at(sceneID);
		scenePtr->activate();

		return true;
	}
} // namespace Flex