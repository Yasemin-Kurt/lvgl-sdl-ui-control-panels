# LVGL SDL UI Control Panels Collection

This repository contains two example projects demonstrating **LVGL-based control panel interfaces** using the **SDL simulator**. These projects provide examples of creating and simulating embedded-style UI layouts with grouped buttons and visual representations.

---

## Projects Overview

This repository includes two separate projects:

### Panel2 – Basic Control Panel
- Simple, flat design for a basic multi-group layout
- Users can add and rearrange buttons within each group
- Includes the Extra1 button to demonstrate adding new buttons, images, or text labels
- No shadows or triggered visual effects

### Panel1 – Detailed Control Console
- Advanced design with shadowing, layered effects, and dynamic behavior
- Demonstrates interactive updates (5-second simulation triggers text and image changes)
- Complex multi-row/grouped left panel with user-configurable placement

> **Recommendation:** Start with Panel2 to understand the basic layout and functionality, then explore Panel1 for more advanced features.

---

## Project Contents

- **Images:** All `.png`, `.c`, and `.h` files used in the projects are in the `images/` folder.  

  **Adding your own images:**
  1. Convert `.png` images to `.c` using the LVGL online image converter
  2. Manually create the corresponding `.h` files
  3. Include new `.c` files in `CMakeLists.txt` for compilation

- **CMakeLists.txt:** Any new `.c` files (buttons, images, etc.) must be included here, for example:

\`\`\`cmake

add_executable(main main.c mouse_cursor_icon.c images/relay_off.c images/home.c images/brigthness.c images/lightning.c images/sound_on.c)

\`\`\`

> Remove any unnecessary files such as `images/home.c` if not used.

- **Configuration files:**
  - `lv_conf.h` – LVGL configuration settings
  - `CMakeLists.txt` – Updated with project-specific source files
  - Project folder: Include the project folder you wish to run (`panel1/` or `panel2/`) with its files

---

## Prerequisites

Before running these projects, ensure the following are installed:

- LVGL graphics library  
- SDL2 library  
- WSL terminal (used for building and running)  
- VS Code environment is recommended

---

## Building and Running

After completing prerequisites and including all necessary files:

\`\`\`bash

cd /mnt/c/Users/LENOVO/lv_sim_eclipse_sdl/build

make -j8

../bin/main

\`\`\`

> File paths may need to be adjusted depending on your system setup. Compilation may produce errors if file paths or locations differ from the examples. Update paths as needed.

---

## Usage Instructions

1. Complete prerequisite installations (LVGL, SDL2, etc.)
2. Include the full `images/` folder, `lv_conf.h`, and `CMakeLists.txt` in your build directory
3. Include the project folder you wish to run (`panel1/` or `panel2/`) with its files
4. Compile and run using the commands above
5. Adjust file paths in the code and `CMakeLists.txt` according to your system

---

## Simulation Notes

### Panel2
- Clean, simple interface
- Users can rearrange buttons within groups in both rows and columns
- Extra1 button demonstrates adding new buttons, images, and labels

### Panel1
- Advanced interface with shadows, layered effects, and dynamic visual feedback
- 5-second simulation triggers changes in button text and images based on user interaction
- Left panel groups allow flexible placement of buttons, background buttons visually represent different units
- Right panel contains buttons with fixed positions for main actions

---

## Summary

These projects serve as practical examples of LVGL UI creation and simulation:

- Demonstrate basic and advanced control panel layouts
- Showcase dynamic and static button placement
- Illustrate how to integrate images and text into interactive UI elements
- Provide a foundation for prototyping embedded UI designs in SDL simulations

By following the instructions above, users can extend the projects with new buttons, images, and text labels, while exploring both simple and detailed LVGL UI designs.
