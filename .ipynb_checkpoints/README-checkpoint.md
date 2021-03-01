# Simple Arduino Pen Plotter

A bit of fun with servos.

I'm new to servos but after finding it very easy to make a [Cat Annoyer](https://github.com/danja/cat-toy) using a servo I wanted to try something a little more ambitious, a plotter using 3 servos.

The obvious way of making a plotter is with stepper motors driving linear screws for the X-Y axes & one servo to lift the pen. But searching around I found a servo-based design that seemed a lot more interesting, a [Mini Drawing Bot](https://www.instructables.com/Mini-Drawing-Bot-Live-Android-App-Trignomentry/) by [Jegatheesan Soundarapandian](https://www.instructables.com/member/jegatheesan.soundarapandian/). (He also has made a brilliant little [walking robot](https://www.instructables.com/Baby-MIT-Cheetah-Robot-V2-Autonomous-and-RC/) using the same mechanism as the drawing bot for each leg).

## Mechanism

The mechanism here is the [5-Bar Linkage](https://en.wikipedia.org/wiki/Five-bar_linkage):

![Five-bar linkage](https://github.com/danja/mini-draw/blob/main/images/five-bar-mechanism.png?raw=true)



https://www.researchgate.net/publication/283356024_Study_and_Development_of_Parallel_Robots_Based_On_5-Bar_Linkage

https://en.wikipedia.org/wiki/Robot_kinematics

https://en.wikipedia.org/wiki/Five-bar_linkage

https://upload.wikimedia.org/wikipedia/commons/thumb/c/cb/5R_robot.gif/220px-5R_robot.gif


A method for optimal kinematic design of five-bar planar parallel manipulators (Tien Dung Le, Hee-Jun Kang and Quang Vinh Doan).