#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_

#include "./interfaces/entity.h"
#include "./interfaces/Ientity_factory.h"
#include "./drone_factory.h"

/**
 * @brief A composite factory for all entity factories in the program. Uses the factory pattern to manage the creation of entities 
 */
class CompositeFactory : public IEntityFactory {
  public:
    /**
     * @brief Creates an Entity with given information
     * @param[in] entity JsonObject of entity details
     */
    IEntity* CreateEntity(JsonObject& entity);
    /**
     * @brief Creates an Entity with given information
     * @param[in] factoryEntity new factory to be added to the composite factory
     */
    void AddFactory(IEntityFactory* factoryEntity);
    /**
     * @brief Destructor
     */
    virtual ~CompositeFactory();

  private:
    /**
     * @brief Vector of all factories in the system
     */
    std::vector<IEntityFactory*> componentFactories;
};

#endif
