#include "spin_lock.h"

void init_lock(lock* lock) { atomic_set(lock, 1); }

bool try_lock(lock* lock) { return atomic_exchange(lock, 0) == 1; }

void spin_lock(lock* lock) {
    do {
        __asm__("pause");
    } while (!try_lock(lock));
}

void spin_unlock(lock* lock) { atomic_set(lock, 1); }

void spin_lock_irq(lock* lock) {
    __asm__ volatile("cli");
    spin_lock(lock);
}

void spin_unlock_irq(lock* lock) {
    spin_unlock(lock);
    __asm__ volatile("sti");
}
