
#define EI_NIDENT 16

// data type
typedef unsigned long int   Elf64_Addr;
typedef unsigned short int  Elf64_Half;
typedef unsigned long int   Elf64_Off;
typedef int                 Elf64_Sword;
typedef unsigned int        Elf64_Word;
typedef unsigned long int   Elf64_Xword;
typedef signed long int     Elf64_Sxword;

// ELF Header
typedef struct elf64_hdr{
	unsigned char e_ident[EI_NIDENT];
	Elf64_Half    e_type;     /* file type */
	Elf64_Half    e_machine;  /* architecture */
	Elf64_Word    e_version;
	Elf64_Addr    e_entry;    /* entry pointer */
	Elf64_Off     e_phoff;    /* PH table offset */
	Elf64_Off     e_shoff;    /* SH table offset */
	Elf64_Word    e_flags;
	Elf64_Half    e_ehsize;      /* ELF header size in bytes */
	Elf64_Half    e_phentsize;   /* PH size */
	Elf64_Half    e_phnum;       /* PH number */   
	Elf64_Half    e_shentsize;   /* SH size */
	Elf64_Half    e_shnum;       /* SH number */   
	Elf64_Half    e_shstrndx;    /* SH name string table index */
} Elf64_Ehdr;

// Section header
typedef struct elf64_shdr{
   Elf64_Word    sh_name;	    /* name of section, index */
   Elf64_Word    sh_type;	
   Elf64_Xword   sh_flags;
   Elf64_Addr    sh_addr;		/* memory address, if any */
   Elf64_Off     sh_offset;
   Elf64_Xword   sh_size;		/* section size in file */
   Elf64_Word    sh_link;
   Elf64_Word    sh_info;
   Elf64_Xword   sh_addralign;
   Elf64_Xword   sh_entsize; 	/* fixed entry size, if have */
} Elf64_Shdr;

// Program header
typedef struct elf64_phdr{
   Elf64_Word    p_type;	
   Elf64_Word    p_flags;
   Elf64_Off     p_offset;
   Elf64_Addr    p_vaddr;		/* virtual address */
   Elf64_Addr    p_paddr;		/* phisical address */
   Elf64_Xword   p_filesz;		/* segment size in file */
   Elf64_Xword   p_memsz;		/* size in memory */
   Elf64_Xword   p_align;	 
} Elf64_Phdr;

// Symbol table
typedef struct elf64_sym{  
   Elf64_Word    st_name;
   unsigned char st_info;  
   unsigned char st_other; 
   Elf64_Half    st_shndx;    
   Elf64_Addr    st_value;  
   Elf64_Xword    st_size;  
} Elf64_Sym;  
