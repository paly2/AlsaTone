# AlsaTone

AlsaTone is a sine wave sound generator.

### How to compile it ?

Just write in a console :  
`sudo apt-get install libasound2-dev`  
`git clone https://github.com/paly2/AlsaTone.git`  
`make`

### How to run it ?

This is the syntax of the program :  
`./alsatone [frequency, default 600Hz] [duration, default 3 seconds]`  
Then you'll hear the sound !

Note: You can't hear sounds over 20,000Hz (ultrasounds) and under 20Hz (infrasounds), but them are still generated (except if your speakers can't generate them) !
