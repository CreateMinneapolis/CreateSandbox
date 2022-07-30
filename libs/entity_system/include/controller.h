#ifndef CONTROLLER_H_
#define CONTROLLER_H_


#include "./interfaces/entity.h"

//--------------------  Controller Interface ----------------------------


/**
 * @brief  Abstract controller class used in the Transit Service.  Uses the Model View Controller Pattern
 */
class IController {
public:
    virtual ~IController() {}
    /**
     * @brief  Adds an entity to the program
     * @param[in] entity accepts any kind of entity passed in
     */
    virtual void AddEntity(const IEntity& entity) = 0;
    /**
     * @brief Adds an entity to the program
     * @param[in] entity accepts any kind of entity passed in
     */
    virtual void UpdateEntity(const IEntity& entity) = 0;
    /**
     * @brief Removes an entity from the program
     * @param[in] id id of entity that is to be removed
     */
    virtual void RemoveEntity(int id) = 0;
    /**
     * @brief Allows messages to be passed back to the view
     * @param[in] event string of what ever event you want to send to the web app
     * @param[in] details details of what you want to be sent to the front end
     */
    virtual void SendEventToView(const std::string& event, const JsonObject& details) = 0;
};

#endif
