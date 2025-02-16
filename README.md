# Steering Project

### After cloning the project

1. Right click on the .uproject file and do "Generate Visual Studio project files".
1. Open the .uproject file, it will ask you rebuild, select "Yes"
1. Unreal should now start


### How to run

#### Through Unreal

You can run in unreal with the green play button at the top of the viewport, and you can also run in a separate window by clicking on the 3 dots close to the play button and selecting the 2nd option "New Editor Window (PIE)".

<!-- CANT PUSH IT

#### Standalone

In the project files, you will find an Executable folder. In Executable/Windows you will find the .exe to run the project without unreal. Beware, it's in fullscreen and can't be closed without Alt+F4 (sorry). -->

### How it works

- You can choose the steering mode in the bottom left by clicking on it. 
- Clicking on the field will set the new target. 
- If the vehicle (the cone) runs out of the window, either restart or make it come back with a seek or arrival.
- For Pursuit : the new character that appears is the one pursuing you (the cone). Same for Evade, he's the one evading you.
- For Circuit, One Way and Two Way : clicking will add points to the circuit, it can be done anytime, the vehicle will also not wait. If you wish to make the vehicle restart the circuit or one way or two way, select the mode in the bottom left again. The circuit is saved between modes, only making the vehicle restart. If you wish make a new circuit, click the button in the bottom right to forget the saved circuit.

### Known issues

- There is a stutter in the movement of the vehicle when choosing the Pursuit or Evade mode sometimes (velocity falling back to 0 when changing mode).
- There are no indicators for the target or for circuit points, making it hard to know the exact target location sometimes.
- The vehicle and character can go out of bounds making it tedious to control sometimes. At least they don't fall into the void and can come back.