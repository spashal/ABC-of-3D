
# ABC-of-3D

## How to run the code?
1. Clone this repo to your local machine
2. Make sure you have glut and glm libraries installed.
3. We will first make a build folder and then move into it so that all our makefiles reside in there. Type the below commands in your terminal

        mkdir build
        cd build
4. Next we use the cmake list given to us and create an executable

        cmake ..
        make
5. Now we can run our executable to see the screen
        
        ./Hello-World

## Controls
You shall choose to see one of the different shapes the code can render by choosing an option.

To move the figure along the 3 axes, use , <kbd>J</kbd> and <kbd>K</kbd>  for the X-axis, <kbd>L</kbd>  and <kbd>;</kbd>  for the Y-axis and <kbd>I</kbd> and <kbd>O</kbd> for the Z-axis.


Use <kbd>A</kbd> and <kbd>S</kbd> for rotating the camera along the X direction and use <kbd>D</kbd> and <kbd>F</kbd> for moving camera in the upward direction, i.e. along the Y-axis.

The camera shall always move in a circle so at to always face the origin. 
