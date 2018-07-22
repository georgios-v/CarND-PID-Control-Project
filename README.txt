NOTE: In the latest version of the Linux simulator, recording is disabled. There is no entry to set the controls and hitting R does nothing. In my experiments the submitted parameters result in perfect laps.


Reflection
===========

PID
---

The PID controller comprises of 3 components:

P: error = (target value) – (sensor reading)
P stands for proportional as it gives a value that is proportional to the current error. Thus a high error will result in a large reaction, and a low error causes a small reaction. P smooths out the behavior of the controller.

I: integral = integral + error*dT
I stands for integral. I's purpose is to model and address biases. In the car example, drift will cause the PID to overshoot and oscillate due to inherent inaccuracy. It can happen that PD converges to a small error which it cannot shrink further; it will either remain static or oscillate. I is useful in those situations of small errors. These small errors are the cause of inaccuracy, caused by biases.

I is quite problematic. For one it is necessary to model the real world, but on the other hand it will cause oscillation in the absence of biases. This is true for situations where the bias suddenly diverges from the range for which the PID was tuned. Changes in ground surface material and wetness can cause this.

D: derivative = ((current error)–(previous error)) / dT

D stands for derivative. D tries to predict the future error in a simplistic way by assuming a constant step. In other words, it assumes that the difference in consecutive errors will remain the same for the immediately next timestep. Thus it calculates the delta of the current error to the previous error, then adds it to the current error to approximate the future error. 

During a single action -- move from A to B in a constant trajectory and acceleration -- D works properly since its assumption is mostly true. However, variances in trajectory will alter the effect of biases; variances in acceleration will cause a non-monotonic error progression, which invalidates the initial assumption. In other words, the stability of D is very sensitive to the environment and to the car's acceleration.


Analysis
--------

This was a frustrating project to work on. The reason was that every attempt seemed hopeless, adding to my belief that PIDs are not sufficient for the requirements of a self-driving car. They seem to be inadequate to handle the complexity of a car's motion.

I came up with several parameter combinations that work acceptably under certain conditions. Conditions being speed and drift. Changing the car's speed would result in severe oscillations, with parameters tuned for a lower speed.

Specifically I had successful tests with the following combinations:

        Kp      Ki      Kd
	 * 0.23, 0.000003, 5.3 : max speed 15
	 * 0.23, 0.03,     2.3 : max speed 30

After I implemented Twiddle, I noticed that most stable runs were done with Kp values around 0.2. So I kept it constant and tried to manually tune Ki and Kd.

My intuition is that Kd is proportional to the oscillation. Kind like it controls the agility and aggressiveness of the controller. A low Kd will result in never reaching the desired value. A high Kd overshoots quickly and then overshoots again trying to fix the deviation with an opposite reaction. This results in intense oscillation.

Ki, on the other hand, seems to be connected to speed. A low Ki is ideal for lower speeds. Otherwise, it might result in the car turning too quickly. A low Ki with a high speed might make the car not turn fast enough. For example, the chicane (left turn with sand on the right edge, followed by the only right turn) is quite steep. The Ki value that made the car fly through it at 15mph, made the car go almost straight out of the track.

I was already aware of these issues. As I'm aware of more evolved PID versions (IdealPID) with several more parameters. Regardless my experience with PIDs is that there is not a golden combination of parameters which works with variable speeds.

Unfortunately, the recording functionality is disabled in the latest version of the simulator and I couldn't include visual material.
