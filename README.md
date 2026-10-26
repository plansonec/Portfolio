# Emma Planson — Software Engineering & Accessibility Portfolio

**Computer Science (B.S.) & User Experience (Minor) • University of Alabama in Huntsville (UAH)**  
**GitHub:** [@plansonec](https://www.google.com/search?q=https://github.com/plansonec) • **Email:** [Emmaplanson@gmail.com](mailto:Emmaplanson@gmail.com) • **Location:** Huntsville & Birmingham, AL

## About Me

I am a Computer Science undergraduate with a minor in User Experience at the **University of Alabama in Huntsville (UAH)** (Expected May 2028), focusing on **software engineering, systems architecture, and digital accessibility**. Alongside my coursework in Data Structures, Object-Oriented Programming, Digital Computer Architecture, and Algorithm Design & Analysis, I serve as a participant in the national **Monarch RISE Project** with the American Printing House for the Blind (APH) and develop web and software accessibility auditing methodologies.

This repository houses my core software engineering projects across **Java (JavaFX/XML/MVC)**, **C++17 (Custom Data Structures & OS Process Scheduling)**, **32-bit ARMv4 Assembly (Systems & Embedded Control)**, and **Front-End Web Development (WCAG 2.1 AA Accessible HTML5, CSS3, and ES6 JavaScript)**.

## Portfolio Projects Overview

| Project Directory | Primary Stack | Core Architecture & Engineering Highlights |
| :--- | :--- | :--- |
| [/board-game-database-java](https://www.google.com/search?q=./board-game-database-java/) | **Java 21, JavaFX, XML (DOM), CSS, Gradle** | Desktop application built on the **MVC** and **Singleton** patterns that parses a 90-game BoardGameGeek XML catalog (`bgg90Games.xml`), supports multi-criteria search and persistent XML wishlists, and features a custom **High-Contrast Accessibility Theme (`highContrast.css`)** and dynamic typography scaling engine (`Session.java`). |
| [/cpu-scheduler-cpp](https://www.google.com/search?q=./cpu-scheduler-cpp/) | **C++17, Templates, Custom Iterators, Make** | Discrete-event **CPU Process Scheduler Simulator (`schedulesim`)** comparing **Round Robin (`ArrayList`)**, **Fast Round Robin (`LinkedList`)**, and **Completely Fair Scheduler (`BSTMultimap`)** across CPU-bound and I/O-bound workloads. Includes 5 automated unit test suites and nanosecond-resolution `std::chrono` benchmarks. |
| [/arm-assembly-cs413](https://www.google.com/search?q=./arm-assembly-cs413/) | **32-bit ARMv4 Assembly (`.s`), GCC, GDB** | Low-level systems programs from CS 413: a **Stack-Based Four-Function Calculator (`lab2.s`)** featuring strict caller/callee register isolation (`r4`–`r5` vs. `r10`–`r11`), repeated-subtraction division, and 64-bit `SMULL`/`ADDS` overflow detection; and an embedded **Coffee Maker Finite State Machine (`lab3.s`)** with 8-byte AAPCS stack-aligned telemetry (`show_hidden`) and automatic low-water shutdown. |
| [docs/index.html](https://www.google.com/search?q=./docs/) | **HTML5, CSS3, Vanilla ES6 JavaScript** | Zero-dependency, **WCAG 2.1 AA accessible interactive web portfolio** featuring a live client-side JavaScript port of the BoardGameGeek XML search engine, an interactive CPU Scheduler benchmark visualizer, an ARMv4 lab simulator & subroutine architecture explorer, and a persistent High-Contrast Mode & font-scaling toolbar. |

## Technical Skills Matrix

| Category | Technologies & Competencies |
| :--- | :--- |
| **Systems & Application Languages** | Java (Java 21, JavaFX, JUnit/Testers), C++ (C++17, Templates, STL/Chrono), 32-bit ARMv4 Assembly, Python, Swift |
| **Web & Front-End Engineering** | HTML5 (Semantic Landmarks, ARIA Live Regions), CSS3 (Custom Properties, Grid/Flexbox, High-Contrast Themes), Vanilla ES6+ JavaScript, XML / DOM Parsing |
| **Accessibility & UX Engineering** | WCAG 2.1 AA Compliance, Screen-Reader Navigation (NVDA, JAWS, VoiceOver), High-Contrast UI Architecture, Keyboard-First Interaction Design, Assistive Technology Field Testing (APH Monarch RISE) |
| **Developer Tools & Environments** | Git & GitHub, Linux / Unix Command Line (SSH, Bash, Make), Gradle, GCC / G++ / GDB, VS Code, IntelliJ IDEA |

## Quick-Start Guide for Reviewers

### 1. Launch the Interactive Web Portfolio (HTML5 / CSS3 / JS)
Open `docs/index.html` (or `index.html`) directly in any modern browser, or visit the live GitHub Pages deployment once hosted. It requires zero build steps or external server dependencies and lets you interactively test the Board Game XML catalog filter, the C++ CPU Scheduler benchmark visualizer, and the ARMv4 Assembly calculator and coffee maker FSM simulators.

### 2. Build & Test the C++17 CPU Process Scheduler (`cpu-scheduler-cpp/`)
```bash
cd cpu-scheduler-cpp
make all
make test
./schedulesim 10 10 100000
```

### 3. Run the Java 21 / JavaFX Board Game Application (`board-game-database-java/`)
```bash
cd board-game-database-java
./gradlew run
```

### 4. Assemble & Run the 32-bit ARMv4 Programs (`arm-assembly-cs413/`)
On an ARMv7/ARM32 Linux machine (such as a Raspberry Pi or UAH lab server):
```bash
cd arm-assembly-cs413
make all
./lab2
./lab3
```

## Contact & Links

- **Email:** [Emmaplanson@gmail.com](mailto:Emmaplanson@gmail.com)
- **Academic Email:** [ecp0018@uah.edu](mailto:ecp0018@uah.edu)
- **GitHub:** [github.com/plansonec](https://www.google.com/search?q=https://github.com/plansonec)
