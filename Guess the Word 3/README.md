# Guess the word Exercise 3
## Introduction
Refer to exercise 2. It’s the same thing but the only changes are that player 2 can’t enter the same letter twice, and if they guess all the letters, they must guess the word.
## Changes
I just added a new string (I made a string instead of list because its an array of chars and it has the ability to use .find() on it which returns if it finds a char) which is added onto when a new letter is used.
But first the program checks if the new letter added isn’t already in the string. Then at the end of the while loop, if every single letter in the secret word was found in the letterlist, then it automatically makes the player guess the words.
