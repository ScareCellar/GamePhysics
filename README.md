## Game Physics Engine
## Spring 2026

A custom physics sandbox developed for my Game Physics course during the Spring 2026 quarter. The engine demonstrates real-time physics simulation through rigid body dynamics, collision detection and response, gravity, spring constraints, object separation, force effectors, and interactive GUI controls.

## Overview

This project was created to explore and implement the fundamental systems found in modern game physics engines. Users can construct dynamic scenes by spawning bodies, connecting them with springs, and introducing force effectors to create complex physical interactions.

The simulation is designed as a sandbox environment that encourages experimentation and visualization of physical behavior in real time.

## Controls
# Spawning Bodies

Left-click anywhere in the simulation window to create a new physics body. The body's properties are determined by the values currently specified in the GUI.

For rapid spawning, hold Left Control while left-clicking. This allows multiple bodies to be created in quick succession and is useful for testing collision handling and large-scale interactions.

# Creating Springs

To connect two bodies with a spring, press and hold the right mouse button on a body and drag to another body. Once the connection is visibly established, release the right mouse button to create the spring constraint.

Springs can be used to construct chains, pendulums, bridges, and other interconnected systems.

# Spawning Effectors

Hold Shift and left-click to create an effector. The effector's properties are determined by the values currently specified in the GUI.

Effectors apply forces that influence nearby bodies, allowing for a variety of dynamic interactions within the simulation.

# Pausing the Simulation

Press Space to pause or resume the simulation. This can be useful for inspecting the state of the system or analyzing interactions at specific moments in time.

## Implemented Features

The engine includes support for rigid body simulation, gravity, collision detection and response, object separation, spring constraints, force effectors, and interactive parameter adjustment through a graphical user interface.

Together, these systems provide a foundation for experimenting with many of the core principles of game physics.

## Purpose

The primary goal of this project was to gain a deeper understanding of how physics systems are implemented in interactive applications and game engines. Rather than relying on existing physics libraries, the focus was placed on building and integrating the underlying mechanics directly.

This project serves both as a technical demonstration and as a platform for exploring physical simulation concepts through direct interaction and experimentation.
