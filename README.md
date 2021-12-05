# TiMRS

## Timers, Made Readable and Simple</h2>

Authors:
Jeff Kline  
Daniel Rindone  
Eric Webb  
Faisal Rahman

### Introduction

Using a device of some sort to measure an elapsed duration of time has proven useful for various purposes across human history. From the earliest Babylonian water clock to smartphones, the basics of these devices have essentially remained the same: mark some starting point, mark some ending point, then “start” the clock. However, some tasks or purposes for which one might use a timer require multiple steps with differing timing requirements at each step, and it may be inconvenient or hinder the task to go back to the device and set a new timer at each step.

TiMRS is a programming language designed to give a user a new way to easily design and script complex timers for any task. 

The concept is simple: a user can code any complex timing procedure using TiMRS’ built-in timer types with easily customizable durations and possibilities for repeats, intervals, and other pre-built timing patterns to track and perform any task where it may be useful. A major component of running a TiMRS script is providing the user with a graphical clock and some indication of stage of/progress through the timing routine.

Pending success of the basics outlined above, we may further seek to incorporate other possibilities with TiMRS that may be more specifically useful for programmers, such as enabling the execution of other programs or scripts within the framework of the TiMRS language.

### Language Components

#### Primitive Types
+ **hr**:	16 bit, unsigned
+ **min**:	8 bit, unsigned 
+ **sec**:	8 bit, unsigned

#### Control Flow
+ **rounds**: describes the number of times to repeat the nested code.
	

### Sample Program

    5 min;              // 5 min timer

    10 rounds:       // 1 minute timer 10 times
	  1 min;

    5 rounds:        // 5 times it runs the following:
	  2 min;            // 	2 minutes followed by 10 seconds
	  10 sec;
	  2 rounds:      // 	30 seconds then 15 seconds 2 times
		30 sec;
		15 sec;
    
	  3 min;            //	3 minutes
	  30 sec;           //	30 seconds
    
    10 min 45 sec;      // 10 minute 45 second timer
    2 hr 3 min;         // 2 hour 10 minute timer 

