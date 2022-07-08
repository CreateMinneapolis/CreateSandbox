#ifndef I_ENTITY_FACTORY_H_
#define I_ENTITY_FACTORY_H_

#include "./../../utils/json.h"
#include "entity.h"


class IEntityFactory {
  public:
    virtual ~IEntityFactory() {}
    virtual IEntity* CreateEntity(JsonObject& entity) = 0;
};

#endif
