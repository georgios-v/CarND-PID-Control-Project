Reflection
===========

This was a frustrating project to work on. The reason was that every attempt seemed hopeless, adding to my belief that PIDs are not sufficient for the requirements of a self-driving car. They seem to be inadaquete to handle the complexity of a car's motion.

I came up with several parameter combinations that work acceptably under certain conditions. Conditions being speed and drift. Changing the car's speed would result in severe oscillations, with parameters tuned for a lower speed.

Specifically I had successful tests with the following combinations:

        Kp      Ki      Kd
	 * 0.23, 0.000003, 5.3 : max speed 15
	 * 0.23, 0.03,     2.3 : max speed 30

After I implemented Twiddle, I noticed that most stable runs were done with Kp values around 0.2. So I kept it constant and tried to manually tune Ki and Kd.

My intuition is that Kd is proportional to the oscillation. Kind like it controls the agility and aggressiveness of the controler. A low Kd will result in never reaching the desired value. A high Kd overshoots quickly, and then overshoots again trying to fix the diviation with an opposite reaction. This results in intense oscillation.

Ki on the other hand seems to be connected to speed. A low Ki is ideal for lower speeds. Otherwise it might result in the car turning too quickly. A low Ki with a high speed might make the car not turn fast enough. For example the chicane (left turn with sand on the right edge, followed by the only right turn) is quite steep. The Ki value that made the car fly through it at 15mph, made the car go almost straight out of the track.

I was already aware of these issues. As I'm aware of more evolved PID versions (IdealPID) with several more parameters. Regardless my experience with PIDs is that there is not golden combination of parameters which works with variable speeds.

Unfortunately the recording functionality is disabled in the latest version of the simulator and I couldn't include visual material.
