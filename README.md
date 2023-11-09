# FreeRTOS POSIX Shutdown Test
This repository exists to test the functionality of POSIX port freeRTOS programs to exit cleanly when starting and ending the scheduler.

### Expected Behavior
The main thread forks a thread that starts the scheduler with `vTaskStartScheduler`, which runs and blocks. This thread then forks another thread to do some work, which then unblocks the main thread and then deletes itself. `vTaskEndScheduler` should then be called, returning to the invokation of `vTaskStartScheduler`. The program should then exit gracefully.

### Obserbed Behavior
Program execution halts after calling `vTaskEndScheduler()` and never exits.

### To run
```
git submodule update --init --recursive
mkdir build && cd build
cmake ..
make
./main
```