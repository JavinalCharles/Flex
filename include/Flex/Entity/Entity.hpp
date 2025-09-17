#pragma once

#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include <SFML/Graphics/Transformable.hpp>

#include <Flex/Component/Component.hpp>
#include <Flex/Entity/SharedContext.hpp>
#include <Flex/Utility/Utility.hpp>

namespace Flex {

template <typename C>
concept ComponentType = std::is_base_of<Flex::Component, C>::value;

class Entity : public sf::Transformable {
public: // public attributes
	const Flex::ID_t ID;

	static ID_t totalEntityCreated();
public:
	/**
	 * @defgroup Constructors
	 * @brief Construct a new Entity object
	 * 
	 * @param i_context contains information from the environment in which
	 * the entity is created.
	 * @{
	 */
	Entity();
	explicit Entity(Flex::SharedContext* i_context);

	constexpr Entity(const Entity&) = delete;
	constexpr Entity(Entity&&) = delete;
	/// @} - End of COnstructor

	// @brief Destructor
	virtual ~Entity();
	
	/**
	 * @defgroup Assignment operators
	 * @brief operator= are deleted to disallow copy and move operations.
	 */
	constexpr Entity& operator=(const Entity&) = delete;
	constexpr Entity& operator=(Entity&&) = delete;
	/** @} */

	/// @brief Signals the entity to awaken all components.
	void awake();

	/// @defgroup Modifiers
	/// @{
	/**
	 * @name addComponent
	 * @brief Creates
	 * 
	 * @tparam C The type of the component.
	 * @return A pointer to the created component
	 */
	/// @{
	template <ComponentType C>
	std::shared_ptr<C> addComponent();
	template <ComponentType C, typename... Args>
	std::shared_ptr<C> addComponent(Args... args);
	/// @} - subgroup addComponent

	/**
	 * @brief Get a specific component from the entity.
	 * 
	 * @tparam C The component type
	 * @returns A pointer to the component if it exist, nullptr otherwise.
	 */
	template <ComponentType C>
	std::shared_ptr<C> getComponent() const;

	/**
	 * @brief Sets the "staticness" of the entity
	 * @paragraph Static Entities are not expected to move, rotate, 
	 * translate or in any way change their state. This allows the systems
	 * to optimize their processes by excluding static entities from most
	 * calculations, focusing mostly on the dynamic entities.
	 * @param isStatic The staticness of this entity. Defaults to true.
	 */
	void setStatic(bool isStatic = true);

	/**
	 * @brief Prepares this entity for removal.
	 * @paragraph Turns a flag that will signal the systems in
	 * the next removal cycle to remove this entity from their systems, 
	 * clearing any reference to its components.
	 * @param remove sets whether to remove this object or not.
	 */
	void queueForRemoval(bool remove = true);

	/// @} - Group Modifiers


	/// @defgroup Lookup
	/// @{
	
	/// @brief Returns whether this entity is ready to be removed.
	/// @return true if this is ready for removal. False otherwise..
	constexpr bool isReadyForRemoval() const noexcept;

	/// @brief Checks if the entity is a static entity.
	/// @return true if this entity is static. False, otherwise.
	constexpr bool isStatic() const noexcept;
	/// @}

private:
	bool m_readyForRemoval = false;
	bool m_static = false;

	std::shared_ptr<Flex::SharedContext> m_context = nullptr;
	std::unordered_map<std::type_index, std::shared_ptr<Flex::Component>> m_components;

private:
	static std::size_t s_count;
}; // class Entity

template <ComponentType C>
std::shared_ptr<C> Entity::addComponent() {
	const std::type_index IDX(typeid(C));
	auto it = m_components.find(IDX);
	if (it == m_components.end()) {
		it = m_components.try_emplace(IDX, this).first;
	}
	return it->second;
}

template <ComponentType C, typename... Args>
std::shared_ptr<C> Entity::addComponent(Args... args) {
	const std::type_index IDX(typeid(C));
	auto it = m_components.find(IDX);
	if (it == m_components.end()) {
		it = m_components.try_emplace(IDX, this, std::forward(args...)).first;
	}
	return it->second;
}

template <ComponentType C>
std::shared_ptr<C> Entity::getComponent() const {
	const std::type_index IDX(typeid(C));
	auto it = m_components.find(IDX);
	if (it == m_components.end()) {
		return nullptr;
	}
	return it->second;
}

constexpr bool Entity::isReadyForRemoval() const noexcept {
	return m_readyForRemoval;
}

constexpr bool Entity::isStatic() const noexcept {
	return m_static;
}

} // namespace Flex