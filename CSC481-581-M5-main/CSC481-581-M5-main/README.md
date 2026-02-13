# The Time Machine ⏰
Welcome to your SDL3-powered timeline clock! This application creates an animated analog clock where you can control the flow of time using **SDL3** and **C++**. Speed up or slow down time with simple keyboard controls while watching the seconds tick by.

## Objectives
By the end of this project, you'll understand:
- How to create SDL3 windows and renderers
- Text rendering with SDL3_ttf
- Real-time animation and timing control

## Setup Instructions
Follow these steps to build and run the timeline clock:

### 1. Clone or download the project
Save the code to a file named `main.cpp` in your project directory.

----------

### 2. Install SDL3 and SDL3_ttf
> You'll need both SDL3 (for graphics) and SDL3_ttf (for text rendering).

#### On **macOS** (with Homebrew):
```bash
brew install sdl3 sdl3_ttf
```

#### On **Ubuntu/Debian**:
```bash
sudo apt install libsdl3-dev libsdl3-ttf-dev
```

#### On **Arch Linux**:
```bash
sudo pacman -S sdl3 sdl3_ttf
```

#### On **Windows**: 
Use [MSYS2](https://www.msys2.org/) or [VCPKG] (https://vcpkg.io/en/) for easiest installation:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL3 mingw-w64-x86_64-SDL3_ttf
```

----------

### 3. Compile the project

From the Root of the Project, Use the following Commands
```bash
mkdir build  && cd build
```
Build the MakeFile
```bash
cmake ..
```
Run the MakeFile
```bash
make
```

----------

### 4. Run the clock
```bash
./main
```

You should see a white window with an analog clock and speed controls. You need to update the timeline class to make it work

----------

## Core Concepts

### What is SDL3_ttf?
**SDL3_ttf** is an extension library that lets you render text using TrueType fonts. It works by:
1. Loading a font file (`.ttf`) from your system
2. Creating text surfaces from strings
3. Converting surfaces to textures for GPU rendering

```cpp
TTF_Font* font = TTF_OpenFont("/path/to/font.ttf", 18);
SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello", color);
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
```

----------

### Timeline System
The `Timeline` struct manages time flow:
- **timeScale**: Controls speed (0.5x = half speed, 2.0x = double speed)
- **accumulated**: Total scaled time elapsed
- **update()**: Calculates delta time and applies scaling

```cpp
struct Timeline {
    double timeScale = 1.0;
    double accumulated = 0.0;
    // ... methods
};
```

----------

### Modular Drawing
The `drawClock()` function handles all rendering:
- Clock face with 12-hour markers
- Numbered positions (1-12)
- Animated second hand
- Speed indicator and instructions

This keeps the main loop clean and focused on events and updates.

----------

## Features

Your timeline clock includes:
✅ Analog clock face with hour markers  
✅ Rotating second hand animation  
✅ Variable time speed (0.5x to 8x)  
✅ Keyboard controls (UP/DOWN arrows)  
✅ Real-time speed display  
✅ Clean, modular code structure  

### Controls:
- **UP Arrow**: Double the time speed
- **DOWN Arrow**: Halve the time speed
- **Close Window**: Exit the application

----------

## 📎 Helpful Resources

- [SDL3 Official Docs](https://wiki.libsdl.org/SDL3/FrontPage)
- [SDL3_ttf Documentation](https://wiki.libsdl.org/SDL3_ttf/CategoryAPI)
- [TrueType Font Basics](https://en.wikipedia.org/wiki/TrueType)

----------

## Troubleshooting

**Font not loading?** 
- Check if DejaVu fonts are present in the fonts directory

**Compilation errors?**
- Make sure SDL3 and SDL3_ttf development packages are installed
- Check that your compiler supports C++11 or later

----------

## Final Notes

This timeline clock demonstrates core game development concepts: real-time rendering, event handling, and modular design. The Timeline system could easily be extended for game physics, while the rendering structure scales well for more complex graphics projects.

Keep experimenting with different speeds and watch time bend to your will!