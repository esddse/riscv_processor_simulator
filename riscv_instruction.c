#include "riscv_instruction.h"


void Error_NoDef(Riscv64_decoder* riscv_decoder)
{
	printf("Instruction not defined: opcode(%d), funct3(%d), funct7(%d)\n",
	        riscv_decoder->opcode, riscv_decoder->funct3, riscv_decoder->funct7);
	exit(1);
}
// return the instuction type according to the opcode
INSTYPE GetINSTYPE(Riscv64_decoder* riscv_decoder)
{
	switch(riscv_decoder->opcode)
	{
		case 0x33: // b0110011
			return R_TYPE;

		case 0x67: // b1100111
		case 0x03: // b0000011
		case 0x73: // b1110011
			return I_TYPE;

		case 0x23: // b0100011
			return S_TYPE;

		case 0x63: // b1100011
			return SB_TYPE;

		case 0x37: // b0110111
		case 0x17: // b0010111
			return U_TYPE;

		case 0x6F: // b1101111
			return UJ_TYPE;

		case 0x13: // b0010011
			switch(riscv_decoder->funct3)
			{
				case 1: // b001
				case 5: // b101
					return R_TYPE;
				case 0: // b000
				case 2: // b010
				case 3: // b011
				case 4: // b100
				case 6: // b110
				case 7: // b111
					return I_TYPE;
				default:
					return NOT_DEFINED;
			}
		default:
			return NOT_DEFINED;
	}
}

// execute R_TYPE instructions
void R_execute(Riscv64_decoder* riscv_decoder, Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	switch(riscv_decoder->opcode)
	{
		case 0x33: // b0110011
			switch(riscv_decoder->funct3)
			{
				case 0: // b000
					switch(riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							add(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						case 0x20: // b0100000
							sub(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 1: // b001
					switch(riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							sll(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 2: // b010
					switch (riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							slt(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 3: // b011
					switch (riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							sltu(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 4: // b100
					switch (riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							xor(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 5: // b101
					switch (riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							srl(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						case 0x20: // b0100000
							sra(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 6: // b110
					switch (riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							or(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 7: // b111
					switch (riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							and(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->rs2);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				default:
					Error_NoDef(riscv_decoder);
			}
			break;
		case 0x13: // b0010011
			switch(riscv_decoder->funct3)
			{
				case 1: // b001
					switch(riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							slli(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->shamt);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				case 5: // b101
					switch(riscv_decoder->funct7)
					{
						case 0x00: // b0000000
							srli(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->shamt);
							break;
						case 0x20: // b0100000
							srai(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->shamt);
							break;
						default:
							Error_NoDef(riscv_decoder);
					}
					break;
				default:
					Error_NoDef(riscv_decoder);
			}
			break;
		default:
			Error_NoDef(riscv_decoder);
	}
}
// execute I_TYPE instructions
void I_execute(Riscv64_decoder* riscv_decoder, Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	switch(riscv_decoder->opcode)
	{
		case 0x67: // b1100111
			switch(riscv_decoder->funct3)
			{
				case 0: // b000
					jalr(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				default:
					Error_NoDef(riscv_decoder);
			}
			break;
		case 0x03: // b0000011
			switch(riscv_decoder->funct3)
			{
				case 0: // b000
					lb(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 1: // b001
					lh(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 2: // b010
					lw(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 4: // b100
					lbu(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 5: // b101
					lhu(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				default:
					Error_NoDef(riscv_decoder);
			}
			break;
		case 0x73: // b1110011
			switch(riscv_decoder->funct3)
			{
				case 0: // b000
					scall();
					break;
				default:
					Error_NoDef(riscv_decoder);
			}
		case 0x13: // b0010011
			switch(riscv_decoder->funct3)
			{
				case 0: // b000
					addi(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 2: // b010
					slti(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 3: // b011
					sltiu(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 4: // b100
					xori(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 6: // b110
					ori(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
					break;
				case 7: // b111
					andi(riscv_register, riscv_decoder->rd, riscv_decoder->rs1, riscv_decoder->I_immediate);
				default:
					Error_NoDef(riscv_decoder);
			}
			break;
		default:
			Error_NoDef(riscv_decoder);
	}
}
// execute S_TYPE instructions
void S_execute(Riscv64_decoder* riscv_decoder, Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	switch(riscv_decoder->opcode)
	{
		case 0x23: // b0100011
			switch(riscv_decoder->funct3)
			{
				case 0: // b000
					sb(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->S_immediate);
					break;
				case 1: // b001
					sh(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->S_immediate);
					break;
				case 2: // b010
					sw(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->S_immediate);
					break;
				default:
					Error_NoDef(riscv_decoder);
			}
			break;
		default:
			Error_NoDef(riscv_decoder);
	}
}
// execute SB_TYPE instructions
void SB_execute(Riscv64_decoder* riscv_decoder, Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	switch(riscv_decoder->opcode)
	{
		case 0x63: // b1100011
			switch(riscv_decoder->funct3)
			{
				case 0: // b000
					beq(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->SB_immediate);
					break;
				case 1: // b001
					bne(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->SB_immediate);
					break;
				case 4: // b400
					blt(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->SB_immediate);
					break;
				case 5: // b101
					bge(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->SB_immediate);
					break;
				case 6: // b110
					bltu(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->SB_immediate);
					break;
				case 7: // b111
					bgeu(riscv_register, riscv_memory, riscv_decoder->rs1, riscv_decoder->rs2, riscv_decoder->SB_immediate);
					break;
				default:
					Error_NoDef(riscv_decoder);
			}
			break;
		default:
			Error_NoDef(riscv_decoder);
	}
}
// execute U_TYPE instructions
void U_execute(Riscv64_decoder* riscv_decoder, Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	switch(riscv_decoder->opcode)
	{
		case 0x37: // b0110111
			lui(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->U_immediate);
			break;
		case 0x17: // b0010111
			auipc(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->U_immediate);
			break;
		default:
			Error_NoDef(riscv_decoder);
	}
}
// execute UJ_TYPE instructions
void UJ_execute(Riscv64_decoder* riscv_decoder, Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	switch(riscv_decoder->opcode)
	{
		case 0x6F: // b1101111
			jal(riscv_register, riscv_memory, riscv_decoder->rd, riscv_decoder->UJ_immediate);
			break;
		default:
			Error_NoDef(riscv_decoder);
	}
}

/*********************************************/
/*                                           */
/* functions for instructions  RV32I base    */
/*                                           */
/*********************************************/
/* @param rd,rrs1,rrs2 stand for the index of a register */

/* Loads */
void lb(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm)  // byte
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg8 load_value = get_memory_reg8(riscv_memory, (byte*)(reg_value + imm));
	set_register_general(riscv_register, rd, (long int)load_value);
}
void lh(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm)  // halfword
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg16 load_value = get_memory_reg16(riscv_memory, (byte*)(reg_value + imm));
	set_register_general(riscv_register, rd, (long int)load_value);
}
void lw(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm)  // word
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg32 load_value = get_memory_reg32(riscv_memory, (byte*)(reg_value + imm));
	set_register_general(riscv_register, rd, (long int)load_value);
}
void lbu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm) // byte unsigned
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg8 load_value = get_memory_reg8(riscv_memory, (byte*)(reg_value + imm));
	set_register_general(riscv_register, rd, (unsigned long int)load_value);
}
void lhu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm) // half unsigned
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg16 load_value = get_memory_reg16(riscv_memory, (byte*)(reg_value + imm));
	set_register_general(riscv_register, rd, (unsigned long int)load_value);
}

/* Stores */
void sb(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)  // byte
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg8 store_value = (reg8)get_register_general(riscv_register, rs2);
	set_memory_reg8(riscv_memory, (byte*)(reg_value + imm), store_value);
}
void sh(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)  // halfword
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg16 store_value = (reg16)get_register_general(riscv_register, rs2);
	set_memory_reg16(riscv_memory, (byte*)(reg_value + imm), store_value);
}
void sw(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)  // word
{
	reg64 reg_value = get_register_general(riscv_register, rs1);
	reg32 store_value = (reg32)get_register_general(riscv_register, rs2);
	set_memory_reg32(riscv_memory, (byte*)(reg_value + imm), store_value);
}

/* Arithmetic */
void add(Riscv64_register* riscv_register, int rd, int rs1, int rs2)               // add
{
	riscv_register->x[rd] = riscv_register->x[rs1] + riscv_register->x[rs2];
	return;
}

void addi(Riscv64_register* riscv_register, int rd, int rs1, int imm)              // add immediate
{
	riscv_register->x[rd] = riscv_register->x[rs1] + imm;
}
void sub(Riscv64_register* riscv_register, int rd, int rs1, int rs2)              // subtract
{
	riscv_register->x[rd] = riscv_register->x[rs1] - riscv_register->x[rs2];
}
void lui(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int imm)       // load upper immediate
{
	set_register_general(riscv_register, rd, (long int)imm);
}
void auipc(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int imm)     // add upper immediate to pc
{
	reg64 reg_value = get_register_pc(riscv_register) - sizeof(instruction);  // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                                          // we have to subtract it to get the current pc
	set_register_general(riscv_register, rd, (long int)(reg_value + imm));
}

/* Logical */
void xor(Riscv64_register* riscv_register, int rd, int rs1, int rs2)        // xor
{
	riscv_register->x[rd] = riscv_register->x[rs1] ^ riscv_register->x[rs2];
}
void xori(Riscv64_register* riscv_register, int rd, int rs1, int imm)       // xor immediate
{
	riscv_register->x[rd] = riscv_register->x[rs1] ^ (long int)imm;
}
void or(Riscv64_register* riscv_register, int rd, int rs1, int rs2)         // or
{
	riscv_register->x[rd] = riscv_register->x[rs1] | riscv_register->x[rs2];
}
void ori(Riscv64_register* riscv_register, int rd, int rs1, int imm)        // or immediate
{
	riscv_register->x[rd] = riscv_register->x[rs1] | (long int)imm;
}
void and(Riscv64_register* riscv_register, int rd, int rs1, int rs2)        // and
{
	riscv_register->x[rd] = riscv_register->x[rs1] & riscv_register->x[rs2];
}
void andi(Riscv64_register* riscv_register, int rd, int rs1, int imm)       // and immediate
{
	riscv_register->x[rd] = riscv_register->x[rs1] & (long int)imm;
}

/* Shifts */
void sll(Riscv64_register* riscv_register, int rd, int rs1, int rs2)        // shift left
{
	reg64 shift_value = get_register_general(riscv_register, rs2) & 0x1F; // get the lower 5 bits of register rs2
	long int reg_value = get_register_general(riscv_register, rs1);
	set_register_general(riscv_register, rd, reg_value << shift_value);
}
void slli(Riscv64_register* riscv_register, int rd, int rs1, int shamt)      // shift left immediate
{
	long int reg_value = get_register_general(riscv_register, rs1);
	set_register_general(riscv_register, rd, reg_value << shamt);
}
void srl(Riscv64_register* riscv_register, int rd, int rs1, int rs2)        // shift right
{
	reg64 shift_value = get_register_general(riscv_register, rs2) & 0x1F; // get the lower 5 bits of register rs2
	unsigned long int reg_value = get_register_general(riscv_register, rs1);
	set_register_general(riscv_register, rd, reg_value >> shift_value);
}
void srli(Riscv64_register* riscv_register, int rd, int rs1, int shamt)      // shift right immediate
{
	unsigned long int reg_value = get_register_general(riscv_register, rs1);
	set_register_general(riscv_register, rd, reg_value >> shamt);
}
void sra(Riscv64_register* riscv_register, int rd, int rs1, int rs2)         // shift right arithmetic
{
	reg64 shift_value = get_register_general(riscv_register, rs2) & 0x1F; // get the lower 5 bits of register rs2
	long int reg_value = get_register_general(riscv_register, rs1);
	set_register_general(riscv_register, rd, reg_value >> shift_value);
}
void srai(Riscv64_register* riscv_register, int rd, int rs1, int shamt)      // shift right arithmetic immediate
{
	long int reg_value = get_register_general(riscv_register, rs1);
	set_register_general(riscv_register, rd, reg_value >> shamt);
}

/* Compare */
void slt(Riscv64_register* riscv_register, int rd, int rs1, int rs2)         // set <
{
	if((long int)(riscv_register->x[rs1] - riscv_register->x[rs2]) < 0)
		set_register_general(riscv_register, rd, 1);
	else
		set_register_general(riscv_register, rd, 0);
}
void slti(Riscv64_register* riscv_register, int rd, int rs1, int imm)        // set < immediate
{
	if((long int)(riscv_register->x[rs1] - (long int)imm) < 0)
		set_register_general(riscv_register, rd, 1);
	else
		set_register_general(riscv_register, rd, 0);
}
void sltu(Riscv64_register* riscv_register, int rd, int rs1, int rs2)        // set < unsigned
{
	if((unsigned long int)(riscv_register->x[rs1] - riscv_register->x[rs2]) < 0)
		set_register_general(riscv_register, rd, 1);
	else
		set_register_general(riscv_register, rd, 0);
}
void sltiu(Riscv64_register* riscv_register, int rd, int rs1, int imm)       // set < unsigned immediate
{
	if((unsigned long int)(riscv_register->x[rs1] - (long int)imm) < 0)
		set_register_general(riscv_register, rd, 1);
	else
		set_register_general(riscv_register, rd, 0);
}

/* Branches */
void beq(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register) - sizeof(instruction) + (long int)imm;  // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                                                          // we have to subtract it to get the current pc
	if(riscv_register->x[rs1] - riscv_register->x[rs2] == 0)
		set_register_pc(riscv_register, reg_value);
}
void bne(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register) - sizeof(instruction) + (long int)imm;  // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                                                          // we have to subtract it to get the current pc
	if(riscv_register->x[rs1] - riscv_register->x[rs2] != 0)
		set_register_pc(riscv_register, reg_value);
}
void blt(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register) - sizeof(instruction) + (long int)imm;  // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                                                          // we have to subtract it to get the current pc
	if((long int)(riscv_register->x[rs1] - riscv_register->x[rs2]) < 0)
		set_register_pc(riscv_register, reg_value);
}
void bge(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register) - sizeof(instruction) + (long int)imm;  // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                                                          // we have to subtract it to get the current pc
	if((long int)(riscv_register->x[rs1] - riscv_register->x[rs2]) >= 0)
		set_register_pc(riscv_register, reg_value);
}
void bltu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register) - sizeof(instruction) + (long int)imm;  // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                                                          // we have to subtract it to get the current pc
	if((unsigned long int)(riscv_register->x[rs1] - riscv_register->x[rs2]) < 0)
		set_register_pc(riscv_register, reg_value);
}
void bgeu(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rs1, int rs2, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register) - sizeof(instruction) + (long int)imm;  // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                                                          // we have to subtract it to get the current pc
	if((unsigned long int)(riscv_register->x[rs1] - riscv_register->x[rs2]) >= 0)
		set_register_pc(riscv_register, reg_value);
}

/* Jump & Link */
void jal(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register);
	if (rd != 0) // check whether it is a 'j' instruction, if so, cancel writing the register rd
		set_register_general(riscv_register, rd, reg_value);
	reg_value = reg_value - sizeof(instruction) + (long int)imm; // a bit tricky here, as the pc has self-increased in the fetch stage,
	                                                             // we have to subtract it to get the current pc
	set_register_pc(riscv_register, reg_value);
}
void jalr(Riscv64_register* riscv_register, Riscv64_memory* riscv_memory, int rd, int rs1, int imm)
{
	reg64 reg_value = get_register_pc(riscv_register);
	if (rd != 0) // check whether the register writing is needed
		set_register_general(riscv_register, rd, reg_value);
	reg_value = get_register_general(riscv_register, rs1) + (long int)imm;
	if(reg_value & 1) // check the least significant bit of reg_value, if it is 1, than set it to 0
		reg_value ^= 1;
	set_register_pc(riscv_register, reg_value);
}

/* System */
void scall()
{}

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