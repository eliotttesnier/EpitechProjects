	.name "Biggy"
	.comment "biggy jump, biggy happy"

hi:
	ld %0, r3
	add r1, r2, r3
	zjmp %:kakou
	live %45

kakou:
	ld %0, r3
	zjmp %:kakou
