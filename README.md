# Prototype
2D game engine.

Prototype is a simple 2D game engine. As of yet it is in a very 
rudimentary stage. This project
is solely developed as a hobby and learning experience.

Prototype utilizes the SDL library.


Structure:
/Assets:
This folder containst all assets for the project. Textures, roomfiles, etc.

/src:
This folder contains all source code. Header and corresponding source
files are placed in the same folder.

  /data_structures:
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
  Home of "Prototype.cpp"
    

//Arne
