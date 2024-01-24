MiniNinja
===
A small C++ SDL2 game project.
---
This is a 2D game built using C++ and SDL2. It is an unfinished project from highschool.

The game engine contains a console, a layered scene management system, scene serialization & deserialization, and a collision system (with broad phase and narrow phase collision). The game renders entities in a window, responds to keyboard input, plays audio, manages textures, and supports fonts via SDL2.

I never got around to actually making the game, but building this low-quality game engine was fun and taught me a lot!

### Install Dependencies
* Install GCC. [Win](https://sourceforge.net/projects/mingw/) [Mac](https://stackoverflow.com/questions/10265742/how-to-install-make-and-gcc-on-a-mac) [Arch](https://wiki.archlinux.org/title/GNU_Compiler_Collection)
* Install make. [Win](https://gnuwin32.sourceforge.net/packages/make.htm) [Mac](https://stackoverflow.com/questions/10265742/how-to-install-make-and-gcc-on-a-mac)
* Install Bash or an equivalent linux shell. [Win](https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/)
* Ensure each of the above command line tools are accessible by PATH. [Win](https://www.computerhope.com/issues/ch000549.htm)
* [Clone this repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository#cloning-a-repository) to a directory on your computer. That directory will be referred to as `root`.
* TODO: install all dll to `root/lib`

From here, everything should be installed to compile this software.

### Run Scripts
To run a script, type the command into a linux shell terminal within `root`.

| command | description |
|:----------- |:----------- |
| `make` | compile the object files into `/build` and application files into `/bin` |
| `make clean` | remove all compiled files |

### Contribute
Unfortunately, this project doesn't support community contributions right now. Feel free to fork, but be sure to read the license.
