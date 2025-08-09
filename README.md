
## Overview

The **AI Dash Engine** is a recreation of the **Geometry Dash Lite** mobile game written fully in **C++**, using **Object-Oriented Principles** and the **SFML (Simple and Fast Multimedia Library)**. This game integrates an AI component, utilizing the **NEAT (NeuroEvolution of Augmenting Topologies)** algorithm written in **Python**, to autonomously learn and beat the game.

## Quick Look
<img width="500" height="220" alt="Screenshot 2025-08-09 130812" src="https://github.com/user-attachments/assets/85a6955e-f147-464d-8bb0-3e1af5274c6a" />

*Snapshot of gameplay in action*

---

## Technologies Used

- **C++**: SFML Library, OOP  
  ![C++](https://img.shields.io/badge/C%2B%2B-%2300599C.svg?logo=c%2B%2B&logoColor=white)  
  ![SFML](https://img.shields.io/badge/SFML-%23000000.svg?logo=sfml&logoColor=white)

- **AI**: NEAT Algorithm, Neural Networks  
  ![AI](https://img.shields.io/badge/AI-%2300FF00.svg?logo=openai&logoColor=white)

- **Python**: Scripting for the NEAT Algorithm  
  ![Python](https://img.shields.io/badge/Python-%233776AB.svg?logo=python&logoColor=white)

- **CMake**: Build System  
  ![CMake](https://img.shields.io/badge/CMake-%23000000.svg?logo=cmake&logoColor=white)

## Installation

1. **Dependencies**
- SFML Library: Make sure you have the SFML library installed. You can find the installation guide here.
- GCC Compiler: Ensure you have a C++ compiler, preferably GCC, installed on your machine.
- Python: The AI uses the NEAT algorithm, so ensure that Python is installed. You will also need the NEAT-Python library:
```bash
pip install neat-python
```

2. **Clone the Repository**

   ```sh
   git clone https://github.com/ssala043/Dash-2.0.git
   cd Dash-2.0
   
2. **Building**
   - Build the /src
   ```sh
   make main
   ```
Then run
```bash
./main
```
