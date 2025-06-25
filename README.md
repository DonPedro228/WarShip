# 🌊 SEA BATTLE – Console Battleship Game in C++

🎮 A turn-based **Sea Battle (Battleship)** game built in modern C++ for the console. Challenge the smart bot, place your ships manually or automatically, and engage in an intense tactical battle!  
Ships sink, fields explode, and only one admiral will prevail. Will it be you?

---

## 🛠️ Technologies Used

| Technology      | Description                             |
|-----------------|-----------------------------------------|
| `C++`           | Core programming language               |
| `OOP`           | Classes for `Cell`, `Ship`, `Board`, `Player`, `Bot`, `Game` |
| `Windows API`   | Console color output via `<windows.h>`  |
| `<iostream>`    | Input/output for console interactions   |
| `Enum classes`  | Used for `CellState` and `HuntState`    |
| `<vector>`      | For bot memory and logic                |
| `<chrono>` & `<thread>` | Bot delay simulation             |

---

## 🧩 Game Features

✅ Manual or automatic ship placement  
✅ Smart bot with 3-phase AI: Searching → Hunting → Targeting  
✅ Console graphics using symbols + colored output  
✅ Input validation and error handling  
✅ Display of both player's and bot's boards  
✅ Win/Loss logic with final result display

---

## 🎯 Gameplay Preview

=========== SEA BATTLE ===========

Your Field:

0 1 2 3 4 5 6 7 8 9

0 |~ ~ ~ ~ ~ ~ ~ ~ ~ ~

1 |~ ■ ■ ■ ~ ~ ~ ~ ~ ~

2 |~ ~ ~ ~ ~ ~ ~ ~ ~ ~

...

Enemy Field:

0 1 2 3 4 5 6 7 8 9

0 |~ ~ ~ ~ ~ ~ ~ ~ ~ ~

1 |~ ~ ~ ~ ~ ~ ~ ~ ~ ~

...


        Your turn:
        Enter target X (0-9): 2
        Enter target Y (0-9): 1
        🎯 Hit!



---

## 🧠 Bot AI Phases

| Phase       | Description |
|-------------|-------------|
| **Searching** | Randomly selects cells until a hit is found |
| **Hunting**   | Queues adjacent cells after a hit |
| **Targeting** | Calculates direction and continues attacking in line |

The bot can **track direction**, **backtrack if necessary**, and continues until your ship is sunk.

---

## 📦 Project Structure

```bash
📁 WarShip
├── 📄 main.cpp
├── 📄 Game.h / Game.cpp
├── 📄 Board.h / Board.cpp
├── 📄 Cell.h / Cell.cpp
├── 📄 Ship.h / Ship.cpp
├── 📄 Player.h
├── 📄 HumanPlayer.h / .cpp
├── 📄 BotPlayer.h / .cpp
├── 📄 ColorUtils.h
└── 📄 README.md

🚀 Getting Started
🧑‍💻 Requirements

    Windows OS

    C++17 or later

    MSVC / MinGW compiler

🔧 Compilation (MSVC)

cl /EHsc *.cpp /FeSeaBattle.exe

▶️ Run

SeaBattle.exe

✨ Example Snippet

switch (result) {
	case CellState::Hit:
		cout << "🎯 Hit!" << endl;
		break;
	case CellState::Killed:
		cout << "💥 Killed!" << endl;
		break;
	case CellState::Miss:
		cout << "💦 Miss." << endl;
		break;
}

🧪 Ship Placement Validation

Ships cannot touch each other even diagonally. This is ensured in Board::can_place_ship(...) via surrounding cell checks.

for (int dx = -1; dx <= 1; ++dx) {
	for (int dy = -1; dy <= 1; ++dy) {
		int nx = cx + dx;
		int ny = cy + dy;

		if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10) {
			if (grid[ny][nx]->get_state() == CellState::Ship) {
				return false;
			}
		}
	}
}

📌 Known Limitations

    Console support only (no GUI)

    Emojis may not render correctly without UTF-8 and wcout setup

    No sound effects (yet 😎)

🧠 Credits

Created as an educational project to practice:

    OOP (Object-Oriented Design)

    AI logic (Finite-State Machine for bot)

    Console UI/UX in C++

    Game loop and input handling

🛳️ Future Plans

    🎨 GUI with SFML or Qt

    🌐 Multiplayer mode

    🎵 Sound effects and animations

    📈 Score tracking

🏁 License

This project is for educational and personal use.
Feel free to modify and expand it!

Made with ❤️ in C++
