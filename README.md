23-03-08 3 points if you pass labs before

git checkout -b labX
git push --set-upstream origin labX
git checkout master #

Pintos:
complications comes from reading and uunderstanding code.
small amount of actual code.
There are questions in labs, answer them.
there is a vm user and password: pintos

Lab 0:
understand C and pointers
Linked lists your own implementation.
debug Pintos with GDB

Linked list is a data structure tto dynamically store data.
pintos has double linked list; they keep track of the previous node.

Lab 1:
Single user process
around 160-200 LOC
should be able to write files, exit process and write to console.

No concurrency
lib/user/syscall.[h|c] - the syscall wrapper

assignment:
???

files that should be studied:
lib/user/syscall
threads/interuppt/
lib/syscall-nr.ha
filesys/filesys

files that should be modified

userprog/syscall
threads/thread

currently the syscall handler kills every calling processf->esp is the stack of calls

FD - represents abstract input/output resources.
User proceese only knows about FDs and os knows resource it represents

* halt - shutdown the machine (already implemented)
* exit - exits current process. free resouces in thread_exit

create - create a file return true if sueccessful, false otherwise
open open a file - modify the thread struct to keep track of its FDs
close - close the file 
read - Read from the file with the given FD. give a buffer (memory) use already functions. use input_getc to read from console
write: writo to a file with FD. 

every process should have at least 128 files open.
its dangoeurs to assume arguments are valid, given FD is not associated with any file, invalid buffer size, too many files open. 

thread_current() to get thread struct for the calling process
filesys_open(char *) opens file. -||- _close closes it.
init thread initiate threads

run lab1test2 to test solution.
pintos -- rm test0 rm test1 rm test2.
implementation will be tested more in lab 3

you will implement 14 system calls
linux has 460, windows around 2000

debuffing. read appendix E: 
if you get Kernel Panic, then try backtrace. free sets the bytes to 0xcc. commit often. commit often, its easy to brake pintos.

If you get something like this:
Call stack: 0xc0106eff 0xc01102fb 0xc010dc22 0xc010cf67
0xc0102319 0xc010325a 0x804812c 0x8048a96 0x8048ac8

Then type this (when standing in the build folder):
backtrace kernel.o 0xc0106eff 0xc01102fb 0xc010dc22 0xc010cf67
0xc0102319 0xc010325a 0x804812c 0x8048a96 0x8048ac8}

You should get something like this:
0xc0106eff: debug_panic (lib/debug.c:86)
0xc01102fb: file_seek (filesys/file.c:405)
0xc010dc22: seek (userprog/syscall.c:744)
0xc010cf67: syscall_handler (userprog/syscall.c:444)
0xc0102319: intr_handler (threads/interrupt.c:334)
0xc010325a: intr_entry (threads/intr-stubs.S:38)

Lab 2:
Multiple system threads
implement sleep
sync required
this lab takes least time
around 40-60LOC

Lab 3:
implement exec.
exec allows a process start thre execution

Lab 4:
implement argument
setup of stack.
required undertsanding of memory layout and pointer arithmetic
around 40-50 LOC
Lab 5:
impkement wait: let a process wait for a child.
around 50-70 LOC
extend lab 3

Lab 6
sync of file system.
syscalls: seek, tell, filesize and remove
40-50 LOC

preemptive
multiple tracks for completion
example - multitasking

non-preemptive
one track
example - Network transmission, I/O, Atomic

Static (off-line)
-Complete a priori knowledge of the task set and its constraints is available
-hard/safety-critical system

dynamic(on-line)
-partial taskset knowledge, rumtime predicitions
-firm/soft/best-effort systems, hybrid systems

Scheduler
resides in the kernel
    - operating system is responsible for managing processes
    -periodically called by a timer interrupt
    - length of timer determines how frequent context switching can occur.

Burstiness
You switch between cpu burst and I/O burst.

Consequence of burst:
    Processes can in some cases be treated as a set of bursts (jobs)
    Each job has a certain execution time (burst time)

What is a good scheduler?

General scheduling criteria
    Cpu utilzation
        keep the cpu as busy as possible

    Throughput
        # of processes that conplete their exec per time unit

    deadlines met?
    - in real-time systems

    energy usage
        mobile and cloud-based computing
        in particular for multi-core


Time-based scheduling

    turnaround time
        time to execute a particular job

    Waiting time
        the time a process has been waiting in the ready queue
    Response time
    time it takes from when a request was submitted until
the first response is produced

First-come, first-served (FCFS) schedulng
FCFS normally used for non-preemptive batch scheduling, e.g printer queues (i.e burst time = job size)


convoy effect
    short process behind long process
    idea: shortest job first?

Shortest-Job first (SJF)
    Associate with each process the length of its next cpu burst
    use there lengths to schedul the shortest ready process
    SJF is optimal
        gives minimum average waiting time for a given set.
    
    Two variants
        Nonpreemptive
            once CPU given to the process, it cannot be preempted until it completes its CPU burst
        preemptie
            preempt if a new process arrives with CPU burst length less than remaining time of current executing process. Also known as Shortest-Remaining-Time-First (SRTF)

    Predict length of next burst
        Need to estimate
        based on length of previous bursts, using exponential averaging

    Priority Scheduling
        A priority value is associated with each process
        The cpu is allocated to the process with the highest priority
        Allows giving high priority to important jobs
        Problems:
            Starvation - low-priority processes
            long jobs, even if delayed will monopolize the cpu
        solution
            asing - as time progresses increease the prio

        How to balance age and priority
            It is experimental.
        Round Robin(RR)
            Each process gets a small unit of cpu time
            After ths time has elapsed, the process is preempted and added to the end of the ready queue.

            performance:
                No process waits more than (n-1)q time units

        Choice of time quantum
            q very large - fcfs
            q very small - many context switches
            q must be large w.r.t. context switch time, otherwise too high overhead

        Problems with RR and priority schd

        Priority based scheduling may cause starvation for some processes
        Round robin based schedulers are maybe too "fair" we sometimes want to prioritize some processes.
        Solution:
            Multilevel queue

        Ready queue is partitioned into separate queues, e.g.:
            – foreground (interactive)
            – background (batch)
        Each queue can have its own scheduling algorithm
            – foreground – RR
            – background – FCFS

        Inter-queue scheduling
            fixed priority scheduling
                -serve

Synchronisation

good for practacing
deadlock empire: deadlockempire.github.io/

Recall: 
shared variables, message passing

Communication using shared variables
often requires atomicity
what is the outcome of running them both to completion?

Atomic access often supported by hardware

Race condition

IF the order of operations affect the outcome, if this is unintended then system suffers from a race condition.

Don't overlap two critical sections at the same time to avoid race conditions

Critical-Section problems:

Mutual Exclusion - only one critical section at time.
Progress - Do not get stuck choosing who enter critical section
Bounded waiting - A bound must exist on the number of times that
other processes are allowed to enter critical
section C after a process has made a request
to enter C and before that request is granted.

Solutions:

Software-only solutions:
Petersons algorithm:
    flag 1- Process P1 wants to enter Critical Section.
    turn = 2 whos turn is it to enter CS
    flag 2- Procees P2 wants to enter CS
     better ways to do it in larger scale.

Hardware support:
    some of these may be on exam.
    Test and Set: test memory word and set value atomically.
        made with transistors
        a solutions where first into the functions gets to use the variable
        this solutions doesnt fix starvation.

    Swap: swap contents of two memory words atomically.
        Swap *A and *B
        keep swapping between local and shared variable when lock gets false the tmp will become false and escape waiting condition.

Synchronization primitives:
    Would be useful to have support from an operating system or a programming language.
    modern languages have this

    abstraction layer:
        easier to use, but must be implemented

    Do not solve all sync probems
    examples:
        Semaphores
        Locks
        Conditions variables
        Monitors - no needed to be used for labs.

    Semaphores - is always non-negative integer. which only two atomic operations wait and signal can be performed. Practically a boolean. Needs to be implemented so two functions doesn't wait at the same time. Use  wait and signal good and you solve the problem. Atomicity must be provided.

    Spin Locks - All entry protocols so far uses a busy wait loop - called a spin lock. Sometimes necessary (kernel-level).
    Eliminate Busy Waiting - With each semaphore there is an associated waiting queue, two operations: block - place the procees invoking the operation on the appriopriate waiting queue and wakeup - remove one of processes in the waiiting queue and place it in the ready queue.

    Counting semaphores
        When more than one instance of a reousce is available, e.g print servers.
        Processes can use up to max available but no more.
        T

    Semaphore initialization
        Crutial to determine the semantics of the semaphore
        must be stated in your exam answers

        a semaphore with maxamium value 1 is called binary semaphore, useful to implement lock.

    Locks
        Binary semaphore

        operations often called
            acquire (wait)
            realese (signlad)

        only the thread that acquired the lock can release it!

Complex data structures
    Data is often structrued
        Lists
        objects
        structs

    Consistency req
        cannot change one part of the data structure but not the other part.

    Two options
        one big lock
            safe (no sync problems)
            slow (reduces concurrency)
        Multiple synch primitives
            fast (allows higher degree of synchronization)
            potentiall dangerous (introduces new concurrency problems)

    Multiple synch primitives:
        Conditional action
            purpose is to avoid busy waiting
            examples:
                compute the interest when all transcactions have been processed
                book a flight seat only if seats are available

        Mutual exclusion
            Purpose is to avoid errors
            Example:
                Two customers shall not be booked on the same seat.
        In pintOS exec sytemcalls will have a problem with this.

    Deadlock and starvation
        Deadlock - two or more processes are waiting indef. for an event that can be caused only by one of the waiting processes
        Starvation - indef. blocking. A process may never be removed from the semaphore queue in which it is suspended.
    
    Focus on the resource (data)!
        Non-shared data does not need protecting
            automatic (stack, local) variables
        Same resource must be protected with the same sync primitive
        Concsistenct req and access patterns determine the granulartiry of sync.

    Two more useful sync primitives
        Conditions variables
        Monitors

    Issues with boundef buffer
        Writing to full buffer(cond action)

        Reading from empty buffer (cond action)

        Two write operations to the same element (mutual exclusion)

    Condition variables
        Declared as special sunc variables: cond x

        With two designated operations:
            Wait: susend the calling process
            Signal/notify: : if there are suspended processes on this variable, wake one up

DEADLOCKS:

    Correctness properties
        safety properties
            something bad will not happen
        Liveness properties
            something good will happen (eventually)
        
    progress
        a form of liveness

    methamatically defined within a given system model
        can be defined on system or process level
        typically ensurer that if system is in some state s, then it will reach some other state sä where some property P holds

    implies freedom from:
        deadlock
        livelock
        starvation depending on the model

    
    deadlock occurs when a group of processes are locked in a circular wait
    Livelock occurs when a group of proceeses are stuck in a loop of actions where they stop each other from progressing

    deadlock freedom
        freedom from deadlock is fundamental to any concurrent system
        necessary but not sufficient for progress

    coffman conditions

        mtual exclusion
            access to a resourse is limited to one process at a time
        hold and wait
            a process may hold a resource and wait for another resource at the same time
        voluntary release
            resources can only be released by a process voluntarily

        circular wait
            there is a chain of processes where each process holds a resource that is required by another process

    Basic Facts
        Graph contain no cycles => no deadlock

        Graph contains a cycle 
            if only one instance per resource type then deadlock
            ifseverral instances per resource type, possivility of deadlock

        deadlock elim
            deadlock prevention
            deadlock avoidance
            deadlock detectin and treatment
            ignore the problem

    Deadlock prevention:
        ensure that at least one of the coffman conditions can never occur

    prevent mutual exclusion
        ME is needed only for limited shared resources
        example: read-only file access by arbitrarily many readers
            Readers-writer lock

    Prevent Hold & wait
        whenever a process requests a resource, it cannot hold any other resources
        request all resouces at once
            dining philosopher solution
        low resource utilization; starvation possible; not flexible.

    Prevent Voluntary release
        ensure preemption
        force another process to release its resources
        preempted resources are added to the list of resources for which the process is waiting
        process will be restarted only when it can regain its old resources, as well as the new ones that is requesting.

    Prevent circular wait
        impose a total ordering of all resources
            requests must be performed in this order
        priorities of processes and resources
            e.g immediate ceiling protocol in realtime scheduling

    Tools to eliminate circular wait
        windows driver verifier
        linux lockdep tool
        static analysis tools

    Deadlock avoidance:

    safe state
        system is in safe state if there exists a safe sequence (i.e completion sequence) of all processes
        if a system is in safe state => no deadlock
        if a system is in unsafe state => possibility of deadlock
        avoidance: 
            snure that a system till never enter an unsafe state

    assumptions
        requiires a priori knowledge of needed resources
        Assume that each process declare the amount
        of resources needed
    deadlock avoidance algorithms
        case 1: all resource types have 1 instance only
            resource allocation graph algorithm
        case 2:
            multiple instances per resource type
                bankers algorithm
        Banker’s algorithm
● Multiple instances of each resource
● Upon each process request
– Check that the request is within the maximum limit
for that process
– Check that the new state is safe

Rejecting a request
● When allocating a request does not lead to a
new “safe” state:
– Refuse to grant
● The request can be repeated in some future
state and get granted

Inputs and outputs of Banker's
● Input:
– Matrix Max
– Vector Available
– Matrix Allocation
– Request[i] for some process i
● Output:
– Yes + new state, or
– No + unchanged state (Request[i] can not be allocated now)

Data structures
Available: Vector of length m. If Available[j] = k, there are k
instances of resource type Rj available
Max: n x m matrix. If Max [i,j] = k, then process i may
request at most k instances of resource type Rj
, Max[i]
denotes the i'th row.
Allocation: n x m matrix. If Allocation[i,j] = k then i is
currently allocated k instances of Rj
, Allocation[i] denotes the
i'th row.
Need: n x m matrix. If Need[i,j] = k, then i may need k more
instances of Rj
to complete its task, Need[i] denotes the i'th
row.
Let n = number of processes, and m = number of resources types.

banker's algorithm
    1. Need := Max – Allocation
 Check that Request[i] <= Need[i]
2. Check whether Request[i] <= Available
 if not, return ”No”
3. Pretend that resources in Request are to be allocated, compute new state:
 Allocation’ := Allocation + Request
 Need’ := Need - Request
 Available’ := Available – Request[i]
4. Test whether the new state is deadlock-avoiding (denoted safe), in which
case return ”Yes”.
Otherwise, return ”No” - roll back to the old state. 

Testing for safe state
● Start with a given Allocation’ and check if it is
safe (avoids future deadlocks) according to the
3-step algorithm.

Safety algorithm data structures
Finish: n vector with Boolean values (initially
false)
Work : m vector denotes the changing resource
set as the processes become ready and release
resources (initially Work := Available')

Safety algorithm

1. Check if there is some process i for which Finish[i] = false and for
which Need’[i] <= Work. If there is no such process i, go to step 3.
2. Free the resources that i has used to get finished:
Work := Work + Allocation’[i]
Finish[i] := true
continue from step 1.
3. If Finish[i] = true for all i then the initial state is deadlock-avoiding,
otherwise it is not.

Banker’s algorithm:
– 4 step algorithm
– 4th step is a 3-step iterative safety algorithm

!!!!!!! BANKERS ALGORTIHM ON EXAM !!!!!!!

Running Bankers algorithm (result)
● The outcome of the Safety algorithm is that the
new state is safe

Weaknesses of the Banker’s
Algorithm
● Assumes a fixed number of resources
– not realistic – number of resources can vary over time
● Assumes a fixed population of processes
– not realistic for interactive systems
● Assumes that processes state maximum needs in advance
– often not known
(depend e.g. on input data or user commands)
● Waiting for completion of one or several processes may take very
long / unpredictable time before a request is granted

Deadlock Detection and Recovery
● Allow system to enter deadlock state
● Detection algorithm
– Single instance of each resource type
– Multiple instances
● Recovery scheme

Deadlock detection with single instance
resources

Search for cycle in wait-for graph
● Maintain wait-for graph
– Nodes are processes.
– Pi  Pj
iff Pi
is waiting for Pj
.
● Periodically invoke an algorithm
that searches for a cycle in the graph.

Deadlock detection with multiple instance
resources
Detection Algorithm [Coffman et al. 1971]
1. Vectors Work[1..m], Finish[1..n] initialized by:
 Work = Available
 for i = 1,2, …, n, if Allocationi  0 then Finish[i] = false
 otherwise Finish[i] = true
2. Find an index i such that both:
 (a) Finish[i] == false
 (b) Requesti  Work
If no such i exists, go to step 4.
3. Work = Work + Allocationi
Finish[i] = true
go to step 2.
4. If Finish[i] == false, for some i, 1  i  n,
 then the system is in deadlock state.
Specifically, if Finish[i] == false, then Pi
 is deadlocked.

 Difference to Banker's algorithm
● What is a safe state?
– Consider the actual request (optimistically),
not the maximum needs
● Reason: We compute if there is a deadlock
now, not if one may happen late

Detection-Algorithm Usage
● When, and how often, to invoke depends on:
– How often a deadlock is likely to occur?
– How many processes will need to be rolled back?
● one for each disjoint cycle
●
Invocation at every resource request?
– Too much overhead
● Occasional invocation?
(e.g., once per hour, or whenever CPU utilization
below 40%)

Recovery from Deadlock: Process
Termination
● Abort all deadlocked processes.
● Abort one process at a time until the deadlock cycle is
eliminated.
● In which order should we choose to abort?
– Priority of the process.
– How long process has computed,
and how much longer to completion.
– Resources the process has used.
– Resources the process needs to complete.
– How many processes will need to be terminated.
Recovery from Deadlock: Resource
Preemption
● Selecting a victim
– minimize cost
● Rollback
– return to some safe state,
restart process for that state.
● Starvation
– same process may always be picked as victim,
include number of rollbacks in cost factor.
Summary
● Deadlock characterization
– 4 necessary conditions (Coffman)
– Resource allocation graph
● Deadlock prevention
– Prohibit one of the four necessary conditions
● Deadlock avoidance
– 1 instance-resources: Resource allocation graph algorithm
– Banker’s algorithm (state safety, request granting)
● Deadlock detection and recovery
– 1 instance-resources: Find cycles in Wait-for graph
– Several instances: Deadlock detection algorithm
● Do nothing – lift the problem to the user / programmer


Lesson 2 - 
You cant have two processes operating at the same time
Conditions is not necessary for the labs
Locks are slow, use semaphores

Semaphores
A generalistation of locks
Can signal that it is okay to go ahead for other resources.

Interrupts
Internal and External
Disabling interrupts is just postponing

The synch is made possible by disabling interrupts
If there is problem check with interrupts
You need to disable interrupts rather than using locks when the interrupt handler can cause race conditions (but use locks otherwise). Dont use interrupts when not needed

Busywaiting - 
timer_sleep and thread_yield. Takes a lot of ticks. We need to improve them

Lab 2: 
can use synch prim but use locks is prefered (thread_block)
Use Pintos list for sleeping threads
Keep the list sorted to know if there any threads to wake up.
make -j check from the threads/ folder
pintos run alarm-single (grab named from make check)
the tests will pass as it is, since busy-waiting is a solution

Lab 3: 
Improve exec and close
Spawn a child that loads the file
Solve implement that does not see if child could spawn
You need to make the parent wait for its child
current imple - process_execute
You assume that TID and PID is the same thing
A process can have several children but one parent
You dont need to strip the arguments from cmd_line, it will function anyways

Code of interest:lesson 2 slide 25:

More hints for lab3:
You can change the parameter of start_process and the argument to threadcreate whatever you want
The first thread doesnt have any parent.

Lab3 exit:
Exit status has to be made available to its parent, will be used later in lab5
The process has to release all its allocated resources when exited
If the process crashes, return -1

If use Malloc, you need to free it
To detect who is the last to exit, keep a
counter together with the exit status. Set the
initial value to 2, when the parent/child exits,
decrement it by 1. When the value is 0 it
represents that both the parent and child has
exited, and whoever decrements it to 0 should free
the memory of the shared struct.

Need to be synced on some kind

Lab 4:
Pintos does not support arguments to program
Remember the -12 from the stack pointer.
Put the words on the stack, add word alignment, the argv array, argc and return adrress
What function within process.c has access to both the stack pointer and the *cmd_line? And when is the stack actually available? And is that function called while a process is starting?
Within load() there is debug code to print the
stack for inspection. To have it run, uncomment /*#define STACK_DEBUG*/
• Remember, if you have a double pointer (void**),
you need to dereference twice to write/read the
memory, dereference once to change what it points
to.

You get a string, such as "binary -s 17\0", and you need to split it up in smaller parts.
You cant write to void pointer, you may need to cast it
You need to save a pointer to every word.
Read the comments for functions for how to use it.

Memory management

CU = control unit
MMU = Memory management unit

Due to the separation between logical address
and physical address the MMU can provide the
process with virtual memory

Memory-Management Unit (MMU)
● Hardware device that maps virtual to physical
address
● The user program deals with logical addresses;
it never sees the real physical addresses
● The MMU provides translation between logical and
physical addresses

Granularity

The chunks of memory given by MMU
Can be: Process level, segmentation, paging

Process-level management
Multi-partition allocation
each process gets one partition
protects from each others

MMU checks logical adress, if less than limit reloacte else reject (trap to OS - invalid memory access).

External fragmentation - blocks of unused memory between processes
internal fragmentation - block of unused memory inside a process

Dynamic storage-allocation problem:
How to satisfy a request of size n from a list of free holes?

Allocation schemes
● First-fit: Allocate the first hole that is big enough
● Best-fit: Allocate the smallest hole that is big
enough;
– must search entire list, unless ordered by size.
– Produces the smallest leftover hole.
● Worst-fit: Allocate the largest hole;
– must also search entire list.
– Produces the largest leftover hole.

Compaction
Reduce external fragmentation
Compaction is possible only if reloactation is dynamic, and is done at execution time
● I/O problem

solution one: Move all occupied areas to one side until there is a hole large enough for pnew
solution two: Search and select one (or a few) processes to move to free a hole large enough

Still not enough space? - Try swapping!
It is costly though

Use frames with a page table

Paging
Physical address space of a process can be noncontiguous
Process is allocated physical memory whenever the latter is available – no external fragmentation
Internal fragmentation

Address generated by CU is divided into:
– Page number (p) – index into a page table
that contains the base address of each page in
physical memory
– Page offset (d) – combined with base address
to define the physical memory address that is sent
to the memory unit

Size of logical address space is 2m
Size of page 2n

Page Table Structure
● The “large page table problem”
● Page table structures:
– Hierarchical Paging: “page the page table”
– Hashed Page Tables
– Inverted Page Tables

Implementation of the Page Table
● Page table is kept in main memory
● Page-table base register (PTBR)
points to the page table
● Page-table length register (PRLR)
indicates size of the page table
● Every data/instruction access requires n+1 memory accesses (for n-level
paging).
– One for the page table and one for the data/instruction.
● Solve the (n+1)-memory-access problem
– by using a special fast-lookup cache (in hardware):
translation look-aside buffer (TLB)
●
Implements an associative memory

Effective Access Time
● Memory cycle time: t
● Time for associative lookup: e
● TLB hit ratio a
– percentage of times that a page number is found in TLB
● Effective Access Time (EAT):
 EAT = (t + e) a + (2t + e)(1-a) = 2t + e - at
Example: For t =100 ns, e = 20 ns, a = 0.8: EAT = 140 ns

Memory Protection
Implemented by associating protection bit with each frame

Valid-invalid bit attached to each entry in the page:
    valid: The associated page is in the process' logical address space, and is thus a legal page
    invalid: the page is not in the process' logical address space

Allows dynamically sized page tables

Shared memory
-easy with paged memory

Combining seg and paging
Each segment is organized as a set of pages.
seg table entries refer to a page table for each seg

Demand paging
Virtual memory that is larger than physical memory

Bring a page into memory only when it is needed
    Less I/O needed
    less memory needed
    Faster response
    More users

Page is needed if refernced (load/store, data/instructions)
    Invalid reference => abort
    not-in-memory => bring to memory

Rather than swapping entire processes (cf. swapping),
we page their pages from/to disk only when first referenced.

What happens if there is no free frame?
    Find some page in memory, but not really in use, swap it out
        Write back only necessary if victim page was modified
        Same page may be brought into memory several times

Performance of Demand Paging
● Page Fault Rate p 0 <= p <= 1.0
– if p = 0, no page faults
– if p = 1, every reference is a fault
● Write-back rate w 0 <= w <= 1
● Memory access time t
● Effective Access Time (EAT)
 EAT = (1 – p) t + p ( page fault overhead
 + w ( time to swap page out )
+ time to swap new page in
+ restart overhead
+ t )

Bring a page into memory only when it is needed
– Less I/O needed
– Less memory needed
– Faster response
– More users
● Page is needed if referenced
(load/store, data/instructions)
– invalid reference => abort
– not-in-memory => bring to memory

What happens if there is no free frame?

Page replacement
    When no free frames, move one page out
    Use modiffy (dirty) bit to reduce overhead of page transfers
        only modified pages are written to disk

How to compare algorithms for page replacement?
Goal: find algorithm with lowest page-fault rate.
Method: simulaton
    Assume initially empty page table
    Run algorithm on a particular string of memory references (reference string - page numbers only)
    Count number of page faults on that string

FIFO
    Use a time stamp or a queue
    Victim is the "oldest page"
    Assume table size = 3 frames / process (3 pages can be in memory at a time per process) and reference string:

An optimal algorithm
    Optimal:
        Has the lowest possible page-fault rate (NV: still ignoring dity-ness)
        does not suffer from Belady's anomaly

    Belady's algorithm
        Replace page that will not be used for the longest period of time....
        How do you know this?
        Remark: belady's algorithm is only optimal if there are no dirty write-backs. Otherwise it is just a heuristic algorithm

Least recentyly used (LRU)
     Optimal algorithm not feasible?
    ....try using recent history as approximation of the future!
    ● Algorithm:
    – Replace the page that has not been used for the longest period of time

Thrashing
    If a process does not have "enough" pages, the page-fault rate is very high
        Page fault to get page
        Replace existing frame
        But quickly need replaced frame back
    This leads to:
        Low CPU utilization
        Operating system thinking that it needs to increase the degree of multiprogramming
        Another process added to the system

Demand Paging and Thrashing
    Why does demand paging work?
    Locality model
       Process migrates from one locality to another
       Localities may overlap
    Why does thrashing occur?
       sigma size of locality > total memory size
    Limit effects by using local or priority page replacement

Working set model check slides

Working set example

Keeping track of the working set
    Approximate with interval timer + a reference bit

    Example: delta = 10,000
       Timer interrupts after every 5000 time units
       Keep in memory 2 bits for each page
       Whenever a timer interrupts copy and sets the values of all reference bits to 0
       If one of the bits in memory = 1  page in working set
    Why is this not completely accurate?
    Improvement = 10 bits and interrupt every 1000 time units

Page-Fault freq.
    More direct approach than WSS
    Establish "acceptable" PFF rate ans use local replacement policy
        if acutual too low, process loses frames
        if high, process gains frames

Working sets and page fault rates
    Direct relationship between working set of a process and its pf rate
    working set changes over time
    peaks and valleys over time

Motivation
    Disk access is very slow
    Memory is fast, and cpu is even faster
    Somtimes there is no more disk
    Flash memory degreades from freq. erasures

Memory compression
    compress memor in ram
    possible to do in HW, but mostly done by OS
    Examples:
        Linxu: zream, zswap
        windows 10
        MAC OS X
        Android & iOS

File systems
Checks slides lecture 08

Wait (lab 4)
see slides

Last lecture:

exam: 

2 parts: a and b

a: 2,5 bonus points added to this section
abcd choices, atleast one is correct for each but more can be right. They are not easy
Always be some kind of synchronization
usualt bankers but not always

b:
more advanced synchronization

banker's algorithm:

resource allocation problem:
3 resources: R1, R2, R3
4 processes P1, P2, P3, P4
Allocation table
    R1      R2      R3      
P1| 1 (1)   0(0)    1(6)
P2| 1(3)    0(0)    0(7)
P3| 0(0)    0(1)    0(4)
P4| 1(2)    1(1)    0(1)

currently available: [0, 0, 8]
use bankers algorithm to determine if the request [0, 0, 1] from P3 should be granted

step 1: Calculate need and check that request is less than need.
need: Max - allocation. =   [0, 0, 5]
                            [2, 0, 7]
                            [0, 1, 4]
                            [1, 0, 1]
request <= need? yes!

step 2:Request <= Available? Yes!
step 3: Update matrixes as if request was granted.
Allocation' (not derivate) =    1 0 1       need' =     0 0 5     available' = [0 ,0 ,7]
                                1 0 0                   2 0 7
                                0 0 1                   0 1 3
                                1 1 0                   1 0 1

Step 4: Check if "new" state is safe. 
work = [0, 0 ,7] finish = [F, F, F, F] 

process P1 can finish
work [0, 0, 7] + [1, 0, 1] = [1, 0 ,8]
finish = [T, F, F, F]

process P4 can finish
work = [1, 0, 8] + [1, 1, 0] = [2, 1, 8]
finish = [T, F, F, T]

process P2 can finish
work = [2, 1, 8] + [1, 0, 0] = [3, 1, 8]
finish [T, T, F, T]

P3 can finish
work = [3, 1, 8] + [0, 0, 1] = [3, 1, 9]
finish = [T, T, T, T]

Answer: the requested state is safe and can be accepted according to bankers algorithm

Least recently used:
use the spot that were used most long ago and use that slot. if the requested thing isn't in memory it will get a page fault.
put it in a table.

scheduling: 
with preemption, higher prio takes over the execution

-----

Consider a system with 32 bit memory, show the pagehierarchy assuming that every page table should fit in one page and that page size is 1kb.

memory: 
2^32 = 4 GB memory
no. frames 2^32/2^10 = 2^22
1 word 32 bits so every row is 4 bytes,
How many rows per page table?
256 = 2^8

How many page tables at last level?
2^22/2^8 = 2^14

How many page tables at the second last level?
2^14/2^8 = 2^6 = 64