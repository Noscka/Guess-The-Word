# Guess the word Exercise 1
## Introduction
The program is a simple and basic starting point of “guess the word” or more popularly known as hang man. So far, the program allows for Player 1 to input a word. Player 2 then has 3 letter guesses that tell the user information like how many letters are in the word. After those they must guess the full word.

## How it works
The program is pretty simple, and it uses for loops in combinations with while loops. The first use of a while loop is when Player 1 inputs a word, the while loop is used to make sure that the player inputs only 1 word (so no whitespaces).
After this the next loop is a for loop for Player 2. It is a for loop that goes 3 times, inside the for loop is a while loop, this just validates that the input is either “show” or a single letter. The show command is used for testing, showing and etc. it just shows the secret word in case the tester forgets or any other reason.
And at the end, Player 2 just has to guess the word and if they get it right, they win, if not. Player 1 wins. 
## Functions
### LowerString
Functions made to just lower strings as c++ only has the ability to lower single chars. <br />
Inputs: <br />
	String Input <br />
Return: <br />
	String Ouput <br />
