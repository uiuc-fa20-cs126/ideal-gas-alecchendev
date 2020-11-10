#include <catch2/catch.hpp>
#include <core/particle_container.h>
#include <core/particle.h>

using idealgas::ParticleContainer;
using idealgas::Particle;

TEST_CASE("Constructor") {
  SECTION("Check all values are present") {
    ParticleContainer particle_container = ParticleContainer(50, 60, 30, vector<Particle>({
      Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3))
    }));
    SECTION("Width") {
      REQUIRE(particle_container.getWidth() == 50);
    }
    SECTION("Height") {
      REQUIRE(particle_container.getHeight() == 60);
    }
  }
  SECTION("Check particles created") {
    SECTION("Created enough particles") {
      ParticleContainer particle_container = ParticleContainer(50, 60, 30, vector<Particle>({
        Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3))
      }));
      REQUIRE(particle_container.getParticles().size() == 30);
    }
    SECTION("Single particle type") {
      ParticleContainer particle_container = ParticleContainer(50, 60, 30, vector<Particle>({
        Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3))
      }));
      REQUIRE(particle_container.getParticles().size() == 30);
      REQUIRE(particle_container.getParticles()[0].radius == 1);
      REQUIRE(particle_container.getParticles()[0].mass == 2);
      REQUIRE(particle_container.getParticles()[0].color == ci::Color(1, 0, 0));
    }
    SECTION("Multiple particle types") {
      ParticleContainer particle_container = ParticleContainer(50, 60, 30, vector<Particle>({
        Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3)),
        Particle("test", 2, 1, ci::Color(0, 1, 0), vec2(10, 5), vec2(3, 2))
      }));
      REQUIRE(particle_container.getParticles().size() == 30);
      REQUIRE(particle_container.getParticles()[0].radius == 1);
      REQUIRE(particle_container.getParticles()[0].mass == 2);
      REQUIRE(particle_container.getParticles()[0].color == ci::Color(1, 0, 0));

      REQUIRE(particle_container.getParticles()[1].radius == 2);
      REQUIRE(particle_container.getParticles()[1].mass == 1);
      REQUIRE(particle_container.getParticles()[1].color == ci::Color(0, 1, 0));
    }
  }
}

TEST_CASE("Check updating particle positions") {
  ParticleContainer particle_container = ParticleContainer(50, 60, 30, vector<Particle>({
    Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3))
  }));
  SECTION("Different timesteps") {
    SECTION("Timestep = 0") {
      vec2 prev_pos = particle_container.getParticles()[0].position;
      particle_container.Update(0.0);
      REQUIRE(particle_container.getParticles()[0].position == prev_pos);
    }
    SECTION("Timestep > 0") {
      vec2 prev_pos = particle_container.getParticles()[0].position;
      particle_container.Update(1.0);
      REQUIRE(particle_container.getParticles()[0].position != prev_pos);
    }
  }
  SECTION("Updating position with a velocity with nonzero length") {
    vec2 prev_pos = particle_container.getParticles()[0].position;
    vec2 prev_vel = particle_container.getParticles()[0].velocity;
    particle_container.Update(1.0);
    REQUIRE(particle_container.getParticles()[0].position == prev_pos + prev_vel);
  }
}

TEST_CASE("Check wall collisions") {
  ParticleContainer particle_container = ParticleContainer(50, 60, 0, vector<Particle>({
    Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3))
  }));
  SECTION("Left bound") {
    particle_container.AddParticle(Particle("test", 1, 1, ci::Color(1, 0, 0), vec2(1, 20), vec2(-5, 0)));
    particle_container.Update(1);
    REQUIRE(particle_container.getParticles()[0].velocity.x == 5);
  }
  SECTION("Right bound") {
    particle_container.AddParticle(Particle("test", 1, 1, ci::Color(1, 0, 0), vec2(49, 20), vec2(5, 0)));
    particle_container.Update(1);
    REQUIRE(particle_container.getParticles()[0].velocity.x == -5);
  }
  SECTION("Lower bound") {
    particle_container.AddParticle(Particle("test", 1, 1, ci::Color(1, 0, 0), vec2(20, 1), vec2(0, 5)));
    particle_container.Update(1);
    REQUIRE(particle_container.getParticles()[0].velocity.y == 5);
  }
  SECTION("Upper bound") {
    particle_container.AddParticle(Particle("test", 1, 1, ci::Color(1, 0, 0), vec2(20, 59), vec2(0, 5)));
    particle_container.Update(1);
    REQUIRE(particle_container.getParticles()[0].velocity.y == -5);
  }
}

TEST_CASE("Check particle collisions") {
  ParticleContainer particle_container = ParticleContainer(50, 60, 0, vector<Particle>({
    Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3))
  }));
  SECTION("Moving towards") {
    SECTION("Vertical and horizontal movement") {
      particle_container.AddParticle(Particle("test", 1, 1, ci::Color(1, 0, 0), vec2(19, 19), vec2(1, 1)));
      particle_container.AddParticle(Particle("test", 2, 2, ci::Color(1, 0, 0), vec2(22, 22), vec2(-1, -1)));
      particle_container.Update(1);
      REQUIRE(abs(particle_container.getParticles()[0].velocity.x - -1.66667f) < 0.01);
      REQUIRE(abs(particle_container.getParticles()[0].velocity.y - -1.66667f) < 0.01);
      REQUIRE(abs(particle_container.getParticles()[1].velocity.x - 0.33333f) < 0.01);
      REQUIRE(abs(particle_container.getParticles()[1].velocity.y - 0.33333f) < 0.01);
    }
  }
  SECTION("Within contact, but moving away") {
    particle_container.AddParticle(Particle("test", 1, 1, ci::Color(1, 0, 0), vec2(20, 20), vec2(-1, -1)));
    particle_container.AddParticle(Particle("test", 2, 2, ci::Color(1, 0, 0), vec2(22, 22), vec2(1, 1)));
    particle_container.Update(1);
    REQUIRE(particle_container.getParticles()[0].velocity.x == -1.0f);
    REQUIRE(particle_container.getParticles()[0].velocity.y == -1.0f);
    REQUIRE(particle_container.getParticles()[1].velocity.x == 1.0f);
    REQUIRE(particle_container.getParticles()[1].velocity.y == 1.0f);
  }
}

TEST_CASE("Check that it gets correct particles by type") {
  ParticleContainer particle_container = ParticleContainer(50, 60, 1, vector<Particle>({
    Particle("test", 1, 2, ci::Color(1, 0, 0), vec2(1, 2), vec2(2, 3))
  }));
  SECTION("From particle type initialization") {
    REQUIRE(particle_container.GetParticlesByType().size() == 1);
    REQUIRE(particle_container.GetParticlesByType()["test"][0].mass == 2);
  }
  SECTION("From adding a particle") {
    particle_container.AddParticle(Particle("test2", 2, 3, ci::Color(1, 0, 0), vec2(22, 22), vec2(1, 1)));
    particle_container.AddParticle(Particle("test2", 2, 3, ci::Color(1, 0, 0), vec2(22, 22), vec2(1, 1)));
    REQUIRE(particle_container.GetParticlesByType()["test"].size() == 1);
    REQUIRE(particle_container.GetParticlesByType()["test"][0].mass == 2);
    REQUIRE(particle_container.GetParticlesByType()["test2"].size() == 2);
    REQUIRE(particle_container.GetParticlesByType()["test2"][0].mass == 3);
  }
}