# 🔄 Inverted Gravity

A 2D platformer built with **C++** and **Raylib** where gravity flips!  
Collect stars across 10 levels while navigating platforms and avoiding the void.

---

## 🎮 Features

- **10 unique levels** — each with different layouts and challenges
- **Gravity flipping** — press Space to invert gravity
- **Star collection** — collect all stars to advance to the next level
- **Moving stars** — some stars follow patterns (circular, bouncing, random)
- **Dynamic levels** — Level 9 regenerates every 7.5 seconds
- **Player orientation** — character sprites change based on direction and gravity
- **Sound effects** — star collection, death, and gravity flip sounds
- **FPS counter** — smooth 60 FPS gameplay

---

## 🛠️ Technologies Used

- **C++** — core logic
- **Raylib** — 2D rendering, input handling, audio

---

## 🚀 How to Build

### Requirements

Install Raylib:

bash
# Ubuntu / Debian
sudo apt install libraylib-dev

# Or build from source
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake ..
make
sudo make install

## Compile

g++ -o inverted_gravity inverted_gravity.cpp \
    -lraylib -lm -lpthread -ldl -lrt -lX11

## Run

./inverted_gravity

🎮 Controls
Key	Action
Left Arrow	Move left
Right Arrow	Move right
Space	Flip gravity
Enter	Exit the game

🧠 How It Works

   1. Player — moves left/right with arrow keys

   2. Gravity — pulls the player down (or up when flipped)

   3. Platforms — solid surfaces the player can stand on

   4. Stars — collect them to progress (some move)

   5. Level completion — collect all stars to advance

   6. Death — falling off the screen ends the game









