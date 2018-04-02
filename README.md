# terminalSimulator

dominick hera
=


to run
=

./msh


to compile
=
type 'make' to run the makeFile


description
=

- this program was designed to act as as simulated bash shell within an application that is able to execute commands as if one was using a real bash shell. For my overall algorithm, I used the provided skeleton files that handled the input and background excutions that are required for the project. After that, for the most part the program just mostly utilizes an infinite while loop whereas exiting the loop can be done by typing the command "exit" into the program.

- for specific commands in which my program was required to do additional things on top of just primarily executing the command, I set specific points before the arguments are executed to look for specific commands like having an "&" at the end of the command or looking for custom commands like "add" or "arg," creating flags with int variables and altering the arguments given into the program so that it'll properly work as expected. 

-As mentioned above, I needed to create if statements as sort of nets to catch custom commands before putting them through the rest of the program, so when certain statements were found in the arguments given by the user, I had to also alter their arguments as such to make sure that their command would be executed properly. For example, with the background execution command that is initalized with an "&" at the end of a command, I had made sure to declare a background mode flag, to let the rest of the program know that the next command should be run in the background, as well as setting that arguement in the array as null as to not confuse the rest of the program when it tries to execute the commands and doesnt understand why an ampersand is there. I also did something similar to this for the file input and output commands in which i would grab the file name and direction the file would be going ahead of time, putting them into personalised variables, setting a flag to let the program know what's going on as well as setting the arrow and everything past it as null. This was all done to give the program as little confusion as possible as it's directions and what it was supposed to do. Considering the stability of the program from my testing, I would assume that it has worked. 



additions
=

- as per the specifications, I had implemented a custom command that would provide the user with a random number between the two numbers that the user provides for example

Example: rand 10 25
Details: lists random number between two parameters.
Output: A random value between 10 and 25 is 18



known limitations
=

- shell is unable to run commands in the background.
