#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  particle_container_ = ParticleContainer(720, 480, 1, 50, vector<Particle>());
  container_visualizer_ = ContainerVisualizer(vec2(100, 50));
}

void IdealGasApp::update() {
  particle_container_.Update();
};

void IdealGasApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);
  container_visualizer_.Draw(particle_container_);
}

}  // namespace visualizer

}  // namespace naivebayes
