// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(mainLoop)
    @KBD
    D=M
    @writeBlack
    D;JGT
@mainLoop
0;JMP

(writeWhite)
    // Initial Setup
    @SCREEN
    D=A
    @counter
    M=D

    // Set memory to all 0's
    @counter
    A=M
    M=0

    (fillWhite)
        // Fill white unless key is pressed
        @KBD
        D=M
        @writeBlack
        D;JGT

        // Increment
        @counter
        M=M+1

        // Set memory to all 0's
        A=M
        M=0

        // Stop if memory is filled, aka counter is at @24575
        @counter
        D=M
        @24575
        D=D-A
    @fillWhite
    D;JNE
    
    @mainLoop
    0;JMP


(writeBlack)
    // Initial Setup
    @SCREEN
    D=A
    @counter
    M=D

    // Set memory to all 1's
    @counter
    A=M
    M=-1

    (fillBlack)
        // Start filling unless key is not pressed
        @KBD
        D=M
        @writeWhite
        D;JLE

        // Increment
        @counter
        M=M+1

        // Set memory to all 1's
        A=M
        M=-1

        // Stop if memory is filled, aka counter is at @24575
        @counter
        D=M
        @24575
        D=D-A
    @fillBlack
    D;JNE

    // loop until key is unpressed
    (waitForKeyUnpressed)
        @KBD
        D=M
        @writeWhite
        D;JEQ
    @waitForKeyUnpressed
    0;JMP





