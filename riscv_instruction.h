#include "memory_system.h"




/* a tool, create a binary number like this :   */
/*                                              */
/*     value:  000... 00000111...1111000...000  */
/*  position:  31...       y  ...   x ...  210  */
/*                                              */
/*  for all k if (31>=x>=k>=y>=0), bit(k) = 1,  */
/*                      otherwise, bit(k) = 0   */
#define ONES(x,y)        (((1<<(x+1))-1)-((1<<y)-1))

/* same in all instructions */
#define OPCODE(inst)     inst&ONES(6,0)              // 7
#define FUNCT3(inst)     ((inst&ONES(14,12))>>12)    // 3
#define FUNCT7(inst)     ((inst&ONES(31,25))>>25)    // 7
#define RD(inst)         ((inst&ONES(11,7))>>7)      // 5
#define RS1(inst)        ((inst&ONES(19,15))>>15)    // 5
#define RS2(inst)        ((inst&ONES(24,20))>>20)    // 5
<<<<<<< HEAD
#define SHAMT(inst)      ((inst&ONES(25,20))>>20)    // 6, RV64I
=======
>>>>>>> 573c4601007db82bb46e59e9a5a767c9d59ebd86
#define IMM_SIGN(inst)   ((inst>>31)&1)               // sign of immediate


/* --------------------   immediates  ------------------------    */


/* R-type                               */
/* funct7--rrs2--rrs1--funct3--rd--opcode */
/*    7-----5----5-----3------5----7    */

// no immediate 

/* I-type                               */
/* imm[11:0]--rrs1--funct3--rd--opcode   */
/*    12-------5-----3-----5-----7      */
#define I_IMM(inst)      (((inst&ONES(31,20)) >> 20) | (IMM_SIGN(inst)*ONES(31,11))) 

/* S-type                                        */
/* imm[11:5]--rrs2--rrs1--funct3--imm[4:0]--opcode */
/*     7-------5----5-----3--------5--------7    */                      
#define S_IMM(inst)      (((inst&ONES(11,7))>>7) | ((inst&ONES(30,25))>>20) | (IMM_SIGN(inst)*ONES(31,11))) 

/* SB-type */
/* imm[12|10:5]--rs2--rs1--funct3--imm[4:1|11]--opcode */
/*     7----------5----5-----3-----------5--------7    */ 
#define SB_IMM(inst)     (((inst&ONES(11,8))>>7) | ((inst&ONES(30,25))>>20) | ((inst&ONES(7,7))<<4) | (IMM_SIGN(inst)*ONES(31,12)))     

/* U-type                 */
/* imm[31:12]--rd--opcode */
/*    20--------5----7    */
#define U_IMM(inst)      (inst&ONES(31,12))  

<<<<<<< HEAD
/* J-type */
#define J_IMM(inst)      (((inst&ONES(30,21))>>20) | ((inst&ONES(20,20))>>9) | (inst&ONES(19,12)) | (IMM_SIGN(inst)*ONES(31,20)))  

/* UJ-type */
#define UJ_IMM(inst)      (((inst&ONES(30,21))>>20) | ((inst&ONES(20,20))>>9) | (inst&ONES(19,12)) | (IMM_SIGN(inst)*ONES(31,20))) 
// same as J-type?



/*********************************************/
/*                                           */
/* functions for instructions  RV32I base    */
/*                                           */
/*********************************************/
/* @param rd,rrs1,rrs2 stand for the index of a register */

/* Loads */
void lb(Riscv64_register*, Riscv64_memory*, int rd, int rs1, int imm);  // byte 
void lh(Riscv64_register*, Riscv64_memory*, int rd, int rs1, int imm);  // halfword
void lw(Riscv64_register*, Riscv64_memory*, int ld, int rs1, int imm);  // word
void lbu(Riscv64_register*, Riscv64_memory*, int ld, int rs1, int imm); // byte unsigned 
void lhu(Riscv64_register*, Riscv64_memory*, int ld, int rs1, int imm); // half unsigned

/* Stores */
void sb(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);  // byte 
void sh(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);  // halfword
void sw(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);  // word

/* Arithmetic */ 
void add(Riscv64_register*, int rd, int rs1, int rs2);               // add
void addi(Riscv64_register*, int rd, int rs1, int imm);              // add immediate
void sub(Riscv64_register*, int rd, int rs1, int rs2);               // subtract
void lui(Riscv64_register*, Riscv64_memory*, int rd, int imm);       // load upper immediate
void auipc(Riscv64_register*, Riscv64_memory*, int rd, int imm);     // add upper immediate to pc

/* Logical */
void xor(Riscv64_register*, int rd, int rs1, int rs2);        // xor 
void xori(Riscv64_register*, int rd, int rs1, int imm);       // xor immediate
void or(Riscv64_register*, int rd, int rs1, int rs2);         // or 
void ori(Riscv64_register*, int rd, int rs1, int imm);        // or immediate
void and(Riscv64_register*, int rd, int rs1, int rs2);        // and
void andi(Riscv64_register*, int rd, int rs1, int imm);       // and immediate

/* Shifts */
void sll(Riscv64_register*, int rd, int rs1, int rs2);         // shift left
void slli(Riscv64_register*, int rd, int rs1, int shamt);      // shift left immediate
void srl(Riscv64_register*, int rd, int rs1, int rs2);         // shift right
void srli(Riscv64_register*, int rd, int rs1, int shamt);      // shift right immediate
void sra(Riscv64_register*, int rd, int rs1, int rs2);         // shift right arithmetic
void srai(Riscv64_register*, int rd, int rs1, int shamt);      // shift right arithmetic immediate

/* Compare */
void slt(Riscv64_register*, int rd, int rs1, int rs2);         // set <
void slti(Riscv64_register*, int rd, int rs1, int imm);        // set < immediate
void sltu(Riscv64_register*, int rd, int rs1, int rs2);        // set < unsigned 
void sltiu(Riscv64_register*, int rd, int rs1, int imm);       // set < unsigned immediate

/* Branches */
void beq(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);
void bne(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);
void blt(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);
void bgt(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);
void bltu(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);
void bgeu(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);

/* Jump & Link */
void jal(Riscv64_register*, Riscv64_memory*, int rd, int imm);
void jalr(Riscv64_register*, Riscv64_memory*, int rd, int rs1, int imm);

/* System */
void scall();


/*********************************************/
/*                                           */
/* functions for instructions  RV64I         */
/*                                           */
/*********************************************/

/* Loads */
void lwu(Riscv64_register*, Riscv64_memory*, int rd, int rs1, int imm);   
void ld(Riscv64_register*, Riscv64_memory*, int rd, int rs1, int imm);   

/* Stores */
void sd(Riscv64_register*, Riscv64_memory*, int rs1, int rs2, int imm);  

/* Arithmetic */
void addw(Riscv64_register*, int rd, int rs1, int rs2);
void addiw(Riscv64_register*, int rd, int rs1, int imm);
void subw(Riscv64_register*, int rd, int rs1, int rs2);

/* Shifts */
void sllw(Riscv64_register*, int rd, int rs1, int rs2);
void slliw(Riscv64_register*, int rd, int rs1, int shamt);
void srlw(Riscv64_register*, int rd, int rs1, int rs2);
void srliw(Riscv64_register*, int rd, int rs1, int shamt);
void sraw(Riscv64_register*, int rd, int rs1, int rs2);
void sraiw(Riscv64_register*, int rd, int rs1, int shamt);
=======
/* UJ-type */
/* imm[20|10:1|11|19:12]--rd--opcode */ 
#define UJ_IMM(inst)      (((inst&ONES(30,21))>>20) | ((inst&ONES(20,20))>>9) | (inst&ONES(19,12) | (IMM_SIGN(inst)*ONES(31,20))))  

/* J-type */

// same as UJ-type?
>>>>>>> 573c4601007db82bb46e59e9a5a767c9d59ebd86
