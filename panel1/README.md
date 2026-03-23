# Panel 1 - Control Panel UI (LVGL SDL Simulator)

This project demonstrates **Panel 1** of our LVGL-based SDL simulator control panels. It showcases a graphical interface with left and right panels, button groups, and interactive elements.

## Project Overview

- **Left Panel:** Contains grouped buttons representing different control units. Each button displays a label and an icon.
- **Right Panel:** Provides quick-access buttons for main actions such as **Power Status**, **Screen Brightness**, **Sound**, and **Home**.
- **Dynamic Behavior:** The "Screen Brightness" button changes color after 5 seconds, simulating a real interactive response from the panel.
- **Visual Feedback:** Buttons have shadows and visual indicators to make the interface more realistic.

### Simulator Output

Here are screenshots from the SDL simulator showing Panel 1 in action:

**Screen 1: Initial State**  
![simulator_outputs](screen1.png)

**Screen 2: After 5 Seconds (Brightness Change)**  
![simulator_outputs](screen2.png)

## Required Files

To run **Panel 1**, the following files are required:

### Inside this folder (`Panel1`):

- `main.c`  
- `arayuz.c`  
- `arayuz.h`  

These files implement the specific logic and UI layout for Panel 1.

### From the main repository root:

- `images/` (common icons used by multiple panels)  
- `lv_conf.h`  
- `CMakeLists.txt`   

> **Note:** Both sets of files are required for the project to function properly.
