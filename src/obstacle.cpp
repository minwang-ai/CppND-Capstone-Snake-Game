#include "obstacle.h"
#include <algorithm>  // for std::clamp 

Obstacle::Obstacle(int x, int y, int grid_width, int grid_height, int speed)
    : x_(std::clamp(x, 0, grid_width - 1)),
      y_(std::clamp(y, 0 , grid_height - 1)), 
      grid_width_(grid_width), 
      grid_height_(grid_height), 
      speed_(speed) {}

Obstacle::~Obstacle() {
    StopMove();
    movement_thread_.join();    
}

std::pair<int, int> Obstacle::GetPosition() const {
    std::lock_guard<std::mutex> lock(position_mutex_);
    return std::make_pair(x_, y_);
}


void Obstacle::UpdatePosition(int x, int y) {
    std::lock_guard<std::mutex> lock(position_mutex_);
    x_ = std::clamp(x, 0, grid_width_ - 1);     // Clamps position to make sure it is within the game grid
    y_ = std::clamp(y, 0, grid_height_ - 1);
}


void Obstacle::MovementLoop() {
    bool moving_right = true;
    auto last_update = std::chrono::steady_clock::now();
    const auto frame_duration = std::chrono::milliseconds(100/speed_);

    while (is_running_) {
        auto current_time = std::chrono::steady_clock::now();
        if (current_time - last_update >= frame_duration) {
            {
                std::lock_guard<std::mutex> lock(position_mutex_);
                // Update position
                if (moving_right) {
                    x_ = (x_ + 1) % grid_width_;
                    if (x_ == grid_width_ - 1) moving_right = false;
                } else {
                    x_ = (x_ - 1 + grid_width_) % grid_width_;
                    if (x_ == 0) moving_right = true;
                }
            }
            last_update = current_time;
        }
        std::this_thread::yield();  // Let other threads run if needed
    }
}

void Obstacle::StartMove() {
    if (!is_running_) {
        is_running_ = true;
        movement_thread_ = std::thread(&Obstacle::MovementLoop, this);
    }
}

void Obstacle::StopMove() {
    if (is_running_) {
        is_running_ = false;
    }
}