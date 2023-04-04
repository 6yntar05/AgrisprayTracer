# AgrisprayTracer
## In development for now...
Trace .kml poly to flight-plan waypoints for agricultural drones. <br>
Usage: `./AgrisprayTracer <Path to .kml> [Path to output .waypoints file]`

## Building
### Linux:
- Install the dependencies:
    - Debian/Ubuntu/... :
      - `sudo apt update; sudo apt install cmake git build-essential minizip liburiparser-dev liburiparser1 libboost-tools-dev`
      - `sudo apt install libkml-dev`
    - Fedora:
      - `sudo dnf update`
      - `sudo dnf group install "C Development Tools and Libraries" "Development Tools"`
      - `sudo dnf install cmake extra-cmake-modules boost uriparser-devel minizip-compat minizip-compat-devel`
      - `# LibKML from repo is broken, build manually:`
        - `git clone https://github.com/libkml/libkml; cd libkml; mkdir -p build; cd build`
        - `curl https://raw.githubusercontent.com/rashadkm/minizip/master/crypt.h -o /usr/include/minizip/crypt.h`
        - `cmake ..; cmake --build . -j${nproc}`
        - `sudo cmake --install .`
    - ArchLinux:
      - `sudo pacman -Suuyy cmake extra-cmake-modules git boost-libs uriparser qt6 minizip`
      - `yay -S libkml-git`
- Build app:
    - `git clone https://github.com/6yntar05/AgrisprayTracer`
    - `cd AgrisprayTracer; mkdir build; cd build`
    - `cmake ..; cmake --build . -j${nproc}`

### Windows:
- Deprecated