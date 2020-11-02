#include <core/particle_container.h>

#include <iostream>

namespace idealgas {

ParticleContainer::ParticleContainer(double width, double height, double time_step, int num_particles,
                  vector<Particle> particle_templates) {
  width_ = width;
  height_ = height;
  time_step_ = time_step;
}

void ParticleContainer::Update() {

}

void ParticleContainer::CheckCollision(Particle& particle, Particle& other_particle) {

}

const vector<Particle> &ParticleContainer::getParticles() const {
  return particles;
}

double ParticleContainer::getWidth() const {
  return width_;
}

double ParticleContainer::getHeight() const {
  return height_;
}

}  // namespace idealgas