# Prototype

Prototype is a simple 2D game engine. As of yet it is in a very 
rudimentary stage. This project is solely developed as a hobby 
and learning experience.

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

## Contributing

As of yet, I, Arne Stenkrona, am sole contributor to the repository.

## Authors

* **Arne Stenkrona** 

## Pictures
![In-Game Example](https://raw.githubusercontent.com/ArneStenkrona/Prototype/master/Examples%20Images/prtExample1.PNG)
![Editor Example](https://raw.githubusercontent.com/ArneStenkrona/Prototype/master/Examples%20Images/prtExample2.PNG)
