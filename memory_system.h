#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef unsigned char      reg8;
typedef unsigned short int reg16;
typedef unsigned int       reg32;
typedef unsigned long int  reg64;

typedef unsigned char bool;
typedef unsigned char byte;
typedef unsigned int instruction;

// abi alias 
#define sp   x[14]   // stack pointer
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
	int shamt;
	int I_immediate;
	int S_immediate;
	int SB_immediate;
	int U_immediate;
	int UJ_immediate;
} Riscv64_decoder;


/*
	x[0]    zero    Hard-wired zero
	x[1]    ra      Return address
	x[2]    s0/fp   Saved register/frame pointer 
	x[3]    s1      Saved registers
	x[4]    s2      ..
	x[5]    s3      ..
	x[6]    s4      ..
	x[7]    s5      ..
	x[8]    s6      ..
	x[9]    s7      ..
	x[10]   s8      ..
	x[11]   s9      ..
	x[12]   s10     ..
	x[13]   s11     ..
	x[14]   sp      Stack pointer
	x[15]   tp      Thread pointer
	x[16]   v0      Return values
	x[17]   v1      ..
	x[18]   a0      Function arguments
	x[19]   a1      ..
	x[20]   a2      ..
	x[21]   a3      ..
	x[22]   a4      ..
	x[23]   a5      ..
	x[24]   a6      ..
	x[25]   a7      ..
	x[26]   t0      Temporaries
	x[27]   t1      ..
	x[28]   t2      ..
	x[29]   t3      .. 
	x[30]   t4      ..
	x[31]   gp      Global pointer
*/
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
void init_decoder(Riscv64_decoder**);
void init_memory(Riscv64_memory**);
void init_register(Riscv64_register**, Riscv64_memory*);
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