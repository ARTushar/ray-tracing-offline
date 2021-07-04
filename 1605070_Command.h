//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_COMMAND_H
#define RAYTRACING_COMMAND_H

#include <string>

enum COMMAND {
    TRIANGLE,
    SPHERE,
    GENERAL,
    END,
    INVALID
};

class Command {
public:
    static COMMAND generate_command(std::string command) {
      if(command == "triangle") return TRIANGLE;
      if(command == "sphere") return SPHERE;
      if(command == "general") return GENERAL;
      if(command == "end") return END;
      return INVALID;
    }
};

#endif //RAYTRACING_COMMAND_H
