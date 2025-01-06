# Minecraft from Open-GL
This was a project I completed for my graphics programming class. I recreated the way that Minecraft generates blocks and then used perlin noise to recreate the landscape generation. This document will go over this project at a high level and then dive into development details.

## Overview
To generate blocks, this application will create cubes and then apply a texture. That texture is wrapped around the cube in the same way that Minecraft does, an example of how this looks is shown below. The terrain is processed in Chunks. In Minecraft, Chunks are 16x16 squares of terrain that go from the lowest vertical height to the highest. In my project, Chunks are only 16x16x16; I did this to limit memory used during terrain generation. For each chunk generated, the terrain generation defines a surface level using Perlin Noise and then fills everything below that level. The only supported block is the dirt block, but it has the capability to support multiple types of blocks. 

## Technical 
