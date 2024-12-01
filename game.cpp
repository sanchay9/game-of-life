#include "screen.h"
#include <SDL2/SDL_timer.h>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 640;
const int M = 480;

G screen;
vector<vector<int>> game;

vector<pair<int, int>> dirs{{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                            {1, 0},  {1, -1}, {0, -1}, {-1, -1}};

bool isValidCell(int x, int y) { return x >= 0 && y >= 0 && x < N && y < M; }

int getCellNextState(const int i, const int j) {
  int alive_neighbors = 0;

  for (auto [di, dj] : dirs) {
    int ni = i + di;
    int nj = j + dj;

    if (isValidCell(ni, nj) && (game[ni][nj] == 1 || game[ni][nj] == -1)) {
      ++alive_neighbors;
    }
  }

  if (game[i][j] == 1 && (alive_neighbors < 2 || alive_neighbors > 3)) {
    return -1;
  }
  if (game[i][j] == 0 && alive_neighbors == 3) {
    return 2;
  }
  return game[i][j];
}

void transformGameToNextState() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      game[i][j] = getCellNextState(i, j);
    }
  }

  for (auto &x : game) {
    for (auto &y : x) {
      if (y == -1) {
        y = 0;
      } else if (y == 2) {
        y = 1;
      }
    }
  }
}

void printGame() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (game[i][j] == 1) {
        screen.drawpixel(i, j);
      }
    }
  }
  screen.update();
  SDL_Delay(20);
  screen.input();
  screen.clearpixels();
}

int main() {
  game.resize(N, vector<int>(M));

  for (auto &x : game) {
    generate(x.begin(), x.end(), []() { return rng() % 10 == 0 ? 1 : 0; });
  }

  while (true) {
    transformGameToNextState();
    printGame();
  }
}
