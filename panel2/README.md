# Panel 2 – LVGL SDL UI Control Panel

This project is a **control panel user interface** developed using **LVGL** with the **SDL simulator**.
It represents a structured UI layout with grouped control buttons and a side control panel.

---

## 📸 Preview

![Panel2 UI](./sim_output.png)

---

## 🧩 Project Overview

Panel 2 is designed as a **multi-group control interface** consisting of:

### 🔹 Left Panel (Grouped Buttons)

* Buttons are organized into **logical groups**
* Each group is split into **multiple rows dynamically**

* Each button contains:

  * Text label
  * Icon (image)

### 🔹 Right Panel (Quick Actions)

Fixed-position control buttons:

* Power output status
* Screen brightness
* Sound control
* Home navigation

---

## ⚙️ Technical Details

* Built with **LVGL graphics library**
* Runs on **SDL-based simulation environment**
* Uses:

  * Dynamic layout calculation (`ceil`, grouping logic)
  * Custom UI structuring (`row_group`)
  * Image-based buttons

---

## 📁 Required Files

This panel **does not work standalone with only `main.c`**.

You must also include the following from the main repository:

* `CMakeLists.txt`
* `lv_conf.h`
* `images/` folder (all image source files)

---

## ❗ Important Configuration (CMake Fix)

Inside `CMakeLists.txt`, the following line exists:

```cmake
add_executable(main main.c mouse_cursor_icon.c images/arayuz.c images/relay_off.c images/home.c images/brigthness.c images/lightning.c images/sound_on.c)
```

### 🔥 You MUST remove:

```
images/arayuz.c
```

### ✅ Correct version:

```cmake
add_executable(main main.c mouse_cursor_icon.c images/relay_off.c images/home.c images/brigthness.c images/lightning.c images/sound_on.c)
```

### Reason:

* This project already includes all required UI logic inside `main.c`

---

## 🧠 Key Implementation Concept

The left panel layout is built using a custom structure:

```c
struct row_group {
    const char **texts;
    const lv_img_dsc_t **imgs;
    int total_count;
    int row_count;
};
```

This allows:

* Flexible grouping of UI elements
* Automatic row distribution
* Scalable UI design

---

## 🎯 Features

* Group-based dynamic button layout
* Image + text combined UI elements
* Clean panel separation (left controls / right actions)
* SDL simulation ready
* Modular and extendable structure

---

## 🛠 Notes

* This project is intended for **UI simulation and design demonstration**
* Hardware integration is not included
* All layout logic is handled programmatically (no GUI designer)

---

## 🚀 Summary

Panel 2 demonstrates a **structured and scalable LVGL UI design** using grouped layouts and control panels, suitable for embedded interface prototyping and simulation.

---

