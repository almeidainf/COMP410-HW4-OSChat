LOYOLA UNIVERSITY CHICAGO
COMP 410-001 - OPERATING SYSTEMS - FALL 2014

Tiago de Almeida - tdealmeida@luc.edu
1394611

Homework #4


OSChat - A simple terminal chat application implemented using named pipes.

This project implements a very simple terminal chat program that allows communication between two terminal windows. It was implemented using named pipes and the goal of this implementation is to learn and practice how to use them.

The program is not supposed to be complex and bug-free, therefore there are some knows issues, for example:
- If two users enter the chat using the same username, they will not receive messages.
- If a user receives a message while he/she is writing a message, his/her message will be messed up.

Besides specific issues, however, the program works well and performs what it is supposed to. The goal of learning and practicing the use of named pipes was successfully reached.


The project was implemented and tested in the following environment:
Programming Language: C
Compiler: GCC 4.8.1
Operating System: OS X Yosemite 10.10.


HOW TO:

- Build:
./do

- Run
./chat

- Chat:
- The program will ask you for a username. Use one word names (do not use spaces);
- Type your messages and hit ENTER to send them;
- Type "exit" to leave the chat (lower case);
