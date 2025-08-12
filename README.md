<img width="150" height="150" alt="image" src="https://github.com/user-attachments/assets/3f125639-dbb8-41a5-984f-b51b4bd35a0d" />

## 📍 Mandatory Part
- The program should be capable of setting the floor and ceiling colors with two different colors.
- It displays the image in a window and follows these rules:
- Left and right arrow keys allow the user to look left and right in the maze.
- W, A, S, and D keys allow movement through the maze.
- Pressing ESC should close the window and exit the program cleanly.
- Clicking the red cross in the window frame should close the window and exit the program cleanly.
- The use of miniLibX images is recommended.

https://github.com/user-attachments/assets/2cea9beb-9b6e-4057-bc44-a704298dd409

## ⭐ Bonus Part

- Wall collisions.
- A minimap system.
- Doors that can be opened and closed.
- Rotating the viewpoint with the mouse.
  
https://github.com/user-attachments/assets/a329a61f-a8a8-418c-bd25-474c950537f6

## 🗺️ Map Requirments
- The program takes a scene description file with the .cub extension as its first argument.
- The map should consist only of 6 possible characters: 0 for an empty space, 1 for a wall, and N, S, E, or W for the player's starting position and orientation.
- The map should be enclosed/surrounded by walls; otherwise, the program should return an error.
- Each element (except the map) has a type identifier (composed of one or two characters), followed by specific information for each object in a strict order.
