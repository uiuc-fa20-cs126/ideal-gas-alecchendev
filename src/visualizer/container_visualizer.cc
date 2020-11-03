#include <visualizer/container_visualizer.h>

namespace idealgas {

namespace visualizer {

ContainerVisualizer::ContainerVisualizer(vec2 top_left_corner) {
  top_left_corner_ = top_left_corner;
}

void ContainerVisualizer::Draw(const ParticleContainer& particle_container) {

  // draw container
  vec2 bottom_right_corner = top_left_corner_ + vec2(particle_container.getWidth(), particle_container.getHeight());
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);

  ci::gl::color(ci::Color8u(255, 252, 245));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(0, 0, 0);
  ci::gl::drawStrokedRect(pixel_bounding_box);

  // draw particles
  for (Particle particle : particle_container.getParticles()) {
    ci::gl::color(particle.color);
    ci::gl::drawSolidCircle(top_left_corner_ + particle.position, particle.radius);
  }


};


}  // namespace visualizer

}  // namespace naivebayes
