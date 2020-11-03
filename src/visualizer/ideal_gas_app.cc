#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  particle_container_ = ParticleContainer(720, 480, 50, vector<Particle>());
  container_visualizer_ = ContainerVisualizer(vec2(100, 50));
}

void IdealGasApp::update() {
  particle_container_.Update(time_step_);
};

void IdealGasApp::draw() {
  ci::Color8u background_color(242, 239, 233);  // light yellow
  ci::gl::clear(background_color);
  container_visualizer_.Draw(particle_container_);
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT: {
      time_step_ += 0.25f;
      break;
    }
    case ci::app::KeyEvent::KEY_LEFT: {
      time_step_ -= (time_step_ >= 0.25f) * 0.25f;
      break;
    }
    case ci::app::KeyEvent::KEY_SPACE: {
      time_step_ = (time_step_ == 0);
      break;
    }
  }
}

}  // namespace visualizer

}  // namespace naivebayes
