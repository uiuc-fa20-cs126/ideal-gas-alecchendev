#include <visualizer/container_visualizer.h>

namespace idealgas {

namespace visualizer {

ContainerVisualizer::ContainerVisualizer(vec2 top_left_corner, Color container_background, Color container_stroke) {
  top_left_corner_ = top_left_corner;
  container_background_ = container_background;
  container_stroke_ = container_stroke;
}

void ContainerVisualizer::Draw(const ParticleContainer& particle_container) {

  // draw container
  vec2 bottom_right_corner = top_left_corner_ + vec2(particle_container.getWidth(), particle_container.getHeight());
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);

  ci::gl::color(container_background_);
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(container_stroke_);
  ci::gl::drawStrokedRect(pixel_bounding_box);

  // draw particles
  for (Particle particle : particle_container.getParticles()) {
    ci::gl::color(particle.color);
    ci::gl::drawSolidCircle(top_left_corner_ + particle.position, particle.radius);
  }


};


}  // namespace visualizer

}  // namespace naivebayes
