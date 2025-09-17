#pragma once

namespace Flex {

class Entity;
/**
 * @brief Class Interface for all Components that could be owned by an
 * Entity.
 * 
 * Components store attributes and data related to their owner entity.
 * The components are also used by the
 * systems which keeps and ID of an entity to determine how the state of
 * the entity should change.
 * @author Charlemagne Javinal
 * @copyright MIT License
 */
class Component {
friend class Flex::Entity;
public:
	/**
	 * @brief Construct a new Component object
	 * 
	 * @param owner pointer to its owner.
	 */
	/// @{
	Component();
	explicit Component(Entity* owner);
	/// @}

	/**
	 * @brief Destroy the Component object
	 * 
	 */
	virtual ~Component();

	/**
	 * @brief Signals to the component to ensure that attributes are initialized properly.
	 * 
	 */
	virtual void awake();

	Entity* getOwner() const;
protected:
	Entity* m_owner = nullptr;
}; 

} // namespace Flex