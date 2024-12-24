#include <iostream>
#include <windows.h>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
#define world_width 20
#define world_height 10
char world[world_height][world_width];
char world_buffer[world_height][world_width];
static HWND current_console = GetConsoleWindow();

#define Alive 1
#define Dead 0
#define IsAlive(cr) ((cr)==Alive)
#define IsDead(cr) ((cr)==Dead)

void start() {
  for (int i = 0; i < world_width; ++i)
    for (int j = 0; j < world_height; ++j) {
      world[i][j] = Dead;
      world_buffer[i][j] = Dead;
    }
  /*****************/
  // world[1][3] = Alive;
  /*****************/
  world[2][2] = Alive;
  world[3][2] = Alive;
  world[3][3] = Alive;
  /*****************/
  // world[3][4] = Alive;
  /*****************/
}

template<size_t _W, size_t _H>
unsigned char CountOfAliveNeighbords(int cx, int cy, char (&_world)[_W][_H]) {
  unsigned char neightbors = 0;
  if (IsAlive(_world[cx - 1][cy - 1])) neightbors++;
  if (IsAlive(_world[cx + 1][cy - 1])) neightbors++;
  if (IsAlive(_world[cx + 1][cy + 1])) neightbors++;
  if (IsAlive(_world[cx - 1][cy + 1])) neightbors++;
  if (IsAlive(_world[cx    ][cy + 1])) neightbors++;
  if (IsAlive(_world[cx    ][cy - 1])) neightbors++;
  if (IsAlive(_world[cx + 1][cy    ])) neightbors++;
  if (IsAlive(_world[cx - 1][cy    ])) neightbors++;
  return neightbors;
}

void update() {
  memcpy(world_buffer, world, world_width*world_height*sizeof(char));
  for (int i = 1; i < world_width - 1; ++i) {
    for (int j = 1; j < world_height - 1; ++j) {
      unsigned char neightbors = CountOfAliveNeighbords(i, j, world);
      if (IsDead(world[i][j]) && neightbors == 3) {
        world_buffer[i][j] = Alive;
      }
      else if (IsAlive(world[i][j]) && (neightbors < 2 || neightbors > 3)) {
        world_buffer[i][j] = Dead;
      }
    }
  }
  memcpy(world, world_buffer, world_width*world_height*sizeof(char));
}

void render()
{
  system("CLS");
  for (int j = 0; j < world_height; ++j) {
    for (int i = 0; i < world_width; ++i) {
      printf("%c", IsAlive(world[i][j])?'#': '.');
    }
    printf("\n");
  }
  printf("\n");
}

int main()
{
  start();
  auto last = std::chrono::system_clock::now();
  while (true) {
    auto cur = std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(cur - last).count() >= 1000) 
    {
      render();
      update();
      last = cur;
    }
  }
  return 0;
}