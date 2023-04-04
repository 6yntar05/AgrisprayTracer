# AgrisprayTracer
## In early development for now...

## Building
### Linux:
- Install the dependencies:
    - Debian/Ubuntu/... :
      - `sudo apt update; sudo apt install cmake git build-essential minizip liburiparser-dev liburiparser1 libboost-tools-dev`
      - `sudo apt install libkml-dev`
    - Fedora:
      - `sudo dnf update`
      - `sudo dnf group install "C Development Tools and Libraries" "Development Tools"`
      - `sudo dnf install cmake extra-cmake-modules libkml libkml-devel minizip-compat minizip-compat-devel`
    - ArchLinux:
      - `sudo pacman -Suuyy cmake extra-cmake-modules git boost-libs uriparser qt6 minizip`
      - `yay -S libkml-git`
- Build app:
    - `git clone https://github.com/6yntar05/AgrisprayTracer`
    - `mkdir build; cd build`
    - `cmake ..; cmake --build . -j${nproc}`
- `./AgrisprayTracer <Path to .kml> [Path to output .waypoints]`

### Windows:
- Deprecated