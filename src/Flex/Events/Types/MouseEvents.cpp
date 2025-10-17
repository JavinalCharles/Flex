#include "Flex/Events/Types/MouseEvents.hpp"

using Flex::Event;
using Flex::ID_t;
using Flex::MouseWheelScrolledEvent;

MouseWheelScrolledEvent::MouseWheelScrolledEvent()
	: Event<MouseWheelScrolledEvent>()
{

}

// MouseWheelScrolledEvent::MouseWheelScrolledEvent(ID_t wheel, float delta, const sf::Vector2i& pos) : Event<MouseWheelScrolledEvent>(),
// 	wheel(wheel), delta(delta), position(pos)
// {

// }

MouseWheelScrolledEvent::MouseWheelScrolledEvent(const sf::Event::MouseWheelScrolled& e) 
	: Event<MouseWheelScrolledEvent>(),
	wheel(static_cast<ID_t>(e.wheel)),
	delta(e.delta),
	position(e.position)
{

}