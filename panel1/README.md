# Panel 1 - Detailed Control Console (LVGL SDL Simulator)

This project demonstrates a detailed control interface using LVGL with the SDL simulator. Panel 1 provides a comprehensive multi-functional console designed for in-depth interaction.

## Overview

- **Left Panel**: Contains multiple groups of buttons. Each group may span multiple rows, giving the interface a flexible layout. Buttons feature labels and icons representing various control units.
- **Right Panel**: Provides main actions such as Power Status, Screen Brightness, Sound, and Home. Each button offers visual feedback with shadows and styled indicators.

## 🎨 UI Design Characteristics

This panel emphasizes a **more visual and styled interface design**:

- Uses shadow and depth effects
- Focus on visual clarity and user-friendly appearance
- More direct and static layout structure

This makes the interface:
- More intuitive for users
- Visually richer
- Suitable for straightforward control scenarios

## Dynamic Behavior

- The "Screen Brightness" button changes color after 5 seconds, simulating interactive feedback.
- Shadows and row backgrounds enhance visual perception, providing a sense of depth.

## Design Highlights

- Multi-row layout for left panel groups allows complex grouping of controls.
- Shadows and styled backgrounds are applied to both panels for a more realistic console appearance.
- The interface aims for a comprehensive user experience, suitable for detailed control tasks.

## Simulator Output

Screenshots below demonstrate Panel 1 in action:

- **Initial State**: Main screen with grouped buttons and default visuals.

![Simulator Screen 1](panel1/simulator_outputs/screen1.png)


- **After 5 Seconds**: Screen Brightness changes color, showing dynamic behavior.

![Simulator Screen 2](panel1/simulator_outputs/screen2.png)


## Required Files

**Inside this folder (Panel1)**:
- `main.c`
- `arayuz.c`
- `arayuz.h`

**From the repository root**:
- `images/` (common icons used across panels)
- `lv_conf.h`
- `CMakeLists.txt`

> Note: Both sets of files are required for the simulator to function correctly.
