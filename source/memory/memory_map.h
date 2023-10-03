#ifndef SOS_MEMORY_MAP_H
#define SOS_MEMORY_MAP_H

#include "../lib/types.h"

//=====================================================
// Complete virtual memory map with 4-level page tables
//=====================================================

//==============================================================================
//    Start addr    | Offset   |     End addr     | Description
//==============================================================================
//                  |          |                  |
// 0000000000000000 |  0       | 00007fffffffffff | user-space virtual memory
//__________________|__________|__________________|_____________________________
//                  |          |                  |
// 0000800000000000 | +128  TB | ffff7fffffffffff | non-canonical virtual memory
//__________________|__________|__________________|_____________________________
//                                                |
//                                                | Kernel-space virtual memory
//________________________________________________|_____________________________
// ffff800000000000 | -128  TB | ffff87ffffffffff | Kernel code
// ffff888000000000 | -119.5TB | ffffc87fffffffff | direct mapping of all
//                  |          |                  | physical memory
//__________________|__________|__________________|_____________________________

#define paddr u64
#define vaddr u64

#define RESERVED_LOWER_PMEM_SIZE 1024 * 1024; // 1MB

#define KERNEL_START_VADDR 0xFFFF800000000000             // 256 entry in p4
#define KERNEL_VMAPPED_RAM_START_VADDR 0XFFFF888000000000 // 273 entry in p4

#define IS_CANONICAL(vaddr)                                                    \
    ((vaddr) < 0x0000800000000000) || ((vaddr) > 0XFFFF7FFFFFFFFFFF)

#define FRAME_SIZE 4096

#define P2V(addr) ((addr) + KERNEL_VMAPPED_RAM_START_VADDR)
#define V2P(addr) ((addr) -KERNEL_VMAPPED_RAM_START_VADDR)

#endif // SOS_MEMORY_MAP_H
