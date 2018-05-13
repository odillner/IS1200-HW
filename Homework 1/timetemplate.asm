  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.
.global delay
.global time2string
.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,10
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
time2string:		
	addi	$t0,$a0,4	#store timestr address and increase
	andi	$t1,$a1,0xffff	#store mytime and mask
	li 	$t2,0		#init counter
	PUSH	($ra)		#save return address
ti2loop:	
	beq	$t2,5,ti2end	#loop condition
	nop
	beq 	$t2,2,ti2divider#check if divider is needed
	nop
	andi	$a0,$t1,0xf	#transfer LSB into arg
	srl	$t1,$t1,4	#shift mytime right
	jal 	hexasc		#jump to hexasc sub
	nop
ti2store:
	sb	$v0,0($t0)	#store ascii char in timestr
	addi	$t0,$t0,-1	#shift
	addiu	$t2,$t2,1	#increase counter
	j	ti2loop		#keep looping
	nop
ti2divider:
	li	$v0,0x3a	#insert divider char into return
	j	ti2store	#jump to store sub
	nop
ti2end:
	li	$t1,0x00	#load null byte
	sb	$t1,6($t0)	#store null byte
	POP	($ra)		#restore return address to original value
	jr	$ra		#return
	nop
hexasc:
	andi	$v0,$a0,0xf	#mask all but 4 LSB
	ble	$v0,0x9,lower	#check if arg =< 9
	nop
	addiu	$v0,$v0,0x37	#increase arg to turn it into ascii char
	jr 	$ra		#return
	nop
lower: 
	addiu	$v0,$v0,0x30	#increase arg to turn it into ascii char
	jr	$ra		#return
	nop
delay:	
	move	$t0,$a0		#init deloop counter
	li	$t2,250		#init delay constant
deloop:
	ble 	$t0,0,deend	#end loop if $t0<=0
	nop
	addi	$t0,$t0,-1	#reduce loop counter by 1
	li	$t1,0		#init deloop2 counter
deloop2:
	beq	$t1,$t2,deloop	#end loop if $t1==$t2
	nop
	addi	$t1,$t1,1	#increase loop counter by 1
	j	deloop2		#keep looping
	nop
deend:
	jr	$ra		#return
	nop
