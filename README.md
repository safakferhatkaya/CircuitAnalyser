# CircuitAnalyser
Goal : Analyzing circuits consisting of AC, RLC or DC only resistors.

Objective : Analyzing circuits using nodal analysis method. with input from the user, for example, the number of nodes, the number of elements, the eigenvalue and type of the element.

Method : By creating mini-circuits, the impedances between the two points were found, then the total impedance was obtained by looking at the big picture and summing the impedances of the mini circuits. The current value was calculated by dividing the voltage value of the gold from the keyboard.

Result : It can calculate total impedance, current, power dissipated and resonant frequency.

Shortcomings : The shortcoming of the project is that it can solve certain types of circuits.
For example, the project cannot solve a circuit with nodes parallel to each other. It is only interested in parallelism or series within itself.
Circuit analysis was done at physics level 2, phase was ignored.
