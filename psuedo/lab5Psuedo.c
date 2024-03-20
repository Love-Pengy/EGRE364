/*
*   CONCEPTS: 
*       + The full step, half step, or fractional steps determine how far the motor
*           moves for each pulse 
*       + Full step has a 90 degree turn for each pulse
*       ---------------
*       | A   B  !A  !B
*       | 1   1   0   0
*       | 0   1   1   0
*       | 0   0   1   1
*       | 1   0   0   1
*       _______________  
*       + for full step you want both phases next to each other active in the same pole, if you want the motor to go in reverse switch the pole tha tthe states are in  
*
*       + Half step has a 45 degree turn for each pulse
*       + combination of wave and full step.  It swaps back and foth between the two. THe full step to get the magenet halfway and then the wave step to get it all the way towards a pole
* */
