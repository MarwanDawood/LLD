## Dhrystone benchmarking
https://wiki.cdot.senecacollege.ca/wiki/Dhrystone_howto

It is configured to be compiled on x86 aith gcc compiler.\
To build, simply run `cd build`, then `make`.\
To run, simply run `./gcc_dry2`

### Result
One common representation of Dhrystone is DMIPS, it can be obtained by dividing the Dhrystone score by 1757 (the number of Dhrystones per second obtained on the VAX 11/780, nominally a 1 MIPS machine).

For my x86 machine, the result was 33333334.0, then **18,971 DMIPS** for 100M number of runs.