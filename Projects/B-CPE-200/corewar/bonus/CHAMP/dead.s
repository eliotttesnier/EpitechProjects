	.name "Dead"
	.comment "Just die."

hi:	sti r1, %:hi, %1
    ld %0, r3
    zjmp %:hi
