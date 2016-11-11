
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
   Elf64_Word    sh_type;	    /* section type  */
   Elf64_Xword   sh_flags;     /* section attribute */
   Elf64_Addr    sh_addr;		 /* memory address, if any */
   Elf64_Off     sh_offset;    /* offset int the file  */
   Elf64_Xword   sh_size;		 /* section size in file */
   Elf64_Word    sh_link;      /* link to other section */
   Elf64_Word    sh_info;
   Elf64_Xword   sh_addralign;
   Elf64_Xword   sh_entsize; 	 /* fixed entry size, if have */
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
   Elf64_Word    st_name;     /* symbol name */
   unsigned char st_info;     /* type and binding attribute */
   unsigned char st_other;    /* reserved */
   Elf64_Half    st_shndx;    /* section table index */
   Elf64_Addr    st_value;    /* symbol value */
   Elf64_Xword   st_size;     /* size of object */
} Elf64_Sym;  


/*********************************************/
/*                                           */
/* macros for section headers                */
/*                                           */
/*********************************************/
// section types, sh_type
#define SHT_NULL           0             // marks an unused section header
#define SHT_PROGBITS       1             // contains the information defined by the program
#define SHT_SYMTAB         2             // contains the link to the symbol table
#define SHT_STRTAB         3             // contains a string table
#define SHT_RELA           4             // contains "Rela" type relocation entries
#define SHT_HASH           5             // contains a symbol hash table
#define SHT_DYNAMIC        6             // contains dynamic linking tables
#define SHT_NOTE           7             // contains note information
#define SHT_NOBITS         8             // contains uninitialized space; does not occupy any space in the file
#define SHT_REL            9             // contains "Rel" type relocation entries
#define SHT_SHLIB          10            // reserved 
#define SHT_DYNSYM         11            // contains a dynamic loader symbol table
#define SHT_LOOS           0x60000000    // environment-specific use
#define SHT_HIOS           0x6fffffff    // 
#define SHT_LOPROC         0x70000000    // processor-specific use
#define SHT_HIPROC         0x7fffffff    //

// section attributes, sh_flags
#define SHF_WRITE          0x1           // section contains writable data
#define SHF_ALLOC          0x2           // section is allocated in memory image of program
#define SHF_EXECINSTR      0x4           // section contains executable instructions
#define SHF_MASKOS         0x0f000000    // environment-specific use
#define SHF_MASKPROC       0xf0000000    // processor-specific use


/*********************************************/
/*                                           */
/* macros symbol tables                      */
/*                                           */
/*********************************************/
// symbol bindings
#define STB_LOCAL          0             // not visible outside the object file
#define STB_GLOBAL         1             // global symbol, visible to all object files
#define STB_WEAK           2             // global scope, but with lower precedence than global symbols 
#define STB_LOOS           10            // environment-specific use
#define STB_HIOS           12            //
#define STB_LOPROC         13            // processor-specific use
#define STB_HIPROC         15            // 

// symbol types
#define STT_NOTYPE         0             // no type specified 
#define STT_OBJECT         1             // data object
#define STT_FUNC           2             // function entry point
#define STT_SECTION        3             // symbol is associated with a section
#define STT_FILE           4             // source file associated with the object file 
#define STT_LOOS           10            // environment-specific use
#define STT_HIOS           12            // 
#define STT_LOPROC         13            // processor-specific use
#define STT_HIPROC         15            //



