![In-Game Example](https://raw.githubusercontent.com/ArneStenkrona/Prototype/master/Examples%20Images/prototypeLogo.PNG)
![In-Game Example](https://raw.githubusercontent.com/ArneStenkrona/Prototype/master/Examples%20Images/example1.png)

# Prototype

Prototype is a simple 2D game/game engine. As of yet it is in a very 
rudimentary stage. This project is developed for personal educational purposes.

It is written in C++ and uses [SDL](https://www.libsdl.org/).


## Getting Started

Clone the repository and open the solution in *Visual Studio 2017*. 
This can be done directly in *Visual Studio*

* Open Visual Studio 2017

* Using the tabs, navigate into File->Open->Open From Source Control

* In the Team Explorer panel, find the clone option and enter the repository URL

* Open the solution and set the platform to preferred architecture

Alternatively, the repository can be cloned in the command line

```
 $ git clone https://github.com/ArneStenkrona/Prototype.git
```
The solution can then be opened in *Visual Studio*.

It is also recommended to set the solution explorer to 'Show All Files' to get a
proper view of the file hierarchy. The game will run more slowly if solution is set to
'debug'. Set solution to 'release' if performance is slow.

## Testing

Testing is done with a Visual Studio Unit Test Project. This project is found in the folder *Prototype Test*. 
To run the tests, open the solution in *Visual Studio*

* Open Visual Studio 2017

* Using the tabs, navigate into Test->Test Settings->Default Processor Architecture->[Current Solution Platform]

* navigate to Test Explorer

* Select Run All to run all tests

## Built With

* [SDL](https://www.libsdl.org/) - Layer for graphics, sound and multimedia
* [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/) - Sound effects and audio playback
* [Tiny Soundfont](https://github.com/schellingb/TinySoundFont) - Used in soundfont rendering and midi playback

## Authors

* **Arne Stenkrona** 

## Current State
I began development on this engine during my first year as a computer science student.
The project was developed in my spare time as a learning experience. Knowing what I do know I would have done many things differently. As of now I've put development on hold. While it is not in a finished state, you can still play around in the editor to build maps. The game is hardcoded to run the map in 'Assets/Rooms/TEST.room'.
![Editor Example](https://raw.githubusercontent.com/ArneStenkrona/Prototype/master/Examples%20Images/example2.png)

## What I've Learned
* If you don't start out using unit tests it will be a serious pain to add them.
* Game engine development is a big undertaking. Reading a book or two prior to starting would've saved me time and given me a more optimized and easily maintainable system.
* While it's fun to implement things yourself, reinventing the wheel is rarely practical.
* The dangers of pushing directly to master is best left to hardcore adrenaline junkies.
