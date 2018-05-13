main:
	addi	$a0,$0,10	#init arg with n
fact_init:
	beq	$a0,$0,stop
	add	$v0,$a0,$0
fact_loop:
	beq	$a0,1,stop
	addi	$a0,$a0,-1
	addi	$a1,$0,1
	add	$a2,$v0,$0
mult_loop:	
	beq	$a0,$a1,fact_loop
	addi	$a1,$a1,1
	add	$v0,$v0,$a2
	beq	$0,$0,mult_loop
stop:
	beq	$0,$0,stop