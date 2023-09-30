#ifndef SOS_SPIN_LOCK_H
#define SOS_SPIN_LOCK_H

#include "types.h"
#include "atomics.h"

typedef volatile u64 lock;

void init_lock(lock* lock);
bool try_lock(lock* lock);
void spin_lock(lock* lock);
void spin_unlock(lock* lock);

void spin_lock_irq(lock* lock);
void spin_unlock_irq(lock* lock);

#endif
