#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "raylib.h"
#include "Inverted_gravity.h"

using namespace std;

// ------------------------------------------------------------
// Global variable definitions (one copy per program)
// ------------------------------------------------------------
int level = 1;
int stars = 0;
float player_x = player_sprite_size;
float player_y = player_sprite_size;
float gravity = 3.0f;
bool game_won = false;
GameState state = {player_sprite_size, player_sprite_size, 3.0f};

// Level‑specific flags
bool star_1_level_2_collected = false;
bool star_2_level_2_collected = false;
bool star_3_level_2_collected = false;
bool star_1_level_3_collected = false;
bool star_2_level_3_collected = false;
bool star_3_level_3_collected = false;
bool star_4_level_3_collected = false;
bool star_1_level_5_collected = false;

// Angles for moving stars
float s1l2 = 0.0f, s2l2 = 0.0f, s3l2 = 0.0f;
float s1l3 = 0.0f, s2l3 = 0.0f, s3l3 = 0.0f, s4l3 = 0.0f;
float s1l5 = 0.0f;

// Level vectors
vector<Level> original_levels;
vector<Level> levels;

// Moving stars data (only needed in this file)
float star_1_x_level_2, star_1_y_level_2;
float star_2_x_level_2, star_2_y_level_2;
float star_3_x_level_2, star_3_y_level_2;

float star_1_x_level_3, star_1_y_level_3;
float star_2_x_level_3, star_2_y_level_3;
float star_3_x_level_3, star_3_y_level_3;
float star_4_x_level_3, star_4_y_level_3;
bool star_1_level_3_left = false, star_1_level_3_right = false;
bool star_2_level_3_left = false, star_2_level_3_right = false;
bool star_3_level_3_up = false, star_3_level_3_down = false;
bool star_4_level_3_up = false, star_4_level_3_down = false;

float star_1_x_level_5, star_1_y_level_5;

const float star_radius = 100.0f;
double lastlevel9update = 0.0;
int sign[] = {-1, +1};

Texture2D platform_texture;
Texture2D player_textures[4];
Texture2D collectable_texture;
Texture2D background_texture;
Texture2D current_player_texture;

// Forward declarations
int count_stars_in_levels(const int grid[scale_y][scale_x]);

int count_stars_in_levels(const int grid[scale_y][scale_x]){
    int total = 0;
    for(int i = 0; i < scale_y; i++){
      for(int j = 0; j < scale_x; j++){
	if(grid[i][j] == STAR){
                total++;
	}
      }
    }
    return total;
}

void Make_Levels(){
    // Level 1
    Level level_1;
    int temp1[scale_y][scale_x] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {2,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    memcpy(level_1.grid, temp1, sizeof(temp1));
    level_1.total_stars = count_stars_in_levels(level_1.grid);
    original_levels.push_back(level_1);

    // Level 2
    Level level_2;
    int temp2[scale_y][scale_x] = {
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}
    };
    memcpy(level_2.grid, temp2, sizeof(temp2));
    level_2.total_stars = count_stars_in_levels(level_2.grid) + 3;
    original_levels.push_back(level_2);

    // Level 3
    Level level_3;
    int temp3[scale_y][scale_x] = {
        {0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0}
    };
    memcpy(level_3.grid, temp3, sizeof(temp3));
    level_3.total_stars = count_stars_in_levels(level_3.grid) + 4;
    original_levels.push_back(level_3);

    // Level 4
    Level level_4;
    int temp4[scale_y][scale_x] = {
        {0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3},
        {3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1},
        {0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3},
        {3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1},
        {0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3},
        {3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1},
        {0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3},
        {3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1},
        {0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3},
        {3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1}
    };
    memcpy(level_4.grid, temp4, sizeof(temp4));
    level_4.total_stars = count_stars_in_levels(level_4.grid);
    original_levels.push_back(level_4);

    // Level 5
    Level level_5;
    int temp5[scale_y][scale_x] = {0}; // all zeros
    memcpy(level_5.grid, temp5, sizeof(temp5));
    level_5.total_stars = count_stars_in_levels(level_5.grid) + 1;
    original_levels.push_back(level_5);

    // Level 6
    Level level_6;
    int temp6[scale_y][scale_x] = {
        {0,0,0,1,0,0,0,0,3,0,0,0,3,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,3,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,3,0,0,0,0,0,0,0,1},
        {0,3,0,0,0,0,3,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,3,0},
        {0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,3,0,0,0,1,0,0,0}
    };
    memcpy(level_6.grid, temp6, sizeof(temp6));
    level_6.total_stars = count_stars_in_levels(level_6.grid);
    original_levels.push_back(level_6);

    // Level 7
    Level level_7;
    int temp7[scale_y][scale_x] = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {3,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3},
        {3,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,3},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };
    memcpy(level_7.grid, temp7, sizeof(temp7));
    level_7.total_stars = count_stars_in_levels(level_7.grid);
    original_levels.push_back(level_7);

    // Level 8
    Level level_8;
    int temp8[scale_y][scale_x] = {
        {3,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,3},
        {0,3,0,0,0,1,0,0,3,3,0,0,0,1,0,0,3,0},
        {0,0,3,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0},
        {0,0,0,3,0,0,3,0,0,0,0,3,0,0,3,0,0,0},
        {0,0,1,0,3,3,0,0,1,1,0,0,3,3,0,0,1,0},
        {0,0,0,0,3,3,0,0,0,0,0,0,3,3,0,0,0,0},
        {0,0,0,3,0,0,3,0,0,0,0,3,0,0,3,0,0,0},
        {0,0,3,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0},
        {0,3,0,0,0,1,0,0,3,3,0,0,0,1,0,0,3,0},
        {3,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,3}
    };
    memcpy(level_8.grid, temp8, sizeof(temp8));
    level_8.total_stars = count_stars_in_levels(level_8.grid);
    original_levels.push_back(level_8);

    // Level 9
    Level level_9;
    int temp9[scale_y][scale_x] = {0};
    for (int j = 0; j < scale_x; j++) temp9[scale_y-1][j] = 1;
    temp9[scale_y-2][scale_x-1] = 3;
    memcpy(level_9.grid, temp9, sizeof(temp9));
    level_9.total_stars = count_stars_in_levels(level_9.grid);
    original_levels.push_back(level_9);

    // Level 10
    Level level_10;
    int temp10[scale_y][scale_x] = {0};
    for(int i = 0; i < scale_y; i++){
      for(int j = 0; j < scale_x; j++){
            temp10[i][j] = STAR;
      }
    }
    
    memcpy(level_10.grid, temp10, sizeof(temp10));
    level_10.total_stars = count_stars_in_levels(level_10.grid);
    original_levels.push_back(level_10);

    // Copy original levels to active levels
    levels = original_levels;
}

void load_level(const Level& level){
    for(int i = 0; i < scale_y; i++){
        for(int j = 0; j < scale_x; j++){
            switch (level.grid[i][j]){
                case PLATFORM:
                    DrawTexturePro(platform_texture,{0,0,(float)platform_texture.width,(float)platform_texture.height},{j * (float)sprite_size, i * (float)sprite_size, (float)1.5*sprite_size, (float)sprite_size},{0,0}, 0, WHITE);
                    break;
                case STAR:
                    DrawTexturePro(collectable_texture,{0,0,(float)collectable_texture.width,(float)collectable_texture.height},{j * (float)sprite_size, i * (float)sprite_size, (float)sprite_size, (float)sprite_size},{0,0}, 0, WHITE);
                    break;
                case PLAYER:
                    // Player position is set from state, not from level tile.
                    break;
            }
        }
    }
}

int run_game(){
    srand(static_cast<unsigned int>(time(nullptr)));

    InitWindow(width, height, "Inverted Gravity");
    InitAudioDevice();

    Sound collect_star = LoadSound("collect.mp3");
    Sound lose = LoadSound("death.mp3");
    Sound gravity_flip = LoadSound("flip.mp3");
    
    SetTargetFPS(60);

    // Load textures
    platform_texture = LoadTexture("Platform.png");
    player_textures[0] = LoadTexture("player_down_left.png");
    player_textures[1] = LoadTexture("player_up_left.png");
    player_textures[2] = LoadTexture("player_down_right.png");
    player_textures[3] = LoadTexture("player_up_right.png");
    collectable_texture = LoadTexture("star.png");
    background_texture = LoadTexture("Background.png");
    current_player_texture = player_textures[3];

    // Initialize game state
    state.player_x = player_sprite_size;
    state.player_y = player_sprite_size;
    state.gravity = 3.0f;
    game_won = false;

    int currentLevel = 1;
    int starsCollected = 0;

    while(!WindowShouldClose()){
        float dx = 0.0f;

        // Input
        if(IsKeyDown(KEY_RIGHT)){
	  dx = 5.0f;
	}
	
        if(IsKeyDown(KEY_LEFT)){
	  dx = -5.0f;
	}
	
        // Player orientation based on movement and gravity
        if(dx < 0 && state.gravity < 0){
            current_player_texture = player_textures[1];
	}
	
        else if(dx < 0 && state.gravity > 0){
            current_player_texture = player_textures[0];
	}
	
        else if(dx > 0 && state.gravity < 0){
            current_player_texture = player_textures[3];
	}
	
        else if(dx > 0 && state.gravity > 0){
            current_player_texture = player_textures[2];
	}
	
        // Gravity flip
        if(IsKeyPressed(KEY_SPACE)){
            state.gravity *= -1.0f;
	    PlaySound(gravity_flip);
	}
	
        // Wrap around screen edges
        if(state.player_x < 0){
            state.player_x = width - player_sprite_size;
	}
	
        else if(state.player_x > width - player_sprite_size){
            state.player_x = 0;
	}
	
        // Check death (fall off top or bottom)
        if(state.player_y < 0 || state.player_y > height - player_sprite_size){
	    PlaySound(lose);
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("You fell into the void!!! Try again!", width/4, height/2, 50, WHITE);
            EndDrawing();
            WaitTime(2);
            // Unload textures
            UnloadTexture(platform_texture);
            for(int i = 0; i < 4; i++){
	      UnloadTexture(player_textures[i]);
	    }
	    
            UnloadTexture(collectable_texture);
            UnloadTexture(background_texture);
            CloseWindow();
            return 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if(!game_won){
            DrawTexture(background_texture, 0, 0, WHITE);
	}
        else{
            DrawText("Congratulations! You collected all the stars!\n\t\t\t YOU WON!!!", width/4, height/2, 50, WHITE);
            EndDrawing();
            WaitTime(2);
            // Unload textures
            UnloadTexture(platform_texture);
            for(int i = 0; i < 4; i++){
	      UnloadTexture(player_textures[i]);
	    }
	    
            UnloadTexture(collectable_texture);
            UnloadTexture(background_texture);
            CloseWindow();
            return 0;
        }

        // Draw level
        load_level(levels[currentLevel-1]);

        // Draw player
        float player_scale = (float)player_sprite_size / current_player_texture.width;
        DrawTextureEx(current_player_texture, {state.player_x, state.player_y}, 0.0f, player_scale, WHITE);

        // Level‑specific moving stars
        float star_scale = (float)sprite_size / collectable_texture.width;
        if(currentLevel == 2){
            if(!star_1_level_2_collected){
                star_1_x_level_2 = 3 * sprite_size + star_radius * cos(s1l2);
                star_1_y_level_2 = 5 * sprite_size + star_radius * sin(s1l2);
                s1l2 += 0.5f;
                DrawTextureEx(collectable_texture, {star_1_x_level_2, star_1_y_level_2}, 0.0f, star_scale, WHITE);
            }
            if(!star_2_level_2_collected){
                star_2_x_level_2 = 9 * sprite_size + star_radius * cos(s2l2);
                star_2_y_level_2 = 5 * sprite_size + star_radius * sin(s2l2);
                s2l2 += 0.5f;
                DrawTextureEx(collectable_texture, {star_2_x_level_2, star_2_y_level_2}, 0.0f, star_scale, WHITE);
            }
            if(!star_3_level_2_collected){
                star_3_x_level_2 = 15 * sprite_size + star_radius * cos(s3l2);
                star_3_y_level_2 = 5 * sprite_size + star_radius * sin(s3l2);
                s3l2 += 0.5f;
                DrawTextureEx(collectable_texture, {star_3_x_level_2, star_3_y_level_2}, 0.0f, star_scale, WHITE);
            }
        }
        else if(currentLevel == 3){
            if(!star_1_level_3_collected){
                star_1_x_level_3 = -150 + s1l3;
                star_1_y_level_3 = 0.45f * height;
                if(star_1_x_level_3 >= 250){
		  star_1_level_3_left = true;
		  star_1_level_3_right = false;
		}
		
                if(star_1_x_level_3 <= -150){
		  star_1_level_3_left = false;
		  star_1_level_3_right = true;
		}
		
                if(star_1_x_level_3 < 250 && star_1_level_3_right){
		  s1l3 += 2.5f;
		}
		
                else if(star_1_x_level_3 >= -150 && star_1_level_3_left){
	      s1l3 -= 2.5f;
	    }
	    
                DrawTextureEx(collectable_texture, {star_1_x_level_3, star_1_y_level_3}, 0.0f, star_scale, WHITE);
            }
	    
            if(!star_2_level_3_collected){
                star_2_x_level_3 = 0.9f * width + s2l3;
                star_2_y_level_3 = 0.45f * height;
                if(star_2_x_level_3 >= 1.05f * width){
		  star_2_level_3_left = true;
		  star_2_level_3_right = false;
		}
		
                if(star_2_x_level_3 <= 0.87f * width)
		  { star_2_level_3_left = false;
		    star_2_level_3_right = true;
		  }
		
                if(star_2_x_level_3 < 1.05f * width && !star_2_level_3_left){
		  s2l3 += 2.5f;
		}
		
                else if(star_2_x_level_3 >= 0.87f * width && !star_2_level_3_right){
		  s2l3 -= 2.5f;
		}
		
                DrawTextureEx(collectable_texture, {star_2_x_level_3, star_2_y_level_3}, 0.0f, star_scale, WHITE);
            }
            if(!star_3_level_3_collected){
                star_3_x_level_3 = 35.0f * width / 72.0f;
                star_3_y_level_3 = -0.1f * height + s3l3;

		if(star_3_y_level_3 <= -0.12f * height){
		  star_3_level_3_up = true;
		  star_3_level_3_down = false;
		}
		
                if(star_3_y_level_3 >= 0.1f * height){
		  star_3_level_3_up = false;
		  star_3_level_3_down = true;
		}
		
                if(star_3_y_level_3 <= 0.1f * height && !star_3_level_3_down){
		  s3l3 += 2.5f;
		}
		
                else if(star_3_y_level_3 >= -0.12f * height && !star_3_level_3_up){
		  s3l3 -= 2.5f;
	    }
                DrawTextureEx(collectable_texture, {star_3_x_level_3, star_3_y_level_3}, 0.0f, star_scale, WHITE);
            }
	      
            if(!star_4_level_3_collected){
                star_4_x_level_3 = 35.0f * width / 72.0f;
                star_4_y_level_3 = 0.94f * height - s4l3;
		
                if(star_4_y_level_3 <= 0.85f * height){
		  star_4_level_3_up = true;
		  star_4_level_3_down = false;
		}
		
                if(star_4_y_level_3 >= 1.1f * height){
		  star_4_level_3_up = false;
		  star_4_level_3_down = true;
		}
		
                if(star_4_y_level_3 >= 0.85f * height && !star_4_level_3_down){
		  s4l3 -= 2.5f;
		}
		
                else if(star_4_y_level_3 <= 1.1f * height && !star_4_level_3_up){
		  s4l3 += 2.5f;
		}
		
                DrawTextureEx(collectable_texture, {star_4_x_level_3, star_4_y_level_3}, 0.0f, star_scale, WHITE);
            }
        }
        else if(currentLevel == 5){
            if(!star_1_level_5_collected){
                star_1_x_level_5 = (rand() % width) * cos(s1l5);
                star_1_y_level_5 = (rand() % height) * sin(s1l5);
                s1l5 += sign[rand() % 2] * (rand() % 10);
                DrawTextureEx(collectable_texture, {star_1_x_level_5, star_1_y_level_5}, 0.0f, star_scale, WHITE);
            }
        }
	    
        else if(currentLevel == 9){
            double now = GetTime();
            if(now - lastlevel9update >= 7.5){
                lastlevel9update = now;
                int index[] = {0, 1, 3};
                for(int i = 0; i < scale_y; i++){
                    for(int j = 0; j < scale_x; j++){
                        levels[currentLevel-1].grid[i][j] = index[rand() % 3];
                    }
                }
                for(int j = 0; j < scale_x; j++){
                    levels[currentLevel-1].grid[scale_y-1][j] = 1;
		}
		
                levels[currentLevel-1].total_stars = count_stars_in_levels(levels[currentLevel-1].grid);
            }
        }

        // ---- Collision and physics ----
        float new_y = state.player_y + state.gravity;
        float new_x = state.player_x + dx;

        for(int i = 0; i < scale_y; i++){
            for(int j = 0; j < scale_x; j++){
                // Star collection from tiles
                if(levels[currentLevel-1].grid[i][j] == STAR){
                    bool x_overlap = (state.player_x + player_sprite_size > j * sprite_size && state.player_x < (j+1) * sprite_size);
                    bool y_overlap = (state.player_y + player_sprite_size > i * sprite_size && state.player_y < (i+1) * sprite_size);
                    if(x_overlap && y_overlap){
		        PlaySound(collect_star);
                        starsCollected++;
                        levels[currentLevel-1].grid[i][j] = 0;
                    }
                }
                // Platform collision
                if(levels[currentLevel-1].grid[i][j] == PLATFORM){
                    bool x_overlap = (state.player_x + player_sprite_size > j * sprite_size && state.player_x < (j+1) * sprite_size);
                    bool y_overlap = (state.player_y + player_sprite_size > i * sprite_size && state.player_y < (i+1) * sprite_size);

                    if(x_overlap){
                        if(state.gravity > 0){
                            bool was_above = (state.player_y + player_sprite_size <= i * sprite_size);
                            bool will_be_below = (new_y + player_sprite_size > i * sprite_size);
                            if(was_above && will_be_below){
                                new_y = i * sprite_size - player_sprite_size;
			    }
                        }
                        else if(state.gravity < 0){
                            bool was_below = (state.player_y >= (i+1) * sprite_size);
                            bool will_be_above = (new_y < (i+1) * sprite_size);
                            if (was_below && will_be_above){
                                new_y = (i+1) * sprite_size;
                        }
			}
                    }

                    if(y_overlap){
		      if(dx > 0 && new_x + player_sprite_size > j * sprite_size && state.player_x + player_sprite_size <= j * sprite_size){
                            new_x = j * sprite_size - player_sprite_size;
		      }
		      
		      else if(dx < 0 && new_x < (j+1) * sprite_size && state.player_x >= (j+1) * sprite_size){
                            new_x = (j+1) * sprite_size;
                    }
		    }
                }
            }
        }

        // Collect moving stars (for levels 2,3,5)
        if(currentLevel == 2){
            if(!star_1_level_2_collected && hypot(state.player_x - star_1_x_level_2, state.player_y - star_1_y_level_2) <= star_radius){
	        PlaySound(collect_star);
                star_1_level_2_collected = true;
                starsCollected++;
            }
	    
            if(!star_2_level_2_collected && hypot(state.player_x - star_2_x_level_2, state.player_y - star_2_y_level_2) <= star_radius){
	        PlaySound(collect_star);
                star_2_level_2_collected = true;
                starsCollected++;
            }
	    
            if(!star_3_level_2_collected && hypot(state.player_x - star_3_x_level_2, state.player_y - star_3_y_level_2) <= star_radius){
	        PlaySound(collect_star);
                star_3_level_2_collected = true;
                starsCollected++;
            }
        }
	
        else if(currentLevel == 3){
            if(!star_1_level_3_collected && hypot(state.player_x - star_1_x_level_3, state.player_y - star_1_y_level_3) <= star_radius){
	        PlaySound(collect_star);
                star_1_level_3_collected = true;
                starsCollected++;
            }
	    
            if(!star_2_level_3_collected && hypot(state.player_x - star_2_x_level_3, state.player_y - star_2_y_level_3) <= star_radius){
	        PlaySound(collect_star);
                star_2_level_3_collected = true;
                starsCollected++;
            }
	    
            if(!star_3_level_3_collected && hypot(state.player_x - star_3_x_level_3, state.player_y - star_3_y_level_3) <= star_radius){
	        PlaySound(collect_star);
                star_3_level_3_collected = true;
                starsCollected++;
            }
	    
            if(!star_4_level_3_collected && hypot(state.player_x - star_4_x_level_3, state.player_y - star_4_y_level_3) <= star_radius){
	        PlaySound(collect_star);
                star_4_level_3_collected = true;
                starsCollected++;
            }
        }
	
        else if(currentLevel == 5){
            if(!star_1_level_5_collected && hypot(state.player_x - star_1_x_level_5, state.player_y - star_1_y_level_5) <= star_radius){
	        PlaySound(collect_star);
                star_1_level_5_collected = true;
                starsCollected++;
            }
        }

        // Level completion
        if(starsCollected >= levels[currentLevel-1].total_stars && currentLevel < (int)original_levels.size()){
            currentLevel++;
            starsCollected = 0;
            state.player_x = player_sprite_size;
            state.player_y = player_sprite_size;
            // Reset level‑specific flags for the next level (only needed when restarting)
            if(currentLevel == 2){
	      star_1_level_2_collected = false;
	      star_2_level_2_collected = false;
	      star_3_level_2_collected = false;

	      s1l2 = s2l2 = s3l2 = 0;
            }
	    
            if(currentLevel == 3){
	      star_1_level_3_collected = false;
	      star_2_level_3_collected = false;
	      star_3_level_3_collected = false;
	      star_4_level_3_collected = false;

	      s1l3 = s2l3 = s3l3 = s4l3 = 0;
            }
	    
            if(currentLevel == 5){
                star_1_level_5_collected = false;
                s1l5 = 0;
            }
        }
	
        else if(starsCollected >= levels[currentLevel-1].total_stars && currentLevel == (int)original_levels.size()){
            game_won = true;
        }

        state.player_x = new_x;
        state.player_y = new_y;

        EndDrawing();
    }

    // Unload textures (normal exit)
    UnloadTexture(platform_texture);
    for(int i = 0; i < 4; i++){
      UnloadTexture(player_textures[i]);
    }
    
    UnloadTexture(collectable_texture);
    UnloadTexture(background_texture);
    CloseWindow();
    return 0;
}
