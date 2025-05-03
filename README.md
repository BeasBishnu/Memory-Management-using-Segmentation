# Segmentation-Based Memory Management Simulation

This program simulates an operating system's memory management using segmentation. It translates logical addresses into physical addresses and handles segmentation faults.

The goal is to:

- Translate 16-bit logical addresses into physical addresses using the concept of segmentation.
- Simulate segmentation fault conditions when an address is outside the bounds of a segment.
- Clearly state any assumptions made.

## Design Details

- The system has three segments:
  - Code Segment
  - Heap Segment
  - Stack Segment

- Each segment has:
  - A base address (start location in memory)
  - A limit (size of the segment in bytes)

- The system has 64KB of physical memory, divided as follows:
  
  | Segment       | Start Address | Size   | Direction       |
  |---------------|---------------|--------|-----------------|
  | Code Segment  | 32KB          | 2KB    | Grows upwards   |
  | Heap Segment  | 34KB          | 3KB    | Grows upwards   |
  | Stack Segment | 28KB          | 2KB    | Grows downwards |

- A segmentation fault occurs if the offset exceeds the segment's limit.
- Address translation is done using pseudocode from **Chapter 16** of the course reference.
- 

Input Format

- The user enters a 16-bit logical address in hexadecimal format.
- Example: `a56f`
  

Output Format

- If the address is valid:
  - Output the 16-bit physical address in hex format.
- If the address is invalid (out of bounds):
  - Output: Segmentation Fault
    

Assumptions

- The 16-bit logical address is divided into:
  - 4 bits for the segment number
  - 12 bits for the offset
- Segment mapping (by segment number):
  - `0x0`: Code Segment
  - `0x1`: Heap Segment
  - `0x2`: Stack Segment
- All addresses are unsigned
- Memory boundaries are strictly enforced
