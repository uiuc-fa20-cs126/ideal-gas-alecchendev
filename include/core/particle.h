#pragma once
#include "cinder/gl/gl.h"
#include <map>
#include <string>
#include <vector>

using glm::vec2;
using std::vector;
using ci::Color;
using std::string;

namespace idealgas {

struct Particle {
  Particle(string type, float radius, float mass, Color color, vec2 position, vec2 velocity) {
    this->type = type;
    this->radius = radius;
    if (mass <= 0.0f)
      throw std::invalid_argument("Mass cannot be 0 or less.");
    this->mass = mass;
    this->color = color;
    this->position = position;
    this->velocity = velocity;
  }

  string type;
  float radius;
  float mass;
  Color color;
  vec2 position;
  vec2 velocity;
};

}  // namespace idealgas