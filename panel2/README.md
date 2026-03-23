# Panel 2 UI Control

Panel 2 is the second control panel developed using LVGL with SDL simulator.  
It demonstrates a graphical interface with left and right panels, button groups, and interactive elements.

## Project Overview

- **Left Panel**:  
  Contains 3 button groups:  
  1. Operator Console & Communication Units  
  2. Interception Units  
  3. Backup DC Units  
  Each group is arranged in a single row. Every button includes a label and an icon.

- **Right Panel**:  
  Provides quick-access buttons for main actions:  
  - Power Status  
  - Screen Brightness  
  - Sound  
  - Home  

- **Dynamic Behavior**:  
  The "Screen Brightness" button changes color after 5 seconds, simulating an interactive panel response.

- **Visual Feedback**:  
  Buttons have shadows and styling to enhance realism.

## Simulator Output

The screenshots below demonstrate Panel 2 running in the SDL simulator:

**Initial State**

![Simulator Screen 1](simulations/panel2_initial.png)

**After 5 Seconds (Brightness Change)**

![Simulator Screen 2](simulations/panel2_brightness.png)

## Required Files

- Inside this folder (`Panel2`):  
  - `main.c`  
  - `arayuz.c`  
  - `arayuz.h`  
  These files implement the specific UI layout and logic for Panel 2.

- From the main repository root:  
  - `images/` (common icons used by multiple panels)  
  - `lv_conf.h`  
  - `CMakeLists.txt`  

> Note: Both sets of files are required to run the project successfully.

## Features

- Single-row button groups in the left panel  
- Quick-access right panel buttons  
- Timer-based dynamic screen brightness change  
- Shadow and color effects for a realistic UI experience
