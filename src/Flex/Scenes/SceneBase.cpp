#include "Flex/Scenes/SceneBase.hpp"
#include "Flex/Scenes/SceneManager.hpp"

using Flex::SceneBase;

SceneBase::SceneBase() = default;

SceneBase::~SceneBase() = default;

void SceneBase::onCreate() { }
void SceneBase::onDestroy() { }
void SceneBase::onActivate() { }
void SceneBase::onDeactivate() { }

void SceneBase::onUpdate(double dt) { }
void SceneBase::onPostUpdate(double dt) { }
void SceneBase::onDraw(sf::RenderWindow& win) { }

void SceneBase::create() {
	this->onCreate();

	for (auto& childScene : m_childScenes) {
		childScene->create();
	}
}

void SceneBase::destroy() {
	for (auto& childScene : m_childScenes) {
		childScene->destroy();
	}

	this->onDestroy();
}

void SceneBase::activate() {
	this->onActivate();

	for (auto& childScene : m_childScenes) {
		childScene->activate();
	}
}

void SceneBase::deactivate() {
	for (auto& childScene : m_childScenes) {
		childScene->deactivate();
	}

	this->onDeactivate();
}

void SceneBase::update(double dt) {
	this->onUpdate(dt);

	for (auto& childScene : m_childScenes) {
		childScene->update(dt);
	}
}

void SceneBase::postUpdate(double dt) {
	this->onPostUpdate(dt);

	for (auto& childScene : m_childScenes) {
		childScene->postUpdate(dt);
	}
}

void SceneBase::draw(sf::RenderWindow& win) {
	this->onDraw(win);

	for (auto& childScene : m_childScenes) {
		childScene->draw(win);
	}
}

