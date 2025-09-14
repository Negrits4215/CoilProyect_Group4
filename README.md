How to Build and Run the Project on Windows
Requirements

Git for Windows
GCC for Windows

Steps

1. Open CMD
Press Win + R, type:
  cmd

and press Enter.

2. Navigate to the folder where you want to clone the repository
Example:
  cd C:\Users\YourName\Desktop

3. Clone the repository from GitHub
Replace <URL> with the repo link:
  git clone <URL>

4. Enter the project folder
  cd CoilProyect_Group4

5. Compile the project with GCC
  gcc -Wall -o programa.exe main.c constants.c backend/bird.c backend/game.c backend/pipes.c frontend/display.c frontend/mainMenu.c frontend/topScore.c

6. Run the program
  programa.exe
