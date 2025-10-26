data arr [1, 2, 3, 4, 5]
data hellow "hellow, world!"
data file "file.txt"

entry:

__push:
	pushn 123                // num
	pushm &arr, 0x20         // addr
	pushb 0x01               // byte
	pushr r0                 // reg
	push  fx0, 0x20          // <arg> <offset> - offset always negative
	
__pop:
	pop
	popr r1                   // pop into register

__call:
	call __function           // jump into label
	calle __external			    // jump into external function

__math:
	add rx0, rdi              // add two numbers
	sub rx1, rdi4             // subtract two numbers
	mul rx2, 5                // multiply two numbers
	div rx3, fx1              // divide two numbers

	inc dx0                   // increment
	dec dx2                   // decrement

	not r5
	xor r5, 0xff
	or  r2, r3
	and r4, r1
	ls  r6, 2
	rs  r7, 3

__logic:
	jmp __push                // unconditional jump
	ret                       // return from function
	exit                      // exit program
	test                      // test top two stack values
	je  entry                 // jump if equal
	jel  entry                // jump if equal or less
	jem  entry                // jump if equal or more
	jne  entry                // jump if not equal
	jl  entry                 // jump if less
	jm  entry                 // jump if more
	mov rx0, rdi0             // <dest> <src> - move values
	swap rx1, rdi8            // swap two values
	mset 0x100, 0xff, 64      // <addr> <value> <size> - memory set
	mset &hellow, 0x41, 2     // set first two bytes of hellow to 'A'

__etc:
	putc 0x41
	puti 41
	puti rx1
	puts &hellow

	getch rx2                 // get character input (not freeze)
	
__file:
	wine &file                // create file if not exists
	open &file                // open file
	popr fx0                  // move file descriptor to fx0
	write fx0, &hellow, 0x32  // write to opened file
	read fx0, rx3, 0x32       // read from opened file
	close fx0                 // close opened file
