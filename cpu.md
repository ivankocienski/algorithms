# Central Processing Units

The CPU is the heart of a computer that performs all the computation necessary to provide utility to the end-user. When paired with memory and IO devices it forms what is called a "computer system".

Please note that this explanation is primarily going to focus on the x86 (64 bit) family of CPUs for examples.

## Basic Logical Computer
!(Logical Computer Diagram)[/images/basic-logical-computer.svg]

The logical computer diagram represents how data flows through a computer system where the CPU is at the centre orchastrating the entire process.

## Basic Physical Computer
!(Physical Computer Diagram)[/images/basic-physical-computer.svg]

The physical layout of a computer is more likely to follow from the above diagram where a "main bus" connects all of the components together. This type of layout is very simple and cheap which is why many early home computers (of the late 1970s and early 1980s) took this approach. It has a low cost but by having all the components share the same bus resource contention was common place. This happens when information is being read from the input device and stored in the RAM whilst the output device could be delivering data from the ROM. Whilst both of these activities share none of same components the main bus (and the CPU) can only do one task at a time- read the input device or write to the output. This is known as a "bottleneck".

## A Modern Computer

Modern desktop PCs have an architecture that is less centralized. Using "intelligent" devices that are essentially problem-specific computers in their own right much of the "work" can be offloaded from the CPU bottleneck. 

# The CPU

The only information that is stored in a computer is the binary representation of numeric values. How these numbers are interpreted to perform operations is constructed from the design engineers layout the circuit board and the CPU designers specifying what the computer can do.

## Instructions

An instruction is just a number that has a special meaning to the CPU to command it to perform an operation. How the CPU executes instructions should not matter to software engineers: there is a specification the CPU implements and the programmers write software to that specification.

There are two approaches to CPU instruction design- RISC (reduced instruction set computing) and CISC (complex instruction set computing). RISC has fewer instructions and constrains the programmer to form an algorithm explicitly as a sequence of steps. CISC has many instructions to use so the programmer can focus on implementing more code rather than solving similar problems many times.

## CISC

In the early days of computers (before 1980) computer memory was very expensive and slow so vendors built as many common operations into the instruction set as possible (to save valuable customer space). Operations like multiply, divide, modulus, string manipulation, floating point mathematics and so on. This reduced code size but made the architectures very complex and many of these esoteric instructions could go unused and be dead weight.
Intel X86 (and the later x86_64) instruction set is so massive it has to employ a technique called "microcode" to implement some of the functionality. Microcode is like having a computer inside your computer where the CPU decodes an instruction and then has to jump to a table (in its own internal memory, no less) to know how to execute that instruction.

## RISC

As a response to the increasingly complicated CPUs with their high power consumption or slower execution time designers developed started exploring a different approach. By reducing the complexity of the CPU to the bare minimum instructions for performing operations programmers could implement the complex algorithms themselves in machine code. This meant the CPU would be much smaller, cost less to buy and run and did not come with functionality that the programmer would never use.

As RISC is simpler and more space/power efficient it is often found in embedded micro-controllers.

## How computation works

At the core of a CPU is the Arithmetic Logic Unit (ALU) that performs basic numerical operations like add, invert, subtract, shift etc. on one or two numbers. These values are fed from the CPU *registers* or *memory* (in CISC). The result of this operation would be written back to an accumulator register. As an aside all ALU operaions would update a special register called the status register that indicated a number of important facts about the previous operation: the zero flag would be set if the operation was zero, the carry flag would be set if the two number over-flowed the machine word size and the negative bit if the result was less than zero. Instructions could then conditionally execute depending on the status of these bits. 
Finally there is the four stage instruction cycle that is controlled by the CPU sequencer. The four stages are (1) fetch, (2) decode, (3) execute and (4) write back.

## Word size

A CPU is often referred to as 8, 16, 32 or 64 bit. This number is how large the basic register size is. The 6502 was 8 bit because its registers had 8 bits or storage although its address registers were 16 bit. The x86-64 has 64 bit basic registers.

## Floating Point (and SIMD)

Floating point is a method of representing non-integer real numbers in binary. Originally (in home PCs) this was done in the software that needed such capability. It was slow (although written in assembler) and took up valuable space in the limited memory. 

Hardware floating point secondary processors existed but were mainly used in high end work-stations meant for serious computation. The domestic market saw wide spread deployment of floating point with the 486DX processor; a variant of the 486 with a FP unit built in (actually all 486s had a floating point units etched into them but during fabrication a test on the FPU was performed and if it failed the FPU was disconnected from the main processor and it was sold as a 'SX' variant. This meant only one fabrication pipeline was needed and Intel could increase its yield).

Floating point is represented at the register as a 32 bit word containing 1 sign bit, 8 exponent bits and 23 mantissa bits. This forms the representation like X^Y where X is the signed 8 bit number and Y is the signed power. When Y is positive numbers greater than 255 can be represented and when Y is negative numbers smaller 1 can be held. One problem of such a scheme is that due to the fixed nature of the representation aliasing can occur where a number will be rounded to its nearest representation in the register. This rounding (sometimes called under-flow) can accumulate into larger and larger errors.

## Interrupts

## Multi-tasking


## Optimisations

### Pipelining

During the cycle of an instructions execution any one piece of the CPU may be idle waiting its signal. Pipelining is a way of fetching an instruction, decoding it and executing it whilst another instruction is being fetched. In this manner the CPU is being better used on each clock cycle. The drawback to this is if a "pipeline miss" happens. When an jump instruction is encountered the CPU must flush the pipeline and set up the new location and re-fill the pipeline again. This can be an expensive operation.

In modern x86_64 CPUs the pipelines are very deep (multi-stage instructions) and may include many instructions "in flight" at once. This facilitates high instruction throughput but makes "pipeline misses" much more expensive. One solution involves having a "speculative execution" unit that can look ahead of the instruction stream and set up *both* sides of a branch. When the branch occurs the path not taken is discarded and none of the clock cycles are wasted by waiting for the pipeline to refill.

### Cache

Another common speed technique is the use of caching. A cache is simply some memory near (or on the same die as) the CPU. Typical main memory is made of a particular kind of circuit that is very compact so a high density can be achieved. It is also fairly slow (compared to CPU register access). CPU cache is much closer to the the CPU and by geometry alone can be accessed faster. But the drawback is it is of a fixed size.

In the x86 core family there exists two types of cache: L1 and L2. L2 cache is how the CPU reads main memory. When a "cache miss" occurs the memory controller will request a page of memory to be copied in. This allows the memory controller to transfer the large page (could be many kilobytes in size) in one go. The CPU then continues reading the memory unaware of the sleight of hand. Sometimes the design of an algorithm must consider the "data locality" where information is stored and accessed to optimise cache use. For example a data structure could be "padded" with extra bytes to reduce cache loads (a data structure larger than the memory page size would need two or more pages to be loaded.) This was a common technique in the 1980s and 90s in video game rendering pipelines to reduce main memory access.

L1 cache is more complicated. Like L2 cache it is even closer to the CPU itself and is found on the same die as the CPU itself. Unlike L2 cache it has two parts: instruction and data. As the CPU consumes instructions and prepares them for execution the intermediate data stream is stored in the L1 cache ready for CPU execution. It is highly desirable for an algorithm to be constructed to fit inside the L1 cache so the only thing the CPU is reading from main memory is user data.

In modern multi core CPUs there is a third layer of cache known as L3 cache. It is like L2 cache in that it is loaded in blocks from main memory but unlike L2 cache it is shared amongst the processor cores in the CPU.

### Register Pool

Modern computers are designed to operate in demanding desktop situations where a user will want to run multiple applications at the same time. To a processor core when one task needs to be put to one side and another bought in the CPU must save its internal state to memory, load the internal state from memory and continue. This is very expensive. So the CPU designers may employ a "register set" where by the CPU treats its registers like slots in a special kind of memory. So when an instruction comes to halt the CPU and save its state it just moves a pointer to the current slot in the register pool along and continues executing with the other data.

### Execution Units

When pipelining gained noteriaty and more common CPU designers found another way to increase throughput was by having multiple execution units. An en execution unit such as an ALU can only do one thing- but by dispatching instructions to multiple ALUs the CPU could operate on multiple levels of instructions at once. blugh

### Dynamic clocking

Power consumption is a key concern of end-users as CPUs become more capable. The electronics on modern chip can be so dense it takes a lot of energy to operate. But as CPU designers worked to decouple the parts of a CPU they started employing more complex clock schemes. This allowed parts of the CPU to reduce their clock speed dynamically saving on power consumption. It also meant that CPU systems could operate much faster in "burst mode".

As computers became more portable the down-clocking became an important method of reducing battery load.

### Virtual Memory

As memory capacity grew (both in purchasable products and more capable processors) demands on computers to perform more increased. By the late 1980s graphical user interfaces and multi-tasking became increasingly desired. Users wanted to run more than one application at the same time but developers wanted to stick to the same style of programming that served their needs.

Virtual Memory is a hardware solution to this problem. The CPU would proxy all its memory accesses through a Memory Management Unit. This allowed the block of memory to become segmented; each application would use its segment as if it were running on a single-tasking platform and the MMU would modify memory accesses from 'program space' to 'memory space'. This involved the MMU keeping a table of segments that could be switched into the CPUs address space with little overhead.

Furthermore these segments could be moved around the physical memory without the user application being aware. Later developments allowed segments of memory to be saved to disk. The MMU table would keep a record of these stored segments and when the CPU tried to access a segment that was out-of-ram an interrupt would be given from the MMU to the CPU that allowed the OS to move the table from disk back into RAM and continue. 

Another feature of the MMU and virtual memory was in security. If one application tried to access memory not in its address space the CPU would be signalled and the application would be terminated.

### Virtual CPUs
