# AgrisprayTracer
## In early development for now...
---

## Building
### Linux:
- Install the dependencies:
    - `sudo apt update; sudo apt install cmake git build-essential minizip liburiparser-dev liburiparser1 qt6-base-dev qt6-base-dev-tools libboost-tools-dev`
- Clone repo and submodules:
- `git clone https://github.com/6yntar05/AgrisprayTracer`
- Build LibKML by hands: (because too old cmake ver.) from submodule:
    - `git submodule init; git submodule update`
    - `cd ./external/LibKML/`
    - `mkdir build; cd build`
    - `cmake ..; cmake --build . -j12`
    - `sudo cmake --install .`
- Build app:
    - `cd ../../../ # Now you in project dir`
    - `mkdir build; cd build`
    - `cmake ..; cmake --build . -j12`
- `./AgrisprayTracer <Path to .kml> [Path to output .waypoints]`
  

### Windows:
- Deprecated