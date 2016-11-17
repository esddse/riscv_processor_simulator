OBJECTS = memory_system.o riscv_instruction.o execute.o debug.o
COMPILEFLAGS = -lm -fno-stack-protector

simulator : $(OBJECTS)
	gcc -std=c99 -o simulator $(OBJECTS) $(COMPILEFLAGS)


memory_system.o : memory_system.c memory_system.h
	gcc -c memory_system.c $(COMPILEFLAGS)
riscv_instruction.o : riscv_instruction.c riscv_instruction.h
	gcc -c riscv_instruction.c $(COMPILEFLAGS)
execute.o : execute.c execute.h
	gcc -c execute.c $(COMPILEFLAGS)
debug.o : debug.c debug.h
	gcc -c debug.c $(COMPILEFLAGS)

clean :
	    rm simulator $(OBJECTS)

