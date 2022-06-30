/**
Copyright (c) 2019 Dan Orban
*/
#include <iostream>
#include <map>
#include "drone_app.h" 

int main(int argc, char**argv) {
    if (argc > 0) {
        int port = std::atoi(argv[1]);

        // Create a web sockets server at a specific port number
        WebServer<DroneApp> server(port, std::string(argv[2]));
        while (true) {
            // Handle requests from clients
            server.service();
        }
    }
    else {
        std::cout << "Usage: ./drone_app 8081" << std::endl;
    }

    return 0;
}


