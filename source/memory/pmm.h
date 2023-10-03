#ifndef SOS_PHYSICAL_MEMORY_MANAGER_H
#define SOS_PHYSICAL_MEMORY_MANAGER_H

#include "memory_map.h"

paddr allocate_frame();
void free_frame(paddr frame);

#endif // SOS_PHYSICAL_MEMORY_MANAGER_H
