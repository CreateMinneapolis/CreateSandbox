#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include "./interfaces/Ientity_factory.h"
#include "drone.h"

#include <vector>

/**
 * @brief Factory for creating drone entities
 */
class DroneFactory : public IEntityFactory {
  public:
    /**
     * @brief Destructor 
     */
    ~DroneFactory() {}
    /**
     * @brief Takes in the Json object and creates a drone entity
     * @param[in] entity JsonObject of all entity details
     */
    IEntity* CreateEntity(JsonObject& entity);
};

#endif
