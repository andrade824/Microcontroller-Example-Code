PWM Servo Example
============================

This example shows how to initialize and use the PWM module inside of the Tiva to control a servo. You'll notice some defines (PWM_LEFT, etc.) up top with seemingly random values. These defines are the exact values needed to control the servo I own. Every servo considers "far left", "center", and "far right" different values, so you'll need to modify these values to fit your own servo accordingly.