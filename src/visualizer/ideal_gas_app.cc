#include <visualizer/ideal_gas_app.h>
#include <visualizer/plot.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  particle_container_ = ParticleContainer(800, 700, 300, kParticleTypes);
}

void IdealGasApp::update() {
  particle_container_.Update(time_step_);
};

void IdealGasApp::draw() {
  ci::gl::clear(background_color_);
  vector<vector<vec2>> particle_positions = particle_container_.GetParticlePositions();
  Plot container_plot(vec2(50, 50), 800.0f, 700.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  container_plot.Draw();
  container_plot.DrawScatter(particle_positions[0], 7.0f, ci::Color8u(52, 146, 235));
  container_plot.DrawScatter(particle_positions[1], 8.0f, ci::Color8u(235, 150, 52));
  container_plot.DrawScatter(particle_positions[2], 6.0f, ci::Color8u(130, 92, 48));

  vector<vector<float>> particle_speeds = particle_container_.GetParticleSpeeds();
  Plot plot1(vec2(50, 50) + vec2(800, 0) + vec2(50, 0), 250.0f, 200.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  plot1.DrawHistogram(particle_speeds[0], 15, ci::Color8u(52, 146, 235));
  Plot plot2(vec2(50, 50) + vec2(800, 0) + vec2(50, 0) + vec2(0, 250), 250.0f, 200.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  plot2.DrawHistogram(particle_speeds[1], 15, ci::Color8u(235, 150, 52));
  Plot plot3(vec2(50, 50) + vec2(800, 0) + vec2(50, 0) + 2.0f * vec2(0, 250), 250.0f, 200.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  plot3.DrawHistogram(particle_speeds[2], 15, ci::Color8u(130, 92, 48));
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT: {
      time_step_ += (time_step_ < kMaxTimeStep) * kTimeStepIncrement;
      break;
    }
    case ci::app::KeyEvent::KEY_LEFT: {
      time_step_ -= (time_step_ >= kTimeStepIncrement) * kTimeStepIncrement;
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
