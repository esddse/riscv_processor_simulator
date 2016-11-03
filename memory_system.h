#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "riscv_instruction.h"

typedef unsigned char      reg8;
typedef unsigned short int reg16;
typedef unsigned int       reg32;
typedef unsigned long int  reg64;

typedef unsigned char bool;
typedef unsigned char byte;
// some alias 
#define zero x[0]    // hard-wired zero
#define ra   x[1]    // return address
#define s0   x[2]    // saved register
#define fp   x[2]    // frame pointer
#define s1   x[3]    // saved register
#define s2   x[4]    // ..
#define s3   x[5]    // .. 
#define s4   x[6]    // ..
#define s5   x[7]    // ..
#define s6   x[8]    // ..
#define s7   x[9]    // ..
#define s8   x[10]   // ..
#define s9   x[11]   // ..
#define s10  x[12]   // ..
#define s11  x[13]   // ..
#define sp   x[14]   // stack pointer
#define tp   x[15]   // thread pointer
#define v0   x[16]   // return values
#define v1   x[17]   // ..
#define a0   x[18]   // function arguments
#define a1   x[19]   // ..
#define a2   x[20]   // ..
#define a3   x[21]   // ..
#define a4   x[22]   // ..
#define a5   x[23]   // ..
#define a6   x[24]   // ..
#define a7   x[25]   // ..
#define t0   x[26]   // temporaries
#define t1   x[27]   // ..
#define t2   x[28]   // ..
#define t3   x[29]   // ..
#define t4   x[30]   // ..
#define gp   x[31]   // global pointer

// memory size 128Mb
#define MEM_SIZE 1<<27           // 0x0800 0000
#define STACK_BOTTOM 0x6000000   // virtual address of stack 
#define TRUE 1
#define FALSE 0

// decoder
typedef struct riscv64_decoder{
	int opcode;
	int funct3;
	int funct7;
	int rd;
	int rs1;
	int rs2;
	int immediate;
} Riscv64_decoder;

// register file
typedef struct riscv64_register{
	reg64 pc;
	reg64 x[32];
} Riscv64_register;

// memory
typedef struct riscv64_memory{
	// main memory
	long int mem_size;
	byte *memory;
	byte *stack_bottom;

} Riscv64_memory;


/*********************************************/
/*                                           */
/* initialization and gc                     */
/*                                           */
/*********************************************/
Riscv64_decoder* init_decoder(Riscv64_decoder*);
Riscv64_register* init_register(Riscv64_register*);
Riscv64_memory* init_memory(Riscv64_memory*);
void delete_memory_system(Riscv64_decoder*, Riscv64_register*, Riscv64_memory*); // free the memory 

/*********************************************/
/*                                           */
/* functions for decoder                     */
/*                                           */
/*********************************************/
void decode_instruction(Riscv64_decoder*);


/*********************************************/
/*                                           */
/* functions for memory                      */
/*                                           */
/*********************************************/

/* note: actual_addr stands for the addr in your machine  */
/*       while virtual_addr for the addr in the simulator */
byte* get_actual_addr(Riscv64_memory*, byte* virtual_addr); // return the actual addr in this machine
byte* get_virtual_addr(Riscv64_memory*, byte* actual_addr); // invese function of the function above
bool out_of_memory_virtual(Riscv64_memory*, byte* virtual_addr);
bool out_of_memory_actual(Riscv64_memory*, byte* actual_addr); // judge if the actual address is out of virtual memory  
void check_valid_memory_virtual(Riscv64_memory*, byte* virtual_addr); // check if the virtual memory is valid, if not exit(1)

/* note: the only way to access memory is through vitual_addr */
void  set_memory_reg8(Riscv64_memory*, byte* virtual_addr, reg8 value);
reg8  get_memory_reg8(Riscv64_memory*, byte* virtual_addr);
void  set_memory_reg16(Riscv64_memory*, byte* virtual_addr, reg16 value);
reg16 get_memory_reg16(Riscv64_memory*, byte* virtual_addr);
void  set_memory_reg32(Riscv64_memory*, byte* virtual_addr, reg32 value);
reg32 get_memory_reg32(Riscv64_memory*, byte* virtual_addr);
void  set_memory_reg64(Riscv64_memory*, byte* virtual_addr, reg64 value);
reg64 get_memory_reg64(Riscv64_memory*, byte* virtual_addr);


/*********************************************/
/*                                           */
/* functions for register file               */
/*                                           */
/*********************************************/
void set_register_pc(Riscv64_register*, reg64 value); // set pc
reg64 get_register_pc(Riscv64_register*); // get a 64-bit value from pc

void set_register_general(Riscv64_register*, int index, reg64 value); // set general register x[index]
reg64 get_register_general(Riscv64_register*, int index); // get a 64-bit value from x[index]

void register_pc_self_increase(Riscv64_register*); // pc self-increase the the next instruction