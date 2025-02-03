#pragma once
#include <string>
#include <chrono>

class Player {
public:
    // constructor
    Player(std::string name)
        : name_(std::move(name)), 
          score_(0), 
          start_time_(std::chrono::system_clock::now()), 
            end_time_(start_time_)
          {}
    // setters and getters
    void SetScore(int score) { 
        score_ = score; 
        end_time_ = std::chrono::system_clock::now(); 
    }

    const std::string& GetName() const { return name_; }
    int GetScore() const { return score_; }
    std::chrono::system_clock::time_point GetStartTime() const { return start_time_; } 
    std::chrono::system_clock::time_point GetEndTime() const { return end_time_; }

    double GetGameDuration() const {
        return std::chrono::duration<double>(end_time_ - start_time_).count();
    }

private:
    std::string name_;
    int score_;
    const std::chrono::system_clock::time_point start_time_;
    std::chrono::system_clock::time_point end_time_;
};
