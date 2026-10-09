# 🏴‍☠️ The Treasure Hunt

A fast-paced, terminal-based treasure hunting game written in **C**. Explore a hidden 5×5 grid, collect treasures, dodge moving traps, and beat the 60-second clock.

## 🎮 Gameplay

You start at the top-left corner of a grid where every cell is hidden (`?`). Move around to reveal what each cell holds. Find **all 5 treasures** before you run out of moves, health, or time.

### Goal
Collect all treasures to win.

### Game Elements

| Symbol | Meaning | Effect |
|--------|---------|--------|
| `P` | Player | Your current position |
| `?` | Unexplored cell | Contents unknown |
| `T` | Treasure | +10 points |
| `X` | Trap | -1 health |
| `+` | Power-up | +3 moves |

### Starting Stats

| Stat | Value |
|------|-------|
| Grid size | 5 × 5 |
| Health | 3 |
| Moves | 20 |
| Time limit | 60 seconds |
| Treasures | 5 |
| Traps | 5 |
| Power-ups | 2 |

### Controls

| Key | Action |
|-----|--------|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |

Input is case-insensitive. Moving outside the grid is rejected and does not use a move.

---

## ✨ Key Features

- **Fog of war:** cells stay hidden until you step on them.
- **Dynamic traps:** after every successful move, all traps shuffle to new random empty cells, so you can't memorize their positions.
- **Power-ups:** extra moves keep the run going.
- **Countdown timer:** a live 60-second clock is shown every turn.
- **Randomized maps:** items are placed randomly on each run (seeded with `time()`).
- **Leaderboard:** your username and score are recorded at the end of a game.
- **Multiple end conditions:** win, lose all health, run out of moves, or time out.

---

## 🛠️ Getting Started

### Requirements
- A C compiler (e.g. GCC)

### Compile
```bash
gcc Treasurehuntfinalprojectt.c -o treasurehunt
```

### Run
```bash
./treasurehunt        # Linux / macOS
treasurehunt.exe      # Windows
```

### How to Play
1. Enter your username.
2. Type `go` to start the challenge.
3. Use `W`, `A`, `S`, `D` to move around the grid.
4. Collect all 5 treasures before the game ends.

---

## 🧠 How It Works

| Function | Purpose |
|----------|---------|
| `initializeGrid()` / `initializeVisibleGrid()` | Set up the hidden map and the player's fog-of-war view |
| `placeItems()` | Randomly places treasures, traps, and power-ups on empty cells |
| `movePlayer()` | Handles movement, boundary checks, and item effects |
| `moveDynamicTraps()` | Relocates all traps after each move |
| `displayGrid()` | Prints the visible grid with the player marker |
| `updateLeaderboard()` / `displayLeaderboard()` | Stores and prints scores (up to 10 entries) |

**Concepts used:** 2D arrays, structs, pointers, functions, loops, switch statements, random number generation, and time handling with `<time.h>`.

---

## 📌 Notes and Limitations

- The leaderboard is stored in memory only, so it resets every time the program closes.
- The timer is checked at the start of each turn, so the game ends on your next input once time has run out.

---

## 🚀 Possible Improvements

- Save the leaderboard to a file so scores persist
- Sort the leaderboard by score
- Add difficulty levels (larger grid, fewer moves)
- Add colored terminal output


