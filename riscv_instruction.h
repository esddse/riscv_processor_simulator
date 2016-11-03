
typedef unsigned int instruction;

/* a tool, create a binary number like this :   */
/*                                              */
/*     value:  000... 00000111...1111000...000  */
/*  position:  31...       y  ...   x ...  210  */
/*                                              */
/*  for all k if (31>=x>=k>=y>=0), bit(k) = 1,  */
/*                       otherwise bit(k) = 0   */
#define ONES(x,y)        (((1<<(x+1))-1)-((1<<y)-1))

/* same in all instructions */
#define OPCODE(inst)     inst&ONES(6,0)              // 7
#define FUNCT3(inst)     ((inst&ONES(14,12))>>12)    // 3
#define FUNCT7(inst)     ((inst&ONES(31,25))>>25)    // 7
#define RD(inst)         ((inst&ONES(11,7))>>7)      // 5
#define RS1(inst)        ((inst&ONES(19,15))>>15)    // 5
#define RS2(inst)        ((inst&ONES(24,20))>>20)    // 5
#define IMM_SIGN(inst)   ((ins>>31)&1)               // sign of immediate


/* --------------------   immediates  ------------------------    */


/* R-type                               */
/* funct7--rs2--rs1--funct3--rd--opcode */
/*    7-----5----5-----3------5----7    */

// no immediate 

/* I-type                               */
/* imm[11:0]--rs1--funct3--rd--opcode   */
/*    12-------5-----3-----5-----7      */
#define I_IMM(inst)      (((inst&ONES(31,20)) >> 20) | (IMM_SIGN(inst)*ONES(31,11))) 

/* S-type                                        */
/* imm[11:5]--rs2--rs1--funct3--imm[4:0]--opcode */
/*     7-------5----5-----3--------5--------7    */                      
#define S_IMM(inst)      (((inst&ONES(11,7))>>7) | ((inst&ONES(30,25))>>20) | (IMM_SIGN(inst)*ONES(31,11))) 

/* SB-type */
#define SB_IMM(inst)     (((inst&ONES(11,8))>>7) | ((inst&ONES(30,25))>>20) | ((inst&ONES(7,7))<<4) | (IMM_SIGN(inst)*ONES(31,12)))     

/* U-type                 */
/* imm[31:12]--rd--opcode */
/*    20--------5----7    */
#define U_IMM(inst)      (inst&ONES(31,12))  

/* J-type */
#define J_IMM(inst)      (((int&ONES(30,21))>>20) | ((inst&ONES(20,20))>>9) | (inst&ONES(19,12) | (IMM_SIGN(inst)*ONES(31,20)))  

/* UJ-type */

// same as J-type?