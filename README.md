# drink-machine
Make-Ohio 2021 Mixed Drink Machine

This is the Arduino code for the mixed drink machine made for the 2021 Make-Ohio event.

10 drinks are offered using a combination of 6 ingredients. These ingredients are:
Vodka, Whiskey, Champagne, Orange Juice, Lemonade, and Tonic Water.

The machine first checks for an empty glass with an ultrasonic sensor, then allows the user to select their drink using a rotary encoder if an empty glass is detected.
The LCD screen shows all options and updates accordingly to user input.
Finally, the system prompts the user to remove their drink, and then it starts over again by checking for a new empty glass.
