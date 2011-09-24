Readme
======

Description
-----------

*workers* is a C++ library for computing tasks in the background through the use of threads. The library provides the minimum amount of code such that all memory control is handeled by the end user. The code is in its early stages and may well be buggy and cause memory poblems if used wihout care, as such be very careful if using this library in your code.

The following is a description of the existing thread managment structures avaliable:

#worker
A worker is simply a background thread that takes an arugment, does some computation and returns a result. the worker class is inherited by child classes which override the work function. The work function is the function that is sent to the background thread. The status of the worker is controlled by a collection of boolean variables such as 'ready' and 'collected' these are used to indicate the current state of the worker while minimizing the change of memory issues (if the boolean is read and written at the same time this will have minimum impact).

#master
A master is essentially a worker controller. It creates a thread and waits to be assigned workers which it executes in a FIFO basis, at the current state the master can only accept one worker at a time. the master will continue to accept and process workers until it is killed. The master class is designed to lower the overhead of creating threads when a high volume of workers are used.

Examples
--------

See the BOOST\_TEST file for examples on how to use workers and masters
