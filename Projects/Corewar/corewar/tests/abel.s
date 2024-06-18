	.name "Abel" #salut les geeks
	.comment "L'amer noir."

	sti r1, %:hi, %1

hi:	live %234
	#coucou
	ld %0, r3
	zjmp %:hi
