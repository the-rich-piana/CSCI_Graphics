HW4 Projections -- Giuliano Costa

Key Bindings:

- WASD    First person movement keys
- z/x     Change FOV
- m       Toggle ortho mode
- f       Toggle first person veiw on and off (higher priority than the other two view modes)
- y          Toggle axes
- arrows     Change view angle
- PgDn/PgUp  Zoom in and out
- 0          Reset view angle
- ESC        Exit
 

Default window size is 1920x1080
Default camera view is perspective with an FOV of 70.
Scene is just some spheres and planes from HW3. Fixed my Znear and Zfar clipping planes by setting them to float values based off a stackoverflow post. Window resizing doesn't affect it which is great. 

Time to complete assignment ~5 hours. FOV wasn't that difficult but fixing the
clipping planes proved to be time consuming. Ideally I'd like to include
mouse input, but from my reading that is a task requiring multiple additional
functions. 