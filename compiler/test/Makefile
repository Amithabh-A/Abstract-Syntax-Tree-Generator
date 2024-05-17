all:
	mips-linux-gnu-gcc-10 codegen_verify.c -S -o codegen_verify.s

verify:
	vimdiff codegen.s codegen_verify.s
