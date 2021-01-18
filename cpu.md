# Computers

A brief overview of what a computer is and how it works. Please note that this explanation is primarily going to focus on the x86/64 family of CPUs for examples.


## Part 1: Computation Theory

### Basic Logical Computer
![Logical Computer Diagram](/images/basic-logical-computer.svg)

The logical computer diagram represents how data flows through a computer system where the CPU is at the centre orchestrating the entire process. This is the Von Neumann architecture where the CPU can read data and execute code from either RAM or ROM.

### Basic Physical Computer
![Physical Computer Diagram](/images/basic-physical-computer.svg)

The physical layout of a computer is more likely to follow from the above diagram where a "main bus" connects all of the components together. This type of layout is very simple and cheap which is why many early home computers (of the late 1970s and early 1980s) took this approach. 
It has a low cost but by having all the components share the same bus resource contention was common place. This happens when two independent sub-systems share a common resource and the CPU has to allow each process some time, slowing down each process. In simple micro-computers this is not much of a problem as they had only one CPU that drove the entire system from keyboard input to video output

### A Modern Computer

![Modern PC Architecture](/images/modern-pc-architecture.svg)

Modern desktop PCs have an architecture that is less centralized. Using "intelligent" devices that are essentially problem-specific computers in their own right. Much of the "work" can be offloaded from the CPU. 

### The CPU

The only information that is stored in a computer is the binary representation of numeric values. How these numbers are interpreted to perform operations is constructed from the designers of the "instruction set". The trade-off of the instruction set design is that a larger number of instructions will make the CPU more capable but also more complicated. Where as a smaller instruction set would make the CPU smaller and more efficient but less capable. This is why there are many kinds of CPUs available- some for embedded devices like a toaster or a keyboard and some CPUs are built for number crunching large amounts of data for scientific analysis.

### How computation works

At the core of a CPU is a set of components: Registers, Sequence control and the Arithmetic Logic Unit.

Registers are a type of memory for setting up values to send to the ALU and receiving results from the ALU. Registers have a size that represents the "bits" a CPU isl: 8, 16, 32 and 64 bits. Registers have a number of types: General purpose registers can store arbitrary values of a user defined nature. Program counters, stack pointer, offset registers are used by the CPU for reading or writing values from memory. Status register(s) track specific information about what is happening in the CPU.

The ALU performs  basic numerical operations like add, invert, subtract, shift etc. on one or two numbers. These values are fed from the CPU registers. The result of this operation would be written back to an accumulator register. These  operations also update the  status register that indicated a number of important facts about the previous operation: the zero flag would be set if the operation was zero, the carry flag would be set if the two number over-flowed the machine word size and the negative bit if the result was less than zero. Instructions could then conditionally execute depending on the status of these bits. 

Finally the sequence controller is responsible for orchestrating all CPU activities. This is a finite state machine that drives the four stage instruction cycle: (1) fetch, (2) decode, (3) execute and (4) write back.

### Instruction sets

An instruction is just an integer number that has a special meaning to the CPU to command it to perform an operation. How the CPU executes instructions internally should not matter to software engineers. There are two basic flavours of CPU instruction set that govern how a processor operates:  RISC and CISC.





## Part 2: The CPU

### CISC

In the early days of computers (before 1980) computer memory was very expensive and slow so vendors built as many common operations into the instruction set as possible (to save valuable customer memory space). Operations like multiply, divide, modulus, string manipulation, floating point mathematics and so on. This reduced code size but made the architectures very complex and many of these esoteric instructions could go unused and be dead weight.
Intel X86 (and the later x86-64) instruction set is so massive it has to employ a technique called "microcode" to implement some of the functionality. Microcode is like having a computer inside your computer where the CPU decodes an instruction and then has to jump to a table (in its own internal memory, no less) to know how to execute that instruction.

### RISC

As a response to the increasingly complicated CPUs with their high power consumption or slower execution time designers started exploring a different approach that took a more conservative approach. By reducing the complexity of the CPU to just a small number of instructions for performing operations programmers could implement the complex algorithms themselves in machine code. This meant the CPU would be much smaller, cost less to buy and run and did not come with functionality that the programmer would never use.

As RISC is simpler and more space/power efficient it is often found in embedded systems.

### Word size

A CPU is often referred to as 8, 16, 32 or 64 bit. This number is how large the basic register size is. The 6502 was 8 bit because its registers had 8 bits or storage although its address registers were 16 bit. The x86-64 has 64 bit basic registers.

### Floating Point (and SIMD)

Floating point is a way of performing real-number mathematics using only integer-numbers. This is done by using integer powers so 1.25 would be encoded as 125^-3. In this way approximations of real numbers could be worked with. It is important to bare in mind that every FP calculation introduces a small error between the theoretical result and what is computed. An algorithm must be designed to calculate as much as possible in the region of numbers with the least aliasing otherwise these small errors can compound upon each other and throw the result off by a large amount. This can be mitigated by using larger floating point representations but this solution will sacrifice speed for accuracy.

In the PC world floating point was initially implemented in software in the system ROM. As computers fell in price and increased in capability external FPU sockets on the motherboard could be populated to provide hardware floating point. Later on by the early 1990s FPUs became embedded in the CPU itself (such as the 486DX).

As domestic software became more capable and more applications relied on floating point operations the FPUs grew in complexity. The major enhancement is SIMD (Single Instruction Multiple Dispatch) where one instruction could operate on several numbers in parallel. In traditional FPUs multiplying two numbers involved loading two numbers into two registers and invoking the multiply operand. In SIMD the registers could store 4 32 bit floating point numbers (128 bits) and invoking multiply would operate on all four numbers at the same time, in parallel, without interfering with each other. This feature greatly sped up algorithms involving vectors and matrices such as music, image or video games/simulations.

### The Stack

As the CPU executes instructions it keeps track of the location where the next instruction is in memory with a register called the "program counter". If an instruction moves a number into the program counter the CPU uses that number to read the next instruction. This is how a CPU can "jump" to a different location. As it jumps, however, it loses the previous location. This meant instructions had to be very careful about where to send the CPU execution.

The CPU has another special register called the "stack pointer" that a number of instructions manipulate. In stead of a basic jump there is the "call". This instruction moves the program counter to the memory location pointed to by the stack pointer, increments the stack pointer, then loads the program counter with the user-supplied location of the next desired location. The CPU carries on executing instructions just like in the jump but when the CPU reads a "return from call" instruction it decrements the stack pointer, reads the value at the stack pointer back into the program counter and the CPU carries on as if no call had been made. In this manner the programmer does not need to carefully construct their algorithm and can make more re-usable subroutines.

### The Heap

Heap memory is the main memory of an application where data is allocated within by the kernel. The memory manager tracks the specific location in physical memory that the process uses so the application can just access its own memory. This is done in the process page table.

### Memory Management Units (MMU)

As computers came with greater memory sizes (and the increase in demands software made of the computer) a dedicated memory controller became a necessary requirement. This sat between the CPU and the RAM chips and allowed an amount of flexibility with regards to how the memory was mapped into the CPU address space. This became important when hardware peripherals started employing local memory for internal buffers.

If an application needed to talk to a video card at a particular adress the MMU could be used to map the video card memory buffer into its address range. When the CPU wrote to that part of the memory it was really writing to the video card directly.

Another feature of the MMU is Direct Memory Access (DMA) that allowed the MMU to copy data from one part of memory to another. This happened independently of the CPU which could carry on doing something else and was much faster than the CPU method.

### Interrupts

An interrupt is a way of getting the 'attention' of the CPU. They are implemented at the hardware level and often involve physical wires connected to an IRQ (interrupt request) pin. When a piece of hardware (like a disk controller) wants to get the attention of the CPU (a disk was inserted into or removed from the drive) a literal wire from the peripheral to the CPU (or interrupt controller) changes its voltage. The CPU then pushes all its registers onto the stack, looks up the location of the interrupt handler and jumps to that location (typically in the kernel). When the interrupt handler has finished it invokes the special "return from interrupt" instruction that pops the pre-interrupt register state back off the stack and continues. The code being interrupted has no awareness that this has happened. 

There are two types of interrupt; maskable and unmaskable that describe if the interrupt can be 'ignored'. A non-maskable interrupt may be a hardware fault line from a disk controller where the kernel *must* respond. A maskable interrupt may be something like an internal timer. Another classification of interrupts are as hardware interrupts or software interrupts with hardware interrupts typically being non-maskable and software interrupts being ignorable.

### Kernel modes and User Modes

Modern CPUs that can run many applications simultaneously (even on a single core) must have a way of segmenting those applications in memory. Further more to this a special priveleged mode for the kernel must be available so the kernel can talk to the hardware and manage computer resources. This is an extension of the MMU where a table in the MMU is kept describing not only the real memory locations of the data but also permissions. A User Space process will have limited scope to read/write to its own memory segments but the Kernel Space mode can read and write to any memory.


### Pipelining

During the cycle of an instructions execution any one piece of the CPU may be idle waiting its signal. Pipelining is a way of fetching an instruction, decoding it and executing it whilst another instruction is being fetched. In this manner the CPU is being better utilised on each clock cycle. The drawback to this is if a "pipeline miss" happens. When a jump instruction is encountered the CPU must flush the pipeline and set up the new location and re-fill the pipeline again. This can be an expensive operation.

In modern x86-64 CPUs the pipelines are very deep (multi-stage instructions) and may include many instructions "in flight" at once. This facilitates high instruction throughput but makes "pipeline misses" much more expensive. One solution involves having a "speculative execution" unit that can look ahead of the instruction stream and set up *both* sides of a branch. When the branch occurs the path not taken is discarded and none of the clock cycles are wasted by waiting for the pipeline to refill.

### Cache

Another common speed technique is the use of caching. A cache is simply some memory near (or on the same die as) the CPU. Typical main memory is made of a particular kind of circuit that is very compact so a high density can be achieved. It is also fairly slow (compared to CPU register access). CPU cache is much closer to the the CPU and by geometry alone can be accessed faster. But the drawback is it is of a fixed size.

In the x86 core family there exists two types of cache: L1 and L2. L2 cache is how the CPU reads main memory. When a "cache miss" occurs the memory controller will request a page of memory to be copied in. This allows the memory controller to transfer the large page (could be many kilobytes in size) in one go. The CPU then continues reading the memory unaware of the sleight of hand. Sometimes the design of an algorithm must consider the "data locality" where information is stored and accessed to optimise cache use. For example a data structure could be "padded" with extra bytes to reduce cache loads (a data structure larger than the memory page size would need two or more pages to be loaded.) This was a common technique in the 1980s and 90s in video game rendering pipelines to reduce main memory access.

L1 cache is more complicated. Like L2 cache it is even closer to the CPU itself and is found on the same die as the CPU itself. Unlike L2 cache it has two parts: instruction and data. As the CPU consumes instructions and prepares them for execution the intermediate data stream is stored in the L1 cache ready for CPU execution. It is highly desirable for an algorithm to be constructed to fit inside the L1 cache so the only thing the CPU is reading from main memory is user data.

In modern multi core CPUs there is a third layer of cache known as L3 cache. It is like L2 cache in that it is loaded in blocks from main memory but unlike L2 cache it is shared amongst the processor cores in the CPU.

### Register Pool

Modern computers are designed to operate in demanding desktop situations where a user will want to run multiple applications at the same time. To a processor core when one task needs to be put to one side and another bought in the CPU must save its internal state to memory, load the internal state from memory and continue. This is very expensive. So the CPU designers may employ a "register set" where by the CPU treats its registers like slots in a special kind of memory. So when an instruction comes to halt the CPU and save its state it just moves a pointer to the current slot in the register pool along and continues executing with the other data.

### Execution Units

When pipelining gained noteriaty and more common CPU designers found another way to increase throughput was by having multiple execution units. An en execution unit such as an ALU can only do one thing- but by dispatching instructions to multiple ALUs the CPU could operate on multiple levels of instructions at once.

### Dynamic clocking

Power consumption is a key concern of end-users as CPUs become more capable. The electronics on modern chip can be so dense it takes a lot of energy to operate. But as CPU designers worked to decouple the parts of a CPU they started employing more complex clock schemes. This allowed parts of the CPU to reduce their clock speed dynamically saving on power consumption. It also meant that CPU systems could operate much faster in "burst mode".

As computers became more portable the down-clocking became an important method of reducing battery load.

### Virtual Memory

Virtual Memory is an extension of the MMU that allows pages to exist in the memory manager but not be in memory. In stead the kernel sets up a special location on the users disk to save snapshots of the memory page. When the kernel runs out of memory it saves infrequently used pages to disk, marks the memory table as "virtualised" and loads the requested data into the now-available memory. If the CPU accesses the "virtualised" memory the MMU signals an interrupt to the CPU (and kernel) and the wanted memory can be restored back to memory (and again the least used emmory page can be shuffled to disk).

Another feature of the MMU and virtual memory was in security. If one application tried to access memory not in its address space the CPU would be signalled and the application would be terminated.

### Virtualised CPUs

The x86 architecture is a testament to backward compatibility. In the latest generation of 64 bit multi-core chips is a capability to execute 8086 instructions in hardware. Another part of this compatibility is the ability to run "virtualised" CPUs where the host kernel can configure a CPU core (the client) to behave as if it itself were a host core. The client environment has little awareness of this virtualisation and can load software into its partition as if it were the only software running. The trick is when the client CPU talks to the "hardware" the host kernel intervenes and proxies the interaction to the real hardware. In practice the host kernel must have this virtualisation capability and the client kernel must speak to the hardware with special drivers for this "virtualised" environment. Peripherals and firmware on the host computer can even have this virtualised capability built into them, for example disk controllers and network adapters.

Much of the "cloud" operates on this principle: one large machine with many CPUs and a lot of RAM will be partitioned into virtualised machines that the customers interact with. The instances are very secure and can be moved or cloned from one machine to the next making for a very dynamic environment. Meanwhile the physical hardware is very static.

In recent years fully virtualised environment have been supplimented with OS level resource partitioning. Docker and kubernetes are examples of this. Using kernel features to partition disk, processor and memory a single process can exist in a "cage" with its requisite libraries and configuration files. As all the cages use the same kernel and IO they consume less resources (not having to virtualize an entire machine with their own kernel and system libraries).












## Part 3: The Computer

### Firmware

Firmware is software that has a permanent residence in a device or computer. Unlike software that is stored on a disk- firmware is stored in such a manner that when a microprocessor first powers on it can start executing the firmware immediately without any set up. In a PC the motherboard has a firmware chip that the CPU uses to turn on various devices and check if the memory and peripherals are behaving as expected.

Firmware is also found extensively in embedded devices like mice, webcams etc. that have a micro-controller in. In embedded systems the firmware is the only software that is needed for the device to function. Where as in a PC the firmware will load the system-loader off an internal disk and pass control to that.

### The Kernel

The OS kernel is responsible for sitting between the physical hardware and the user-space software. It is loaded by the system loader and handed control of the computer. The kernel then initializes its various subsystems (like the memory manager and networking) and loads drivers. Usually the kernel then loads the initial process which is responsible for bringing up the users operating environment.

### Libraries and linking

One of the key parts of the kernel is the ability to start user selected applications. In a modern multi-tasking environment this is done by the kernel forking a process to allocate memory pages, reading the binary code of the application into memory (marking the page as executable), and then linking the applications code points to any required libraries.

In single-tasking OS environments (like DOS) the kernel just loaded the binary into RAM and did a CPU jump to the codes entry point. When the application was done it would signal an interrupt and DOS would continue.

### Multi-tasking

Multi tasking is the ability for a computer to run many pieces of code at the same time. Before multi-core computers existed this was achieved by slicing up time between different pieces of code. In the late 1980s this was done through "cooperative multi tasking" where the application (typically a GUI running in early Mac OS or Windows) would 'yield' execution to the kernel that would pass execution onto the next piece of code in the task pool. If an application crashed or locked up it may never yield back to the kernel and the entire desktop would lock up.

Later versions of Windows (95 and onward) used "pre-emptive multi-tasking" where a timer would fire and the kernel would move onto the next application in the pool. This meant applications had no awareness of when they would lose control. If an application crashed the other applications would keep running.

In multi-processor systems only interrupt based multi-tasking is used as the cores can literally run two or more things at once. It also means drivers and hardware have to be capable of handling this access pattern.

### System calls

As user processes run in user mode they cannot access hardware directly. In order to perform IO they must employ what is called a "system call" where a set of parameters are placed in specific registers and a (software) interrupt. This allows the CPU to switch mode to kernel mode and invoke the handler that then dispatches the user request to the relevant drivers that can talk to the hardware. In this way the kernel provides functionality to the running user-land software.

In practice these system calls are wrapped in layers of abstraction through shared libraries. For example in a network based application that uses TCP sockets most of the network abstraction is in the user space library and only the very low level IO has to be passed to the kernel. This can be pushed out further if the user is utilising a HTTP library that is built on the TCP library.


### The Operating System

An Operating system is the name of a group of software that work together to provide the user an environment to run applications. The primary components of an OS are: the system loader, the kernel, device drivers, service manager and desktop. In an OS like Linux these components can be swapped around at will (except the kernel/drivers must match each other). This allows the construction of a very cut down environment that can do a very specific task. e.g. a mail server running in a data centre would not need a print server or GUI.





