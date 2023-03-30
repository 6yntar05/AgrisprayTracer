# AgrisprayTracer
## In early development for now...

## Building
### Linux:
- Install the dependencies:
    - Debian/Ubuntu/... :
      - `sudo apt update; sudo apt install cmake git build-essential minizip liburiparser-dev liburiparser1 libboost-tools-dev`
      - `sudo apt install libkml-dev`
    - ArchLinux:
      - `sudo pacman -Suuyy cmake extra-cmake-modules git boost-libs uriparser qt6 minizip`
      - `yay -S libkml-git`
- Build app:
    - `git clone https://github.com/6yntar05/AgrisprayTracer`
    - `mkdir build; cd build`
    - `cmake ..; cmake --build . -j12`
- `./AgrisprayTracer <Path to .kml> [Path to output .waypoints]`

### Windows:
- Deprecated