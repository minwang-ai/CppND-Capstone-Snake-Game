#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      obstacle(grid_width/2, grid_height/2, grid_width, grid_height, 1),  // Center of grid, speed 1
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  obstacle.StartMove();  // Start obstacle movement before loop starts

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, obstacle);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Get current obstacle position
    auto [obs_x, obs_y] = obstacle.GetPosition();
    
    // Check that the location is not occupied by snake or obstacle before placing
    // food.
    if (!snake.SnakeCell(x, y)&& !(x == obs_x && y == obs_y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) {
    obstacle.StopMove();  // Stop obstacle when snake dies
    return;
  }

  snake.Update();

  int head_x = static_cast<int>(snake.GetHeadX());
  int head_y = static_cast<int>(snake.GetHeadY());

  // Obstacle detection
  auto [obs_x, obs_y] = obstacle.GetPosition();

  // Check if head collides with obstacle
  if (head_x == obs_x && head_y == obs_y) {
    snake.alive = false;
    obstacle.StopMove();  // Stop obstacle on collision
    return;
  }

  // Check if body collides with obstacle
  for (auto const &item : snake.body) {
    if (item.x == obs_x && item.y == obs_y) {
      snake.alive = false;
      obstacle.StopMove();  // Stop obstacle on collision
      return;
    }
  }

  // Check if there's food over here
  if (food.x == head_x && food.y == head_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }