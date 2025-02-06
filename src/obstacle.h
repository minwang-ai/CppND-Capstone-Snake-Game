#pragma once
#include <mutex>
#include <thread>
#include <atomic>
#include <utility> // for std::pair

class Obstacle {
    public:
    // constructor
    Obstacle(int x, int y, int grid_width, int grid_height, int speed);
    // destructor
    ~Obstacle();
    // getter
    std::pair<int, int> GetPosition() const;
    // setter   
    void SetSpeed(int speed_);

    void StartMove();
    void StopMove();

    private:
        int x_;     // Position of the obstacle
        int y_;
        int grid_width_;    // Grid boundaries of the obstacle
        int grid_height_;

        int speed_;

        // Thread control
        mutable std::mutex position_mutex_;     // Mutable for mutex - allows locking in const methods
        std::thread movement_thread_;
        std::atomic<bool> is_running_{false};

        void MovementLoop();
        void UpdatePosition(int x, int y);

};