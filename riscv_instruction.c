#include <stdio.h>
#include <stdlib.h>
#include "riscv_instruction.h"
#include "instruction_def.h"


/*********************************************/
/*                                           */
/* functions for instructions  RV32I base    */
/*                                           */
/*********************************************/
/* @param rd,rrs1,rrs2 stand for the index of a register */

/* Loads */
void lb(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm);  // byte 
void lh(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm);  // halfword
void lw(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int ld, int rs1, int imm);  // word
void lbu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int ld, int rs1, int imm); // byte unsigned 
void lhu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int ld, int rs1, int imm); // half unsigned

/* Stores */
void sb(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);  // byte 
void sh(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);  // halfword
void sw(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);  // word

/* Arithmetic */ 
void add(Riscv64_register* riscv_register, int rd, int rs1, int rs2)               // add
{
	riscv_register->x[rd] = riscv_register->x[rs1] + riscv_register->x[rs2]; 
	return;
}

void addi(Riscv64_register* riscv_register, int rd, int rs1, int imm);              // add immediate
void sub(Riscv64_register* riscv_register, int rd, int rs1, int rs2);               // subtract
void lui(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int imm);       // load upper immediate
void auipc(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int imm);     // add upper immediate to pc

/* Logical */
void xor(Riscv64_register* riscv_register, int rd, int rs1, int rs2);        // xor 
void xori(Riscv64_register* riscv_register, int rd, int rs1, int imm);       // xor immediate
void or(Riscv64_register* riscv_register, int rd, int rs1, int rs2);         // or 
void ori(Riscv64_register* riscv_register, int rd, int rs1, int imm);        // or immediate
void and(Riscv64_register* riscv_register, int rd, int rs1, int rs2);        // and
void andi(Riscv64_register* riscv_register, int rd, int rs1, int imm);       // and immediate

/* Shifts */
void sll(Riscv64_register* riscv_register, int rd, int rs1, int rs2);         // shift left
void slli(Riscv64_register* riscv_register, int rd, int rs1, int shamt);      // shift left immediate
void srl(Riscv64_register* riscv_register, int rd, int rs1, int rs2);         // shift right
void srli(Riscv64_register* riscv_register, int rd, int rs1, int shamt);      // shift right immediate
void sra(Riscv64_register* riscv_register, int rd, int rs1, int rs2);         // shift right arithmetic
void srai(Riscv64_register* riscv_register, int rd, int rs1, int shamt);      // shift right arithmetic immediate

/* Compare */
void slt(Riscv64_register* riscv_register, int rd, int rs1, int rs2);         // set <
void slti(Riscv64_register* riscv_register, int rd, int rs1, int imm);        // set < immediate
void sltu(Riscv64_register* riscv_register, int rd, int rs1, int rs2);        // set < unsigned 
void sltiu(Riscv64_register* riscv_register, int rd, int rs1, int imm);       // set < unsigned immediate

/* Branches */
void beq(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);
void bne(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);
void blt(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);
void bgt(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);
void bltu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);
void bgeu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);

/* Jump & Link */
void jal(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int imm);
void jalr(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm);

/* System */
void scall();


/*********************************************/
/*                                           */
/* functions for instructions  RV64I         */
/*                                           */
/*********************************************/

/* Loads */
void lwu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm);   
void ld(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm);   

/* Stores */
void sd(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm);  

/* Arithmetic */
void addw(Riscv64_register* riscv_register, int rd, int rs1, int rs2);
void addiw(Riscv64_register* riscv_register, int rd, int rs1, int imm);
void subw(Riscv64_register* riscv_register, int rd, int rs1, int rs2);

/* Shifts */
void sllw(Riscv64_register* riscv_register, int rd, int rs1, int rs2);
void slliw(Riscv64_register* riscv_register, int rd, int rs1, int shamt);
void srlw(Riscv64_register* riscv_register, int rd, int rs1, int rs2);
void srliw(Riscv64_register* riscv_register, int rd, int rs1, int shamt);
void sraw(Riscv64_register* riscv_register, int rd, int rs1, int rs2);
void sraiw(Riscv64_register* riscv_register, int rd, int rs1, int shamt);