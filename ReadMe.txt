Just type "make", to see the project component, "hangman game"

to see exercise components run
"make -f exerciseMakeFile"

SECRET WORD GAME
This game makes a call to system in order to clear the terminal screen
This has worked on flip for me but if it gives you hassle for any reason at all then run it in simple mode

simply run the program with the -s argument
"./hangman -s"  and it will run with an alternate clear screen function

Additionally this game uses a dictionary file to restrict input of secret word
If you would like to enter your name or other proper nouns you can run the program with no dictionary
simply use the -nodict command line argument
"./hangman -nodict"

Dictionary file proveded by oracle
http://docs.oracle.com/javase/tutorial/collections/interfaces/examples/dictionary.txt

compile and enjoy
Brandon Swanson