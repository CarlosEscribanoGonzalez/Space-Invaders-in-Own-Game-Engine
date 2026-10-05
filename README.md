## Overview
Very small and simple game engine written in C++ with OpenGL and GLUT, on top of which a Space Invaders own simplified implementation has been built.
The engine provides a scene system, an `.obj` model loader and a fixed-timestep game loop, while the game itself is implemented as a set of scripts that use it.

## Features
**Engine**
* Scene-based architecture: each scene (main game, end screen) implements its own initialization, update, render and input handling, and the game switches between them
* Base `Solid` class that gives every object position, speed, orientation, angular speed, color, texture coordinates and transparency, with a common `Render` / `Update` interface
* Custom `Vector2D` and `Vector3D` templates with the usual vector operations
* `.obj` model loader with configurable scale, used to load the 3D models of the ship, the UFOs and the projectiles
* Fixed-timestep update loop, independent of the rendering rate
* Camera object and on-screen text rendering for the HUD
* Keyboard input handling for both regular keys and arrow keys, with separate press and release events to allow smooth continuous movement

**Space Invaders**
* Hit detection between projectiles, enemies and the player through bounding checks on position
* Points for every enemy destroyed, and a lives system for the player
* Progressive difficulty: every time the whole formation is destroyed, the wave restarts with faster enemies
* Projectile reuse (object pool): player's and enemies' projectiles are instantiated during scene initialization and reused
<p align = "center">
  <img width="534" height="400" alt="spaceinvaders" src="https://github.com/user-attachments/assets/f7fdd4c0-da62-47ce-bcfd-4bac330c2a0a" />
</p>

## Technologies
* C++
* OpenGL
* GLUT

## Usage
* Open the `.sln` file in Visual Studio
* Build and run the project
* Move with **A** / **D** or the arrow keys, and shoot with **Space** or **W**
