@@[Home](Home.md) -> [Specs](Specs.md) -> [ChatInterface](ChatInterface.md)

# Introduction #

This page explains the chat interface details in aHuman and its implementation

# Library Used #

The library used to interpret AIML ( A bot language) is RebeccaAIML. It is developed based on the A.L.I.C.E specification. Library can be used to get advance usage for the bot but for now we limit it to normal chat with the end user.

# Implementation Details #

A rebeccachat.cpp class implements the functionality. There are two listeners listening on two ports. One for getting the user input at port 19000 and other to give user output on port 19001. These are separate as they are analogous to aHuman ear and mouth.

Obviously bot is not truly cognitive component.
It does not have neural interface and cannot be connected directly to other mind.

Idea is to have:
  1. non-neural inputs/outputs pure listeners - only connected to input/output topics
  1. physiology is intended to integrate sensors and effectors in primitive way - like old brain - limbic system
  1. specific physiology control can be used to create immediate response to sensor data
  1. later to chat-in sensor and chat-out effector can be created based on data from the same topics
  1. future chat sensor and effector can live in parallel with rebecca and have controls to ensure rebecca will not reply when mind is going to do that

## Method to Test ##

  * Start the server, first time it can take time as it creates the database from the aiml files.
  * Telnet or connect to server on port 19000 in one window
  * Telnet or connect to server on port 19001 in other window
  * Type anything in window connected to port 19000
  * See the output in window connected to port 19001

## Future Modifications ##

Current implementation does not include any intelligent component of aHuman but in future there will be a ear sensor which will take the user input and this sensor will be connected to brain where some intelligent logic will calculate the final output to be sent to mouth for speaking (or output in any form)

We can create the aiml based on the interactions that aHuman will hear from others, this way it will learn to respond to certain questions.

We can create a component in knowledge base where we can create aiml files by parsing text from online services like wki this will be another component where aHuman can use ready to use knowledge.

Using AIML is alos beneficial as aHuman can use plugins of various knowledge e.g we can create a aHuman who is smart in physics or other who is smart in directions.