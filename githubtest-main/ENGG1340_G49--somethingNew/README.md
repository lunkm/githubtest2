# Customizable Minesweeper - ENGG1340_G49
  * Welcome to the Customizable Minesweeper! This game is a text-based Minesweeper, try our game by setting your own board!
  *  3 Minute Demo Video:
https:// 

  
## Team Members:
  * Park Chanhyuk (3036086804)
  * Son ()
  * Kim ()
  * Jung ()

### How to Play
1.	Compile the program and run the executable.
2.	Set the board size 
3.	Click the cell to reveal 
4.	If 

<br/>

### The introduction and rule of the game


 
## Moves:


<br/>

### **Game Components**
1.	main.cpp: The `main.cpp` file contains the main game loop and logic.

2.	board.h: The `board.h` file contains 

3.	colors.h: The `colors.h` file

4.	display.h: The `display.h` file 

5.	score.h: The `score.h` file 
<br/>

### **Dependencies**
* C++ Standard Library
* `<iostream>`
* `<cstdlib>`
* `<ctime>`
* `<string>`
* `<vector>`
<br/>

***
## Components

### Main.cpp
> Running the game and supporting file input and output

|Name|Type|Type|
|:-:|:-:|:-:|
|gameMap|Map|Represents the game map|
|player1|Player|Represents the first player|
|player2|Player|Represents the second player|
|counter|int|Counts the number of turns|
|turn|int|Indicates whose turn it is (0 for player1, 1 for player2)|
|TicketResult|int|Stores the result of the ticket roll|
|input|string|Stores user input|
|tickets|vector<int>|Stores the remaining tickets|
|malVector|vector<string>|Stores the list of Mal names to be displayed|

### Functions.cpp
> various functions that we used to run the game

|Name|Type|Purpose|Parameter|
|:-:|:-:|:-:|:-:|
|save_game|void|Saves the game state to a file|string &filename, Map &gameMap, Player &player1, Player &player2, int counter|
|load_game|bool|Loads the game state from a file| string &filename, Map &gameMap, Player &player1, Player &player2, int &counter|
|askWhichTicket|int|Asks the user which ticket they want to use| vector<int> &tickets|
|askMalMovement|vector<string>|Asks the user which mal they want to move| int turn, Player one, Player two|
|getTicket|int|Generates and returns a random ticket| N/A|
|getTicketName|string|Returns the name of a ticket based on the ticket number|int ticketNum|
|move_or_carry_Mal|void|Moves or carries a mal based on the malSign string| Player &player, int playerNum, int malSelect, string malSign, int TicketResult, Map &gameMap, int pRow, int pCol, int row, int col|
|killMal|void|Kills an opponent's mal based on its location| Map &gameMap, Player &opponent, int killerPlayerNum, int row, int col|
|moveMalDisplay|void|Updates the game map after moving a mal| Map &gameMap, string malSign, int previRow, int previCol, int row, int col|
|addMalDisplay|void|Adds Mal display when loading the saved game| Map &gameMap, Player player1, Player player2|
|PrintExplain|void|Prints out the explanation of the location| int row, int col|


### Map.cpp
> This code defines a `Map` class that manages a board game map, handling player locations, mapping between different coordinate systems, and updating the game board's visual representation.

|Name|Type|Type|
|:-:|:-:|:-:|
|TicketResult|int|Stores the result of the ticket roll|
|input|string|Stores user input|
|malSelect|int|Stores the selected Mal index|
|tickets|vector<int>|Stores the remaining tickets|
|malVector|vector<string>|Stores the list of Mal names to be displayed|

### The Coding Requirements
>Coding requirement demonstration

|Requirenment name|Code|Explanation|
|:-:|:-:|:-:|
|Generation of random game sets or events| <img src= "https://user-images.githubusercontent.com/125568011/235907659-8400837f-6e08-4ad7-a468-c2c3dc0ca04e.png" width = "900px">|The getTicket() function simulates a random distribution of tickets with different rarity levels by generating a random integer and using conditional statements to determine the ticket type, with probabilities skewed towards more common types.|
|Data structures for storing game status|<img src= "https://user-images.githubusercontent.com/125568011/235909056-39aedd6a-aa30-4b67-84d3-e44bdbd8376a.png" width = "900px">|This code initializes a Player object with a name and three Mals, represented as a custom data structure, storing their initial positions and game states in a vector called Mals. This Player Class is used in the main function to store status of each player.|
|Dynamic memory management|<img src= "https://user-images.githubusercontent.com/125568011/235911029-5ba1024a-b11c-4a47-8085-e65ea2f1a16d.png" width = "500px">| This code reads game names from a file into a vector of strings, dynamically resizing the vector as needed to accommodate the names, and then prints the saved game names to the console.|
|File input/output (e.g., for loading/saving game status)|<img src= "https://user-images.githubusercontent.com/125568011/235911571-ff747506-4078-4a04-b062-52692ef5f630.png" width = "900px">|This code appends a given filename to the "Games.txt" file, using file output operations to save game names persistently, while handling potential file opening errors.|
|Program codes in multiple files|<img src= "https://user-images.githubusercontent.com/125568011/235912113-4183c594-286e-449d-ada9-00414f6bb9b1.png" width = "900px">| Our group have divided our code to multiple files in terms of their purposes.|
|Proper indentation and naming styles|<img src= "https://user-images.githubusercontent.com/125568011/235912686-bb9e2895-c413-4753-a56a-ff7033f4a146.png" width = "900px">| We have done proper indentation and naming styles for functions, so the names represent their function in the code.|
|In-code documentation|<img src= "https://user-images.githubusercontent.com/125568011/235913947-d72d9b1b-585f-4fe3-874c-09cb4e10e31a.png" width = "900px">| we have explained each code to help readers to understand the code.|


### How to Compile and Run
> Type "make game" in the same directory
> Type "./game" to launch the game
> Type "make clean", if you want to delete saved games.
