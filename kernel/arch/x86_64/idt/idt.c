#include <arch/x86_64/cpu/cpu.h>
#include <arch/x86_64/idt/idt.h>
#include <libc/stdio/printf.h>
#include <stddef.h>
#include <stdint.h>
#include <tools/logger.h>
#include <tools/panic.h>

#define IDT_ENTRIES 256

idt_entry_t idt[IDT_ENTRIES];
idt_pointer_t idt_p;
extern void *last_rbp;

extern uint64_t isr_tbl[];

static const char *exception_strings[32] = {"Division By Zero",
											"Debug",
											"Nonmaskable Interrupt",
											"Breakpoint",
											"Overflow",
											"Bound Range Exceeded",
											"Invalid Opcode",
											"Device Not Available",
											"Double Fault",
											"Coprocessor Segment Overrun",
											"Invalid TSS",
											"Segment Not Present",
											"Stack Segment Fault",
											"General Protection Fault",
											"Page Fault",
											"Reserved",
											"x87 FPU Error"
											"Alignment Check",
											"Machine Check",
											"Simd Exception",
											"Virtualization Exception",
											"Control Protection Exception",
											"Reserved",
											"Reserved",
											"Reserved",
											"Reserved",
											"Reserved",
											"Reserved",
											"Hypervisor Injection Exception",
											"VMM Communication Exception",
											"Security Exception",
											"Reserved"};
extern void load_idt(uint64_t);

void set_idt_gate(int num, uint64_t base, uint16_t sel, uint8_t flags) {
	idt[num].offset_low = (base & 0xFFFF);
	idt[num].offset_middle = (base >> 16) & 0xFFFF;
	idt[num].offset_high = (base >> 32) & 0xFFFFFFFF;
	idt[num].selector = sel;
	idt[num].ist = 0;
	idt[num].flags = flags;
	idt[num].zero = 0;
}

void init_idt() {
	idt_p.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
	idt_p.base = (uint64_t)&idt;

	asm("sti");

	for(int i = 0; i < IDT_ENTRIES; ++i) {
		set_idt_gate(i, isr_tbl[i], 0x28, 0x8E);
	}

	load_idt((uint64_t)&idt_p);
	asm("cli");
}

void excp_handler(int_frame_t frame) {
	if(frame.vector < 0x20) {
		panic(exception_strings[frame.vector], &frame);
		hcf();
	} else if(frame.vector >= 0x20 && frame.vector <= 0x2f) {
		// TODO: IRQ and PIC remapping
	} else if(frame.vector == 0x80) {
		// TODO: System calls
	}
}
