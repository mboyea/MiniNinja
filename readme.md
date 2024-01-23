MiniNinja
===
A small C++ game project.
---
This is a 2D game built using C++ and SDL2. It is an unfinished project from highschool.

I wrote this game engine with homemade game console, homemade scene serialization & deserialization, a homemade collision system (with broad phase and narrow phase collision), a homemade entity management system, audio support, texture support, and font support.

I never got around to actually making the game, but building this low-quality game engine was fun and taught me a lot!

### Fork & Clone This Repository
* [Fork this repository](https://docs.github.com/en/get-started/quickstart/fork-a-repo#forking-a-repository).
* [Clone that repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository#cloning-a-repository) to a folder on your computer, which will be referred to as `root`

### Install Dependencies
* Fork & Clone This Repository.
* Install gcc. [Windows](https://sourceforge.net/projects/mingw/) [Arch](https://wiki.archlinux.org/title/GNU_Compiler_Collection)
* Install make. [Windows](https://gnuwin32.sourceforge.net/packages/make.htm) [Arch](https://man.archlinux.org/man/make.1)
* Ensure each of the above command line tools are accessible by PATH. [Windows](https://www.computerhope.com/issues/ch000549.htm) [Arch]()
* TODO: install dll to `root/lib`

From here, everything should be installed to compile this software.

### Run Scripts
To run a script, type the command into a terminal within `root`.

| command | description |
|:----------- |:----------- |
| `make` | compile the object files into /build/ and link application into /bin/ |
| `make clean` | remove all compiled object files |

### Contribute
Unfortunately, this project doesn't support community contributions right now.
