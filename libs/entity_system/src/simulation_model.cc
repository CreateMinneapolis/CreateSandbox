#include "./../include/simulation_model.h"

double* JsonArrayToDoublePtr(JsonArray arr){
    double* newArray = (double*) malloc(sizeof(double)*3);
    newArray[0] = arr[0];
    newArray[1] = arr[1];
    newArray[2] = arr[2];
    return newArray;
}


SimulationModel::SimulationModel(IController& controller) : controller(controller){
    compFactory = CompositeFactory();
    compFactory.AddFactory(new DroneFactory());
}


void SimulationModel::CreateEntity(JsonObject& entity) {

    IEntity* myNewEntity = compFactory.CreateEntity(entity);
    JsonArray position = entity["position"];
    JsonArray velocity = entity["velocity"];
    AddEntity(entity["name"], JsonArrayToDoublePtr(position), JsonArrayToDoublePtr(velocity));
    int id = entity["entityId"];
    std::string type = entity["type"];
    std::string name = entity["name"];
   
    std::cout << "Entity of type: " << type << " Has been made" << std::endl;
    // // Call AddEntity to add it to the view
    controller.AddEntity(*myNewEntity);
    entities.push_back(myNewEntity);
}

void SimulationModel::Update(double dt) {
    //std::cout << "Update: " << dt << std::endl;
    // Call controller to update changed entities
   
    UpdateSimulationTime(dt);
    CircleForce();

    for (int i = 0; i < entities.size(); i++) {
      static_cast<IEntity*>(entities[i])->Update(dt);
      Vec* pos = GetPositionVectorOfEntity(entities[i]->GetDetails()["name"]);
      entities[i]->SetPosition(pos);
      //std::cout << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
      controller.UpdateEntity(*entities[i]);
      free(pos);
    }
   
   
    // Remove entites you no longer need
    // controller.RemoveEntity(myDeletedEntityId);

    // Remove paths you no longer want to see:
    // controller.RemovePath(myDeletedPathId);
}
