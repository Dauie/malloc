# Malloc

This is a personal implementation of the functions: malloc(), free(), and realloc().

## The design

![alt text](https://github.com/Dauie/malloc/blob/master/mallocSS.png "Slab design")

### Tiny and Small allocations
On the first call to malloc() a "slab" sized chunk of memory will be mapped to the program's memory space. The slab will be
segmented into 'tiny' and 'small' blocks, and each block with have a portion of meta-data at its head to manage the block.
Sequential calls to malloc() will return pointers to sufficiently sized blocks in said slab. Once the slab has run out of
blocks to allocate, a new slab will be mapped, segmented, and a block from the new slab will be given.

The manager of these slabs keeps a reference to the next tiny and small blocks that can be given, to increase speed. And when a block is returned from the user, that block will be queued for the next allocation.

### Large allocations

All requests exceeding the size of our small blocks will be mapped separately and stored together as a linked list. When returned from the user, the resource will be immediately given back to the system.

## How to compile:

`git clone https://github.com/dauie/malloc.git`

`cd malloc`

`git clone https://github.com/dauie/libft.git`

`make`
