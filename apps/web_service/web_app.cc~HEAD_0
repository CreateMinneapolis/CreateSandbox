#include <map>
#include <chrono>
#include "WebServer.h"
#include "simulation_model.h"
#include "json.h"

//--------------------  Controller ----------------------------

/// A Transit Service that communicates with a web page through web sockets.  It also acts as the controller
/// in the model view controller pattern.
class WebAppService : public JsonSession, public IController {
public:
    WebAppService(SimulationModel& model) : model(model), start(std::chrono::system_clock::now()), time(0.0) {
        
    }

    /// Handles specific commands from the web server
    void ReceiveCommand(const std::string& cmd, JsonObject& data, JsonObject& returnValue) {
        //std::cout << cmd << ": " << data << std::endl;
        if (cmd == "CreateEntity") {
            model.CreateEntity(data);
        }
        else if (cmd == "ping") {
            returnValue["response"] = data;
        }
        else if (cmd == "update") {
            updateEntites.clear();

            std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            double delta = diff.count() - time;
            time += delta;

            double simSpeed = data["simSpeed"];
            delta *= simSpeed;

            if (delta > 0.1) {
                for (float f = 0.0; f < delta; f+=0.01) {
                    model.Update(0.01);
                }
            }
            else {
                model.Update(delta);
            }

            for (std::map<int, const IEntity*>::iterator it = updateEntites.begin(); it != updateEntites.end(); it++) {
                // Send updated entities
                SendEntity("UpdateEntity", *it->second, false);
            }
        }
    }

    void SendEntity(const std::string& event, const IEntity& entity, bool includeDetails) {
        //JsonObject details = entity.GetDetails();
        JsonObject details;
        if (includeDetails) {
            details["details"] = entity.GetDetails();
        }
        details["id"] = entity.GetId();
        JsonArray pos = {entity.GetPosition(0), entity.GetPosition(1), entity.GetPosition(2)};
        JsonArray dir = {entity.GetDirection(0), entity.GetDirection(1), entity.GetDirection(2)};
        details["pos"] = pos;
        details["dir"] = dir;
        SendEventToView(event, details);
    }

    void AddEntity(const IEntity& entity) {
        SendEntity("AddEntity", entity, true);
    }
    
    void UpdateEntity(const IEntity& entity) {
        updateEntites[entity.GetId()] = &entity;
    }

    void RemoveEntity(int id) {
        JsonObject details;
        details["id"] = id;
        SendEventToView("RemoveEntity", details);
    }

    /// Allows messages to be passed back to the view
    void SendEventToView(const std::string& event, const JsonObject& details) {
        JsonObject eventData;
        eventData["event"] = event;
        eventData["details"] = details;
        sendMessage(eventData.ToString());
    }

private:
    // Simulation Model
    SimulationModel& model;
    // Used for tracking time since last update
    std::chrono::time_point<std::chrono::system_clock> start;
    // The total time the server has been running.
    double time;
    // Current entities to update
    std::map<int, const IEntity*> updateEntites;
};


//--------------------  View / Web Server Code ----------------------------

/// The WebAppServer holds the simulation and updates sessions.
class WebAppServer : public WebServerBase, public IController {
public:
	WebAppServer(int port = 8081, const std::string& webDir = ".") : WebServerBase(port, webDir), model(*this) {}
    void AddEntity(const IEntity& entity) {
        for (int i = 0; i < sessions.size(); i++) {
            static_cast<WebAppService*>(sessions[i])->AddEntity(entity);
        }
    }
    
    void UpdateEntity(const IEntity& entity) {
        for (int i = 0; i < sessions.size(); i++) {
            static_cast<WebAppService*>(sessions[i])->UpdateEntity(entity);
        }
    }

    void RemoveEntity(int id) {
        for (int i = 0; i < sessions.size(); i++) {
            static_cast<WebAppService*>(sessions[i])->RemoveEntity(id);
        }
    }

    void SendEventToView(const std::string& event, const JsonObject& details) {
        for (int i = 0; i < sessions.size(); i++) {
            static_cast<WebAppService*>(sessions[i])->SendEventToView(event, details);
        }
    }

protected:
	Session* createSession() { return new WebAppService(model); }
private:
    SimulationModel model;
};

int main(int argc, char**argv) {
    if (argc > 1) {
        int port = std::atoi(argv[1]);
        std::string webDir = std::string(argv[2]);
        WebAppServer server(port, webDir);
        while (true) {
            server.service();
        }
    }
    else {
        std::cout << "Usage: ./build/bin/DroneSim 8081 apps/drone_sim/web/" << std::endl;
    }

    return 0;
}

