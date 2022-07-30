#ifndef ENTITY_H_
#define ENTITY_H_

#include "./../../utils/json.h"

//--------------------  Entity Interface ----------------------------
/**
 * @brief  Abstract entity class. Defines behavior for all entities
 */
class IEntity {
public:
    IEntity() {
      static int currentId = 0;
      id = currentId;
      currentId++;
    }
    virtual ~IEntity() {}
    virtual int GetId() const { return id; }
    virtual double GetPosition(int index) const = 0;
    virtual double GetDirection(int index) const = 0;
    virtual void SetPosition(double* position) = 0;
    virtual JsonObject GetDetails() const = 0;
    virtual void Update(double dt) {}
private:
    int id;
};

#endif
