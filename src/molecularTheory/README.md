# Brownian Motion Particle Simulation

## Overview
A 2D particle simulation demonstrating thermal and collision dynamics using OpenGL. The simulation models particle interactions, energy transfer, and thermal color representation.

## Features
- 99 particles with random initial positions and velocities
- Real-time particle movement and collision physics
- Thermal color visualization based on particle velocity
- Interactive energy control (increase/decrease)
- Boundary wall reflections

## Controls
- `W` or `+`: Increase system energy
- `S` or `-`: Decrease system energy
- `ESC`: Exit simulation

## Dependencies
- OpenGL
- GLUT

## Compilation
Compile with OpenGL and GLUT libraries:
```bash
g++ -o brownian_motion main.cpp -lGL -lGLU -lglut
```

## Key Concepts
- Particle energy transfer
- Elastic collisions
- Thermal color mapping