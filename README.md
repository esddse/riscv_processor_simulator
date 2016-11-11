

文件夹中各文件的功能如下：
模拟器：
	execute.h、execute.c: 执行的主程序，定义了模拟器的一般流程，包括：解析elf、装载程序、取指、解码、执行
	parse_elf.h： 定义了elf文件的各种头部表结构
	memory_system.h、memory_system.c: 存储系统， 包括解码器（存储解码后的指令信息）、寄存器文件、主存
	riscv_instruction.h riscv_instruction.c： 

测试文件：
	hello.c：包括printf
	test.c：包括一个初始化的全局变量和一个未初始化的全局变量


编译方式: gcc -std=c99 -o simulator memory_system.c riscv_instruction.c execute.c -lm

