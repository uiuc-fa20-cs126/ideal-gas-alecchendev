#include <core/particle_container.h>

#include <iostream>

using ci::Rand;

namespace idealgas {

ParticleContainer::ParticleContainer(float width, float height, float time_step, int num_particles,
                  vector<Particle> particle_templates) {
  width_ = width;
  height_ = height;
  time_step_ = time_step;
  for (int idx = 0; idx < num_particles; idx++) {
    particles_.push_back(Particle(3, 0, ci::Color(1, 0, 0),
                                  vec2(Rand::randFloat(1, width_ - 1), Rand::randFloat(1, height_ - 1)),
                                  Rand::randFloat(1, 3) * Rand::randVec2()));
  }
}

void ParticleContainer::Update() {
  for (Particle& particle : particles_) {
    for (Particle& other_particle : particles_) {
      CheckCollisionParticle(particle, other_particle);
    }
    CheckCollisionWall(particle);
  }
  for (Particle& particle : particles_) {
    particle.position += particle.velocity * time_step_;
  }
}

void ParticleContainer::CheckCollisionParticle(Particle& particle, Particle& other_particle) {

}

void ParticleContainer::CheckCollisionWall(Particle& particle) {
  if (particle.position.x - particle.radius < 0 && particle.velocity.x < 0) {
    particle.velocity.x *= -1;
  }
  if (particle.position.x + particle.radius > width_ && particle.velocity.x > 0) {
    particle.velocity.x *= -1;
  }
  if (particle.position.y - particle.radius < 0 && particle.velocity.y < 0) {
    particle.velocity.y *= -1;
  }
  if (particle.position.y + particle.radius > height_ && particle.velocity.y > 0) {
    particle.velocity.y *= -1;
  }
}

const vector<Particle> &ParticleContainer::getParticles() const {
  return particles_;
}

float ParticleContainer::getWidth() const {
  return width_;
}

float ParticleContainer::getHeight() const {
  return height_;
}

}  // namespace idealgas