

文件夹中各文件的功能如下：
模拟器：
	execute.h、execute.c: 执行的主程序，定义了模拟器的一般流程，包括：解析elf、装载程序、取指、解码、执行
	parse_elf.h： 定义了elf文件的各种头部表结构
	memory_system.h、memory_system.c: 存储系统， 包括解码器（存储解码后的指令信息）、寄存器文件、主存
	riscv_instruction.h：包括一些指令解码的宏

测试文件：
	hello.c：包括printf
	test.c：包括一个初始化的全局变量和一个未初始化的全局变量

编译方式: gcc -o -std=c99 simulator memory_system.c execute.c

运行方式: ./simulator test hello  (可以支持多个程序顺序执行)




还缺：
1、解码函数，作用是将一条指令分成decoder中的各个部分，并保存在decoder中。主要的宏都已经写好（取立即数那一部分没检查不保证正确）直接调用就可以，主要就是根据opcode等判断immediate,这个比较迷，文档我还没仔细看
2、执行函数，（将执行、访存、写回合并，减少点复杂性）根据decoder中的信息执行功能，具体是分情况调用各个指令函数
3、riscv_instruction.c没写，解释执行各个指令
4、程序退出貌似还没考虑？
5、debug功能等
