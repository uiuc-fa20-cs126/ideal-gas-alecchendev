#include <core/particle_container.h>

#include <iostream>

using ci::Rand;

namespace idealgas {

ParticleContainer::ParticleContainer(float width, float height, int num_particles,
                  vector<Particle> particle_types) {
  width_ = width;
  height_ = height;
  for (int idx = 0; idx < num_particles; idx++) {
    Particle new_particle = particle_types[idx % particle_types.size()];
    new_particle.position = vec2(Rand::randFloat(new_particle.radius, width_ - new_particle.radius),
                                 Rand::randFloat(new_particle.radius, height_ - new_particle.radius));
    new_particle.velocity = Rand::randFloat(0, new_particle.radius) * Rand::randVec2();
    particles_.push_back(new_particle);
  }
}

void ParticleContainer::Update(const float& time_step) {
  for (Particle& particle : particles_) {
    particle.position += particle.velocity * time_step;
  }
  for (Particle& particle : particles_) {
    for (Particle& other_particle : particles_) {
      CheckCollisionParticle(particle, other_particle);
    }
    CheckCollisionWall(particle);
  }
}

void ParticleContainer::CheckCollisionParticle(Particle& particle, Particle& other_particle) {
  bool touching = distance(particle.position, other_particle.position) < (particle.radius + other_particle.radius);
  bool getting_closer = dot((particle.position - other_particle.position),
                            (particle.velocity - other_particle.velocity)) < 0;
  if (touching && getting_closer) {
    vec2 x1 = particle.position;
    vec2 x2 = other_particle.position;
    vec2 v1 = particle.velocity;
    vec2 v2 = other_particle.velocity;
    float m1 = particle.mass;
    float m2 = other_particle.mass;
    particle.velocity = v1 - (2 * m2 / (m1 + m2) * (dot((v1 - v2), (x1 - x2)) / (length(x1 - x2)
            * length(x1 - x2)))) * (x1 - x2);
    other_particle.velocity = v2 - (2 * m1 / (m1 + m2) * (dot((v2 - v1), (x2 - x1)) / (length(x2 - x1)
            * length(x2 - x1)))) * (x2 - x1);
  }
}

void ParticleContainer::CheckCollisionWall(Particle& particle) {
  bool moving_left = particle.velocity.x < 0;
  bool moving_right = particle.velocity.x > 0;
  bool moving_up = particle.velocity.y < 0;
  bool moving_down = particle.velocity.y > 0;

  bool outside_left_bound = particle.position.x - particle.radius < 0;
  bool outside_right_bound = particle.position.x + particle.radius > width_;
  bool outside_upper_bound = particle.position.y - particle.radius < 0;
  bool outside_lower_bound = particle.position.y + particle.radius > height_;

  if (outside_left_bound && moving_left) {
    particle.velocity.x *= -1;
  }
  if (outside_right_bound && moving_right) {
    particle.velocity.x *= -1;
  }
  if (outside_upper_bound && moving_up) {
    particle.velocity.y *= -1;
  }
  if (outside_lower_bound && moving_down) {
    particle.velocity.y *= -1;
  }
}

const vector<Particle>& ParticleContainer::getParticles() const {
  return particles_;
}

const float& ParticleContainer::getWidth() const {
  return width_;
}

const float& ParticleContainer::getHeight() const {
  return height_;
}

}  // namespace idealgas