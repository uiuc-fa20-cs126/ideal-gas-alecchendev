#pragma once
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include <map>
#include <string>
#include <vector>
#include "particle.h"
#include <math.h>
#include <algorithm>

using glm::vec2;
using std::vector;
using ci::Color;
using std::max;

namespace idealgas {

/**
 * Holds particles and handles all movement and collisions
 */
class ParticleContainer {
 public:
  ParticleContainer(){}

  /**
   * Initialize equal number of particles for each template provided
   * Distributes pixel positions in a grid, gives them random directions given magnitude of template velocity
   * @param width float representing horizontal size of container
   * @param height float representing vertical size of container
   * @param num_particles Total number of particles to initialize
   * @param particle_templates Vector of particles that gives templates for particles ot be created
   */
  ParticleContainer(float width, float height, int num_particles,
                    vector<Particle> particle_types);

  /**
   * Checks for particle collisions, updates velocities, and updates positions
   * @param time_step float to indicate the rate of passing time to increase magnitude of movement
   */
  void Update(const float& time_step, const vec2& mouse_location);

  /**
   * Adds particle to containers particle list
   * @param particle Particle to be added
   */
  void AddParticle(const Particle& particle);

  /**
   * Gets a list of speeds for each group of particles of the same mass
   * @return Vector of vectors of floats each containing speeds for particles of each mass
   */
  vector<vector<float>> GetParticleSpeeds() const;

  /**
   * Gets a list of positions for each group of particles of the same mass
   * @return Vector of vectors of vec2 each containing positions for particles of each mass
   */
  vector<vector<vec2>> GetParticlePositions() const;

  const vector<Particle>& getParticles() const;
  const float& getWidth() const;
  const float& getHeight() const;

private:
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

  float width_;
  float height_;
  vector<Particle> particles_;
};

}  // namespace idealgas