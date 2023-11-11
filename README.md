# opengl-startup-linux
This is startup project for OpenGL on LINUX Fedorra. 

Clone the project. 

Install needed dependecies...

    sudo dnf/apt-get install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev libglew-dev 
Build with CMake or to run it manually without cmake

    g++ main.cpp -o main -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

    
    
