main:
	li	$v0,30
	syscall
	move	$t4,$a0
	li	$a0,1000
	jal delay
	nop
	li	$v0,30
	syscall
	sub	$t4,$a0,$t4
	j main
	nop
delay:	
	move	$t0,$a0		#init deloop counter
	li	$t2,270		#init delay constant
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
