#include "Flex/Scenes/SceneManager.hpp"

using Flex::SceneBase;
using Flex::SceneManager;

SceneManager::SceneManager() = default;
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
	if (m_activeSceneID >= m_scenes.size()) return;
	std::shared_ptr<SceneBase>& scenePtr = m_scenes.at(m_activeSceneID);
	if (scenePtr == nullptr) return;

	scenePtr->update(dt);
}

void SceneManager::postUpdate(double dt) {
	if (m_activeSceneID >= m_scenes.size()) return;
	std::shared_ptr<SceneBase>& scenePtr = m_scenes.at(m_activeSceneID);
	if (scenePtr == nullptr) return;

	scenePtr->postUpdate(dt);
}

void SceneManager::draw(Window& win) {
	if (m_activeSceneID >= m_scenes.size()) return;
	std::shared_ptr<SceneBase>& scenePtr = m_scenes.at(m_activeSceneID);
	if (scenePtr == nullptr) return;

	scenePtr->draw(win);
}

bool SceneManager::setActiveScene(ID_t sceneID) {
	
}