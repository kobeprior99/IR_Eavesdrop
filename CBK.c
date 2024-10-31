// This code will be on a dev board that will interface with putty
// Look at page 3 which describes secure
// The board sends IR packet to itself and confirmation will appear on pic that it was recieved "ACCESS GRANTED"
//Then the board will cycle the acceptable code somehow
// we will have our eavesdrop PCB copy the initial signal and send it to the dev board 
// The dev board should say "access denied"
//We would then show that the dev board can transmit the new signal and it will be accepted

//This might be challenging to code but I bet we can do it.