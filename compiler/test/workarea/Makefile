all:
	mips-linux-gnu-gcc-10 test.c -S -o test.s

d:
	mips-linux-gnu-gcc-10 test1.c -S -o test1.s
	mips-linux-gnu-gcc-10 test2.c -S -o test2.s
	rm diff.txt
	touch diff.txt
	diff test1.s test2.s >> diff.txt

vd:
	vimdiff test1.s test2.s
