# Arrays

The array is the simplest data structure in a computer after the integer and can be accessed directly through an instruction inside the CPU. They are defined as a contiguous sequence of memory that is accessed by [POSITION+OFFSET] notation making it very fast. Arrays can contain any data *of the same type* but as CPUs have no type awareness this leaves the interpretation of the contents up to the user. 

Arrays are used as the basis of many other types including buffers, strings, ring buffers, queues and stacks. They are also useful because they can be sorted and searched very quickly.

## Considerations

### Advantages

- fast to access; CPU instruction level access
- cache friendly; CPU cache loads in chunks greater than machine-word length. If the algorithm is progressing from start to end this can ameliroate cache-misses.
- simple; 
- can be pre-computed;

### Dissadvantages

- expensive to allocate/re-allocate
- care must be taken to not go out-of-bounds
- fixed types (each element must have the same structure)
- if large enough and accessed in random order they can negatively affect memory/cache timing.
- if allocated on 

## Variants

### Static arrays

An array where the size is determined once and cannot be changed (unless re-allocated manually). Useful for loaded data off of storage at application start-up. Can even be stored in the executable at compile time to keep expensive-to-compute tables near by and speed up start up times. 

### Dynamic arrays

The array his hidden behind a facade and the client uses an indirect API to read and write. By so doing the facade can allocate the array internally as needed. If the client reads index beyond the end of the array the internal space can be re-allocated, the contents copied, the old contents released and the client code will be none the wiser. Another advantage is security where every access can be bounds checked.

## Analysis

Access time is always O(1). 
