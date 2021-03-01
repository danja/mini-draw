# Simple Arduino Pen Plotter

A bit of fun with servos. *Details will appear here of design/construction, a bit more background will be in a [blog post](https://dannyayers.wordpress.com/2021/03/01/simple-drawing-robot-python-sums-weirdness/).*

## Status

**2021-02-01** I've made a first prototype of the hardware. This revealed quite a few issues both hardware & software-related. I'm now working on the calculations (ie. (Robot Kinematics)[https://en.wikipedia.org/wiki/Robot_kinematics]).

It's really obvious that the (SG90s) servos need a lot more current that the Arduino alone can supply. I've got a little linear PSU from a wall plug hooked up right now, still probably not quite enough.

The *guesswork* code I tried to drive the code was pretty hopeless. A big issue seems to be the timing, making small changes so it doesn't drop into a (high current) stall condition (the cure is known as *servo easing*, apparently).

But I'm taking a step back, do some simulation to guide redesign of the hardware.


## Design

The obvious way of making a plotter is with stepper motors driving linear screws for the X-Y axes & one servo to lift the pen. But searching around I found a servo-based design that seemed a lot more interesting, a [Mini Drawing Bot](https://www.instructables.com/Mini-Drawing-Bot-Live-Android-App-Trignomentry/) by [Jegatheesan Soundarapandian](https://www.instructables.com/member/jegatheesan.soundarapandian/). (He also has made a truly wonderful little [walking robot](https://www.instructables.com/Baby-MIT-Cheetah-Robot-V2-Autonomous-and-RC/) using the same mechanism as the drawing bot for each leg).

*If I was to make a drawing robot designed to be practical but inexpensive compared to full-on ball & screw systems, I'd follow the ingenious technique from one of the authors of the paper referred to below, described in [Study and Design of Control Belt Driven 2D CNC Systems](https://www.academia.edu/13297276/STUDY_DESIGN_AND_CONTROL_BELT_DRIVEN_2_D_CNC_SYSTEMS)* [T.S. Dinh Le and C.B. Pham, 2013]

## Mechanism

The mechanism chosen here is the [5-Bar Linkage](https://en.wikipedia.org/wiki/Five-bar_linkage):

![Five-bar linkage](https://github.com/danja/mini-draw/blob/main/images/five-bar-mechanism.png?raw=true)

If you imagine a person with their arms flat on a table, holding their hands together around a pen, it could be drawn something like this:

![Five-bar schematic](https://github.com/danja/mini-draw/blob/main/images/five-bar-schematic.png?raw=true)

Where **O** and **B** are the person's shoulders, **A** and **C** their elbows and **P** is the pen.

Here the 'shoulders' will each be attached to a servo, the 'elbows' loose joints and the 'hands' a servo that will lift the pen up and down. 

![animation](https://github.com/danja/mini-draw/blob/main/images/5R_robot.gif)

## Simulation

Python code under [sums](https://github.com/danja/mini-draw/tree/main/sums).

The paper [Study and Development of Parallel Robots based on 5-Bar Linkage](https://www.researchgate.net/publication/283356024_Study_and_Development_of_Parallel_Robots_Based_On_5-Bar_Linkage) (Manh Tuong Hoang, Trung Tin Vuong, Cong Bang Pham) includes analysis of these systems. Two parts are of particular interest. The *forward kinematic* gives the x,y position of the pen given the angles of the servos. The *inverse kinematic* gives the angles of the servos give the x, y position of the pen.

The inverse kinematic will be a significant part of the Arduino code. But before getting to that, the forward kinematic should be useful in determining optimal proportions of the system to allow drawing on a reasonable large rectangle.

I've coded up the forward kinematic in Python (with matplotlib for diagrams) with *moderate* success. Wikipedia gives a diagram for the area covered by a 5-bar linkage:

![velocity ellipses](https://github.com/danja/mini-draw/blob/main/images/velocity-ellipses.png?raw=true)

My simulation came out rather different :

![imprecise 360 forward](https://github.com/danja/mini-draw/blob/main/images/forward-360.png?raw=true)

But restricting the range of of servo angles to 90 +/-10 degrees gave a plot that showed I was probably on the right track:

![limited forward](https://github.com/danja/mini-draw/blob/main/images/limited.png?raw=true)

(The blob at the bottom is what happens when the arms bend inwards, correct here but not desirable in the physical version).

Making the angles vary 60-120 degrees gave something a little better, but strangely skewed - it should be symmetric :

![forward](https://github.com/danja/mini-draw/blob/main/images/imprecise.png?raw=true)


The calculations are quite long-winded so my guess was the distortion was down to inadequate precision in my code. But I modified the code to use the ```mpmath``` library, I believe using 1,000 decimal places (!) and still got a strange result.  

![forward](https://github.com/danja/mini-draw/blob/main/images/imprecise.png?raw=true)

**Ok, whatever.** I think I'll leave that bit there, have a crack at coding the inverse kinematics. Might be interesting to see what happens if I do forward-then-inverse, see what distortion appears there.




https://en.wikipedia.org/wiki/Five-bar_linkage

https://upload.wikimedia.org/wikipedia/commons/thumb/c/cb/5R_robot.gif/220px-5R_robot.gif


