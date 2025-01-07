# Minecraft Recreation Using OpenGL

This project was completed as part of my graphics programming coursework. It showcases a high-level recreation of Minecraft's block generation and terrain creation mechanisms, utilizing OpenGL and Perlin noise. This document provides an overview of the project and dives into its technical implementation.

## Overview

The application generates blocks by creating textured cubes. These textures are applied in the same manner as Minecraft. The terrain is divided into Chunks, which in Minecraft represent 16x16 squares of terrain extending from the lowest to the highest vertical height. In this project, Chunks are implemented as 16x16x16 cubes to optimize memory usage during terrain generation. 

Terrain generation utilizes Perlin noise to determine surface levels, filling all blocks below the surface. While the current implementation supports only dirt blocks, the system is extensible to accommodate multiple block types in the future.

![image](https://github.com/user-attachments/assets/bbc0caa6-c17b-47a8-9502-1d337a6a1203)


## Implementation Details

This project was developed using an OpenGL template provided by Professor Mike Bailey, accessible [here](https://web.engr.oregonstate.edu/~mjb/cs550/). The core components include the following classes:

- [Block](https://github.com/jackhart591/Minecraft-OpenGL/blob/main/Block.cpp)
- [Chunk](https://github.com/jackhart591/Minecraft-OpenGL/blob/main/Chunk.cpp)
- [World](https://github.com/jackhart591/Minecraft-OpenGL/blob/main/World.cpp)
- [Sample.cpp](https://github.com/jackhart591/Minecraft-OpenGL/blob/main/sample.cpp)

### Key Components

#### **Sample.cpp**

`Sample.cpp` serves as the driver script and abstracts OpenGL functionality away from the other classes. Its primary responsibilities include:

- Initializing OpenGL and setting up the rendering pipeline.
- Creating the block model and defining how textures are applied to blocks.
- Managing the dimensions of the rendered world (width, length, and height).
- Translating block coordinates into world-space positions, allowing other scripts to operate purely in block-based units.

#### **Chunk Class**

The `Chunk` class is responsible for initializing a 16x16x16 section of terrain filled with a default "none" block type, which represents empty space. Key functionalities include:

- Getters and setters for accessing and modifying block data at specific positions.
- Integration with the `World` class to facilitate terrain generation and rendering.

#### **World Class**

The `World` class manages high-level terrain generation and composition. Its key functionalities include:

- Defining the collection of Chunks required to fill the world.
- Utilizing Perlin noise to calculate surface levels for terrain.
- Placing blocks at and below the calculated surface level to create a realistic landscape.

### Additional Notes

The `Block` class was initially designed to support multiple block types. However, as the scope of this project focused on core terrain generation, it remains largely unused in the current implementation.
