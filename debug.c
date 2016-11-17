#include "debug.h"

// void DEBUG(char* p1, ...)
// {
// 	va_list va;  
//     va_start(va, p1); // init va, pointing to the first argument  
//     int tmp,smax=-1;  
//     int i;  
//     for(i = 0;i<n;i++)  
//         {  
//                 tmp=va_arg(va,int); // get the next argument, the type is int  
//                 if(tmp>smax) smax=tmp;  
//         }  
//         va_end(va); 
// }
void DEBUG_MESSAGE(char* message)
{
	printf("%s, I showed here!\n", message);
}
void DEBUG_INST(char* inst_name, char* type, Riscv64_decoder* riscv_decoder, Riscv64_register* riscv_register)
{
	int d_rd = riscv_decoder->rd;
	int d_rs1 = riscv_decoder->rs1;
	int d_rs2 = riscv_decoder->rs2;
	int d_imm = riscv_decoder->immediate;
	int d_shamt = riscv_decoder->shamt64;
	reg64 d_reg_rd = riscv_register->x[d_rd];
	reg64 d_reg_rs1 = riscv_register->x[d_rs1];
	reg64 d_reg_rs2 = riscv_register->x[d_rs2];

	printf("%s:", inst_name);
	if(!strcmp(type, "di"))
	{
		printf("reg[rd] = %lu, imm = %d", d_reg_rd, d_imm);
	}
	else if(!strcmp(type, "d1i"))
	{
		printf("reg[rd] = %lu, reg[rs1] = %lu, imm = %d", d_reg_rd, d_reg_rs1, d_imm);
	}
	else if(!strcmp(type, "12i"))
	{
		printf("reg[rs1] = %lu, reg[rs2] = %lu, imm = %d", d_reg_rs1, d_reg_rs2, d_imm);
	}
	else if(!strcmp(type, "d12"))
	{
		printf("reg[rd] = %lu, reg[rs1] = %lu, reg[rs2] = %lu", d_reg_rd, d_reg_rs1, d_reg_rs2);
	}
	else if(!strcmp(type, "d1s"))
	{
		printf("reg[rd] = %lu, reg[rs1] = %lu, shamt = %d", d_reg_rd, d_reg_rs1, d_shamt);
	}
	printf("\n");
}