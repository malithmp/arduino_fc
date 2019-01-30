## Description
Simple flight controller based off arduino. This contains 2 elements. 
1. PPM Decoder:
   Decode 2 PPM signals (Utilizing the external interrupts for best accuracy) on pins 2 and 3.
2. Flight Controller:
   Combine the 2 singals to control the Ailerons to both roll and lift

## PPM Decoding logic
   A   B         C
    ____          __
   |    |        |
   |    |        |
---     ---------
   <-t->
   <------T----->

T is the pulse width. For the FS-iA6B Receiver, this is 20ms
t is the pulse period. This changes based on the input

t goes from x --> y where x > 0 and y < T

To decode this signal:
- We first setup pin change interrupts for a given external interrupt pin
- If the pin went from LOW to HIGH (Position A) we note down the time as `pin_x_start`
- If the pin went from HIGH to LOW (Position B) we note down the time `pin_x_end`
- Now we can calcualte the pulse period using `pin_x_end - pin_x_start`
-- Note, in the code we dont use the exact variable names.
