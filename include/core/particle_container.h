#pragma once
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include <map>
#include <string>
#include <vector>
#include "particle.h"

using glm::vec2;
using std::vector;
using ci::Color;

namespace idealgas {

class ParticleContainer {
 public:
  ParticleContainer() {
    width_ = 720;
    height_ = 480;
    time_step_ = 1;
  }

  /**
   * Initialize equal number of particles for each template provided
   * Distributes pixel positions in a grid, gives them random directions given magnitude of template velocity
   * @param num_particles Total number of particles to initialize
   * @param particle_templates Vector of particles that gives templates for particles ot be created
   */
  ParticleContainer(float width, float height, float time_step, int num_particles,
                    vector<Particle> particle_templates);

  /**
   * Checks for particle collisions, updates velocities, and updates positions
   */
  void Update();

  /**
   * Checks if a given particle will collide with another particle on the next timestep
   * Updates velocity of both particles after colliding
   * @param particle
   * @param other_particle
   */
  void CheckCollisionParticle(Particle& particle, Particle& other_particle);

  /**
   * Checks if a given particle will collide with a wall on the next timestep
   * Updates velocity of the particle after colliding
   * @param particle
   */
  void CheckCollisionWall(Particle& particle);

  const vector<Particle> &getParticles() const;
  float getWidth() const;
  float getHeight() const;

private:

  float width_ = 720;
  float height_ = 480;
  float time_step_ = 1;
  vector<Particle> particles_;
};

}  // namespace idealgas