#include "gdt.h"
#include "interrupts/idt.h"
#include "multiboot.h"
#include "timer.h"
#include "types.h"
#include "vga_print.h"

void init(void);

_Noreturn void kernel_main(void* multiboot_structure) {
    init();

    clear_screen();
    multiboot_info multiboot_info = parse_multiboot_info(multiboot_structure);

    println("memory map: ");
    for (u8 i = 0; i < multiboot_info.mmap.entries_count; i++) {
        print("t: ");
        print_u32(multiboot_info.mmap.entries[i].type);
        print(" s: ");
        print_u64_hex(multiboot_info.mmap.entries[i].base_addr);
        print(" e: ");
        print_u64_hex(multiboot_info.mmap.entries[i].base_addr
                      + multiboot_info.mmap.entries[i].length - 1);
        print(" l: ");
        print_u64(multiboot_info.mmap.entries[i].length / 1024);
        println("kb");
    }

        println("");
        println("elf sections: ");
        elf64_shdr name_table =
            multiboot_info.elf_sections.sections[multiboot_info.elf_sections.shndx];

        for (u64 i = 0; i < multiboot_info.elf_sections.sections_number; i++) {
            print("s: ");
            print_u64_hex(multiboot_info.elf_sections.sections[i].addr);
            print(" e: ");
            print_u64_hex(multiboot_info.elf_sections.sections[i].addr
                          + multiboot_info.elf_sections.sections[i].size);
            print(" n: ");
            print(
                (const char*) (name_table.addr +
                               multiboot_info.elf_sections.sections[i].name));
            print(" f: ");
            print_u32(multiboot_info.elf_sections.sections[i].flags);
            println("");
        }

    u64 kernel_start = 0xFFFFFFFFFFFFFFFF;
    u64 kernel_end = 0;

    for (u32 i = 1; i < multiboot_info.elf_sections.sections_number; ++i) {
        elf64_shdr* section = &multiboot_info.elf_sections.sections[i];
        if (section->addr < kernel_start)
            kernel_start = section->addr;
        if (section->addr + section->size > kernel_end)
            kernel_end = section->addr + section->size;
    }

    print("kernel s: ");
    print_u64_hex(kernel_start);
    print(" e: ");
    print_u64_hex(kernel_end);
    println("");

    print("multiboot s: ");
    print_u64_hex((u64) multiboot_structure);
    print(" e: ");
    print_u64_hex((u64) multiboot_structure + multiboot_info.size);

    while (true) {
    }
}

void init(void) {
    init_gdt();

    init_console();

    init_timer();
    init_idt();
}