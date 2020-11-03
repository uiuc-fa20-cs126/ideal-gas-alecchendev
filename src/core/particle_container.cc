#include <core/particle_container.h>

#include <iostream>

namespace idealgas {

ParticleContainer::ParticleContainer(double width, double height, double time_step, int num_particles,
                  vector<Particle> particle_templates) {
  width_ = width;
  height_ = height;
  time_step_ = time_step;
  particles_.push_back(Particle(3, 0, ci::Color(1, 0, 0), vec2(5, 10), vec2(0.8, 0.5)));
}

void ParticleContainer::Update() {
  for (Particle particle : particles_) {
    for (Particle other_particle : particles_) {
      CheckCollisionParticle(particle, other_particle);
    }
    CheckCollisionWall(particle);
  }
  for (Particle particle : particles_) {
    particle.position += vec2(1, 1);
  }
}

void ParticleContainer::CheckCollisionParticle(Particle& particle, Particle& other_particle) {

}

void ParticleContainer::CheckCollisionWall(Particle& particle) {

}

const vector<Particle> &ParticleContainer::getParticles() const {
  return particles_;
}

double ParticleContainer::getWidth() const {
  return width_;
}

double ParticleContainer::getHeight() const {
  return height_;
}

}  // namespace idealgas