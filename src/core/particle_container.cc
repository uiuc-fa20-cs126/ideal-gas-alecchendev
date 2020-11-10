#include <core/particle_container.h>

#include <iostream>

using ci::Rand;
using std::map;
using std::pair;

namespace idealgas {

ParticleContainer::ParticleContainer(float width, float height, int num_particles,
                  vector<Particle> particle_types) {
  width_ = width;
  height_ = height;
  for (int idx = 0; idx < num_particles; idx++) {
    Particle new_particle = particle_types[idx % particle_types.size()];
    new_particle.position = vec2(Rand::randFloat(new_particle.radius, width_ - new_particle.radius),
                                 Rand::randFloat(new_particle.radius, height_ - new_particle.radius));
    new_particle.velocity = Rand::randFloat(0, new_particle.radius / 2) * Rand::randVec2();
    AddParticle(new_particle);
  }
}

void ParticleContainer::AddParticle(const Particle &particle) {
  particles_.push_back(particle);
}

void ParticleContainer::Update(const float& time_step, const vec2& mouse_location) {
  for (Particle& particle : particles_) {
    for (Particle& other_particle : particles_) {
      CheckCollisionParticle(particle, other_particle);
    }
    CheckCollisionWall(particle);
  }
  for (Particle& particle : particles_) {
    particle.position += particle.velocity * time_step;

    // mouse effect
    float effect_radius = 75.0f;
    float dist_from_mouse = length(particle.position - mouse_location);
    particle.velocity += static_cast<float>(dist_from_mouse <= effect_radius) * 1.0f / max(dist_from_mouse, 1.0f) * (particle.position - mouse_location);
  }
}

map<string, vector<Particle>> ParticleContainer::GetParticlesByType() const {
  map<string, vector<Particle>> particles_by_mass;
  for (const Particle& particle : particles_) {
    if (particles_by_mass.find(particle.type) == particles_by_mass.end() ) {
      particles_by_mass.insert(pair<string, vector<Particle>>(particle.type, vector<Particle>{}));
    }
    particles_by_mass[particle.type].push_back(particle);
  }
  return particles_by_mass;
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