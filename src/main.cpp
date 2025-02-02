#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "player.h"

void CreatePlayer() {
  std::string name;
  std::cout << "Please enter your name: ";
  std::getline(std::cin, name);
  Player player_(name);
}

void GameOver(){
  player.SetScore(game.GetScore());

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Player: " << player.GetName() << "\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Game Duration: " << player.GetGameDuration() << " seconds\n";
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  CreatePlayer();

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);

  GameOver();
  return 0;
}