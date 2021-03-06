## Mini Drawing Robot Dev Log

**2021-03-06**

I've ordered some small bearings for  another version of the hardware.

I stumbled on designs by [Andrés Zibula](https://andres-zibula.github.io/) : [1st](https://www.youtube.com/watch?v=B5Zup7bcReA) is a wonderful jumble of wooden dowels & rubber bands, [2nd](https://www.youtube.com/watch?v=a46DMy_3xc4) pretty convincing, using 3D printed parts. Those both use servos in the same kind of configuration I'm after. For a [3rd](https://www.youtube.com/watch?v=4yyozFsPI_I) he uses stepper motors and an STM32.

He's done the [inverse kinematics code](https://github.com/andres-zibula/Parallel-SCARA-Plotter-v2) for the Arduino. Which looks like it could be a nice time-saver for me.

Another vid I found of interest is this [High-speed SCARA parallel robot](https://www.youtube.com/watch?v=R_AIzCTYBNs) which crosses the singularities to allow a much greater drawing area. Not something I plan on trying, but it's nice to know it can be done.


**2021-02-01** I've made a first prototype of the hardware. This revealed quite a few issues both hardware & software-related. I'm now working on the calculations (ie. (Robot Kinematics)[https://en.wikipedia.org/wiki/Robot_kinematics]).

It's really obvious that the (SG90s) servos need a lot more current that the Arduino alone can supply. I've got a little linear PSU from a wall plug hooked up right now, still probably not quite enough.

The *guesswork* code I tried to drive the code was pretty hopeless. A big issue seems to be the timing, making small changes so it doesn't drop into a (high current) stall condition (the cure is known as *servo easing*, apparently).

But I'm taking a step back, do some simulation to guide redesign of the hardware.

