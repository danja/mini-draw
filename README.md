# Simple Arduino Pen Plotter

A [SCARA](https://en.wikipedia.org/wiki/SCARA) robot using an Arduino, servos and hand cut aluminium sheet. 

## Status

Revised hardware, close to working. Back to software.

Video : https://www.youtube.com/watch?v=ijvBr-nKirs

More details in [devlog.md](devlog.md)

**2021-03-11** After making a very rough first prototype which flagged up loads of little problems, I've started working on another version taking these into account.

I also played around with [simulating the forward kinematics](https://github.com/danja/mini-draw/tree/main/sums). (in Python).

I've not used any CAD for years so in the interests of speed I hand-drew a [template](https://github.com/danja/mini-draw/blob/main/images/arms-template_2021-03-11.pdf) for the new arms, currently making these.

This is the first prototype: 

![prototype v1](https://github.com/danja/mini-draw/blob/main/images/early-top-view.jpeg)

I only did enough code to check the general behaviour. Which wasn't too wonderful:

![first lines](https://github.com/danja/mini-draw/blob/main/images/first-lines.jpeg)

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

## Glossary

*move this elsewhere later*

**[end effector](https://en.wikipedia.org/wiki/Robot_end_effector)** - the device at the end of a robotic arm (here, the pen)

**[distal](https://en.wikipedia.org/wiki/Anatomical_terms_of_location)** - a thing further away from the body (here, the arms farther from the servo)

**[prismatic joint](https://en.wikipedia.org/wiki/Prismatic_joint)** - a slider 

**[proximal](https://en.wikipedia.org/wiki/Anatomical_terms_of_location)** - a thing nearer the body (here, the arms nearer the servo)

**[revolute joint](https://en.wikipedia.org/wiki/Revolute_joint)** - a rotary joint or hinge 


