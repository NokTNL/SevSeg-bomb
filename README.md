# SevSeg-bomb

🎥 Watch demo on youtube ⬇️

<a href="https://youtube.com/shorts/pB1G3svIqNQ" target="_blank">
 <img width="600" alt="Watch demo on Youtube" src="https://user-images.githubusercontent.com/94875599/162025374-a5412533-6679-4aec-b738-56c69cf65bc4.png">
</a>

## Inspiration
One day I was playing with a 4-digit seven-segment display and decided to make a "bomb" that you will find in movies. Luckily I did not connect it to a detonation device... but still freaked my flatmates out.

## Technical details
Basically the Arduino display a countdown timer on the sevseg and moves the servo when the timer is up. Loads of DuPont wires! Used the [SevSegShift](https://github.com/bridystone/SevSegShift) library for displaying the numbers.

To try it at home:
1. Grab all the components needed as stated in `sketch` and connect them properly. These are widely available (e.g. in an Arduino starter kit)
2. Download this repo into a folder and install the `SevSegShift` and `Servo` libraries in your Arduino IDE. Upload the `.ino` into your Arduino.
