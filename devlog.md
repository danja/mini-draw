## Mini Drawing Robot Dev Log

**2021-03-11**

I found a good paper [Development of a Five-Bar Parallel Robot with Large Workspace](https://github.com/danja/mini-draw/blob/main/references/dextar.pdf). Here (and in other designs I found online) they talk about the arm lengths being about the same. There's a video of their machine working and it's notable in that the servos are mounted *above* the arms (workspace below), significantly increasing the available workspace size.
I'm not going to bother with that.

From initial experiments I reckon there'll be adequate power in the SG90s servos to support 120mm arms, given the use of bearings and vertical supports and more sturdy construction overall. 

I'm not sure yet what distance to use for the spacing between the servo axes, I'll have a play around once I've made the new arms.

I've made a start on making some, [template](https://github.com/danja/mini-draw/blob/main/images/arms-design_2021-03-11.pdf), current state:

![work-in-progress](https://github.com/danja/mini-draw/blob/main/images/arms-v2-rough.jpeg)

I've a rough idea of what to do for supports, a little trial & error will again be needed. I'll start by using the existing pen lifter but this will almost certainly need replacing, it's quite wobbly.

Thinking about making the drawings more accurate by other means, some kind of feedback might be desirable. It would be possible to pop open the servos, disable internal control, and route their potentiometers through the microcontroller, but I'm not sure that's worth bothering with for this toy machine.

Independent feedback from the pen position could be fun. My first thought was to use a [MPU-6050 Accelerometer + Gyro](https://playground.arduino.cc/Main/MPU-6050/) (I have one) but on reading round, it seems they're ill-suited for position measurement. It's not impossible, but things like the double-integration needed for acceleration -> position introduce huge amounts of drift. Apparently, if you can constrain the expected behaviour then [Kalman filters](https://en.wikipedia.org/wiki/Kalman_filter) the errors can be minimised to some extent. But it still sounds like a lot of work for little benefit.

Another possibility would be to use ultrasonic distance sensors like the [HC-SR04](https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/) (I also have some of these). The added weight of using one for each of x & y axes as well as having to have a reflective surface to take the distance from, this probably isn't suitable for a permanent setup. But it might well be worth trying just for calibration - just use one, first for x, then for y.  

And...what about a laser and detector mounted by the pen, with a page printed with registration marks (or a grid for calibration)? Hmm, maybe use a black workspace with blank pages cut to target size..?


**2021-03-09**

Reckon I'm going to pull out the (angleA, angleB) => (x, y) function out of Andrés Zibula's code, refactor it as a function taking & returning a std:pair.
I find it notable he used the Arduino IDE. I'm increasingly convinced it encourages poor coding practices (one big C file when independent C++ classes are easily doable in PlatformIO).

**2021-03-08**

The little bearings have arrived, as has a pair of chunkier servos, MG996R. They can shift about 10kg cm. But I'll save them, at least for now, see if I can get a bit further using the SG90s. 

To use the bearings I will need to make some more arms. So I've been playing with the simulation code a bit, wondering again about the best arm lengths/workspace area.

With a nasty hack, cropping the plots to the top-right hand quadrant and refleting against the midpoint, I get pictures that correspond much more closely to what they should look like.

sums/forward-precise-reduced.py
sums/forward-precise-reduced.ipynb

One thing I hadn't tried was using a separate PSU for the servos - essential really, they can pull a lot of current. I've got an old laptop one that has 5v @ 1.5A, should be ideal.
Yup, huge improvement in behaviour.

Tried Andrés Zibula's code - bit beserk to start with, but I think I can refactor it into something I can use. The key part, the inverse kinematics, should be pretty directly usable.

The power went off briefly so I'm calling it a day.

**2021-03-06**

I've ordered some small bearings for  another version of the hardware.

I stumbled on designs by [Andrés Zibula](https://andres-zibula.github.io/) : [1st](https://www.youtube.com/watch?v=B5Zup7bcReA) is a wonderful jumble of wooden dowels & rubber bands, [2nd](https://www.youtube.com/watch?v=a46DMy_3xc4) pretty convincing, using 3D printed parts. Those both use servos in the same kind of configuration I'm after. For a [3rd](https://www.youtube.com/watch?v=4yyozFsPI_I) he uses stepper motors and an STM32.

He's done the [inverse kinematics code](https://github.com/andres-zibula/Parallel-SCARA-Plotter-v2) for the Arduino. Which looks like it could be a nice time-saver for me.

Good to see another whiteboard fan :

![sums](https://github.com/andres-zibula/Parallel-SCARA-Plotter-v2)

Another vid I found of interest is this [High-speed SCARA parallel robot](https://www.youtube.com/watch?v=R_AIzCTYBNs) which crosses the singularities to allow a much greater drawing area. Not something I plan on trying, but it's nice to know it can be done.


**2021-02-01** I've made a first prototype of the hardware. This revealed quite a few issues both hardware & software-related. I'm now working on the calculations (ie. (Robot Kinematics)[https://en.wikipedia.org/wiki/Robot_kinematics]).

It's really obvious that the (SG90s) servos need a lot more current that the Arduino alone can supply. I've got a little linear PSU from a wall plug hooked up right now, still probably not quite enough.

The *guesswork* code I tried to drive the code was pretty hopeless. A big issue seems to be the timing, making small changes so it doesn't drop into a (high current) stall condition (the cure is known as *servo easing*, apparently).

But I'm taking a step back, do some simulation to guide redesign of the hardware.

