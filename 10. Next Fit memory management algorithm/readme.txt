Input :
No. of blocks in memory n
A list of n block sizes
No. of processes to be fit in memeory m
A list of n process block sizes


Output : 
Process - Allocated Block mapping, internal fragmentation according to next fit allocation.

NOTE : This program reassigns a block to a process of process size is smaller than internal fragmentation in that block. This is wrong, in correct implementation, one block can be allocated to only one process at a time.