#pragma once
#include <mutex>
#include <thread>
#include <atomic>
#include <utility> // for std::pair

class Obstacle {
    public:
    // constructor
    Obstacle(int x, int y, int grid_width, int grid_height);
    // getter
    std::pair<int, int> GetPosition() const;

    void StartMove();
    void StopMove();

    private:
        // Position of the obstacle
        int x_;
        int y_;
        // Grid boundaries of the obstacle
        int grid_width_;
        int grid_height_;
        // Thread control
        std::mutex position_mutex_;
        std::thread movement_thread_;
        std::atomic<bool> is_running_{false};

        void movement_loop();

};