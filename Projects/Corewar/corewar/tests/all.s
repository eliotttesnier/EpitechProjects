	.name "ALL"
	.comment "L'amer noir."

	sti r1, %:hi, %1

hi:	live %234
	ld %0, r3
	add r1, r2, r3
	sub r1, r2, r3
	and r1, r2, r3
	or r1, r2, r3
	xor r1, r2, r3
	zjmp %:hi
