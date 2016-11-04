#include "execute.h"


/*********************************************/
/*                                           */
/* functions for parsing elf and load program*/
/*                                           */
/*********************************************/

// print the help information
void help()
{
	printf("This is a simulator to execute riscv ELF!\n\n");
	printf("     Usage: ./exeute filename\n\n");
	printf("Multiple ELFs is supported, just separate the filename with space. The order of execution is the same as the input order.\n");

}

void print_mem(byte* start, int length)
{
	for(int i = 1; i <= length; i++)
	{
		printf("%x", start[i]);
		if(i % 4 == 0)
			printf(" ");
	}
	printf("\n");
	return;
}

// read the  whole file into the mem
byte* read_file(FILE* fp, int* p_size)
{
	// get size of the file
	fseek(fp, 0, SEEK_END);
	*p_size = ftell(fp);
	rewind(fp);

	// malloc buffer
	byte* buffer = (byte*) malloc (sizeof(byte) * *p_size);
	if(buffer == NULL)
	{
		printf("Memory error.\n");
		exit(1);
	}  

	// read
	fread(buffer, 1, *p_size, fp);

	return buffer;
}

// load the program to the memory system 
void load_program(Elf64_Ehdr* elf_header, Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	// set PC
	riscv_register->pc = elf_header->e_entry;
	
	// load program segment to the memory
	Elf64_Phdr* program_header_1 = (Elf64_Phdr*)((byte*)elf_header + elf_header->e_phoff);
	int ph_size = elf_header->e_phentsize;
	int ph_num = elf_header->e_phnum;

	printf("segment_num = %d\n", ph_num);

	for(int i = 0; i < ph_num; i++)
	{
		Elf64_Phdr* program_header = (Elf64_Phdr*)((byte*)program_header_1 + ph_size*i);
		
		// pointer to segment in the file
		byte* p_seg_in_file = (byte*)elf_header + program_header->p_offset;
		// pointer to segment in the virtual memory 
		byte* p_seg_actual_addr = get_actual_addr(riscv_memory, (byte*)program_header->p_vaddr);
		
		// copy the segment to virtual memory
		memcpy(p_seg_actual_addr, p_seg_in_file, program_header->p_memsz);
		// set pc to head of the 1st seg
		if (i == 0)
		{
			set_register_pc(riscv_register, (reg64)program_header->p_vaddr);
		}

		printf("%x\n", *(instruction*)p_seg_actual_addr);

	}
/*
	// section
	Elf64_Shdr* section_header_1 = (Elf64_Shdr*)((byte*)elf_header + elf_header->e_shoff);
	int sh_size = elf_header->e_shentsize;
	int sh_num = elf_header->e_shnum;

	for(int i = 0; i < sh_num; i++)
	{
		Elf64_Shdr* section_header = (Elf64_Shdr*)((byte*)section_header_1 + sh_size*i);
	}
*/
	return;
}


/*********************************************/
/*                                           */
/* functions for executing instructions      */
/*                                           */
/*********************************************/

instruction fetch(Riscv64_memory* riscv_memory, Riscv64_register* riscv_register)
{
	byte* virtual_addr_pc = (byte*) get_register_pc(riscv_register);
	instruction inst = (instruction) get_memory_reg64(riscv_memory, virtual_addr_pc);
	register_pc_self_increase(riscv_register);
	return inst;
}

void decode(Riscv64_decoder* riscv_decoder, instruction inst)
{
<<<<<<< HEAD
	riscv_decoder->opcode       = OPCODE(inst);
	riscv_decoder->funct3       = FUNCT3(inst);
	riscv_decoder->funct7       = FUNCT7(inst);
	riscv_decoder->rd           = RD(inst);
	riscv_decoder->rs1          = RS1(inst);
	riscv_decoder->rs2          = RS2(inst);
	riscv_decoder->shamt        = SHAMT(inst);
	riscv_decoder->I_immediate  = I_IMM(inst);
	riscv_decoder->S_immediate  = S_IMM(inst);
	riscv_decoder->SB_immediate = SB_IMM(inst);
	riscv_decoder->U_immediate  = U_IMM(inst);
	riscv_decoder->UJ_immediate = UJ_IMM(inst);

	printf("opcode = %x\n", riscv_decoder->opcode);
	return;
=======
	riscv_decoder->opcode = OPCODE(inst);
	riscv_decoder->funct3 = FUNCT3(inst);
	riscv_decoder->funct7 = FUNCT7(inst);
	riscv_decoder->rd     = RD(inst);
	riscv_decoder->rs1    = RS1(inst);
	riscv_decoder->rs2    = RS2(inst);

	switch (opToINSTYPE(riscv_decoder->opcode))
	{
		case R_TYPE:
			riscv_decoder->immediate = 0;
			break;
		case I_TYPE:
			riscv_decoder->immediate = I_IMM(inst);
			break;
		case S_TYPE:
			riscv_decoder->immediate = S_IMM(inst);
			break;
		case SB_TYPE:
			riscv_decoder->immediate = SB_IMM(inst);
			break;
		case U_TYPE:
			riscv_decoder->immediate = U_IMM(inst);
			break;
		case UJ_TYPE:
			riscv_decoder->immediate = UJ_IMM(inst);
			break;
		default:
			printf("error: OPCODE not defined!\n");
			exit(1);
	}

>>>>>>> 573c4601007db82bb46e59e9a5a767c9d59ebd86
}

void execute(Riscv64_decoder* riscv_decoder, 
	Riscv64_register* riscv_register, Riscv64_memory* riscv_memory)
{
	// classification by opcode
	switch (opToINSTYPE(riscv_decoder->opcode))
	{
		case R_TYPE:
		
			break;
		case I_TYPE:
			
			break;
		case S_TYPE:
			
			break;
		case SB_TYPE:
			
			break;
		case U_TYPE:
			
			break;
		case UJ_TYPE:
			
			break;
		default:
			printf("error: OPCODE not defined!\n");
			exit(1);
	}
}


/*********************************************/
/*                                           */
/* main function                             */
/*                                           */
/*********************************************/

int main(int argc, char const *argv[])
{
	// check
	if(argc < 2 || strcmp(argv[1],"help") == 0)
	{
		help();
		return 0;
	}

	int file_num = argc - 1; // number of file
	FILE *fp;  // file pointer 

	// memory system
	Riscv64_register *riscv_register;
	Riscv64_memory *riscv_memory;
	Riscv64_decoder *riscv_decoder;

	// execute elf one by one 
	for (int i = 1; i <= file_num; i++ )
	{
		char *file_name = argv[i];

		// not absolute addr, add "./" to the head of the str
		char pre_addr[3] = "./";
		if(file_name[0] != '/')
		{
			file_name = strcat(pre_addr, file_name);
			printf("%s", file_name);
		}

		fp = fopen(file_name, "rb");  // binary mode

		if(fp == NULL)
		{
			printf("Can not open file : %s successfully.\n", file_name);
			exit(1);
		}

		printf("executing file : %s ...\n", file_name);
		
		// read the whole elf
		int size;
		byte* buffer = read_file(fp, &size);
		printf("the size of the file is : %d bytes\n", size);

		// get the elf header 
		Elf64_Ehdr* elf_header = (Elf64_Ehdr*) buffer;

		// initialize memory system
		/* XJM modified */
		// riscv_decoder = init_decoder(riscv_decoder);
		// riscv_register = init_register(riscv_register);
		// riscv_memory = init_memory(riscv_memory);
		init_decoder(&riscv_decoder);
<<<<<<< HEAD
		init_memory(&riscv_memory);
		init_register(&riscv_register, riscv_memory);
		
=======
		init_register(&riscv_register);
		init_memory(&riscv_memory);
>>>>>>> 573c4601007db82bb46e59e9a5a767c9d59ebd86
		//load program
		load_program(elf_header, riscv_register, riscv_memory);
		
		int j = 1;
		while(j--)
		{
			instruction inst = fetch(riscv_memory, riscv_register);
			decode(riscv_decoder, inst);
			execute(riscv_decoder, riscv_register, riscv_memory);
		}


		// gc
		delete_memory_system(riscv_decoder, riscv_register, riscv_memory);
		free(buffer);
	}

	return 0;
}