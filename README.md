# Prototype
2D game engine.

Prototype is a simple 2D game engine. As of yet it is in a very 
rudimentary stage. This project is solely developed as a hobby 
and learning experience.

This repository is based on a visual studio project. While
you could get it to run without VS studio, using it will
save a lot of headache.
Prototype utilizes the SDL library. It also uses SDL_mixer for sound.


Structure:
/Assets:
This folder containst all assets for the project. Textures, roomfiles, etc.

/src
This folder contains all source code. Header and corresponding source
files are placed in the same folder.

  /data_structures
  As the name entails, sources for data-structures are stored here.
  Currently the only example is the quadTree class, which stores
  colliders in a quadTree in order to quickly find nearby colliders
  necessary to examine for potential collision.
  
  /GameObject
  This folder contains source code relating to gameObjects.
  A GameObject is the basic entity of the game engine. A GameObject
  in and of itself does not do too much. Object of type Component
  can be added to a GameObject in order to provide functionality.
  Examples of components are "position", "velocity", "renderer"
  etc.
  
  /main
  Home of "Prototype.cpp", which contains the main method.
  
  /math
  Source code relating to more general, mathematical entities.
  Examples include a timer "lTimer", or geometric objects. One can
  question whether or not a timer and a polygon belongs in the same
  folder.
  
  /System
  This folder contains more basic, necessary code to make the
  program run. Home of subfolders "/game", which contains things
  relating to the game aspects of the engine, "/graphics", "/GUI",
  "/IO", all of which are self-explanatory, and "/physics", which
  is the home of the physics engine. The physics engine works
  in tandem with the game. As such it is natural to wonder if
  the folder structure should be changed to better reflect their
  relationship.
  
  /Tools
  This folder is used for any general tools that might come in
  handy in development. For example, "stringTools.cpp" which has
  some parsing implemented.
  
  /World
  This folder contains code relating to the representation of the
  game world. It is home to entities such as "room.cpp" and "Tile.cpp"
  which make the building blocks of the game world. The editor is
  also stored here. Separating these from the "/game"-folder might
  seem questionable to some. 
  
 
 
Editor:
The editor is in a very rudimentary stage. It is dependent on a
custom file format to load rooms into memory from files which 
can then be edited and saved. Here follows a specification
of the file format:
  Typically, the extension ".room" is used.
  First line contains an integer representing the tileMapIndex
  of the room. 
  Second line contains an integer representing the backgroundIndex.
  
  Then follows a matrix containing cells, representing tiles, of the form 
  "[Int| Bool| <(Point),..>]" where 
  "Int" denotes an integer value specifying the index of the tileTexture, 
  "Bool" denotes either "T" or "F" specifying wether the tile has a collider, 
  "T", or not, "F",
  "<(Point),..>" denotes a vector of points of arbitrary length describing 
  the polygon used for the collider. 
  
  A cell can also be empty which is denoted by "[N]", where "N" stands for
  "Null".
  
  A line represents a row of tiles and linebreak denotes a new row.
  
  
  The WASD keys moves the room inside the editor around. Holding leftshift
  while using WASD will instead scroll through the available tiles.
  
  
  
    

//Arne
