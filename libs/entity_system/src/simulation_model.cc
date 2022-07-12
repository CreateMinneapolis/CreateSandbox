#include "./../include/simulation_model.h"

SimulationModel::SimulationModel(IController& controller) : controller(controller){
    compFactory = CompositeFactory();
    compFactory.AddFactory(new DroneFactory());
}


void SimulationModel::CreateEntity(JsonObject& entity) {

    IEntity* myNewEntity = compFactory.CreateEntity(entity);
    int id = entity["entityId"];
    std::string type = entity["type"];
    std::string name = entity["name"];
    JsonArray position = entity["position"];
    std::cout << "Entity of type: " << type << " Has been made" << std::endl;
    // // Call AddEntity to add it to the view
    controller.AddEntity(*myNewEntity);
    entities.push_back(myNewEntity);
}

void SimulationModel::Update(double dt) {
    //std::cout << "Update: " << dt << std::endl;
    // Call controller to update changed entities
    for (int i = 0; i < entities.size(); i++) {
      static_cast<IEntity*>(entities[i])->Update(dt);
      controller.UpdateEntity(*entities[i]);
    }


    // Remove entites you no longer need
    // controller.RemoveEntity(myDeletedEntityId);

    // Remove paths you no longer want to see:
    // controller.RemovePath(myDeletedPathId);
}
