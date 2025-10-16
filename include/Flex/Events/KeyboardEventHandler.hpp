#pragma once

#include <array>
#include <functional>
#include <vector>
#include <SFML/Window/Event.hpp>

#include "Flex/Events/EventHandler.hpp"
#include "Flex/Utilities/Utility.hpp"


namespace Flex {

class KeyboardEventHandler : public EventHandler {
public:
	using KeyPressedCallback = std::function<void(const sf::Event::KeyPressed&)>;
	using KeyReleasedCallback = std::function<void(const sf::Event::KeyReleased&)>;
	static constexpr ID_t MAX_KEYS = 256u;

	KeyboardEventHandler();
	KeyboardEventHandler(const KeyboardEventHandler&) = delete;
	KeyboardEventHandler(KeyboardEventHandler&&) = delete;
	KeyboardEventHandler& operator=(const KeyboardEventHandler&) = delete;
	KeyboardEventHandler& operator=(KeyboardEventHandler&&) = delete;
	virtual ~KeyboardEventHandler();

	[[nodiscard]] ID_t registerKeyPressedCallback(KeyPressedCallback callback);
	[[nodiscard]] ID_t registerKeyReleasedCallback(KeyReleasedCallback callback);

	void bindKeyPress(ID_t key, ID_t callbackID);
	void bindKeyPress(ID_t key, KeyPressedCallback callback);

	void bindKeyRelease(ID_t key, ID_t callbackID);
	void bindKeyRelease(ID_t key, KeyReleasedCallback callback);

	[[nodiscard]] virtual std::vector<std::type_index> getEventTypes() const override;

	[[nodiscard]] bool handleEvent(const sf::Event::KeyPressed& event) override;
	[[nodiscard]] bool handleEvent(const sf::Event::KeyReleased& event) override;
private:
	std::array<std::vector<ID_t>, MAX_KEYS> m_keyPressBindings{};
	std::array<std::vector<ID_t>, MAX_KEYS> m_keyReleaseBindings{};

	std::vector<KeyPressedCallback> m_keyPressedCallbacks{};
	std::vector<KeyReleasedCallback> m_keyReleasedCallbacks{};
}; // class KeyPressEventHandler

} // namespace Flex