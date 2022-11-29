Basic Lorenz Attractor that allows rotation with the up, down, left, right arrow keys. Tried to adjust the viewport perspective focal length.
Including the far and near camera plane clipping. But was having trouble finding suitable resources online. 

So there is clipping to some extent but it's not terrible. Rotating to the other side will eliminate it. Could probably easily be fixed by moving the camera back. 
For some reason gluPerspective() wasn't working.

Keys/Commands:

0 resets the viewport angle.
S and W changes the sigma coefficient.