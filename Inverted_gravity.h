#ifndef INVERTED_GRAVITY_H
#define INVERTED_GRAVITY_H

#include <vector>
#include "raylib.h"

// ------------------------------------------------------------
// Compile‑time constants (available in all translation units)
// ------------------------------------------------------------
constexpr int width = 1800;
constexpr int height = 1000;
constexpr int sprite_size = 100;
constexpr int player_sprite_size = 3 * sprite_size / 4;   // 75
constexpr int scale_x = width / sprite_size;   // 18
constexpr int scale_y = height / sprite_size;  // 10

// ------------------------------------------------------------
// Tile types
// ------------------------------------------------------------
constexpr int EMPTY   = 0;
constexpr int PLATFORM = 1;
constexpr int PLAYER   = 2;
constexpr int STAR     = 3;

// ------------------------------------------------------------
// Game structures
// ------------------------------------------------------------
struct Level {
    int grid[scale_y][scale_x];
    int total_stars;
};

struct GameState {
    float player_x;
    float player_y;
    float gravity;
};

// ------------------------------------------------------------
// Global variables (defined in Inverted_Gravity.cpp)
// ------------------------------------------------------------
extern int level;
extern int stars;
extern float player_x;
extern float player_y;
extern float gravity;
extern bool game_won;
extern GameState state;

// Level‑specific flags
extern bool star_1_level_2_collected;
extern bool star_2_level_2_collected;
extern bool star_3_level_2_collected;
extern bool star_1_level_3_collected;
extern bool star_2_level_3_collected;
extern bool star_3_level_3_collected;
extern bool star_4_level_3_collected;
extern bool star_1_level_5_collected;

// Angles for moving stars
extern float s1l2, s2l2, s3l2;
extern float s1l3, s2l3, s3l3, s4l3;
extern float s1l5;

// Level vectors
extern std::vector<Level> original_levels;
extern std::vector<Level> levels;

// ------------------------------------------------------------
// Function declarations
// ------------------------------------------------------------
void Make_Levels();
void load_level(const Level& level);
int run_game();   // the main game loop, returns to caller when finished

#endif // INVERTED_GRAVITY_H
