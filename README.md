﻿# NES Emulator (C++ from Scratch)

This is a Nintendo Entertainment System (NES) emulator built from scratch in C++, developed using Visual Studio. It emulates the classic 8-bit NES hardware and runs NES ROMs with basic CPU, PPU, and memory functionality.

## 🎮 Features

- 6502 CPU emulation
- PPU rendering (backgrounds and sprites)
- Memory mapping and mirroring
- ROM loading (.nes format)
- Basic input handling (keyboard/controller)
- Debugging tools (optional)

> **Note:** This project is a work in progress. Some features or mappers may not be fully implemented.

## 🙏 Acknowledgements

This project is heavily inspired by and based on the outstanding **NES emulator tutorial series by [Javidx9 (OneLoneCoder)](https://github.com/OneLoneCoder/olcNES)**. His step-by-step breakdown of the NES hardware and emulator development made this possible.

> Huge thanks to OneLoneCoder for making emulation approachable and enjoyable to learn.

## 🚀 Getting Started

### Prerequisites

- Windows 10/11
- Visual Studio 2019/2022
- Basic understanding of C++ and computer architecture

### Build Instructions

1. Clone the repository:

   ```bash
   git clone https://github.com/iasjad/nes_emulator.git
   cd nes_emulator
   ```

2. Open the `.sln` file in Visual Studio.

3. Place your ROMS which end's with `.nes` in the working directory path.

4. Build and run the project (`F5` or Ctrl+F5).

5. From the console chose the corresponding ROM which you want to play.

### Controls

- `Arrow Keys` – D-Pad
- `X` – A Button
- `Z` – B Button
- `S` – Start
- `A` – Select

> You can change the key mappings in the source code if needed.



## ⚖️ License

This project is for educational purposes. Please ensure you legally own any ROMs you use with this emulator.


---

Feel free to fork, modify, and expand the emulator. Happy hacking!
