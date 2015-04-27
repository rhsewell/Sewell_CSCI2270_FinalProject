# Sewell_CSCI2270_FinalProject
# Robert Sewell

PROJECT SUMMARY
This project will use a binary search tree to implement a guessing game (similar to 20 questions). The program will initially have a few simple questions built in that it will ask the user. The user will respond yes or no to each until the program makes a guess. If the guess is incorrect the program will ask for the user's answer and for the user to input a question to differentiate between what it guessed and the user's answer. The program will then add the question and answer to the tree and to the text file, and then ask to play again. In this way the game will be able to update with each playthrough. 

HOW TO RUN
The program will automatically create the binary tree from the given QuestionFile. In order for this to happen QuestionFile.txt must be located in the same folder as main.cpp. Instructions will desiplay in the command window, and the user will see a main menu. to select a choice, enter the number coresponding to the menu option.

1. Play Game
The program will begin asking yes or no questions from the binary tree. To answer yes enter y or enter n for no. At the end of the tree path the program will make a guess; if the program wins the user will be taken back to the menu, but if it loses it will ask for the user's answer, a question to differentiate between the computer's guess and the user's answer, and then if the user's answer would be a yes or a no to this question.
Sample:
"Are you thinking of a box?"
n
"You win!"

"What were you thinking of?"
bread
"What is a question to differentiate between a box and bread?"
Can you eat it?
"Would your answer be a yes or no to this question?"
y
"Thank you for adding to my knowledge!"

The question and answer are then added to the tree and the text file.

2. Change a Question
This asks for the question to search for and what it should be replaced with. The replaced question still must make sense in the context of it's parent and also the following questions or answer, in order to prevent confusion. If the question is found it will change the node's question at tell the user it was found. It it was not found it will tell the user and nothing will be changed.
Sample:
"Enter the question to be changed?"
Is it a mammal?
"What should it be changed to?"
Is it a feline?
"Question found and changed."

2. Change a Question
The same method is called for finding a question and the same results occur.

4. Print Question and Answer Base
Prints all questions and answers from the top of the tree down when selected. No user input required.

5. Quit
Main program loop exits and the destructor is called, then program is terminated.

DEPENDENCIES
Must have the file with questions (QuestionFile.txt) in the same folder as main, in order for the tree to built upon running.

SYSTEM REQUIREMENTS
No system requirements.

GROUP MEMBERS
Robert Sewell

OPEN ISSUES/BUGS
Currently, there are no known issues; however there are several improvements that I am looking to make. As of now the text file is only updated after the user wins instead of also happening when the user changes a question or an answer (as only the tree in that instance is changed), so it would be nice to have another function to do this. Also, I'm questioning if it would be logical to add an option to delete a node, as the very nature of this requires each child node to be reliant on only its parents question and cannot be moved to some other question without checking to see if it is a logical placement, but if someone can think of a way to do this that makes sense, that could be added. Lastly, I'm hoping to add a method to insert a question into the tree given it's parent and wether it would be a yes or a no to it's parent's question.