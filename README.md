# 42-Philosophers

Commit #3: May 5th 2023

Finished project + bonus.
Grade: 125/125;

Mandatory:
>> Application of threads on the philosophers themselves and also the monitor.
>> Use of mutexes.

Bonus:
>> Application on forks to divide the philosophers into multiple processes. Each process has it's own monitor.
>> Use of semaphores to "communicate" between each process.

Changes and Fixes:
 - Fixed all data races and deadlocks;
 - Removed fsanitize=thread flag from Makefile's CFLAGS (you need to add it to run the checks);

Notes:
 - Valgrind output is bugged, but memory checks are correct;
 - Do not use valgrind when compiling with fsanitize, as it will show memory errors and may crash your computer;
 - Do not test with more than 200 philosophers;
 - Do not test with time values lower than 60ms.

-----------------------------------------

Commit #2: April 27th 2023

Still WIP, project was behaving abnormally in certain situations. Currently resolving fsanitize errors.

-----------------------------------------

This is a WIP project.

This is 42's version of the dinning philosopher's problem. The difference in this project is that besides eating and thinking, here the philosophers also need to sleep between eating and thinking. This project focuses on multithreading processes. The mandatory part of the project is technically done, using threads. I will soon be working on the bonus part which focuses on multi processing/forks.
