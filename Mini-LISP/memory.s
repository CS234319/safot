	.file	"memory.cc"
	.text
	.align 2
	.type	_ZN6Memory3._4C2Ev, @function
_ZN6Memory3._4C2Ev:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movb	$78, 8188(%rax)
	movq	-8(%rbp), %rax
	movb	$73, 8189(%rax)
	movq	-8(%rbp), %rax
	movb	$76, 8190(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 8191(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN6Memory3._4C2Ev, .-_ZN6Memory3._4C2Ev
	.set	_ZN6Memory3._4C1Ev,_ZN6Memory3._4C2Ev
	.local	_ZN6MemoryL3allE
	.comm	_ZN6MemoryL3allE,40960,32
	.globl	_ZN6Memory1PE
	.section	.data.rel.ro.local,"aw"
	.align 8
	.type	_ZN6Memory1PE, @object
	.size	_ZN6Memory1PE, 8
_ZN6Memory1PE:
	.quad	_ZN6MemoryL3allE+8188
	.align 8
	.type	_ZN6MemoryL2P0E, @object
	.size	_ZN6MemoryL2P0E, 8
_ZN6MemoryL2P0E:
	.quad	_ZN6MemoryL3allE+8188
	.align 8
	.type	_ZN6MemoryL2P1E, @object
	.size	_ZN6MemoryL2P1E, 8
_ZN6MemoryL2P1E:
	.quad	_ZN6MemoryL3allE+40960
	.globl	_ZN6Memory1AE
	.align 8
	.type	_ZN6Memory1AE, @object
	.size	_ZN6Memory1AE, 8
_ZN6Memory1AE:
	.quad	_ZN6MemoryL3allE+8188
	.align 8
	.type	_ZN6MemoryL2A0E, @object
	.size	_ZN6MemoryL2A0E, 8
_ZN6MemoryL2A0E:
	.quad	_ZN6MemoryL3allE
	.align 8
	.type	_ZN6MemoryL2A1E, @object
	.size	_ZN6MemoryL2A1E, 8
_ZN6MemoryL2A1E:
	.quad	_ZN6MemoryL3allE+16380
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.align 4
	.type	_ZN9__gnu_cxxL21__default_lock_policyE, @object
	.size	_ZN9__gnu_cxxL21__default_lock_policyE, 4
_ZN9__gnu_cxxL21__default_lock_policyE:
	.long	2
	.type	_ZStL13allocator_arg, @object
	.size	_ZStL13allocator_arg, 1
_ZStL13allocator_arg:
	.zero	1
	.type	_ZStL6ignore, @object
	.size	_ZStL6ignore, 1
_ZStL6ignore:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN7testing8internal8GTestLog9GetStreamEv,"axG",@progbits,_ZN7testing8internal8GTestLog9GetStreamEv,comdat
	.align 2
	.weak	_ZN7testing8internal8GTestLog9GetStreamEv
	.type	_ZN7testing8internal8GTestLog9GetStreamEv, @function
_ZN7testing8internal8GTestLog9GetStreamEv:
.LFB3207:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	_ZSt4cerr(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3207:
	.size	_ZN7testing8internal8GTestLog9GetStreamEv, .-_ZN7testing8internal8GTestLog9GetStreamEv
	.section	.rodata
	.align 8
	.type	_ZN7testing8internalL14kMaxBiggestIntE, @object
	.size	_ZN7testing8internalL14kMaxBiggestIntE, 8
_ZN7testing8internalL14kMaxBiggestIntE:
	.quad	9223372036854775807
	.section	.text._ZN7testing8internal15TestFactoryBaseD2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryBaseD5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryBaseD2Ev
	.type	_ZN7testing8internal15TestFactoryBaseD2Ev, @function
_ZN7testing8internal15TestFactoryBaseD2Ev:
.LFB4040:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryBaseE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4040:
	.size	_ZN7testing8internal15TestFactoryBaseD2Ev, .-_ZN7testing8internal15TestFactoryBaseD2Ev
	.weak	_ZN7testing8internal15TestFactoryBaseD1Ev
	.set	_ZN7testing8internal15TestFactoryBaseD1Ev,_ZN7testing8internal15TestFactoryBaseD2Ev
	.section	.text._ZN7testing8internal15TestFactoryBaseD0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryBaseD5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryBaseD0Ev
	.type	_ZN7testing8internal15TestFactoryBaseD0Ev, @function
_ZN7testing8internal15TestFactoryBaseD0Ev:
.LFB4042:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4042:
	.size	_ZN7testing8internal15TestFactoryBaseD0Ev, .-_ZN7testing8internal15TestFactoryBaseD0Ev
	.section	.text._ZN7testing8internal15TestFactoryBaseC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryBaseC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryBaseC2Ev
	.type	_ZN7testing8internal15TestFactoryBaseC2Ev, @function
_ZN7testing8internal15TestFactoryBaseC2Ev:
.LFB4044:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryBaseE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4044:
	.size	_ZN7testing8internal15TestFactoryBaseC2Ev, .-_ZN7testing8internal15TestFactoryBaseC2Ev
	.weak	_ZN7testing8internal15TestFactoryBaseC1Ev
	.set	_ZN7testing8internal15TestFactoryBaseC1Ev,_ZN7testing8internal15TestFactoryBaseC2Ev
	.section	.text._ZN7testing8internal12CodeLocationC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi,"axG",@progbits,_ZN7testing8internal12CodeLocationC5ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi,comdat
	.align 2
	.weak	_ZN7testing8internal12CodeLocationC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
	.type	_ZN7testing8internal12CodeLocationC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi, @function
_ZN7testing8internal12CodeLocationC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi:
.LFB4048:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
	movq	-8(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, 32(%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4048:
	.size	_ZN7testing8internal12CodeLocationC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi, .-_ZN7testing8internal12CodeLocationC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
	.weak	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
	.set	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi,_ZN7testing8internal12CodeLocationC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
	.section	.text._ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_,"axG",@progbits,_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_,comdat
	.weak	_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_
	.type	_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_, @function
_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_:
.LFB4050:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	cmpq	-16(%rbp), %rax
	je	.L9
	movq	-8(%rbp), %rax
	jmp	.L11
.L9:
	movl	$0, %eax
.L11:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4050:
	.size	_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_, .-_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_
	.section	.text._ZN7testing8internal12CodeLocationD2Ev,"axG",@progbits,_ZN7testing8internal12CodeLocationD5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal12CodeLocationD2Ev
	.type	_ZN7testing8internal12CodeLocationD2Ev, @function
_ZN7testing8internal12CodeLocationD2Ev:
.LFB4070:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4070:
	.size	_ZN7testing8internal12CodeLocationD2Ev, .-_ZN7testing8internal12CodeLocationD2Ev
	.weak	_ZN7testing8internal12CodeLocationD1Ev
	.set	_ZN7testing8internal12CodeLocationD1Ev,_ZN7testing8internal12CodeLocationD2Ev
	.section	.rodata
	.align 8
	.type	_ZN7testing9internal2L26kProtobufOneLinerMaxLengthE, @object
	.size	_ZN7testing9internal2L26kProtobufOneLinerMaxLengthE, 8
_ZN7testing9internal2L26kProtobufOneLinerMaxLengthE:
	.quad	50
	.align 16
	.type	_ZN7testing8internalL19kDeathTestStyleFlagE, @object
	.size	_ZN7testing8internalL19kDeathTestStyleFlagE, 17
_ZN7testing8internalL19kDeathTestStyleFlagE:
	.string	"death_test_style"
	.align 16
	.type	_ZN7testing8internalL17kDeathTestUseForkE, @object
	.size	_ZN7testing8internalL17kDeathTestUseForkE, 20
_ZN7testing8internalL17kDeathTestUseForkE:
	.string	"death_test_use_fork"
	.align 16
	.type	_ZN7testing8internalL25kInternalRunDeathTestFlagE, @object
	.size	_ZN7testing8internalL25kInternalRunDeathTestFlagE, 24
_ZN7testing8internalL25kInternalRunDeathTestFlagE:
	.string	"internal_run_death_test"
	.align 4
	.type	_ZN7testingL19kMaxStackTraceDepthE, @object
	.size	_ZN7testingL19kMaxStackTraceDepthE, 4
_ZN7testingL19kMaxStackTraceDepthE:
	.long	100
	.section	.text._ZNK7testing15AssertionResultcvbEv,"axG",@progbits,_ZNK7testing15AssertionResultcvbEv,comdat
	.align 2
	.weak	_ZNK7testing15AssertionResultcvbEv
	.type	_ZNK7testing15AssertionResultcvbEv, @function
_ZNK7testing15AssertionResultcvbEv:
.LFB4636:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4636:
	.size	_ZNK7testing15AssertionResultcvbEv, .-_ZNK7testing15AssertionResultcvbEv
	.section	.rodata
.LC0:
	.string	""
	.section	.text._ZNK7testing15AssertionResult7messageEv,"axG",@progbits,_ZNK7testing15AssertionResult7messageEv,comdat
	.align 2
	.weak	_ZNK7testing15AssertionResult7messageEv
	.type	_ZNK7testing15AssertionResult7messageEv, @function
_ZNK7testing15AssertionResult7messageEv:
.LFB4637:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	testq	%rax, %rax
	je	.L16
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5c_strEv@PLT
	jmp	.L18
.L16:
	leaq	.LC0(%rip), %rax
.L18:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4637:
	.size	_ZNK7testing15AssertionResult7messageEv, .-_ZNK7testing15AssertionResult7messageEv
	.section	.text._ZNK7testing15AssertionResult15failure_messageEv,"axG",@progbits,_ZNK7testing15AssertionResult15failure_messageEv,comdat
	.align 2
	.weak	_ZNK7testing15AssertionResult15failure_messageEv
	.type	_ZNK7testing15AssertionResult15failure_messageEv, @function
_ZNK7testing15AssertionResult15failure_messageEv:
.LFB4638:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult7messageEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4638:
	.size	_ZNK7testing15AssertionResult15failure_messageEv, .-_ZNK7testing15AssertionResult15failure_messageEv
	.section	.text._ZN7testing7MessageD2Ev,"axG",@progbits,_ZN7testing7MessageD5Ev,comdat
	.align 2
	.weak	_ZN7testing7MessageD2Ev
	.type	_ZN7testing7MessageD2Ev, @function
_ZN7testing7MessageD2Ev:
.LFB4642:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED1Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4642:
	.size	_ZN7testing7MessageD2Ev, .-_ZN7testing7MessageD2Ev
	.weak	_ZN7testing7MessageD1Ev
	.set	_ZN7testing7MessageD1Ev,_ZN7testing7MessageD2Ev
	.section	.text._ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE,"axG",@progbits,_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE,comdat
	.align 2
	.weak	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE
	.type	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE, @function
_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE:
.LFB4644:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4644
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$64, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-72(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	testq	%rax, %rax
	sete	%al
	testb	%al, %al
	je	.L23
	movq	-72(%rbp), %rax
	leaq	8(%rax), %rbx
	movl	$32, %edi
.LEHB0:
	call	_Znwm@PLT
	movq	%rax, %r12
	movq	%r12, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1Ev@PLT
	movq	%r12, %rsi
	movq	%rbx, %rdi
	call	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_
.L23:
	movq	-72(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	-80(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNK7testing7Message9GetStringB5cxx11Ev@PLT
.LEHE0:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5c_strEv@PLT
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB1:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKc@PLT
.LEHE1:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L25
	jmp	.L27
.L26:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
.L27:
	call	__stack_chk_fail@PLT
.L25:
	addq	$64, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4644:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE,"aG",@progbits,_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE,comdat
.LLSDA4644:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4644-.LLSDACSB4644
.LLSDACSB4644:
	.uleb128 .LEHB0-.LFB4644
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB4644
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L26-.LFB4644
	.uleb128 0
	.uleb128 .LEHB2-.LFB4644
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE4644:
	.section	.text._ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE,"axG",@progbits,_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE,comdat
	.size	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE, .-_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE
	.section	.text._ZN7testing4Test14SetUpTestSuiteEv,"axG",@progbits,_ZN7testing4Test14SetUpTestSuiteEv,comdat
	.weak	_ZN7testing4Test14SetUpTestSuiteEv
	.type	_ZN7testing4Test14SetUpTestSuiteEv, @function
_ZN7testing4Test14SetUpTestSuiteEv:
.LFB4652:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4652:
	.size	_ZN7testing4Test14SetUpTestSuiteEv, .-_ZN7testing4Test14SetUpTestSuiteEv
	.section	.text._ZN7testing4Test17TearDownTestSuiteEv,"axG",@progbits,_ZN7testing4Test17TearDownTestSuiteEv,comdat
	.weak	_ZN7testing4Test17TearDownTestSuiteEv
	.type	_ZN7testing4Test17TearDownTestSuiteEv, @function
_ZN7testing4Test17TearDownTestSuiteEv:
.LFB4653:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4653:
	.size	_ZN7testing4Test17TearDownTestSuiteEv, .-_ZN7testing4Test17TearDownTestSuiteEv
	.section	.text._ZN7testing4Test16TearDownTestCaseEv,"axG",@progbits,_ZN7testing4Test16TearDownTestCaseEv,comdat
	.weak	_ZN7testing4Test16TearDownTestCaseEv
	.type	_ZN7testing4Test16TearDownTestCaseEv, @function
_ZN7testing4Test16TearDownTestCaseEv:
.LFB4654:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4654:
	.size	_ZN7testing4Test16TearDownTestCaseEv, .-_ZN7testing4Test16TearDownTestCaseEv
	.section	.text._ZN7testing4Test13SetUpTestCaseEv,"axG",@progbits,_ZN7testing4Test13SetUpTestCaseEv,comdat
	.weak	_ZN7testing4Test13SetUpTestCaseEv
	.type	_ZN7testing4Test13SetUpTestCaseEv, @function
_ZN7testing4Test13SetUpTestCaseEv:
.LFB4655:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4655:
	.size	_ZN7testing4Test13SetUpTestCaseEv, .-_ZN7testing4Test13SetUpTestCaseEv
	.section	.text._ZN7testing4Test5SetupEv,"axG",@progbits,_ZN7testing4Test5SetupEv,comdat
	.align 2
	.weak	_ZN7testing4Test5SetupEv
	.type	_ZN7testing4Test5SetupEv, @function
_ZN7testing4Test5SetupEv:
.LFB4658:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4658:
	.size	_ZN7testing4Test5SetupEv, .-_ZN7testing4Test5SetupEv
	.section	.text._ZN7testing15AssertionResultD2Ev,"axG",@progbits,_ZN7testing15AssertionResultD5Ev,comdat
	.align 2
	.weak	_ZN7testing15AssertionResultD2Ev
	.type	_ZN7testing15AssertionResultD2Ev, @function
_ZN7testing15AssertionResultD2Ev:
.LFB4759:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED1Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4759:
	.size	_ZN7testing15AssertionResultD2Ev, .-_ZN7testing15AssertionResultD2Ev
	.weak	_ZN7testing15AssertionResultD1Ev
	.set	_ZN7testing15AssertionResultD1Ev,_ZN7testing15AssertionResultD2Ev
	.section	.text._Z13RUN_ALL_TESTSv,"axG",@progbits,_Z13RUN_ALL_TESTSv,comdat
	.weak	_Z13RUN_ALL_TESTSv
	.type	_Z13RUN_ALL_TESTSv, @function
_Z13RUN_ALL_TESTSv:
.LFB4786:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	_ZN7testing8UnitTest11GetInstanceEv@PLT
	movq	%rax, %rdi
	call	_ZN7testing8UnitTest3RunEv@PLT
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4786:
	.size	_Z13RUN_ALL_TESTSv, .-_Z13RUN_ALL_TESTSv
	.section	.text._ZN25Memory_PrimitiveSizs_TestC2Ev,"axG",@progbits,_ZN25Memory_PrimitiveSizs_TestC5Ev,comdat
	.align 2
	.weak	_ZN25Memory_PrimitiveSizs_TestC2Ev
	.type	_ZN25Memory_PrimitiveSizs_TestC2Ev, @function
_ZN25Memory_PrimitiveSizs_TestC2Ev:
.LFB4788:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV25Memory_PrimitiveSizs_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4788:
	.size	_ZN25Memory_PrimitiveSizs_TestC2Ev, .-_ZN25Memory_PrimitiveSizs_TestC2Ev
	.weak	_ZN25Memory_PrimitiveSizs_TestC1Ev
	.set	_ZN25Memory_PrimitiveSizs_TestC1Ev,_ZN25Memory_PrimitiveSizs_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC2Ev:
.LFB4791:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4791:
	.size	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC2Ev
	.globl	_ZN25Memory_PrimitiveSizs_Test10test_info_E
	.bss
	.align 8
	.type	_ZN25Memory_PrimitiveSizs_Test10test_info_E, @object
	.size	_ZN25Memory_PrimitiveSizs_Test10test_info_E, 8
_ZN25Memory_PrimitiveSizs_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC1:
	.string	"1"
.LC2:
	.string	"sizeof(byte)"
.LC3:
	.string	"memory.cc"
.LC4:
	.string	"sizeof(char)"
.LC5:
	.string	"2"
.LC6:
	.string	"sizeof(H)"
.LC7:
	.string	"4"
.LC8:
	.string	"sizeof(W)"
.LC9:
	.string	"sizeof(pair)"
	.text
	.align 2
	.globl	_ZN25Memory_PrimitiveSizs_Test8TestBodyEv
	.type	_ZN25Memory_PrimitiveSizs_Test8TestBodyEv, @function
_ZN25Memory_PrimitiveSizs_Test8TestBodyEv:
.LFB4796:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4796
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$1, -64(%rbp)
	movq	$1, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC1(%rip), %rdx
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
.LEHB3:
	call	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE3:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L40
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB4:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE4:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$120, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB5:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE5:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB6:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE6:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L40:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$1, -64(%rbp)
	movq	$1, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC1(%rip), %rdx
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
.LEHB7:
	call	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE7:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L41
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB8:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE8:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$121, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB9:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE9:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB10:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE10:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L41:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$2, -64(%rbp)
	movq	$2, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC5(%rip), %rdx
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
.LEHB11:
	call	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE11:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L42
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB12:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE12:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$122, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB13:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE13:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB14:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE14:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L42:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$4, -64(%rbp)
	movq	$4, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC7(%rip), %rdx
	leaq	.LC8(%rip), %rsi
	movq	%rax, %rdi
.LEHB15:
	call	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE15:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L43
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB16:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE16:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$123, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB17:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE17:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB18:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE18:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L43:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$4, -64(%rbp)
	movq	$4, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC7(%rip), %rdx
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
.LEHB19:
	call	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE19:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L44
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB20:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE20:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$124, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB21:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE21:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB22:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE22:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L44:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L60
	jmp	.L76
.L63:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L46
.L62:
	endbr64
	movq	%rax, %rbx
.L46:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L47
.L61:
	endbr64
	movq	%rax, %rbx
.L47:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB23:
	call	_Unwind_Resume@PLT
.L66:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L49
.L65:
	endbr64
	movq	%rax, %rbx
.L49:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L50
.L64:
	endbr64
	movq	%rax, %rbx
.L50:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L69:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L52
.L68:
	endbr64
	movq	%rax, %rbx
.L52:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L53
.L67:
	endbr64
	movq	%rax, %rbx
.L53:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L72:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L55
.L71:
	endbr64
	movq	%rax, %rbx
.L55:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L56
.L70:
	endbr64
	movq	%rax, %rbx
.L56:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L75:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L58
.L74:
	endbr64
	movq	%rax, %rbx
.L58:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L59
.L73:
	endbr64
	movq	%rax, %rbx
.L59:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE23:
.L76:
	call	__stack_chk_fail@PLT
.L60:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4796:
	.section	.gcc_except_table,"a",@progbits
.LLSDA4796:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4796-.LLSDACSB4796
.LLSDACSB4796:
	.uleb128 .LEHB3-.LFB4796
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB4796
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L61-.LFB4796
	.uleb128 0
	.uleb128 .LEHB5-.LFB4796
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L62-.LFB4796
	.uleb128 0
	.uleb128 .LEHB6-.LFB4796
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L63-.LFB4796
	.uleb128 0
	.uleb128 .LEHB7-.LFB4796
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB4796
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L64-.LFB4796
	.uleb128 0
	.uleb128 .LEHB9-.LFB4796
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L65-.LFB4796
	.uleb128 0
	.uleb128 .LEHB10-.LFB4796
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L66-.LFB4796
	.uleb128 0
	.uleb128 .LEHB11-.LFB4796
	.uleb128 .LEHE11-.LEHB11
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB12-.LFB4796
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L67-.LFB4796
	.uleb128 0
	.uleb128 .LEHB13-.LFB4796
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L68-.LFB4796
	.uleb128 0
	.uleb128 .LEHB14-.LFB4796
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L69-.LFB4796
	.uleb128 0
	.uleb128 .LEHB15-.LFB4796
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB16-.LFB4796
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L70-.LFB4796
	.uleb128 0
	.uleb128 .LEHB17-.LFB4796
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L71-.LFB4796
	.uleb128 0
	.uleb128 .LEHB18-.LFB4796
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L72-.LFB4796
	.uleb128 0
	.uleb128 .LEHB19-.LFB4796
	.uleb128 .LEHE19-.LEHB19
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB20-.LFB4796
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L73-.LFB4796
	.uleb128 0
	.uleb128 .LEHB21-.LFB4796
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L74-.LFB4796
	.uleb128 0
	.uleb128 .LEHB22-.LFB4796
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L75-.LFB4796
	.uleb128 0
	.uleb128 .LEHB23-.LFB4796
	.uleb128 .LEHE23-.LEHB23
	.uleb128 0
	.uleb128 0
.LLSDACSE4796:
	.text
	.size	_ZN25Memory_PrimitiveSizs_Test8TestBodyEv, .-_ZN25Memory_PrimitiveSizs_Test8TestBodyEv
	.section	.text._ZN15Memory_NIL_TestC2Ev,"axG",@progbits,_ZN15Memory_NIL_TestC5Ev,comdat
	.align 2
	.weak	_ZN15Memory_NIL_TestC2Ev
	.type	_ZN15Memory_NIL_TestC2Ev, @function
_ZN15Memory_NIL_TestC2Ev:
.LFB4798:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV15Memory_NIL_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4798:
	.size	_ZN15Memory_NIL_TestC2Ev, .-_ZN15Memory_NIL_TestC2Ev
	.weak	_ZN15Memory_NIL_TestC1Ev
	.set	_ZN15Memory_NIL_TestC1Ev,_ZN15Memory_NIL_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC2Ev:
.LFB4801:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4801:
	.size	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC2Ev
	.globl	_ZN15Memory_NIL_Test10test_info_E
	.bss
	.align 8
	.type	_ZN15Memory_NIL_Test10test_info_E, @object
	.size	_ZN15Memory_NIL_Test10test_info_E, 8
_ZN15Memory_NIL_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC10:
	.string	"A1"
.LC11:
	.string	"(char *) all.P"
.LC12:
	.string	"NIL"
.LC13:
	.string	"\"NIL\""
.LC14:
	.string	"(char *)all.P"
	.text
	.align 2
	.globl	_ZN15Memory_NIL_Test8TestBodyEv
	.type	_ZN15Memory_NIL_Test8TestBodyEv, @function
_ZN15Memory_NIL_Test8TestBodyEv:
.LFB4803:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4803
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	16380+_ZN6MemoryL3allE(%rip), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %r8
	leaq	8192+_ZN6MemoryL3allE(%rip), %rcx
	leaq	.LC10(%rip), %rdx
	leaq	.LC11(%rip), %rsi
	movq	%rax, %rdi
.LEHB24:
	call	_ZN7testing8internal14CmpHelperSTREQEPKcS2_S2_S2_@PLT
.LEHE24:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L80
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB25:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE25:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$129, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB26:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE26:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB27:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE27:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L80:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	leaq	16380+_ZN6MemoryL3allE(%rip), %rdx
	leaq	-48(%rbp), %rax
	leaq	.LC12(%rip), %r8
	movq	%rdx, %rcx
	leaq	.LC13(%rip), %rdx
	leaq	.LC10(%rip), %rsi
	movq	%rax, %rdi
.LEHB28:
	call	_ZN7testing8internal14CmpHelperSTREQEPKcS2_S2_S2_@PLT
.LEHE28:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L81
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB29:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE29:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$130, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB30:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE30:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB31:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE31:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L81:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	leaq	-48(%rbp), %rax
	leaq	.LC12(%rip), %r8
	leaq	8192+_ZN6MemoryL3allE(%rip), %rcx
	leaq	.LC13(%rip), %rdx
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
.LEHB32:
	call	_ZN7testing8internal14CmpHelperSTREQEPKcS2_S2_S2_@PLT
.LEHE32:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L82
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB33:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE33:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$131, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB34:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE34:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB35:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE35:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L82:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L92
	jmp	.L102
.L95:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L84
.L94:
	endbr64
	movq	%rax, %rbx
.L84:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L85
.L93:
	endbr64
	movq	%rax, %rbx
.L85:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB36:
	call	_Unwind_Resume@PLT
.L98:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L87
.L97:
	endbr64
	movq	%rax, %rbx
.L87:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L88
.L96:
	endbr64
	movq	%rax, %rbx
.L88:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L101:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L90
.L100:
	endbr64
	movq	%rax, %rbx
.L90:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L91
.L99:
	endbr64
	movq	%rax, %rbx
.L91:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE36:
.L102:
	call	__stack_chk_fail@PLT
.L92:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4803:
	.section	.gcc_except_table
.LLSDA4803:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4803-.LLSDACSB4803
.LLSDACSB4803:
	.uleb128 .LEHB24-.LFB4803
	.uleb128 .LEHE24-.LEHB24
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB25-.LFB4803
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L93-.LFB4803
	.uleb128 0
	.uleb128 .LEHB26-.LFB4803
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L94-.LFB4803
	.uleb128 0
	.uleb128 .LEHB27-.LFB4803
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L95-.LFB4803
	.uleb128 0
	.uleb128 .LEHB28-.LFB4803
	.uleb128 .LEHE28-.LEHB28
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB29-.LFB4803
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L96-.LFB4803
	.uleb128 0
	.uleb128 .LEHB30-.LFB4803
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L97-.LFB4803
	.uleb128 0
	.uleb128 .LEHB31-.LFB4803
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L98-.LFB4803
	.uleb128 0
	.uleb128 .LEHB32-.LFB4803
	.uleb128 .LEHE32-.LEHB32
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB33-.LFB4803
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L99-.LFB4803
	.uleb128 0
	.uleb128 .LEHB34-.LFB4803
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L100-.LFB4803
	.uleb128 0
	.uleb128 .LEHB35-.LFB4803
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L101-.LFB4803
	.uleb128 0
	.uleb128 .LEHB36-.LFB4803
	.uleb128 .LEHE36-.LEHB36
	.uleb128 0
	.uleb128 0
.LLSDACSE4803:
	.text
	.size	_ZN15Memory_NIL_Test8TestBodyEv, .-_ZN15Memory_NIL_Test8TestBodyEv
	.section	.text._ZN31Memory_innerAndOuterArrays_TestC2Ev,"axG",@progbits,_ZN31Memory_innerAndOuterArrays_TestC5Ev,comdat
	.align 2
	.weak	_ZN31Memory_innerAndOuterArrays_TestC2Ev
	.type	_ZN31Memory_innerAndOuterArrays_TestC2Ev, @function
_ZN31Memory_innerAndOuterArrays_TestC2Ev:
.LFB4805:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV31Memory_innerAndOuterArrays_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4805:
	.size	_ZN31Memory_innerAndOuterArrays_TestC2Ev, .-_ZN31Memory_innerAndOuterArrays_TestC2Ev
	.weak	_ZN31Memory_innerAndOuterArrays_TestC1Ev
	.set	_ZN31Memory_innerAndOuterArrays_TestC1Ev,_ZN31Memory_innerAndOuterArrays_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC2Ev:
.LFB4808:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4808:
	.size	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC2Ev
	.globl	_ZN31Memory_innerAndOuterArrays_Test10test_info_E
	.bss
	.align 8
	.type	_ZN31Memory_innerAndOuterArrays_Test10test_info_E, @object
	.size	_ZN31Memory_innerAndOuterArrays_Test10test_info_E, 8
_ZN31Memory_innerAndOuterArrays_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC15:
	.string	"all.A"
.LC16:
	.string	"A"
.LC17:
	.string	"all.P"
.LC18:
	.string	"P - 1"
	.text
	.align 2
	.globl	_ZN31Memory_innerAndOuterArrays_Test8TestBodyEv
	.type	_ZN31Memory_innerAndOuterArrays_Test8TestBodyEv, @function
_ZN31Memory_innerAndOuterArrays_Test8TestBodyEv:
.LFB4810:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4810
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-48(%rbp), %rax
	leaq	8188+_ZN6MemoryL3allE(%rip), %r8
	leaq	_ZN6Memory1AE(%rip), %rcx
	leaq	.LC15(%rip), %rdx
	leaq	.LC16(%rip), %rsi
	movq	%rax, %rdi
.LEHB37:
	call	_ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_
.LEHE37:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L106
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB38:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE38:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$136, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB39:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE39:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB40:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE40:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L106:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	leaq	8184+_ZN6MemoryL3allE(%rip), %rax
	movq	%rax, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rdx
	leaq	8192+_ZN6MemoryL3allE(%rip), %r8
	movq	%rdx, %rcx
	leaq	.LC17(%rip), %rdx
	leaq	.LC18(%rip), %rsi
	movq	%rax, %rdi
.LEHB41:
	call	_ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
.LEHE41:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L107
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB42:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE42:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$137, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB43:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE43:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB44:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE44:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L107:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L114
	jmp	.L121
.L117:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L109
.L116:
	endbr64
	movq	%rax, %rbx
.L109:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L110
.L115:
	endbr64
	movq	%rax, %rbx
.L110:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB45:
	call	_Unwind_Resume@PLT
.L120:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L112
.L119:
	endbr64
	movq	%rax, %rbx
.L112:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L113
.L118:
	endbr64
	movq	%rax, %rbx
.L113:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE45:
.L121:
	call	__stack_chk_fail@PLT
.L114:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4810:
	.section	.gcc_except_table
.LLSDA4810:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4810-.LLSDACSB4810
.LLSDACSB4810:
	.uleb128 .LEHB37-.LFB4810
	.uleb128 .LEHE37-.LEHB37
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB38-.LFB4810
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L115-.LFB4810
	.uleb128 0
	.uleb128 .LEHB39-.LFB4810
	.uleb128 .LEHE39-.LEHB39
	.uleb128 .L116-.LFB4810
	.uleb128 0
	.uleb128 .LEHB40-.LFB4810
	.uleb128 .LEHE40-.LEHB40
	.uleb128 .L117-.LFB4810
	.uleb128 0
	.uleb128 .LEHB41-.LFB4810
	.uleb128 .LEHE41-.LEHB41
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB42-.LFB4810
	.uleb128 .LEHE42-.LEHB42
	.uleb128 .L118-.LFB4810
	.uleb128 0
	.uleb128 .LEHB43-.LFB4810
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L119-.LFB4810
	.uleb128 0
	.uleb128 .LEHB44-.LFB4810
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L120-.LFB4810
	.uleb128 0
	.uleb128 .LEHB45-.LFB4810
	.uleb128 .LEHE45-.LEHB45
	.uleb128 0
	.uleb128 0
.LLSDACSE4810:
	.text
	.size	_ZN31Memory_innerAndOuterArrays_Test8TestBodyEv, .-_ZN31Memory_innerAndOuterArrays_Test8TestBodyEv
	.section	.text._ZN34Memory_twoArrayAreConsecutive_TestC2Ev,"axG",@progbits,_ZN34Memory_twoArrayAreConsecutive_TestC5Ev,comdat
	.align 2
	.weak	_ZN34Memory_twoArrayAreConsecutive_TestC2Ev
	.type	_ZN34Memory_twoArrayAreConsecutive_TestC2Ev, @function
_ZN34Memory_twoArrayAreConsecutive_TestC2Ev:
.LFB4812:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV34Memory_twoArrayAreConsecutive_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4812:
	.size	_ZN34Memory_twoArrayAreConsecutive_TestC2Ev, .-_ZN34Memory_twoArrayAreConsecutive_TestC2Ev
	.weak	_ZN34Memory_twoArrayAreConsecutive_TestC1Ev
	.set	_ZN34Memory_twoArrayAreConsecutive_TestC1Ev,_ZN34Memory_twoArrayAreConsecutive_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC2Ev:
.LFB4815:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4815:
	.size	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC2Ev
	.globl	_ZN34Memory_twoArrayAreConsecutive_Test10test_info_E
	.bss
	.align 8
	.type	_ZN34Memory_twoArrayAreConsecutive_Test10test_info_E, @object
	.size	_ZN34Memory_twoArrayAreConsecutive_Test10test_info_E, 8
_ZN34Memory_twoArrayAreConsecutive_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC19:
	.string	"A + sizeof(A)"
.LC20:
	.string	"0"
.LC21:
	.string	"A + sizeof(A) - (char *)all.P"
.LC22:
	.string	"(void *)all.P"
.LC23:
	.string	"(void *)(A + sizeof A)"
	.text
	.align 2
	.globl	_ZN34Memory_twoArrayAreConsecutive_Test8TestBodyEv
	.type	_ZN34Memory_twoArrayAreConsecutive_Test8TestBodyEv, @function
_ZN34Memory_twoArrayAreConsecutive_Test8TestBodyEv:
.LFB4817:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4817
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	8192+_ZN6MemoryL3allE(%rip), %rax
	movq	%rax, -56(%rbp)
	leaq	8196+_ZN6MemoryL3allE(%rip), %rax
	movq	%rax, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC14(%rip), %rdx
	leaq	.LC19(%rip), %rsi
	movq	%rax, %rdi
.LEHB46:
	call	_ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
.LEHE46:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L125
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB47:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE47:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$142, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB48:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE48:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB49:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE49:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L125:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	leaq	8192+_ZN6MemoryL3allE(%rip), %rax
	movq	%rax, -56(%rbp)
	leaq	8196+_ZN6MemoryL3allE(%rip), %rax
	movq	%rax, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC14(%rip), %rdx
	leaq	.LC19(%rip), %rsi
	movq	%rax, %rdi
.LEHB50:
	call	_ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
.LEHE50:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L126
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB51:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE51:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$143, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB52:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE52:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB53:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE53:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L126:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$0, -64(%rbp)
	leaq	8196+_ZN6MemoryL3allE(%rip), %rdx
	leaq	8192+_ZN6MemoryL3allE(%rip), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC20(%rip), %rdx
	leaq	.LC21(%rip), %rsi
	movq	%rax, %rdi
.LEHB54:
	call	_ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE54:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L127
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB55:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE55:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$144, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB56:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE56:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB57:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE57:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L127:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	leaq	8192+_ZN6MemoryL3allE(%rip), %rax
	movq	%rax, -56(%rbp)
	leaq	8196+_ZN6MemoryL3allE(%rip), %rax
	movq	%rax, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC22(%rip), %rdx
	leaq	.LC23(%rip), %rsi
	movq	%rax, %rdi
.LEHB58:
	call	_ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE58:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L128
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB59:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE59:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$145, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB60:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE60:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB61:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE61:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L128:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L141
	jmp	.L154
.L144:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L130
.L143:
	endbr64
	movq	%rax, %rbx
.L130:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L131
.L142:
	endbr64
	movq	%rax, %rbx
.L131:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB62:
	call	_Unwind_Resume@PLT
.L147:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L133
.L146:
	endbr64
	movq	%rax, %rbx
.L133:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L134
.L145:
	endbr64
	movq	%rax, %rbx
.L134:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L150:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L136
.L149:
	endbr64
	movq	%rax, %rbx
.L136:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L137
.L148:
	endbr64
	movq	%rax, %rbx
.L137:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L153:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L139
.L152:
	endbr64
	movq	%rax, %rbx
.L139:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L140
.L151:
	endbr64
	movq	%rax, %rbx
.L140:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE62:
.L154:
	call	__stack_chk_fail@PLT
.L141:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4817:
	.section	.gcc_except_table
.LLSDA4817:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4817-.LLSDACSB4817
.LLSDACSB4817:
	.uleb128 .LEHB46-.LFB4817
	.uleb128 .LEHE46-.LEHB46
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB47-.LFB4817
	.uleb128 .LEHE47-.LEHB47
	.uleb128 .L142-.LFB4817
	.uleb128 0
	.uleb128 .LEHB48-.LFB4817
	.uleb128 .LEHE48-.LEHB48
	.uleb128 .L143-.LFB4817
	.uleb128 0
	.uleb128 .LEHB49-.LFB4817
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L144-.LFB4817
	.uleb128 0
	.uleb128 .LEHB50-.LFB4817
	.uleb128 .LEHE50-.LEHB50
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB51-.LFB4817
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L145-.LFB4817
	.uleb128 0
	.uleb128 .LEHB52-.LFB4817
	.uleb128 .LEHE52-.LEHB52
	.uleb128 .L146-.LFB4817
	.uleb128 0
	.uleb128 .LEHB53-.LFB4817
	.uleb128 .LEHE53-.LEHB53
	.uleb128 .L147-.LFB4817
	.uleb128 0
	.uleb128 .LEHB54-.LFB4817
	.uleb128 .LEHE54-.LEHB54
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB55-.LFB4817
	.uleb128 .LEHE55-.LEHB55
	.uleb128 .L148-.LFB4817
	.uleb128 0
	.uleb128 .LEHB56-.LFB4817
	.uleb128 .LEHE56-.LEHB56
	.uleb128 .L149-.LFB4817
	.uleb128 0
	.uleb128 .LEHB57-.LFB4817
	.uleb128 .LEHE57-.LEHB57
	.uleb128 .L150-.LFB4817
	.uleb128 0
	.uleb128 .LEHB58-.LFB4817
	.uleb128 .LEHE58-.LEHB58
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB59-.LFB4817
	.uleb128 .LEHE59-.LEHB59
	.uleb128 .L151-.LFB4817
	.uleb128 0
	.uleb128 .LEHB60-.LFB4817
	.uleb128 .LEHE60-.LEHB60
	.uleb128 .L152-.LFB4817
	.uleb128 0
	.uleb128 .LEHB61-.LFB4817
	.uleb128 .LEHE61-.LEHB61
	.uleb128 .L153-.LFB4817
	.uleb128 0
	.uleb128 .LEHB62-.LFB4817
	.uleb128 .LEHE62-.LEHB62
	.uleb128 0
	.uleb128 0
.LLSDACSE4817:
	.text
	.size	_ZN34Memory_twoArrayAreConsecutive_Test8TestBodyEv, .-_ZN34Memory_twoArrayAreConsecutive_Test8TestBodyEv
	.section	.text._ZN21Memory_totalSize_TestC2Ev,"axG",@progbits,_ZN21Memory_totalSize_TestC5Ev,comdat
	.align 2
	.weak	_ZN21Memory_totalSize_TestC2Ev
	.type	_ZN21Memory_totalSize_TestC2Ev, @function
_ZN21Memory_totalSize_TestC2Ev:
.LFB4819:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV21Memory_totalSize_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4819:
	.size	_ZN21Memory_totalSize_TestC2Ev, .-_ZN21Memory_totalSize_TestC2Ev
	.weak	_ZN21Memory_totalSize_TestC1Ev
	.set	_ZN21Memory_totalSize_TestC1Ev,_ZN21Memory_totalSize_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC2Ev:
.LFB4822:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4822:
	.size	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC2Ev
	.globl	_ZN21Memory_totalSize_Test10test_info_E
	.bss
	.align 8
	.type	_ZN21Memory_totalSize_Test10test_info_E, @object
	.size	_ZN21Memory_totalSize_Test10test_info_E, 8
_ZN21Memory_totalSize_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC24:
	.string	"all.n"
.LC25:
	.string	"sizeof all.block"
.LC26:
	.string	"sizeof all.block - all.n"
.LC27:
	.string	"all.n - sizeof all.block"
	.text
	.align 2
	.globl	_ZN21Memory_totalSize_Test8TestBodyEv
	.type	_ZN21Memory_totalSize_Test8TestBodyEv, @function
_ZN21Memory_totalSize_Test8TestBodyEv:
.LFB4824:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4824
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movw	$-24576, -64(%rbp)
	movq	$40960, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC24(%rip), %rdx
	leaq	.LC25(%rip), %rsi
	movq	%rax, %rdi
.LEHB63:
	call	_ZN7testing8internal8EqHelper7CompareImN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
.LEHE63:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L158
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB64:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE64:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$150, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB65:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE65:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB66:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE66:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L158:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC20(%rip), %rdx
	leaq	.LC26(%rip), %rsi
	movq	%rax, %rdi
.LEHB67:
	call	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE67:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L159
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB68:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE68:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$151, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB69:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE69:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB70:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE70:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L159:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-64(%rbp), %rcx
	leaq	-56(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC20(%rip), %rdx
	leaq	.LC27(%rip), %rsi
	movq	%rax, %rdi
.LEHB71:
	call	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
.LEHE71:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L160
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB72:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE72:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$152, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB73:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE73:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB74:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE74:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L160:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L170
	jmp	.L180
.L173:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L162
.L172:
	endbr64
	movq	%rax, %rbx
.L162:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L163
.L171:
	endbr64
	movq	%rax, %rbx
.L163:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB75:
	call	_Unwind_Resume@PLT
.L176:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L165
.L175:
	endbr64
	movq	%rax, %rbx
.L165:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L166
.L174:
	endbr64
	movq	%rax, %rbx
.L166:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L179:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L168
.L178:
	endbr64
	movq	%rax, %rbx
.L168:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L169
.L177:
	endbr64
	movq	%rax, %rbx
.L169:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE75:
.L180:
	call	__stack_chk_fail@PLT
.L170:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4824:
	.section	.gcc_except_table
.LLSDA4824:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4824-.LLSDACSB4824
.LLSDACSB4824:
	.uleb128 .LEHB63-.LFB4824
	.uleb128 .LEHE63-.LEHB63
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB64-.LFB4824
	.uleb128 .LEHE64-.LEHB64
	.uleb128 .L171-.LFB4824
	.uleb128 0
	.uleb128 .LEHB65-.LFB4824
	.uleb128 .LEHE65-.LEHB65
	.uleb128 .L172-.LFB4824
	.uleb128 0
	.uleb128 .LEHB66-.LFB4824
	.uleb128 .LEHE66-.LEHB66
	.uleb128 .L173-.LFB4824
	.uleb128 0
	.uleb128 .LEHB67-.LFB4824
	.uleb128 .LEHE67-.LEHB67
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB68-.LFB4824
	.uleb128 .LEHE68-.LEHB68
	.uleb128 .L174-.LFB4824
	.uleb128 0
	.uleb128 .LEHB69-.LFB4824
	.uleb128 .LEHE69-.LEHB69
	.uleb128 .L175-.LFB4824
	.uleb128 0
	.uleb128 .LEHB70-.LFB4824
	.uleb128 .LEHE70-.LEHB70
	.uleb128 .L176-.LFB4824
	.uleb128 0
	.uleb128 .LEHB71-.LFB4824
	.uleb128 .LEHE71-.LEHB71
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB72-.LFB4824
	.uleb128 .LEHE72-.LEHB72
	.uleb128 .L177-.LFB4824
	.uleb128 0
	.uleb128 .LEHB73-.LFB4824
	.uleb128 .LEHE73-.LEHB73
	.uleb128 .L178-.LFB4824
	.uleb128 0
	.uleb128 .LEHB74-.LFB4824
	.uleb128 .LEHE74-.LEHB74
	.uleb128 .L179-.LFB4824
	.uleb128 0
	.uleb128 .LEHB75-.LFB4824
	.uleb128 .LEHE75-.LEHB75
	.uleb128 0
	.uleb128 0
.LLSDACSE4824:
	.text
	.size	_ZN21Memory_totalSize_Test8TestBodyEv, .-_ZN21Memory_totalSize_Test8TestBodyEv
	.section	.text._ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC2Ev,"axG",@progbits,_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC5Ev,comdat
	.align 2
	.weak	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC2Ev
	.type	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC2Ev, @function
_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC2Ev:
.LFB4826:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4826:
	.size	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC2Ev, .-_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC2Ev
	.weak	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC1Ev
	.set	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC1Ev,_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC2Ev:
.LFB4829:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4829:
	.size	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC2Ev
	.globl	_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test10test_info_E
	.bss
	.align 8
	.type	_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test10test_info_E, @object
	.size	_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test10test_info_E, 8
_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC28:
	.string	"all.a"
.LC29:
	.string	"(H) all.a"
.LC30:
	.string	"all.p"
.LC31:
	.string	"(H) all.p"
.LC32:
	.string	"(unsigned H) all.n"
	.text
	.align 2
	.globl	_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test8TestBodyEv
	.type	_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test8TestBodyEv, @function
_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test8TestBodyEv:
.LFB4831:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4831
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movw	$8192, -56(%rbp)
	movw	$8192, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC28(%rip), %rdx
	leaq	.LC29(%rip), %rsi
	movq	%rax, %rdi
.LEHB76:
	call	_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
.LEHE76:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L184
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB77:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE77:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$157, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB78:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE78:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB79:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE79:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L184:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movw	$8192, -56(%rbp)
	movw	$8192, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC30(%rip), %rdx
	leaq	.LC31(%rip), %rsi
	movq	%rax, %rdi
.LEHB80:
	call	_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut0_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
.LEHE80:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L185
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB81:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE81:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$158, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB82:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE82:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB83:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE83:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L185:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movw	$-24576, -56(%rbp)
	movw	$-24576, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC24(%rip), %rdx
	leaq	.LC32(%rip), %rsi
	movq	%rax, %rdi
.LEHB84:
	call	_ZN7testing8internal8EqHelper7CompareItN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
.LEHE84:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L186
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB85:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE85:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$159, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB86:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE86:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB87:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE87:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L186:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L196
	jmp	.L206
.L199:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L188
.L198:
	endbr64
	movq	%rax, %rbx
.L188:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L189
.L197:
	endbr64
	movq	%rax, %rbx
.L189:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB88:
	call	_Unwind_Resume@PLT
.L202:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L191
.L201:
	endbr64
	movq	%rax, %rbx
.L191:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L192
.L200:
	endbr64
	movq	%rax, %rbx
.L192:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L205:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L194
.L204:
	endbr64
	movq	%rax, %rbx
.L194:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L195
.L203:
	endbr64
	movq	%rax, %rbx
.L195:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE88:
.L206:
	call	__stack_chk_fail@PLT
.L196:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4831:
	.section	.gcc_except_table
.LLSDA4831:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4831-.LLSDACSB4831
.LLSDACSB4831:
	.uleb128 .LEHB76-.LFB4831
	.uleb128 .LEHE76-.LEHB76
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB77-.LFB4831
	.uleb128 .LEHE77-.LEHB77
	.uleb128 .L197-.LFB4831
	.uleb128 0
	.uleb128 .LEHB78-.LFB4831
	.uleb128 .LEHE78-.LEHB78
	.uleb128 .L198-.LFB4831
	.uleb128 0
	.uleb128 .LEHB79-.LFB4831
	.uleb128 .LEHE79-.LEHB79
	.uleb128 .L199-.LFB4831
	.uleb128 0
	.uleb128 .LEHB80-.LFB4831
	.uleb128 .LEHE80-.LEHB80
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB81-.LFB4831
	.uleb128 .LEHE81-.LEHB81
	.uleb128 .L200-.LFB4831
	.uleb128 0
	.uleb128 .LEHB82-.LFB4831
	.uleb128 .LEHE82-.LEHB82
	.uleb128 .L201-.LFB4831
	.uleb128 0
	.uleb128 .LEHB83-.LFB4831
	.uleb128 .LEHE83-.LEHB83
	.uleb128 .L202-.LFB4831
	.uleb128 0
	.uleb128 .LEHB84-.LFB4831
	.uleb128 .LEHE84-.LEHB84
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB85-.LFB4831
	.uleb128 .LEHE85-.LEHB85
	.uleb128 .L203-.LFB4831
	.uleb128 0
	.uleb128 .LEHB86-.LFB4831
	.uleb128 .LEHE86-.LEHB86
	.uleb128 .L204-.LFB4831
	.uleb128 0
	.uleb128 .LEHB87-.LFB4831
	.uleb128 .LEHE87-.LEHB87
	.uleb128 .L205-.LFB4831
	.uleb128 0
	.uleb128 .LEHB88-.LFB4831
	.uleb128 .LEHE88-.LEHB88
	.uleb128 0
	.uleb128 0
.LLSDACSE4831:
	.text
	.size	_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test8TestBodyEv, .-_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test8TestBodyEv
	.section	.text._ZN23Memory_minimalSize_TestC2Ev,"axG",@progbits,_ZN23Memory_minimalSize_TestC5Ev,comdat
	.align 2
	.weak	_ZN23Memory_minimalSize_TestC2Ev
	.type	_ZN23Memory_minimalSize_TestC2Ev, @function
_ZN23Memory_minimalSize_TestC2Ev:
.LFB4833:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV23Memory_minimalSize_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4833:
	.size	_ZN23Memory_minimalSize_TestC2Ev, .-_ZN23Memory_minimalSize_TestC2Ev
	.weak	_ZN23Memory_minimalSize_TestC1Ev
	.set	_ZN23Memory_minimalSize_TestC1Ev,_ZN23Memory_minimalSize_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC2Ev:
.LFB4836:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4836:
	.size	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC2Ev
	.globl	_ZN23Memory_minimalSize_Test10test_info_E
	.bss
	.align 8
	.type	_ZN23Memory_minimalSize_Test10test_info_E, @object
	.size	_ZN23Memory_minimalSize_Test10test_info_E, 8
_ZN23Memory_minimalSize_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC33:
	.string	"100"
	.text
	.align 2
	.globl	_ZN23Memory_minimalSize_Test8TestBodyEv
	.type	_ZN23Memory_minimalSize_Test8TestBodyEv, @function
_ZN23Memory_minimalSize_Test8TestBodyEv:
.LFB4838:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4838
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$100, -56(%rbp)
	movw	$8192, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC33(%rip), %rdx
	leaq	.LC29(%rip), %rsi
	movq	%rax, %rdi
.LEHB89:
	call	_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_
.LEHE89:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L210
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB90:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE90:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$165, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB91:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE91:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB92:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE92:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L210:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$100, -56(%rbp)
	movw	$8192, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC33(%rip), %rdx
	leaq	.LC31(%rip), %rsi
	movq	%rax, %rdi
.LEHB93:
	call	_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_
.LEHE93:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L211
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB94:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE94:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$166, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB95:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE95:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB96:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE96:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L211:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L218
	jmp	.L225
.L221:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L213
.L220:
	endbr64
	movq	%rax, %rbx
.L213:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L214
.L219:
	endbr64
	movq	%rax, %rbx
.L214:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB97:
	call	_Unwind_Resume@PLT
.L224:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L216
.L223:
	endbr64
	movq	%rax, %rbx
.L216:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L217
.L222:
	endbr64
	movq	%rax, %rbx
.L217:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE97:
.L225:
	call	__stack_chk_fail@PLT
.L218:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4838:
	.section	.gcc_except_table
.LLSDA4838:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4838-.LLSDACSB4838
.LLSDACSB4838:
	.uleb128 .LEHB89-.LFB4838
	.uleb128 .LEHE89-.LEHB89
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB90-.LFB4838
	.uleb128 .LEHE90-.LEHB90
	.uleb128 .L219-.LFB4838
	.uleb128 0
	.uleb128 .LEHB91-.LFB4838
	.uleb128 .LEHE91-.LEHB91
	.uleb128 .L220-.LFB4838
	.uleb128 0
	.uleb128 .LEHB92-.LFB4838
	.uleb128 .LEHE92-.LEHB92
	.uleb128 .L221-.LFB4838
	.uleb128 0
	.uleb128 .LEHB93-.LFB4838
	.uleb128 .LEHE93-.LEHB93
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB94-.LFB4838
	.uleb128 .LEHE94-.LEHB94
	.uleb128 .L222-.LFB4838
	.uleb128 0
	.uleb128 .LEHB95-.LFB4838
	.uleb128 .LEHE95-.LEHB95
	.uleb128 .L223-.LFB4838
	.uleb128 0
	.uleb128 .LEHB96-.LFB4838
	.uleb128 .LEHE96-.LEHB96
	.uleb128 .L224-.LFB4838
	.uleb128 0
	.uleb128 .LEHB97-.LFB4838
	.uleb128 .LEHE97-.LEHB97
	.uleb128 0
	.uleb128 0
.LLSDACSE4838:
	.text
	.size	_ZN23Memory_minimalSize_Test8TestBodyEv, .-_ZN23Memory_minimalSize_Test8TestBodyEv
	.section	.text._ZN20Memory_overflow_TestC2Ev,"axG",@progbits,_ZN20Memory_overflow_TestC5Ev,comdat
	.align 2
	.weak	_ZN20Memory_overflow_TestC2Ev
	.type	_ZN20Memory_overflow_TestC2Ev, @function
_ZN20Memory_overflow_TestC2Ev:
.LFB4840:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestC2Ev@PLT
	leaq	16+_ZTV20Memory_overflow_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4840:
	.size	_ZN20Memory_overflow_TestC2Ev, .-_ZN20Memory_overflow_TestC2Ev
	.weak	_ZN20Memory_overflow_TestC1Ev
	.set	_ZN20Memory_overflow_TestC1Ev,_ZN20Memory_overflow_TestC2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC2Ev
	.type	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC2Ev, @function
_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC2Ev:
.LFB4843:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseC2Ev
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4843:
	.size	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC2Ev, .-_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC1Ev
	.set	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC1Ev,_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC2Ev
	.globl	_ZN20Memory_overflow_Test10test_info_E
	.bss
	.align 8
	.type	_ZN20Memory_overflow_Test10test_info_E, @object
	.size	_ZN20Memory_overflow_Test10test_info_E, 8
_ZN20Memory_overflow_Test10test_info_E:
	.zero	8
	.section	.rodata
.LC34:
	.string	"(H) all.p + 1"
.LC35:
	.string	"(H) - all.a - 1"
	.text
	.align 2
	.globl	_ZN20Memory_overflow_Test8TestBodyEv
	.type	_ZN20Memory_overflow_Test8TestBodyEv, @function
_ZN20Memory_overflow_Test8TestBodyEv:
.LFB4845:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4845
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$0, -56(%rbp)
	movl	$8193, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC20(%rip), %rdx
	leaq	.LC34(%rip), %rsi
	movq	%rax, %rdi
.LEHB98:
	call	_ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_
.LEHE98:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L229
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB99:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE99:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$172, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB100:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE100:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB101:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE101:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L229:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movl	$0, -56(%rbp)
	movl	$-8193, -64(%rbp)
	leaq	-48(%rbp), %rax
	leaq	-56(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC20(%rip), %rdx
	leaq	.LC35(%rip), %rsi
	movq	%rax, %rdi
.LEHB102:
	call	_ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_
.LEHE102:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResultcvbEv
	testb	%al, %al
	jne	.L230
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
.LEHB103:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE103:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK7testing15AssertionResult15failure_messageEv
	movq	%rax, %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %r8
	movl	$173, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
.LEHB104:
	call	_ZN7testing8internal12AssertHelperC1ENS_14TestPartResult4TypeEPKciS5_@PLT
.LEHE104:
	leaq	-56(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB105:
	call	_ZNK7testing8internal12AssertHelperaSERKNS_7MessageE@PLT
.LEHE105:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
.L230:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L237
	jmp	.L244
.L240:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L232
.L239:
	endbr64
	movq	%rax, %rbx
.L232:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L233
.L238:
	endbr64
	movq	%rax, %rbx
.L233:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB106:
	call	_Unwind_Resume@PLT
.L243:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12AssertHelperD1Ev@PLT
	jmp	.L235
.L242:
	endbr64
	movq	%rax, %rbx
.L235:
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	jmp	.L236
.L241:
	endbr64
	movq	%rax, %rbx
.L236:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE106:
.L244:
	call	__stack_chk_fail@PLT
.L237:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4845:
	.section	.gcc_except_table
.LLSDA4845:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4845-.LLSDACSB4845
.LLSDACSB4845:
	.uleb128 .LEHB98-.LFB4845
	.uleb128 .LEHE98-.LEHB98
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB99-.LFB4845
	.uleb128 .LEHE99-.LEHB99
	.uleb128 .L238-.LFB4845
	.uleb128 0
	.uleb128 .LEHB100-.LFB4845
	.uleb128 .LEHE100-.LEHB100
	.uleb128 .L239-.LFB4845
	.uleb128 0
	.uleb128 .LEHB101-.LFB4845
	.uleb128 .LEHE101-.LEHB101
	.uleb128 .L240-.LFB4845
	.uleb128 0
	.uleb128 .LEHB102-.LFB4845
	.uleb128 .LEHE102-.LEHB102
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB103-.LFB4845
	.uleb128 .LEHE103-.LEHB103
	.uleb128 .L241-.LFB4845
	.uleb128 0
	.uleb128 .LEHB104-.LFB4845
	.uleb128 .LEHE104-.LEHB104
	.uleb128 .L242-.LFB4845
	.uleb128 0
	.uleb128 .LEHB105-.LFB4845
	.uleb128 .LEHE105-.LEHB105
	.uleb128 .L243-.LFB4845
	.uleb128 0
	.uleb128 .LEHB106-.LFB4845
	.uleb128 .LEHE106-.LEHB106
	.uleb128 0
	.uleb128 0
.LLSDACSE4845:
	.text
	.size	_ZN20Memory_overflow_Test8TestBodyEv, .-_ZN20Memory_overflow_Test8TestBodyEv
	.globl	main
	.type	main, @function
main:
.LFB4846:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing14InitGoogleTestEPiPPc@PLT
	call	_Z13RUN_ALL_TESTSv
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4846:
	.size	main, .-main
	.section	.text._ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev,"axG",@progbits,_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED5Ev,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev
	.type	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev, @function
_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev:
.LFB5125:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L248
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	movq	(%rax), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_
.L248:
	movq	-24(%rbp), %rax
	movq	$0, (%rax)
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5125:
	.size	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev, .-_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev
	.weak	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED1Ev
	.set	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED1Ev,_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev
	.section	.text._ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv,"axG",@progbits,_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv,comdat
	.align 2
	.weak	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	.type	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv, @function
_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv:
.LFB5127:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5127:
	.size	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv, .-_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	.section	.rodata
.LC36:
	.string	"(null)"
	.section	.text._ZN7testing7MessagelsIKcEERS0_RKPT_,"axG",@progbits,_ZN7testing7MessagelsIKcEERS0_RKPT_,comdat
	.align 2
	.weak	_ZN7testing7MessagelsIKcEERS0_RKPT_
	.type	_ZN7testing7MessagelsIKcEERS0_RKPT_, @function
_ZN7testing7MessagelsIKcEERS0_RKPT_:
.LFB5130:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L252
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	addq	$16, %rax
	leaq	.LC36(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L253
.L252:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	leaq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
.L253:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5130:
	.size	_ZN7testing7MessagelsIKcEERS0_RKPT_, .-_ZN7testing7MessagelsIKcEERS0_RKPT_
	.section	.text._ZN7testing8internal7PrintToIPKvEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToIPKvEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToIPKvEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIPKvEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIPKvEEvRKT_PSo:
.LFB5186:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L256
	call	__stack_chk_fail@PLT
.L256:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5186:
	.size	_ZN7testing8internal7PrintToIPKvEEvRKT_PSo, .-_ZN7testing8internal7PrintToIPKvEEvRKT_PSo
	.section	.text._ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv,"axG",@progbits,_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv,comdat
	.align 2
	.weak	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	.type	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv, @function
_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv:
.LFB5272:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5272:
	.size	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv, .-_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	.section	.text._ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv,"axG",@progbits,_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv,comdat
	.align 2
	.weak	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv
	.type	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv, @function
_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv:
.LFB5273:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5273:
	.size	_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv, .-_ZNKSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEptEv
	.section	.text._ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_,"axG",@progbits,_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_
	.type	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_, @function
_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_:
.LFB5277:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	movq	%rax, %rdx
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_
	movq	-32(%rbp), %rax
	testq	%rax, %rax
	je	.L263
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	movq	(%rax), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_
.L263:
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5277:
	.size	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_, .-_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE5resetEPS5_
	.section	.text._ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev,"axG",@progbits,_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED5Ev,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev
	.type	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev, @function
_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev:
.LFB5282:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L265
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	movq	(%rax), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_
.L265:
	movq	-24(%rbp), %rax
	movq	$0, (%rax)
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5282:
	.size	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev, .-_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev
	.weak	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED1Ev
	.set	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED1Ev,_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EED2Ev
	.section	.rodata
	.align 8
.LC37:
	.string	"/usr/include/gtest/internal/gtest-internal.h"
	.align 8
.LC38:
	.string	"Condition !test_case_fp || !test_suite_fp failed. "
	.align 8
.LC39:
	.string	"Test can not provide both SetUpTestSuite and SetUpTestCase, please make sure there is only one present at "
.LC40:
	.string	":"
	.section	.text._ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci,"axG",@progbits,_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci,comdat
	.weak	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	.type	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci, @function
_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci:
.LFB5284:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5284
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	_ZN7testing4Test13SetUpTestCaseEv(%rip), %rsi
	leaq	_ZN7testing4Test13SetUpTestCaseEv(%rip), %rdi
	call	_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_
	movq	%rax, -40(%rbp)
	leaq	_ZN7testing4Test14SetUpTestSuiteEv(%rip), %rsi
	leaq	_ZN7testing4Test14SetUpTestSuiteEv(%rip), %rdi
	call	_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_
	movq	%rax, -32(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L267
	cmpq	$0, -32(%rbp)
	jne	.L268
.L267:
	movl	$1, %eax
	jmp	.L269
.L268:
	movl	$0, %eax
.L269:
	movzbl	%al, %eax
	movl	%eax, %edi
.LEHB107:
	call	_ZN7testing8internal6IsTrueEb@PLT
	testb	%al, %al
	jne	.L270
	leaq	-44(%rbp), %rax
	movl	$516, %ecx
	leaq	.LC37(%rip), %rdx
	movl	$3, %esi
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLogC1ENS0_16GTestLogSeverityEPKci@PLT
.LEHE107:
	leaq	-44(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLog9GetStreamEv
	leaq	.LC38(%rip), %rsi
	movq	%rax, %rdi
.LEHB108:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	.LC39(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	.LC40(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
.LEHE108:
	leaq	-44(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLogD1Ev@PLT
.L270:
	cmpq	$0, -40(%rbp)
	je	.L271
	movq	-40(%rbp), %rax
	jmp	.L273
.L271:
	movq	-32(%rbp), %rax
.L273:
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L275
	jmp	.L277
.L276:
	endbr64
	movq	%rax, %rbx
	leaq	-44(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLogD1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB109:
	call	_Unwind_Resume@PLT
.LEHE109:
.L277:
	call	__stack_chk_fail@PLT
.L275:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5284:
	.section	.gcc_except_table
.LLSDA5284:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5284-.LLSDACSB5284
.LLSDACSB5284:
	.uleb128 .LEHB107-.LFB5284
	.uleb128 .LEHE107-.LEHB107
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB108-.LFB5284
	.uleb128 .LEHE108-.LEHB108
	.uleb128 .L276-.LFB5284
	.uleb128 0
	.uleb128 .LEHB109-.LFB5284
	.uleb128 .LEHE109-.LEHB109
	.uleb128 0
	.uleb128 0
.LLSDACSE5284:
	.section	.text._ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci,"axG",@progbits,_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci,comdat
	.size	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci, .-_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	.section	.rodata
	.align 8
.LC41:
	.string	"Test can not provide both TearDownTestSuite and TearDownTestCase, please make sure there is only one present at"
	.section	.text._ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci,"axG",@progbits,_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci,comdat
	.weak	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	.type	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci, @function
_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci:
.LFB5285:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5285
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	_ZN7testing4Test16TearDownTestCaseEv(%rip), %rsi
	leaq	_ZN7testing4Test16TearDownTestCaseEv(%rip), %rdi
	call	_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_
	movq	%rax, -40(%rbp)
	leaq	_ZN7testing4Test17TearDownTestSuiteEv(%rip), %rsi
	leaq	_ZN7testing4Test17TearDownTestSuiteEv(%rip), %rdi
	call	_ZN7testing8internal19GetNotDefaultOrNullEPFvvES2_
	movq	%rax, -32(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L279
	cmpq	$0, -32(%rbp)
	jne	.L280
.L279:
	movl	$1, %eax
	jmp	.L281
.L280:
	movl	$0, %eax
.L281:
	movzbl	%al, %eax
	movl	%eax, %edi
.LEHB110:
	call	_ZN7testing8internal6IsTrueEb@PLT
	testb	%al, %al
	jne	.L282
	leaq	-44(%rbp), %rax
	movl	$531, %ecx
	leaq	.LC37(%rip), %rdx
	movl	$3, %esi
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLogC1ENS0_16GTestLogSeverityEPKci@PLT
.LEHE110:
	leaq	-44(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLog9GetStreamEv
	leaq	.LC38(%rip), %rsi
	movq	%rax, %rdi
.LEHB111:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	.LC41(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	.LC40(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
.LEHE111:
	leaq	-44(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLogD1Ev@PLT
.L282:
	cmpq	$0, -40(%rbp)
	je	.L283
	movq	-40(%rbp), %rax
	jmp	.L285
.L283:
	movq	-32(%rbp), %rax
.L285:
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L287
	jmp	.L289
.L288:
	endbr64
	movq	%rax, %rbx
	leaq	-44(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal8GTestLogD1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB112:
	call	_Unwind_Resume@PLT
.LEHE112:
.L289:
	call	__stack_chk_fail@PLT
.L287:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5285:
	.section	.gcc_except_table
.LLSDA5285:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5285-.LLSDACSB5285
.LLSDACSB5285:
	.uleb128 .LEHB110-.LFB5285
	.uleb128 .LEHE110-.LEHB110
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB111-.LFB5285
	.uleb128 .LEHE111-.LEHB111
	.uleb128 .L288-.LFB5285
	.uleb128 0
	.uleb128 .LEHB112-.LFB5285
	.uleb128 .LEHE112-.LEHB112
	.uleb128 0
	.uleb128 0
.LLSDACSE5285:
	.section	.text._ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci,"axG",@progbits,_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci,comdat
	.size	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci, .-_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	.section	.text._ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_:
.LFB5286:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L292
	call	__stack_chk_fail@PLT
.L292:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5286:
	.size	_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareImiLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.section	.text._ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_:
.LFB5287:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L295
	call	__stack_chk_fail@PLT
.L295:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5287:
	.size	_ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareIPcA4_cLPv0EEENS_15AssertionResultEPKcS8_RKT_RKT0_
	.section	.text._ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_:
.LFB5288:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L298
	call	__stack_chk_fail@PLT
.L298:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5288:
	.size	_ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareIP4pairA8192_S3_LPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
	.section	.rodata
.LC42:
	.string	">="
	.section	.text._ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_:
.LFB5289:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jb	.L300
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L299
.L300:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	leaq	.LC42(%rip), %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_
.L299:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L302
	call	__stack_chk_fail@PLT
.L302:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5289:
	.size	_ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperGEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.section	.rodata
.LC43:
	.string	"<="
	.section	.text._ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_:
.LFB5290:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	ja	.L304
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L303
.L304:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	leaq	.LC43(%rip), %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_
.L303:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L306
	call	__stack_chk_fail@PLT
.L306:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5290:
	.size	_ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperLEIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.section	.text._ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_:
.LFB5291:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L309
	call	__stack_chk_fail@PLT
.L309:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5291:
	.size	_ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareIliLPv0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.section	.text._ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_:
.LFB5292:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L312
	call	__stack_chk_fail@PLT
.L312:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5292:
	.size	_ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareIPvS3_LS3_0EEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.text
	.type	_ZN7testing8internal8EqHelper7CompareImN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareImN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_:
.LFB5293:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L315
	call	__stack_chk_fail@PLT
.L315:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5293:
	.size	_ZN7testing8internal8EqHelper7CompareImN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareImN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_:
.LFB5294:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L318
	call	__stack_chk_fail@PLT
.L318:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5294:
	.size	_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut0_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut0_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_:
.LFB5295:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L321
	call	__stack_chk_fail@PLT
.L321:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5295:
	.size	_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut0_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareIsN6Memory3._4Ut0_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
	.type	_ZN7testing8internal8EqHelper7CompareItN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, @function
_ZN7testing8internal8EqHelper7CompareItN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_:
.LFB5296:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal11CmpHelperEQItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L324
	call	__stack_chk_fail@PLT
.L324:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5296:
	.size	_ZN7testing8internal8EqHelper7CompareItN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_, .-_ZN7testing8internal8EqHelper7CompareItN6Memory3._4Ut1_ELPv0EEENS_15AssertionResultEPKcS9_RKT_RKT0_
	.section	.rodata
.LC44:
	.string	">"
	.section	.text._ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_:
.LFB5297:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movzwl	(%rax), %eax
	movswl	%ax, %edx
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L326
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L325
.L326:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	leaq	.LC44(%rip), %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_
.L325:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L328
	call	__stack_chk_fail@PLT
.L328:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5297:
	.size	_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperGTIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.section	.text._ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_:
.LFB5298:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movl	(%rax), %edx
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L330
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L329
.L330:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	leaq	.LC44(%rip), %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_
.L329:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L332
	call	__stack_chk_fail@PLT
.L332:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5298:
	.size	_ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperGTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.section	.rodata
.LC45:
	.string	"<"
	.section	.text._ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_:
.LFB5299:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movl	(%rax), %edx
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jge	.L334
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L333
.L334:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	leaq	.LC45(%rip), %r9
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_
.L333:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L336
	call	__stack_chk_fail@PLT
.L336:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5299:
	.size	_ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperLTIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.section	.text._ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,"axG",@progbits,_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.type	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, @function
_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv:
.LFB5438:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5438:
	.size	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, .-_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.section	.text._ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv,"axG",@progbits,_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv
	.type	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv, @function
_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv:
.LFB5439:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5439:
	.size	_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv, .-_ZNSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv
	.section	.text._ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_,"axG",@progbits,_ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_,comdat
	.weak	_ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	.type	_ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_, @function
_ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_:
.LFB5440:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5440:
	.size	_ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_, .-_ZSt4moveIRPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	.section	.text._ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_,"axG",@progbits,_ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_,comdat
	.align 2
	.weak	_ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_
	.type	_ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_, @function
_ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_:
.LFB5441:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	testq	%rax, %rax
	je	.L345
	movq	(%rax), %rdx
	addq	$8, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
.L345:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5441:
	.size	_ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_, .-_ZNKSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEclEPS5_
	.section	.text._ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv,"axG",@progbits,_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv,comdat
	.align 2
	.weak	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	.type	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv, @function
_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv:
.LFB5442:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5442:
	.size	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv, .-_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE3getEv
	.section	.rodata
.LC46:
	.string	"NULL"
	.section	.text._ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, @function
_ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo:
.LFB5495:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L349
	movq	-16(%rbp), %rax
	leaq	.LC46(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L351
.L349:
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPKv@PLT
.L351:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5495:
	.size	_ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, .-_ZN7testing8internal14DefaultPrintToIKvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.section	.text._ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,"axG",@progbits,_ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.type	_ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, @function
_ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv:
.LFB5587:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_
	movq	(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5587:
	.size	_ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, .-_ZNKSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.section	.text._ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,"axG",@progbits,_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.type	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, @function
_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv:
.LFB5588:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5588:
	.size	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, .-_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.section	.text._ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_,"axG",@progbits,_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_,comdat
	.weak	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	.type	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_, @function
_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_:
.LFB5590:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5590:
	.size	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_, .-_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	.section	.text._ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_,"axG",@progbits,_ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_,comdat
	.weak	_ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_
	.type	_ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_, @function
_ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_:
.LFB5589:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEONSt16remove_referenceIT_E4typeEOS9_
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L359
	call	__stack_chk_fail@PLT
.L359:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5589:
	.size	_ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_, .-_ZSt4swapIPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleISB_ESt18is_move_assignableISB_EEE5valueEvE4typeERSB_SL_
	.section	.text._ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv,"axG",@progbits,_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv
	.type	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv, @function
_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv:
.LFB5591:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5591:
	.size	_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv, .-_ZNSt10unique_ptrINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE11get_deleterEv
	.section	.text._ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_,"axG",@progbits,_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_,comdat
	.align 2
	.weak	_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_
	.type	_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_, @function
_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_:
.LFB5592:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rbx
	testq	%rbx, %rbx
	je	.L364
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movl	$32, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
.L364:
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5592:
	.size	_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_, .-_ZNKSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEclEPS5_
	.section	.text._ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_:
.LFB5595:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	cltq
	cmpq	%rax, %rdx
	jne	.L366
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L365
.L366:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_
.L365:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L368
	call	__stack_chk_fail@PLT
.L368:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5595:
	.size	_ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQImiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.section	.text._ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_:
.LFB5596:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -56(%rbp)
	jne	.L370
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L369
.L370:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_
.L369:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L372
	call	__stack_chk_fail@PLT
.L372:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5596:
	.size	_ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.section	.text._ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5597:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -56(%rbp)
	jne	.L374
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L373
.L374:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_
.L373:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L376
	call	__stack_chk_fail@PLT
.L376:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5597:
	.size	_ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_
	.section	.rodata
.LC47:
	.string	"Expected: ("
.LC48:
	.string	") "
.LC49:
	.string	" ("
.LC50:
	.string	"), actual: "
.LC51:
	.string	" vs "
	.section	.text._ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_,"axG",@progbits,_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_,comdat
	.weak	_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_
	.type	_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_, @function
_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_:
.LFB5598:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5598
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -120(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%rdx, -136(%rbp)
	movq	%rcx, -144(%rbp)
	movq	%r8, -152(%rbp)
	movq	%r9, -160(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
.LEHB113:
	call	_ZN7testing16AssertionFailureEv@PLT
.LEHE113:
	leaq	-112(%rbp), %rax
	leaq	.LC47(%rip), %rsi
	movq	%rax, %rdi
.LEHB114:
	call	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC48(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-160(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC49(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-136(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC50(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	-144(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE114:
	leaq	-96(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB115:
	call	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	leaq	.LC51(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	-144(%rbp), %rdx
	movq	-152(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE115:
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB116:
	call	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	movq	%rax, %rdx
	movq	-120(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultC1ERKS0_@PLT
.LEHE116:
	nop
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L382
	jmp	.L386
.L385:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L380
.L384:
	endbr64
	movq	%rax, %rbx
.L380:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L381
.L383:
	endbr64
	movq	%rax, %rbx
.L381:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB117:
	call	_Unwind_Resume@PLT
.LEHE117:
.L386:
	call	__stack_chk_fail@PLT
.L382:
	movq	-120(%rbp), %rax
	addq	$152, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5598:
	.section	.gcc_except_table
.LLSDA5598:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5598-.LLSDACSB5598
.LLSDACSB5598:
	.uleb128 .LEHB113-.LFB5598
	.uleb128 .LEHE113-.LEHB113
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB114-.LFB5598
	.uleb128 .LEHE114-.LEHB114
	.uleb128 .L383-.LFB5598
	.uleb128 0
	.uleb128 .LEHB115-.LFB5598
	.uleb128 .LEHE115-.LEHB115
	.uleb128 .L384-.LFB5598
	.uleb128 0
	.uleb128 .LEHB116-.LFB5598
	.uleb128 .LEHE116-.LEHB116
	.uleb128 .L385-.LFB5598
	.uleb128 0
	.uleb128 .LEHB117-.LFB5598
	.uleb128 .LEHE117-.LEHB117
	.uleb128 0
	.uleb128 0
.LLSDACSE5598:
	.section	.text._ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_,"axG",@progbits,_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_,comdat
	.size	_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_, .-_ZN7testing8internal18CmpHelperOpFailureIPcS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_S5_
	.section	.text._ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_:
.LFB5599:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	cltq
	cmpq	%rax, %rdx
	jne	.L388
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L387
.L388:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_
.L387:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L390
	call	__stack_chk_fail@PLT
.L390:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5599:
	.size	_ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQIliEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.section	.text._ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_:
.LFB5600:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L392
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L391
.L392:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
.L391:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L394
	call	__stack_chk_fail@PLT
.L394:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5600:
	.size	_ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.text
	.type	_ZN7testing8internal11CmpHelperEQImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5601:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-56(%rbp), %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	cmpq	%rax, %rdx
	jne	.L396
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L395
.L396:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
.L395:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L398
	call	__stack_chk_fail@PLT
.L398:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5601:
	.size	_ZN7testing8internal11CmpHelperEQImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5602:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movzwl	(%rax), %edx
	movq	-56(%rbp), %rax
	movzwl	(%rax), %eax
	cmpw	%ax, %dx
	jne	.L400
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L399
.L400:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
.L399:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L402
	call	__stack_chk_fail@PLT
.L402:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5602:
	.size	_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5603:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movzwl	(%rax), %edx
	movq	-56(%rbp), %rax
	movzwl	(%rax), %eax
	cmpw	%ax, %dx
	jne	.L404
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L403
.L404:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
.L403:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L406
	call	__stack_chk_fail@PLT
.L406:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5603:
	.size	_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal11CmpHelperEQItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal11CmpHelperEQItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5604:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%r8, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	movzwl	(%rax), %edx
	movq	-56(%rbp), %rax
	movzwl	(%rax), %eax
	cmpw	%ax, %dx
	jne	.L408
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing16AssertionSuccessEv@PLT
	jmp	.L407
.L408:
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdi
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	_ZN7testing8internal18CmpHelperEQFailureItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
.L407:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L410
	call	__stack_chk_fail@PLT
.L410:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5604:
	.size	_ZN7testing8internal11CmpHelperEQItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal11CmpHelperEQItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.section	.text._ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,"axG",@progbits,_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,comdat
	.weak	_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_
	.type	_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_, @function
_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_:
.LFB5605:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5605
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -120(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%rdx, -136(%rbp)
	movq	%rcx, -144(%rbp)
	movq	%r8, -152(%rbp)
	movq	%r9, -160(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
.LEHB118:
	call	_ZN7testing16AssertionFailureEv@PLT
.LEHE118:
	leaq	-112(%rbp), %rax
	leaq	.LC47(%rip), %rsi
	movq	%rax, %rdi
.LEHB119:
	call	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC48(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-160(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC49(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-136(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC50(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	-144(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE119:
	leaq	-96(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB120:
	call	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	leaq	.LC51(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	-144(%rbp), %rdx
	movq	-152(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE120:
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB121:
	call	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	movq	%rax, %rdx
	movq	-120(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultC1ERKS0_@PLT
.LEHE121:
	nop
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L416
	jmp	.L420
.L419:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L414
.L418:
	endbr64
	movq	%rax, %rbx
.L414:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L415
.L417:
	endbr64
	movq	%rax, %rbx
.L415:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB122:
	call	_Unwind_Resume@PLT
.LEHE122:
.L420:
	call	__stack_chk_fail@PLT
.L416:
	movq	-120(%rbp), %rax
	addq	$152, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5605:
	.section	.gcc_except_table
.LLSDA5605:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5605-.LLSDACSB5605
.LLSDACSB5605:
	.uleb128 .LEHB118-.LFB5605
	.uleb128 .LEHE118-.LEHB118
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB119-.LFB5605
	.uleb128 .LEHE119-.LEHB119
	.uleb128 .L417-.LFB5605
	.uleb128 0
	.uleb128 .LEHB120-.LFB5605
	.uleb128 .LEHE120-.LEHB120
	.uleb128 .L418-.LFB5605
	.uleb128 0
	.uleb128 .LEHB121-.LFB5605
	.uleb128 .LEHE121-.LEHB121
	.uleb128 .L419-.LFB5605
	.uleb128 0
	.uleb128 .LEHB122-.LFB5605
	.uleb128 .LEHE122-.LEHB122
	.uleb128 0
	.uleb128 0
.LLSDACSE5605:
	.section	.text._ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,"axG",@progbits,_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,comdat
	.size	_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_, .-_ZN7testing8internal18CmpHelperOpFailureIsiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_
	.section	.text._ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,"axG",@progbits,_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,comdat
	.weak	_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_
	.type	_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_, @function
_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_:
.LFB5606:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5606
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -120(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%rdx, -136(%rbp)
	movq	%rcx, -144(%rbp)
	movq	%r8, -152(%rbp)
	movq	%r9, -160(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
.LEHB123:
	call	_ZN7testing16AssertionFailureEv@PLT
.LEHE123:
	leaq	-112(%rbp), %rax
	leaq	.LC47(%rip), %rsi
	movq	%rax, %rdi
.LEHB124:
	call	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC48(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-160(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC49(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	movq	%rax, %rdx
	leaq	-136(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	leaq	.LC50(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	-144(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE124:
	leaq	-96(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB125:
	call	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	leaq	.LC51(%rip), %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	-144(%rbp), %rdx
	movq	-152(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE125:
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB126:
	call	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	movq	%rax, %rdx
	movq	-120(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultC1ERKS0_@PLT
.LEHE126:
	nop
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L426
	jmp	.L430
.L429:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L424
.L428:
	endbr64
	movq	%rax, %rbx
.L424:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L425
.L427:
	endbr64
	movq	%rax, %rbx
.L425:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResultD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB127:
	call	_Unwind_Resume@PLT
.LEHE127:
.L430:
	call	__stack_chk_fail@PLT
.L426:
	movq	-120(%rbp), %rax
	addq	$152, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5606:
	.section	.gcc_except_table
.LLSDA5606:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5606-.LLSDACSB5606
.LLSDACSB5606:
	.uleb128 .LEHB123-.LFB5606
	.uleb128 .LEHE123-.LEHB123
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB124-.LFB5606
	.uleb128 .LEHE124-.LEHB124
	.uleb128 .L427-.LFB5606
	.uleb128 0
	.uleb128 .LEHB125-.LFB5606
	.uleb128 .LEHE125-.LEHB125
	.uleb128 .L428-.LFB5606
	.uleb128 0
	.uleb128 .LEHB126-.LFB5606
	.uleb128 .LEHE126-.LEHB126
	.uleb128 .L429-.LFB5606
	.uleb128 0
	.uleb128 .LEHB127-.LFB5606
	.uleb128 .LEHE127-.LEHB127
	.uleb128 0
	.uleb128 0
.LLSDACSE5606:
	.section	.text._ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,"axG",@progbits,_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_,comdat
	.size	_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_, .-_ZN7testing8internal18CmpHelperOpFailureIiiEENS_15AssertionResultEPKcS4_RKT_RKT0_S4_
	.section	.text._ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,"axG",@progbits,_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,comdat
	.weak	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.type	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, @function
_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_:
.LFB5655:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5655:
	.size	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, .-_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.section	.text._ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv,"axG",@progbits,_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv
	.type	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv, @function
_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv:
.LFB5656:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5656:
	.size	_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv, .-_ZNSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv
	.section	.text._ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,"axG",@progbits,_ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.type	_ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, @function
_ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv:
.LFB5657:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_
	movq	(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5657:
	.size	_ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv, .-_ZNKSt15__uniq_ptr_implINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE6_M_ptrEv
	.section	.text._ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_,"axG",@progbits,_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_,comdat
	.weak	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_
	.type	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_, @function
_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_:
.LFB5765:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5765:
	.size	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_, .-_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_
	.section	.text._ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,"axG",@progbits,_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,comdat
	.weak	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.type	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, @function
_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_:
.LFB5766:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5766:
	.size	_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, .-_ZSt3getILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.section	.text._ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv,"axG",@progbits,_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv
	.type	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv, @function
_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv:
.LFB5767:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5767:
	.size	_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv, .-_ZNSt15__uniq_ptr_implINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EE10_M_deleterEv
	.section	.text._ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_:
.LFB5770:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5770
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB128:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE128:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB129:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE129:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB130:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE130:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L447
	jmp	.L450
.L449:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L446
.L448:
	endbr64
	movq	%rax, %rbx
.L446:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB131:
	call	_Unwind_Resume@PLT
.LEHE131:
.L450:
	call	__stack_chk_fail@PLT
.L447:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5770:
	.section	.gcc_except_table
.LLSDA5770:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5770-.LLSDACSB5770
.LLSDACSB5770:
	.uleb128 .LEHB128-.LFB5770
	.uleb128 .LEHE128-.LEHB128
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB129-.LFB5770
	.uleb128 .LEHE129-.LEHB129
	.uleb128 .L448-.LFB5770
	.uleb128 0
	.uleb128 .LEHB130-.LFB5770
	.uleb128 .LEHE130-.LEHB130
	.uleb128 .L449-.LFB5770
	.uleb128 0
	.uleb128 .LEHB131-.LFB5770
	.uleb128 .LEHE131-.LEHB131
	.uleb128 0
	.uleb128 0
.LLSDACSE5770:
	.section	.text._ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.size	_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureImiEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_:
.LFB5771:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5771
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB132:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE132:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB133:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE133:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB134:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE134:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L455
	jmp	.L458
.L457:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L454
.L456:
	endbr64
	movq	%rax, %rbx
.L454:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB135:
	call	_Unwind_Resume@PLT
.LEHE135:
.L458:
	call	__stack_chk_fail@PLT
.L455:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5771:
	.section	.gcc_except_table
.LLSDA5771:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5771-.LLSDACSB5771
.LLSDACSB5771:
	.uleb128 .LEHB132-.LFB5771
	.uleb128 .LEHE132-.LEHB132
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB133-.LFB5771
	.uleb128 .LEHE133-.LEHB133
	.uleb128 .L456-.LFB5771
	.uleb128 0
	.uleb128 .LEHB134-.LFB5771
	.uleb128 .LEHE134-.LEHB134
	.uleb128 .L457-.LFB5771
	.uleb128 0
	.uleb128 .LEHB135-.LFB5771
	.uleb128 .LEHE135-.LEHB135
	.uleb128 0
	.uleb128 0
.LLSDACSE5771:
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_,comdat
	.size	_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureIPcA4_cEENS_15AssertionResultEPKcS6_RKT_RKT0_
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5772:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5772
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB136:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE136:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB137:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE137:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB138:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE138:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L463
	jmp	.L466
.L465:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L462
.L464:
	endbr64
	movq	%rax, %rbx
.L462:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB139:
	call	_Unwind_Resume@PLT
.LEHE139:
.L466:
	call	__stack_chk_fail@PLT
.L463:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5772:
	.section	.gcc_except_table
.LLSDA5772:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5772-.LLSDACSB5772
.LLSDACSB5772:
	.uleb128 .LEHB136-.LFB5772
	.uleb128 .LEHE136-.LEHB136
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB137-.LFB5772
	.uleb128 .LEHE137-.LEHB137
	.uleb128 .L464-.LFB5772
	.uleb128 0
	.uleb128 .LEHB138-.LFB5772
	.uleb128 .LEHE138-.LEHB138
	.uleb128 .L465-.LFB5772
	.uleb128 0
	.uleb128 .LEHB139-.LFB5772
	.uleb128 .LEHE139-.LEHB139
	.uleb128 0
	.uleb128 0
.LLSDACSE5772:
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_,comdat
	.size	_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureIP4pairA8192_S2_EENS_15AssertionResultEPKcS7_RKT_RKT0_
	.section	.text._ZN7testing15AssertionResultlsIA12_cEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	.type	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_, @function
_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_:
.LFB5773:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5773
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB140:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE140:
	movq	-48(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB141:
	call	_ZN7testing7MessagelsIA12_cEERS0_RKT_
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE
.LEHE141:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L470
	jmp	.L472
.L471:
	endbr64
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB142:
	call	_Unwind_Resume@PLT
.LEHE142:
.L472:
	call	__stack_chk_fail@PLT
.L470:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5773:
	.section	.gcc_except_table
.LLSDA5773:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5773-.LLSDACSB5773
.LLSDACSB5773:
	.uleb128 .LEHB140-.LFB5773
	.uleb128 .LEHE140-.LEHB140
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB141-.LFB5773
	.uleb128 .LEHE141-.LEHB141
	.uleb128 .L471-.LFB5773
	.uleb128 0
	.uleb128 .LEHB142-.LFB5773
	.uleb128 .LEHE142-.LEHB142
	.uleb128 0
	.uleb128 0
.LLSDACSE5773:
	.section	.text._ZN7testing15AssertionResultlsIA12_cEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_,comdat
	.size	_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_, .-_ZN7testing15AssertionResultlsIA12_cEERS0_RKT_
	.section	.text._ZN7testing15AssertionResultlsIPKcEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIPKcEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	.type	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_, @function
_ZN7testing15AssertionResultlsIPKcEERS0_RKT_:
.LFB5774:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5774
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB143:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE143:
	movq	-48(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB144:
	call	_ZN7testing7MessagelsIKcEERS0_RKPT_
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE
.LEHE144:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L476
	jmp	.L478
.L477:
	endbr64
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB145:
	call	_Unwind_Resume@PLT
.LEHE145:
.L478:
	call	__stack_chk_fail@PLT
.L476:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5774:
	.section	.gcc_except_table
.LLSDA5774:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5774-.LLSDACSB5774
.LLSDACSB5774:
	.uleb128 .LEHB143-.LFB5774
	.uleb128 .LEHE143-.LEHB143
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB144-.LFB5774
	.uleb128 .LEHE144-.LEHB144
	.uleb128 .L477-.LFB5774
	.uleb128 0
	.uleb128 .LEHB145-.LFB5774
	.uleb128 .LEHE145-.LEHB145
	.uleb128 0
	.uleb128 0
.LLSDACSE5774:
	.section	.text._ZN7testing15AssertionResultlsIPKcEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIPKcEERS0_RKT_,comdat
	.size	_ZN7testing15AssertionResultlsIPKcEERS0_RKT_, .-_ZN7testing15AssertionResultlsIPKcEERS0_RKT_
	.section	.text._ZN7testing15AssertionResultlsIA3_cEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	.type	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_, @function
_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_:
.LFB5775:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5775
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB146:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE146:
	movq	-48(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB147:
	call	_ZN7testing7MessagelsIA3_cEERS0_RKT_
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE
.LEHE147:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L482
	jmp	.L484
.L483:
	endbr64
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB148:
	call	_Unwind_Resume@PLT
.LEHE148:
.L484:
	call	__stack_chk_fail@PLT
.L482:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5775:
	.section	.gcc_except_table
.LLSDA5775:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5775-.LLSDACSB5775
.LLSDACSB5775:
	.uleb128 .LEHB146-.LFB5775
	.uleb128 .LEHE146-.LEHB146
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB147-.LFB5775
	.uleb128 .LEHE147-.LEHB147
	.uleb128 .L483-.LFB5775
	.uleb128 0
	.uleb128 .LEHB148-.LFB5775
	.uleb128 .LEHE148-.LEHB148
	.uleb128 0
	.uleb128 0
.LLSDACSE5775:
	.section	.text._ZN7testing15AssertionResultlsIA3_cEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_,comdat
	.size	_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_, .-_ZN7testing15AssertionResultlsIA3_cEERS0_RKT_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5776:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L487
	call	__stack_chk_fail@PLT
.L487:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5776:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIPcS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	.type	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_, @function
_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_:
.LFB5777:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5777
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB149:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE149:
	movq	-48(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB150:
	call	_ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE
.LEHE150:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L491
	jmp	.L493
.L492:
	endbr64
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB151:
	call	_Unwind_Resume@PLT
.LEHE151:
.L493:
	call	__stack_chk_fail@PLT
.L491:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5777:
	.section	.gcc_except_table
.LLSDA5777:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5777-.LLSDACSB5777
.LLSDACSB5777:
	.uleb128 .LEHB149-.LFB5777
	.uleb128 .LEHE149-.LEHB149
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB150-.LFB5777
	.uleb128 .LEHE150-.LEHB150
	.uleb128 .L492-.LFB5777
	.uleb128 0
	.uleb128 .LEHB151-.LFB5777
	.uleb128 .LEHE151-.LEHB151
	.uleb128 0
	.uleb128 0
.LLSDACSE5777:
	.section	.text._ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_,comdat
	.size	_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_, .-_ZN7testing15AssertionResultlsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	.section	.text._ZN7testing15AssertionResultlsIA5_cEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_
	.type	_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_, @function
_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_:
.LFB5778:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5778
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB152:
	call	_ZN7testing7MessageC1Ev@PLT
.LEHE152:
	movq	-48(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB153:
	call	_ZN7testing7MessagelsIA5_cEERS0_RKT_
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing15AssertionResult13AppendMessageERKNS_7MessageE
.LEHE153:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L497
	jmp	.L499
.L498:
	endbr64
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing7MessageD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB154:
	call	_Unwind_Resume@PLT
.LEHE154:
.L499:
	call	__stack_chk_fail@PLT
.L497:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5778:
	.section	.gcc_except_table
.LLSDA5778:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5778-.LLSDACSB5778
.LLSDACSB5778:
	.uleb128 .LEHB152-.LFB5778
	.uleb128 .LEHE152-.LEHB152
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB153-.LFB5778
	.uleb128 .LEHE153-.LEHB153
	.uleb128 .L498-.LFB5778
	.uleb128 0
	.uleb128 .LEHB154-.LFB5778
	.uleb128 .LEHE154-.LEHB154
	.uleb128 0
	.uleb128 0
.LLSDACSE5778:
	.section	.text._ZN7testing15AssertionResultlsIA5_cEERS0_RKT_,"axG",@progbits,_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_,comdat
	.size	_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_, .-_ZN7testing15AssertionResultlsIA5_cEERS0_RKT_
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_:
.LFB5779:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5779
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB155:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE155:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB156:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE156:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB157:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE157:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L504
	jmp	.L507
.L506:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L503
.L505:
	endbr64
	movq	%rax, %rbx
.L503:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB158:
	call	_Unwind_Resume@PLT
.LEHE158:
.L507:
	call	__stack_chk_fail@PLT
.L504:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5779:
	.section	.gcc_except_table
.LLSDA5779:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5779-.LLSDACSB5779
.LLSDACSB5779:
	.uleb128 .LEHB155-.LFB5779
	.uleb128 .LEHE155-.LEHB155
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB156-.LFB5779
	.uleb128 .LEHE156-.LEHB156
	.uleb128 .L505-.LFB5779
	.uleb128 0
	.uleb128 .LEHB157-.LFB5779
	.uleb128 .LEHE157-.LEHB157
	.uleb128 .L506-.LFB5779
	.uleb128 0
	.uleb128 .LEHB158-.LFB5779
	.uleb128 .LEHE158-.LEHB158
	.uleb128 0
	.uleb128 0
.LLSDACSE5779:
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_,comdat
	.size	_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureIliEENS_15AssertionResultEPKcS4_RKT_RKT0_
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,comdat
	.weak	_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_:
.LFB5780:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5780
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB159:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE159:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB160:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE160:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB161:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE161:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L512
	jmp	.L515
.L514:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L511
.L513:
	endbr64
	movq	%rax, %rbx
.L511:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB162:
	call	_Unwind_Resume@PLT
.LEHE162:
.L515:
	call	__stack_chk_fail@PLT
.L512:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5780:
	.section	.gcc_except_table
.LLSDA5780:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5780-.LLSDACSB5780
.LLSDACSB5780:
	.uleb128 .LEHB159-.LFB5780
	.uleb128 .LEHE159-.LEHB159
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB160-.LFB5780
	.uleb128 .LEHE160-.LEHB160
	.uleb128 .L513-.LFB5780
	.uleb128 0
	.uleb128 .LEHB161-.LFB5780
	.uleb128 .LEHE161-.LEHB161
	.uleb128 .L514-.LFB5780
	.uleb128 0
	.uleb128 .LEHB162-.LFB5780
	.uleb128 .LEHE162-.LEHB162
	.uleb128 0
	.uleb128 0
.LLSDACSE5780:
	.section	.text._ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,"axG",@progbits,_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_,comdat
	.size	_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureIPvS2_EENS_15AssertionResultEPKcS5_RKT_RKT0_
	.text
	.type	_ZN7testing8internal18CmpHelperEQFailureImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5781:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5781
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB163:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EmEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE163:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB164:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageImN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE164:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB165:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE165:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L520
	jmp	.L523
.L522:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L519
.L521:
	endbr64
	movq	%rax, %rbx
.L519:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB166:
	call	_Unwind_Resume@PLT
.LEHE166:
.L523:
	call	__stack_chk_fail@PLT
.L520:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5781:
	.section	.gcc_except_table
.LLSDA5781:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5781-.LLSDACSB5781
.LLSDACSB5781:
	.uleb128 .LEHB163-.LFB5781
	.uleb128 .LEHE163-.LEHB163
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB164-.LFB5781
	.uleb128 .LEHE164-.LEHB164
	.uleb128 .L521-.LFB5781
	.uleb128 0
	.uleb128 .LEHB165-.LFB5781
	.uleb128 .LEHE165-.LEHB165
	.uleb128 .L522-.LFB5781
	.uleb128 0
	.uleb128 .LEHB166-.LFB5781
	.uleb128 .LEHE166-.LEHB166
	.uleb128 0
	.uleb128 0
.LLSDACSE5781:
	.text
	.size	_ZN7testing8internal18CmpHelperEQFailureImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureImN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5782:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5782
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB167:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE167:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB168:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE168:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB169:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE169:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L528
	jmp	.L531
.L530:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L527
.L529:
	endbr64
	movq	%rax, %rbx
.L527:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB170:
	call	_Unwind_Resume@PLT
.LEHE170:
.L531:
	call	__stack_chk_fail@PLT
.L528:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5782:
	.section	.gcc_except_table
.LLSDA5782:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5782-.LLSDACSB5782
.LLSDACSB5782:
	.uleb128 .LEHB167-.LFB5782
	.uleb128 .LEHE167-.LEHB167
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB168-.LFB5782
	.uleb128 .LEHE168-.LEHB168
	.uleb128 .L529-.LFB5782
	.uleb128 0
	.uleb128 .LEHB169-.LFB5782
	.uleb128 .LEHE169-.LEHB169
	.uleb128 .L530-.LFB5782
	.uleb128 0
	.uleb128 .LEHB170-.LFB5782
	.uleb128 .LEHE170-.LEHB170
	.uleb128 0
	.uleb128 0
.LLSDACSE5782:
	.text
	.size	_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5783:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5783
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB171:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut0_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE171:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB172:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE172:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB173:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE173:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L536
	jmp	.L539
.L538:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L535
.L537:
	endbr64
	movq	%rax, %rbx
.L535:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB174:
	call	_Unwind_Resume@PLT
.LEHE174:
.L539:
	call	__stack_chk_fail@PLT
.L536:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5783:
	.section	.gcc_except_table
.LLSDA5783:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5783-.LLSDACSB5783
.LLSDACSB5783:
	.uleb128 .LEHB171-.LFB5783
	.uleb128 .LEHE171-.LEHB171
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB172-.LFB5783
	.uleb128 .LEHE172-.LEHB172
	.uleb128 .L537-.LFB5783
	.uleb128 0
	.uleb128 .LEHB173-.LFB5783
	.uleb128 .LEHE173-.LEHB173
	.uleb128 .L538-.LFB5783
	.uleb128 0
	.uleb128 .LEHB174-.LFB5783
	.uleb128 .LEHE174-.LEHB174
	.uleb128 0
	.uleb128 0
.LLSDACSE5783:
	.text
	.size	_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureIsN6Memory3._4Ut0_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.type	_ZN7testing8internal18CmpHelperEQFailureItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, @function
_ZN7testing8internal18CmpHelperEQFailureItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_:
.LFB5784:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA5784
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%r8, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	-128(%rbp), %rdx
	movq	-136(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB175:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EtEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE175:
	leaq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB176:
	call	_ZN7testing8internal33FormatForComparisonFailureMessageItN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
.LEHE176:
	movq	-104(%rbp), %rax
	leaq	-64(%rbp), %rdi
	leaq	-96(%rbp), %rcx
	movq	-120(%rbp), %rdx
	movq	-112(%rbp), %rsi
	movl	$0, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB177:
	call	_ZN7testing8internal9EqFailureEPKcS2_RKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESA_b@PLT
.LEHE177:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L544
	jmp	.L547
.L546:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L543
.L545:
	endbr64
	movq	%rax, %rbx
.L543:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB178:
	call	_Unwind_Resume@PLT
.LEHE178:
.L547:
	call	__stack_chk_fail@PLT
.L544:
	movq	-104(%rbp), %rax
	addq	$136, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5784:
	.section	.gcc_except_table
.LLSDA5784:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE5784-.LLSDACSB5784
.LLSDACSB5784:
	.uleb128 .LEHB175-.LFB5784
	.uleb128 .LEHE175-.LEHB175
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB176-.LFB5784
	.uleb128 .LEHE176-.LEHB176
	.uleb128 .L545-.LFB5784
	.uleb128 0
	.uleb128 .LEHB177-.LFB5784
	.uleb128 .LEHE177-.LEHB177
	.uleb128 .L546-.LFB5784
	.uleb128 0
	.uleb128 .LEHB178-.LFB5784
	.uleb128 .LEHE178-.LEHB178
	.uleb128 0
	.uleb128 0
.LLSDACSE5784:
	.text
	.size	_ZN7testing8internal18CmpHelperEQFailureItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_, .-_ZN7testing8internal18CmpHelperEQFailureItN6Memory3._4Ut1_EEENS_15AssertionResultEPKcS7_RKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5785:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L550
	call	__stack_chk_fail@PLT
.L550:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5785:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIsiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5786:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L553
	call	__stack_chk_fail@PLT
.L553:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5786:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIisEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5787:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L556
	call	__stack_chk_fail@PLT
.L556:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5787:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIiiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE
	.type	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE, @function
_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE:
.LFB5816:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5816:
	.size	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE, .-_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE
	.section	.text._ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,"axG",@progbits,_ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,comdat
	.weak	_ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.type	_ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, @function
_ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_:
.LFB5817:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5817:
	.size	_ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, .-_ZSt3getILm1EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.section	.text._ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_,"axG",@progbits,_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_,comdat
	.weak	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_
	.type	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_, @function
_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_:
.LFB5818:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5818:
	.size	_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_, .-_ZSt3getILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKSD_
	.section	.text._ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE
	.type	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE, @function
_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE:
.LFB5902:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5902:
	.size	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE, .-_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE
	.section	.text._ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE
	.type	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE, @function
_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE:
.LFB5903:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5903:
	.size	_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE, .-_ZSt12__get_helperILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERT0_RSt11_Tuple_implIXT_EJS9_DpT1_EE
	.section	.text._ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,"axG",@progbits,_ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_,comdat
	.weak	_ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.type	_ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, @function
_ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_:
.LFB5904:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5904:
	.size	_ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_, .-_ZSt3getILm1EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERSD_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5907:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L571
	call	__stack_chk_fail@PLT
.L571:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5907:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageImiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5908:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L574
	call	__stack_chk_fail@PLT
.L574:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5908:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIimEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5909:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L577
	call	__stack_chk_fail@PLT
.L577:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5909:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIPcA4_cEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5910:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L580
	call	__stack_chk_fail@PLT
.L580:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5910:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIA4_cPcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5911:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L583
	call	__stack_chk_fail@PLT
.L583:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5911:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIP4pairA8192_S2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5912:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L586
	call	__stack_chk_fail@PLT
.L586:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5912:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIA8192_4pairPS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing7MessagelsIA12_cEERS0_RKT_,"axG",@progbits,_ZN7testing7MessagelsIA12_cEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing7MessagelsIA12_cEERS0_RKT_
	.type	_ZN7testing7MessagelsIA12_cEERS0_RKT_, @function
_ZN7testing7MessagelsIA12_cEERS0_RKT_:
.LFB5913:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	leaq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5913:
	.size	_ZN7testing7MessagelsIA12_cEERS0_RKT_, .-_ZN7testing7MessagelsIA12_cEERS0_RKT_
	.section	.text._ZN7testing7MessagelsIA3_cEERS0_RKT_,"axG",@progbits,_ZN7testing7MessagelsIA3_cEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing7MessagelsIA3_cEERS0_RKT_
	.type	_ZN7testing7MessagelsIA3_cEERS0_RKT_, @function
_ZN7testing7MessagelsIA3_cEERS0_RKT_:
.LFB5914:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	leaq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5914:
	.size	_ZN7testing7MessagelsIA3_cEERS0_RKT_, .-_ZN7testing7MessagelsIA3_cEERS0_RKT_
	.section	.text._ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_
	.type	_ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_, @function
_ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_:
.LFB5915:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	leaq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L593
	call	__stack_chk_fail@PLT
.L593:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5915:
	.size	_ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_, .-_ZN7testing8internal19FormatForComparisonIPcS2_E6FormatB5cxx11ES2_
	.section	.text._ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_,"axG",@progbits,_ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	.type	_ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_, @function
_ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_:
.LFB5916:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	leaq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5916:
	.size	_ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_, .-_ZN7testing7MessagelsINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEERS0_RKT_
	.section	.text._ZN7testing7MessagelsIA5_cEERS0_RKT_,"axG",@progbits,_ZN7testing7MessagelsIA5_cEERS0_RKT_,comdat
	.align 2
	.weak	_ZN7testing7MessagelsIA5_cEERS0_RKT_
	.type	_ZN7testing7MessagelsIA5_cEERS0_RKT_, @function
_ZN7testing7MessagelsIA5_cEERS0_RKT_:
.LFB5917:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt10unique_ptrINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEdeEv
	leaq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5917:
	.size	_ZN7testing7MessagelsIA5_cEERS0_RKT_, .-_ZN7testing7MessagelsIA5_cEERS0_RKT_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5918:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L600
	call	__stack_chk_fail@PLT
.L600:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5918:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIliEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5919:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L603
	call	__stack_chk_fail@PLT
.L603:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5919:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIilEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,"axG",@progbits,_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_,comdat
	.weak	_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5920:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L606
	call	__stack_chk_fail@PLT
.L606:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5920:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIPvS2_EENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.text
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageImN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageImN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5921:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonImN6Memory3._4Ut1_EE6FormatERKm
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L609
	call	__stack_chk_fail@PLT
.L609:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5921:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageImN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageImN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EmEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EmEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5922:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EmE6FormatERKS4_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L612
	call	__stack_chk_fail@PLT
.L612:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5922:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EmEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EmEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5923:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut_EE6FormatERKs
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L615
	call	__stack_chk_fail@PLT
.L615:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5923:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5924:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut_EsE6FormatERKS4_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L618
	call	__stack_chk_fail@PLT
.L618:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5924:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5925:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut0_EE6FormatERKs
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L621
	call	__stack_chk_fail@PLT
.L621:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5925:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIsN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut0_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut0_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5926:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut0_EsE6FormatERKS4_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L624
	call	__stack_chk_fail@PLT
.L624:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5926:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut0_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut0_EsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageItN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageItN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5927:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonItN6Memory3._4Ut1_EE6FormatERKt
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L627
	call	__stack_chk_fail@PLT
.L627:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5927:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageItN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageItN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.type	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EtEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, @function
_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EtEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_:
.LFB5928:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EtE6FormatERKS4_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L630
	call	__stack_chk_fail@PLT
.L630:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5928:
	.size	_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EtEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_, .-_ZN7testing8internal33FormatForComparisonFailureMessageIN6Memory3._4Ut1_EtEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_RKT0_
	.section	.text._ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs
	.type	_ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs, @function
_ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs:
.LFB5929:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L633
	call	__stack_chk_fail@PLT
.L633:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5929:
	.size	_ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs, .-_ZN7testing8internal19FormatForComparisonIsiE6FormatB5cxx11ERKs
	.section	.text._ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi
	.type	_ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi, @function
_ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi:
.LFB5930:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L636
	call	__stack_chk_fail@PLT
.L636:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5930:
	.size	_ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi, .-_ZN7testing8internal19FormatForComparisonIisE6FormatB5cxx11ERKi
	.section	.text._ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi
	.type	_ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi, @function
_ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi:
.LFB5931:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L639
	call	__stack_chk_fail@PLT
.L639:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5931:
	.size	_ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi, .-_ZN7testing8internal19FormatForComparisonIiiE6FormatB5cxx11ERKi
	.section	.text._ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_
	.type	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_, @function
_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_:
.LFB5964:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5964:
	.size	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_, .-_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_
	.section	.text._ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE
	.type	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE, @function
_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE:
.LFB5965:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5965:
	.size	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE, .-_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE
	.section	.text._ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE
	.type	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE, @function
_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE:
.LFB5966:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5966:
	.size	_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE, .-_ZSt12__get_helperILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEJSt14default_deleteIS5_EEERKT0_RKSt11_Tuple_implIXT_EJS9_DpT1_EE
	.section	.text._ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_
	.type	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_, @function
_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_:
.LFB6023:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6023:
	.size	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_, .-_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_
	.section	.text._ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_
	.type	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_, @function
_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_:
.LFB6024:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6024:
	.size	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_, .-_ZNSt11_Tuple_implILm0EJPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERS9_
	.section	.text._ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE
	.type	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE, @function
_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE:
.LFB6025:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6025:
	.size	_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE, .-_ZSt12__get_helperILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEJEERT0_RSt11_Tuple_implIXT_EJS8_DpT1_EE
	.section	.text._ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm,"axG",@progbits,_ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm,comdat
	.weak	_ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm
	.type	_ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm, @function
_ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm:
.LFB6027:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L654
	call	__stack_chk_fail@PLT
.L654:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6027:
	.size	_ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm, .-_ZN7testing8internal19FormatForComparisonImiE6FormatB5cxx11ERKm
	.section	.text._ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi
	.type	_ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi, @function
_ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi:
.LFB6028:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L657
	call	__stack_chk_fail@PLT
.L657:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6028:
	.size	_ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi, .-_ZN7testing8internal19FormatForComparisonIimE6FormatB5cxx11ERKi
	.section	.text._ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_
	.type	_ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_, @function
_ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_:
.LFB6029:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	leaq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L660
	call	__stack_chk_fail@PLT
.L660:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6029:
	.size	_ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_, .-_ZN7testing8internal19FormatForComparisonIPcA4_cE6FormatB5cxx11ES2_
	.section	.text._ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc
	.type	_ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc, @function
_ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc:
.LFB6030:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L663
	call	__stack_chk_fail@PLT
.L663:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6030:
	.size	_ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc, .-_ZN7testing8internal19FormatForComparisonIA4_cPcE6FormatB5cxx11EPKc
	.section	.text._ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_
	.type	_ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_, @function
_ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_:
.LFB6031:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L666
	call	__stack_chk_fail@PLT
.L666:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6031:
	.size	_ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_, .-_ZN7testing8internal19FormatForComparisonIP4pairA8192_S2_E6FormatB5cxx11ERKS3_
	.section	.text._ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_
	.type	_ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_, @function
_ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_:
.LFB6032:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	leaq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L669
	call	__stack_chk_fail@PLT
.L669:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6032:
	.size	_ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_, .-_ZN7testing8internal19FormatForComparisonIA8192_4pairPS2_E6FormatB5cxx11EPKS2_
	.section	.text._ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6033:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6033
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB179:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE179:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB180:
	call	_ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE180:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L673
	jmp	.L675
.L674:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB181:
	call	_Unwind_Resume@PLT
.LEHE181:
.L675:
	call	__stack_chk_fail@PLT
.L673:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6033:
	.section	.gcc_except_table
.LLSDA6033:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6033-.LLSDACSB6033
.LLSDACSB6033:
	.uleb128 .LEHB179-.LFB6033
	.uleb128 .LEHE179-.LEHB179
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB180-.LFB6033
	.uleb128 .LEHE180-.LEHB180
	.uleb128 .L674-.LFB6033
	.uleb128 0
	.uleb128 .LEHB181-.LFB6033
	.uleb128 .LEHE181-.LEHB181
	.uleb128 0
	.uleb128 0
.LLSDACSE6033:
	.section	.text._ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl
	.type	_ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl, @function
_ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl:
.LFB6034:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L678
	call	__stack_chk_fail@PLT
.L678:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6034:
	.size	_ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl, .-_ZN7testing8internal19FormatForComparisonIliE6FormatB5cxx11ERKl
	.section	.text._ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi
	.type	_ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi, @function
_ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi:
.LFB6035:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L681
	call	__stack_chk_fail@PLT
.L681:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6035:
	.size	_ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi, .-_ZN7testing8internal19FormatForComparisonIilE6FormatB5cxx11ERKi
	.section	.text._ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_
	.type	_ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_, @function
_ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_:
.LFB6036:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L684
	call	__stack_chk_fail@PLT
.L684:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6036:
	.size	_ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_, .-_ZN7testing8internal19FormatForComparisonIPvS2_E6FormatB5cxx11ERKS2_
	.text
	.type	_ZN7testing8internal19FormatForComparisonImN6Memory3._4Ut1_EE6FormatERKm, @function
_ZN7testing8internal19FormatForComparisonImN6Memory3._4Ut1_EE6FormatERKm:
.LFB6037:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L687
	call	__stack_chk_fail@PLT
.L687:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6037:
	.size	_ZN7testing8internal19FormatForComparisonImN6Memory3._4Ut1_EE6FormatERKm, .-_ZN7testing8internal19FormatForComparisonImN6Memory3._4Ut1_EE6FormatERKm
	.type	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EmE6FormatERKS4_, @function
_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EmE6FormatERKS4_:
.LFB6038:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L690
	call	__stack_chk_fail@PLT
.L690:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6038:
	.size	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EmE6FormatERKS4_, .-_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EmE6FormatERKS4_
	.type	_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut_EE6FormatERKs, @function
_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut_EE6FormatERKs:
.LFB6039:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L693
	call	__stack_chk_fail@PLT
.L693:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6039:
	.size	_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut_EE6FormatERKs, .-_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut_EE6FormatERKs
	.type	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut_EsE6FormatERKS4_, @function
_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut_EsE6FormatERKS4_:
.LFB6040:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L696
	call	__stack_chk_fail@PLT
.L696:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6040:
	.size	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut_EsE6FormatERKS4_, .-_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut_EsE6FormatERKS4_
	.type	_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut0_EE6FormatERKs, @function
_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut0_EE6FormatERKs:
.LFB6041:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L699
	call	__stack_chk_fail@PLT
.L699:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6041:
	.size	_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut0_EE6FormatERKs, .-_ZN7testing8internal19FormatForComparisonIsN6Memory3._4Ut0_EE6FormatERKs
	.type	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut0_EsE6FormatERKS4_, @function
_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut0_EsE6FormatERKS4_:
.LFB6042:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L702
	call	__stack_chk_fail@PLT
.L702:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6042:
	.size	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut0_EsE6FormatERKS4_, .-_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut0_EsE6FormatERKS4_
	.type	_ZN7testing8internal19FormatForComparisonItN6Memory3._4Ut1_EE6FormatERKt, @function
_ZN7testing8internal19FormatForComparisonItN6Memory3._4Ut1_EE6FormatERKt:
.LFB6043:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L705
	call	__stack_chk_fail@PLT
.L705:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6043:
	.size	_ZN7testing8internal19FormatForComparisonItN6Memory3._4Ut1_EE6FormatERKt, .-_ZN7testing8internal19FormatForComparisonItN6Memory3._4Ut1_EE6FormatERKt
	.type	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EtE6FormatERKS4_, @function
_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EtE6FormatERKS4_:
.LFB6044:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L708
	call	__stack_chk_fail@PLT
.L708:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6044:
	.size	_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EtE6FormatERKS4_, .-_ZN7testing8internal19FormatForComparisonIN6Memory3._4Ut1_EtE6FormatERKS4_
	.section	.text._ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6045:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6045
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB182:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE182:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB183:
	call	_ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE183:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L712
	jmp	.L714
.L713:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB184:
	call	_Unwind_Resume@PLT
.LEHE184:
.L714:
	call	__stack_chk_fail@PLT
.L712:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6045:
	.section	.gcc_except_table
.LLSDA6045:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6045-.LLSDACSB6045
.LLSDACSB6045:
	.uleb128 .LEHB182-.LFB6045
	.uleb128 .LEHE182-.LEHB182
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB183-.LFB6045
	.uleb128 .LEHE183-.LEHB183
	.uleb128 .L713-.LFB6045
	.uleb128 0
	.uleb128 .LEHB184-.LFB6045
	.uleb128 .LEHE184-.LEHB184
	.uleb128 0
	.uleb128 0
.LLSDACSE6045:
	.section	.text._ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIsEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6046:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6046
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB185:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE185:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB186:
	call	_ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE186:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L718
	jmp	.L720
.L719:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB187:
	call	_Unwind_Resume@PLT
.LEHE187:
.L720:
	call	__stack_chk_fail@PLT
.L718:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6046:
	.section	.gcc_except_table
.LLSDA6046:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6046-.LLSDACSB6046
.LLSDACSB6046:
	.uleb128 .LEHB185-.LFB6046
	.uleb128 .LEHE185-.LEHB185
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB186-.LFB6046
	.uleb128 .LEHE186-.LEHB186
	.uleb128 .L719-.LFB6046
	.uleb128 0
	.uleb128 .LEHB187-.LFB6046
	.uleb128 .LEHE187-.LEHB187
	.uleb128 0
	.uleb128 0
.LLSDACSE6046:
	.section	.text._ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIiEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_,"axG",@progbits,_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_,comdat
	.weak	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_
	.type	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_, @function
_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_:
.LFB6073:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6073:
	.size	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_, .-_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_,comdat
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_:
.LFB6074:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6074:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_
	.section	.text._ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_
	.type	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_, @function
_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_:
.LFB6075:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6075:
	.size	_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_, .-_ZNSt11_Tuple_implILm0EJPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEESt14default_deleteIS5_EEE7_M_headERKS9_
	.section	.text._ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_,"axG",@progbits,_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_,comdat
	.weak	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_
	.type	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_, @function
_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_:
.LFB6123:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6123:
	.size	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_, .-_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_
	.section	.text._ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_,"axG",@progbits,_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_,comdat
	.weak	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_
	.type	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_, @function
_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_:
.LFB6124:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6124:
	.size	_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_, .-_ZNSt10_Head_baseILm0EPNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0EE7_M_headERS7_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_,comdat
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_:
.LFB6125:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6125:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEEE7_M_headERS8_
	.section	.text._ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6127:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6127
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB188:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE188:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB189:
	call	_ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE189:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L736
	jmp	.L738
.L737:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB190:
	call	_Unwind_Resume@PLT
.LEHE190:
.L738:
	call	__stack_chk_fail@PLT
.L736:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6127:
	.section	.gcc_except_table
.LLSDA6127:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6127-.LLSDACSB6127
.LLSDACSB6127:
	.uleb128 .LEHB188-.LFB6127
	.uleb128 .LEHE188-.LEHB188
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB189-.LFB6127
	.uleb128 .LEHE189-.LEHB189
	.uleb128 .L737-.LFB6127
	.uleb128 0
	.uleb128 .LEHB190-.LFB6127
	.uleb128 .LEHE190-.LEHB190
	.uleb128 0
	.uleb128 0
.LLSDACSE6127:
	.section	.text._ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringImEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_
	.type	_ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_, @function
_ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_:
.LFB6128:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	leaq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIPKvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L741
	call	__stack_chk_fail@PLT
.L741:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6128:
	.size	_ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_, .-_ZN7testing8internal19FormatForComparisonIPKcPcE6FormatB5cxx11ES3_
	.section	.text._ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6129:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6129
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB191:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE191:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB192:
	call	_ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE192:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L745
	jmp	.L747
.L746:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB193:
	call	_Unwind_Resume@PLT
.LEHE193:
.L747:
	call	__stack_chk_fail@PLT
.L745:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6129:
	.section	.gcc_except_table
.LLSDA6129:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6129-.LLSDACSB6129
.LLSDACSB6129:
	.uleb128 .LEHB191-.LFB6129
	.uleb128 .LEHE191-.LEHB191
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB192-.LFB6129
	.uleb128 .LEHE192-.LEHB192
	.uleb128 .L746-.LFB6129
	.uleb128 0
	.uleb128 .LEHB193-.LFB6129
	.uleb128 .LEHE193-.LEHB193
	.uleb128 0
	.uleb128 0
.LLSDACSE6129:
	.section	.text._ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIP4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_,"axG",@progbits,_ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_,comdat
	.weak	_ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_
	.type	_ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_, @function
_ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_:
.LFB6130:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L750
	call	__stack_chk_fail@PLT
.L750:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6130:
	.size	_ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_, .-_ZN7testing8internal19FormatForComparisonIPK4pairPS2_E6FormatB5cxx11ERKS4_
	.section	.text._ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo
	.type	_ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo, @function
_ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo:
.LFB6131:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6131:
	.size	_ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo, .-_ZN7testing8internal21UniversalTersePrinterIPKvE5PrintERKS3_PSo
	.section	.text._ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6132:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6132
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB194:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE194:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB195:
	call	_ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE195:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L755
	jmp	.L757
.L756:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB196:
	call	_Unwind_Resume@PLT
.LEHE196:
.L757:
	call	__stack_chk_fail@PLT
.L755:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6132:
	.section	.gcc_except_table
.LLSDA6132:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6132-.LLSDACSB6132
.LLSDACSB6132:
	.uleb128 .LEHB194-.LFB6132
	.uleb128 .LEHE194-.LEHB194
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB195-.LFB6132
	.uleb128 .LEHE195-.LEHB195
	.uleb128 .L756-.LFB6132
	.uleb128 0
	.uleb128 .LEHB196-.LFB6132
	.uleb128 .LEHE196-.LEHB196
	.uleb128 0
	.uleb128 0
.LLSDACSE6132:
	.section	.text._ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIlEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6133:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6133
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB197:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE197:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB198:
	call	_ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE198:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L761
	jmp	.L763
.L762:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB199:
	call	_Unwind_Resume@PLT
.LEHE199:
.L763:
	call	__stack_chk_fail@PLT
.L761:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6133:
	.section	.gcc_except_table
.LLSDA6133:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6133-.LLSDACSB6133
.LLSDACSB6133:
	.uleb128 .LEHB197-.LFB6133
	.uleb128 .LEHE197-.LEHB197
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB198-.LFB6133
	.uleb128 .LEHE198-.LEHB198
	.uleb128 .L762-.LFB6133
	.uleb128 0
	.uleb128 .LEHB199-.LFB6133
	.uleb128 .LEHE199-.LEHB199
	.uleb128 0
	.uleb128 0
.LLSDACSE6133:
	.section	.text._ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIPvEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.text
	.type	_ZN7testing13PrintToStringIN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6134:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6134
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB200:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE200:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB201:
	call	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE201:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L767
	jmp	.L769
.L768:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB202:
	call	_Unwind_Resume@PLT
.LEHE202:
.L769:
	call	__stack_chk_fail@PLT
.L767:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6134:
	.section	.gcc_except_table
.LLSDA6134:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6134-.LLSDACSB6134
.LLSDACSB6134:
	.uleb128 .LEHB200-.LFB6134
	.uleb128 .LEHE200-.LEHB200
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB201-.LFB6134
	.uleb128 .LEHE201-.LEHB201
	.uleb128 .L768-.LFB6134
	.uleb128 0
	.uleb128 .LEHB202-.LFB6134
	.uleb128 .LEHE202-.LEHB202
	.uleb128 0
	.uleb128 0
.LLSDACSE6134:
	.text
	.size	_ZN7testing13PrintToStringIN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIN6Memory3._4Ut1_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6135:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6135
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB203:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE203:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB204:
	call	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE204:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L773
	jmp	.L775
.L774:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB205:
	call	_Unwind_Resume@PLT
.LEHE205:
.L775:
	call	__stack_chk_fail@PLT
.L773:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6135:
	.section	.gcc_except_table
.LLSDA6135:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6135-.LLSDACSB6135
.LLSDACSB6135:
	.uleb128 .LEHB203-.LFB6135
	.uleb128 .LEHE203-.LEHB203
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB204-.LFB6135
	.uleb128 .LEHE204-.LEHB204
	.uleb128 .L774-.LFB6135
	.uleb128 0
	.uleb128 .LEHB205-.LFB6135
	.uleb128 .LEHE205-.LEHB205
	.uleb128 0
	.uleb128 0
.LLSDACSE6135:
	.text
	.size	_ZN7testing13PrintToStringIN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIN6Memory3._4Ut_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6136:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6136
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB206:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE206:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB207:
	call	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE207:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L779
	jmp	.L781
.L780:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB208:
	call	_Unwind_Resume@PLT
.LEHE208:
.L781:
	call	__stack_chk_fail@PLT
.L779:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6136:
	.section	.gcc_except_table
.LLSDA6136:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6136-.LLSDACSB6136
.LLSDACSB6136:
	.uleb128 .LEHB206-.LFB6136
	.uleb128 .LEHE206-.LEHB206
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB207-.LFB6136
	.uleb128 .LEHE207-.LEHB207
	.uleb128 .L780-.LFB6136
	.uleb128 0
	.uleb128 .LEHB208-.LFB6136
	.uleb128 .LEHE208-.LEHB208
	.uleb128 0
	.uleb128 0
.LLSDACSE6136:
	.text
	.size	_ZN7testing13PrintToStringIN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIN6Memory3._4Ut0_EEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6137:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6137
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB209:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE209:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB210:
	call	_ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE210:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L785
	jmp	.L787
.L786:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB211:
	call	_Unwind_Resume@PLT
.LEHE211:
.L787:
	call	__stack_chk_fail@PLT
.L785:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6137:
	.section	.gcc_except_table
.LLSDA6137:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6137-.LLSDACSB6137
.LLSDACSB6137:
	.uleb128 .LEHB209-.LFB6137
	.uleb128 .LEHE209-.LEHB209
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB210-.LFB6137
	.uleb128 .LEHE210-.LEHB210
	.uleb128 .L786-.LFB6137
	.uleb128 0
	.uleb128 .LEHB211-.LFB6137
	.uleb128 .LEHE211-.LEHB211
	.uleb128 0
	.uleb128 0
.LLSDACSE6137:
	.section	.text._ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringItEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo
	.type	_ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo, @function
_ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo:
.LFB6138:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIsEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6138:
	.size	_ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo, .-_ZN7testing8internal21UniversalTersePrinterIsE5PrintERKsPSo
	.section	.text._ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo
	.type	_ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo, @function
_ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo:
.LFB6139:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIiEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6139:
	.size	_ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo, .-_ZN7testing8internal21UniversalTersePrinterIiE5PrintERKiPSo
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_,comdat
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_:
.LFB6148:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6148:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_, .-_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_
	.section	.text._ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_,"axG",@progbits,_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_,comdat
	.weak	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_
	.type	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_, @function
_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_:
.LFB6149:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6149:
	.size	_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_, .-_ZNSt10_Head_baseILm0EPNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEELb0EE7_M_headERKS7_
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_,comdat
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_:
.LFB6166:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6166:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_, .-_ZNSt10_Head_baseILm1ESt14default_deleteINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEELb1EE7_M_headERS8_
	.section	.text._ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo
	.type	_ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo, @function
_ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo:
.LFB6167:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintImEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6167:
	.size	_ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo, .-_ZN7testing8internal21UniversalTersePrinterImE5PrintERKmPSo
	.section	.text._ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo
	.type	_ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo, @function
_ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo:
.LFB6168:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6168:
	.size	_ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo, .-_ZN7testing8internal21UniversalTersePrinterIP4pairE5PrintERKS3_PSo
	.section	.text._ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB6169:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6169
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$424, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
.LEHB212:
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE212:
	leaq	-416(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB213:
	call	_ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo
	movq	-424(%rbp), %rax
	leaq	-416(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNKSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE213:
	nop
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L801
	jmp	.L803
.L802:
	endbr64
	movq	%rax, %rbx
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB214:
	call	_Unwind_Resume@PLT
.LEHE214:
.L803:
	call	__stack_chk_fail@PLT
.L801:
	movq	-424(%rbp), %rax
	addq	$424, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6169:
	.section	.gcc_except_table
.LLSDA6169:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6169-.LLSDACSB6169
.LLSDACSB6169:
	.uleb128 .LEHB212-.LFB6169
	.uleb128 .LEHE212-.LEHB212
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB213-.LFB6169
	.uleb128 .LEHE213-.LEHB213
	.uleb128 .L802-.LFB6169
	.uleb128 0
	.uleb128 .LEHB214-.LFB6169
	.uleb128 .LEHE214-.LEHB214
	.uleb128 0
	.uleb128 0
.LLSDACSE6169:
	.section	.text._ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_ZN7testing13PrintToStringIPK4pairEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo:
.LFB6170:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6170:
	.size	_ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIPKvEEvRKT_PSo
	.section	.text._ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo
	.type	_ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo, @function
_ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo:
.LFB6171:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIlEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6171:
	.size	_ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo, .-_ZN7testing8internal21UniversalTersePrinterIlE5PrintERKlPSo
	.section	.text._ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo
	.type	_ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo, @function
_ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo:
.LFB6172:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6172:
	.size	_ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo, .-_ZN7testing8internal21UniversalTersePrinterIPvE5PrintERKS2_PSo
	.text
	.type	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo, @function
_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo:
.LFB6173:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut1_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6173:
	.size	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo, .-_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo
	.type	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo, @function
_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo:
.LFB6174:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6174:
	.size	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo, .-_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo
	.type	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo, @function
_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo:
.LFB6175:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut0_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6175:
	.size	_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo, .-_ZN7testing8internal21UniversalTersePrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo
	.section	.text._ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo
	.type	_ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo, @function
_ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo:
.LFB6176:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintItEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6176:
	.size	_ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo, .-_ZN7testing8internal21UniversalTersePrinterItE5PrintERKtPSo
	.section	.text._ZN7testing8internal14UniversalPrintIsEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintIsEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintIsEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIsEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIsEEvRKT_PSo:
.LFB6177:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6177:
	.size	_ZN7testing8internal14UniversalPrintIsEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIsEEvRKT_PSo
	.section	.text._ZN7testing8internal14UniversalPrintIiEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintIiEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintIiEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIiEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIiEEvRKT_PSo:
.LFB6178:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6178:
	.size	_ZN7testing8internal14UniversalPrintIiEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIiEEvRKT_PSo
	.section	.text._ZN7testing8internal14UniversalPrintImEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintImEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintImEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintImEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintImEEvRKT_PSo:
.LFB6189:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6189:
	.size	_ZN7testing8internal14UniversalPrintImEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintImEEvRKT_PSo
	.section	.text._ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo:
.LFB6190:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6190:
	.size	_ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIP4pairEEvRKT_PSo
	.section	.text._ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo,"axG",@progbits,_ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo,comdat
	.weak	_ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo
	.type	_ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo, @function
_ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo:
.LFB6191:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6191:
	.size	_ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo, .-_ZN7testing8internal21UniversalTersePrinterIPK4pairE5PrintERKS4_PSo
	.section	.text._ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo
	.type	_ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo, @function
_ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo:
.LFB6192:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIPKvEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6192:
	.size	_ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo, .-_ZN7testing8internal16UniversalPrinterIPKvE5PrintERKS3_PSo
	.section	.text._ZN7testing8internal14UniversalPrintIlEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintIlEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintIlEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIlEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIlEEvRKT_PSo:
.LFB6193:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6193:
	.size	_ZN7testing8internal14UniversalPrintIlEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIlEEvRKT_PSo
	.section	.text._ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo:
.LFB6194:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6194:
	.size	_ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIPvEEvRKT_PSo
	.text
	.type	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut1_EEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut1_EEEvRKT_PSo:
.LFB6195:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6195:
	.size	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut1_EEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut1_EEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut_EEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut_EEEvRKT_PSo:
.LFB6196:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6196:
	.size	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut_EEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut_EEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut0_EEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut0_EEEvRKT_PSo:
.LFB6197:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6197:
	.size	_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut0_EEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIN6Memory3._4Ut0_EEEvRKT_PSo
	.section	.text._ZN7testing8internal14UniversalPrintItEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintItEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintItEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintItEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintItEEvRKT_PSo:
.LFB6198:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6198:
	.size	_ZN7testing8internal14UniversalPrintItEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintItEEvRKT_PSo
	.section	.text._ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo
	.type	_ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo, @function
_ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo:
.LFB6199:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIsEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6199:
	.size	_ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo, .-_ZN7testing8internal16UniversalPrinterIsE5PrintERKsPSo
	.section	.text._ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo
	.type	_ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo, @function
_ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo:
.LFB6200:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIiEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6200:
	.size	_ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo, .-_ZN7testing8internal16UniversalPrinterIiE5PrintERKiPSo
	.section	.text._ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo
	.type	_ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo, @function
_ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo:
.LFB6208:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToImEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6208:
	.size	_ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo, .-_ZN7testing8internal16UniversalPrinterImE5PrintERKmPSo
	.section	.text._ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo
	.type	_ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo, @function
_ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo:
.LFB6209:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIP4pairEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6209:
	.size	_ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo, .-_ZN7testing8internal16UniversalPrinterIP4pairE5PrintERKS3_PSo
	.section	.text._ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo
	.type	_ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo, @function
_ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo:
.LFB6210:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6210:
	.size	_ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo, .-_ZN7testing8internal14UniversalPrintIPK4pairEEvRKT_PSo
	.section	.text._ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo
	.type	_ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo, @function
_ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo:
.LFB6211:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIlEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6211:
	.size	_ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo, .-_ZN7testing8internal16UniversalPrinterIlE5PrintERKlPSo
	.section	.text._ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo
	.type	_ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo, @function
_ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo:
.LFB6212:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIPvEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6212:
	.size	_ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo, .-_ZN7testing8internal16UniversalPrinterIPvE5PrintERKS2_PSo
	.text
	.type	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo, @function
_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo:
.LFB6213:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIN6Memory3._4Ut1_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6213:
	.size	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo, .-_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut1_EE5PrintERKS4_PSo
	.type	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo, @function
_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo:
.LFB6214:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIN6Memory3._4Ut_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6214:
	.size	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo, .-_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut_EE5PrintERKS4_PSo
	.type	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo, @function
_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo:
.LFB6215:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIN6Memory3._4Ut0_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6215:
	.size	_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo, .-_ZN7testing8internal16UniversalPrinterIN6Memory3._4Ut0_EE5PrintERKS4_PSo
	.section	.text._ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo
	.type	_ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo, @function
_ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo:
.LFB6216:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToItEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6216:
	.size	_ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo, .-_ZN7testing8internal16UniversalPrinterItE5PrintERKtPSo
	.section	.text._ZN7testing8internal7PrintToIsEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToIsEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToIsEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIsEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIsEEvRKT_PSo:
.LFB6217:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L835
	call	__stack_chk_fail@PLT
.L835:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6217:
	.size	_ZN7testing8internal7PrintToIsEEvRKT_PSo, .-_ZN7testing8internal7PrintToIsEEvRKT_PSo
	.section	.text._ZN7testing8internal7PrintToIiEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToIiEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToIiEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIiEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIiEEvRKT_PSo:
.LFB6218:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L837
	call	__stack_chk_fail@PLT
.L837:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6218:
	.size	_ZN7testing8internal7PrintToIiEEvRKT_PSo, .-_ZN7testing8internal7PrintToIiEEvRKT_PSo
	.section	.text._ZN7testing8internal7PrintToImEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToImEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToImEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToImEEvRKT_PSo, @function
_ZN7testing8internal7PrintToImEEvRKT_PSo:
.LFB6221:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L839
	call	__stack_chk_fail@PLT
.L839:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6221:
	.size	_ZN7testing8internal7PrintToImEEvRKT_PSo, .-_ZN7testing8internal7PrintToImEEvRKT_PSo
	.section	.text._ZN7testing8internal7PrintToIP4pairEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToIP4pairEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToIP4pairEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIP4pairEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIP4pairEEvRKT_PSo:
.LFB6222:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L841
	call	__stack_chk_fail@PLT
.L841:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6222:
	.size	_ZN7testing8internal7PrintToIP4pairEEvRKT_PSo, .-_ZN7testing8internal7PrintToIP4pairEEvRKT_PSo
	.section	.text._ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo,"axG",@progbits,_ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo,comdat
	.weak	_ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo
	.type	_ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo, @function
_ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo:
.LFB6223:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6223:
	.size	_ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo, .-_ZN7testing8internal16UniversalPrinterIPK4pairE5PrintERKS4_PSo
	.section	.text._ZN7testing8internal7PrintToIlEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToIlEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToIlEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIlEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIlEEvRKT_PSo:
.LFB6224:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L844
	call	__stack_chk_fail@PLT
.L844:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6224:
	.size	_ZN7testing8internal7PrintToIlEEvRKT_PSo, .-_ZN7testing8internal7PrintToIlEEvRKT_PSo
	.section	.text._ZN7testing8internal7PrintToIPvEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToIPvEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToIPvEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIPvEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIPvEEvRKT_PSo:
.LFB6225:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L846
	call	__stack_chk_fail@PLT
.L846:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6225:
	.size	_ZN7testing8internal7PrintToIPvEEvRKT_PSo, .-_ZN7testing8internal7PrintToIPvEEvRKT_PSo
	.text
	.type	_ZN7testing8internal7PrintToIN6Memory3._4Ut1_EEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIN6Memory3._4Ut1_EEEvRKT_PSo:
.LFB6226:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut1_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L848
	call	__stack_chk_fail@PLT
.L848:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6226:
	.size	_ZN7testing8internal7PrintToIN6Memory3._4Ut1_EEEvRKT_PSo, .-_ZN7testing8internal7PrintToIN6Memory3._4Ut1_EEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIN6Memory3._4Ut_EEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIN6Memory3._4Ut_EEEvRKT_PSo:
.LFB6227:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L850
	call	__stack_chk_fail@PLT
.L850:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6227:
	.size	_ZN7testing8internal7PrintToIN6Memory3._4Ut_EEEvRKT_PSo, .-_ZN7testing8internal7PrintToIN6Memory3._4Ut_EEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIN6Memory3._4Ut0_EEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIN6Memory3._4Ut0_EEEvRKT_PSo:
.LFB6228:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut0_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L852
	call	__stack_chk_fail@PLT
.L852:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6228:
	.size	_ZN7testing8internal7PrintToIN6Memory3._4Ut0_EEEvRKT_PSo, .-_ZN7testing8internal7PrintToIN6Memory3._4Ut0_EEEvRKT_PSo
	.section	.text._ZN7testing8internal7PrintToItEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToItEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToItEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToItEEvRKT_PSo, @function
_ZN7testing8internal7PrintToItEEvRKT_PSo:
.LFB6229:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L854
	call	__stack_chk_fail@PLT
.L854:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6229:
	.size	_ZN7testing8internal7PrintToItEEvRKT_PSo, .-_ZN7testing8internal7PrintToItEEvRKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6230:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6230:
	.size	_ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToIsEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6231:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6231:
	.size	_ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToIiEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.type	_ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6233:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6233:
	.size	_ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToImEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.type	_ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, @function
_ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo:
.LFB6234:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L859
	movq	-16(%rbp), %rax
	leaq	.LC46(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L861
.L859:
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPKv@PLT
.L861:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6234:
	.size	_ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, .-_ZN7testing8internal14DefaultPrintToI4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.section	.text._ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo,"axG",@progbits,_ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo,comdat
	.weak	_ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo
	.type	_ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo, @function
_ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo:
.LFB6235:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L863
	call	__stack_chk_fail@PLT
.L863:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6235:
	.size	_ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo, .-_ZN7testing8internal7PrintToIPK4pairEEvRKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6236:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6236:
	.size	_ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToIlEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, @function
_ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo:
.LFB6237:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L866
	movq	-16(%rbp), %rax
	leaq	.LC46(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L868
.L866:
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPKv@PLT
.L868:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6237:
	.size	_ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, .-_ZN7testing8internal14DefaultPrintToIvEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.text
	.type	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut1_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut1_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6238:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut1_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6238:
	.size	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut1_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut1_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6239:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6239:
	.size	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut0_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut0_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6240:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut0_EEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6240:
	.size	_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut0_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToIN6Memory3._4Ut0_EEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.type	_ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, @function
_ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo:
.LFB6241:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6241:
	.size	_ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo, .-_ZN7testing8internal14DefaultPrintToItEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE3EEERKT_PSo
	.section	.text._ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo,"axG",@progbits,_ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo,comdat
	.weak	_ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo
	.type	_ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo:
.LFB6242:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movzwl	(%rax), %eax
	movswl	%ax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEs@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6242:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToIsEEvRKT_PSo
	.section	.text._ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo,"axG",@progbits,_ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo,comdat
	.weak	_ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo
	.type	_ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo:
.LFB6243:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6243:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToIiEEvRKT_PSo
	.section	.text._ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo,"axG",@progbits,_ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo,comdat
	.weak	_ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo
	.type	_ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo:
.LFB6244:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEm@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6244:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToImEEvRKT_PSo
	.section	.text._ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,"axG",@progbits,_ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo,comdat
	.weak	_ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.type	_ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, @function
_ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo:
.LFB6245:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L877
	movq	-16(%rbp), %rax
	leaq	.LC46(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L879
.L877:
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPKv@PLT
.L879:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6245:
	.size	_ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo, .-_ZN7testing8internal14DefaultPrintToIK4pairEEvNS0_15WrapPrinterTypeILNS0_18DefaultPrinterTypeE1EEEPT_PSo
	.section	.text._ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo,"axG",@progbits,_ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo,comdat
	.weak	_ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo
	.type	_ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo:
.LFB6246:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEl@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6246:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToIlEEvRKT_PSo
	.text
	.type	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut1_EEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut1_EEEvRKT_PSo:
.LFB6247:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut1_EEERSt13basic_ostreamIT_T0_ESB_RKT1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6247:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut1_EEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut1_EEEvRKT_PSo
	.type	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut_EEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut_EEEvRKT_PSo:
.LFB6248:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut_EEERSt13basic_ostreamIT_T0_ESB_RKT1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6248:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut_EEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut_EEEvRKT_PSo
	.type	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut0_EEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut0_EEEvRKT_PSo:
.LFB6249:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut0_EEERSt13basic_ostreamIT_T0_ESB_RKT1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6249:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut0_EEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToIN6Memory3._4Ut0_EEEvRKT_PSo
	.section	.text._ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo,"axG",@progbits,_ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo,comdat
	.weak	_ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo
	.type	_ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo, @function
_ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo:
.LFB6250:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6250:
	.size	_ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo, .-_ZN16testing_internal26DefaultPrintNonContainerToItEEvRKT_PSo
	.text
	.type	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut1_EEERSt13basic_ostreamIT_T0_ESB_RKT1_, @function
_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut1_EEERSt13basic_ostreamIT_T0_ESB_RKT1_:
.LFB6253:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut1_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6253:
	.size	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut1_EEERSt13basic_ostreamIT_T0_ESB_RKT1_, .-_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut1_EEERSt13basic_ostreamIT_T0_ESB_RKT1_
	.type	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut_EEERSt13basic_ostreamIT_T0_ESB_RKT1_, @function
_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut_EEERSt13basic_ostreamIT_T0_ESB_RKT1_:
.LFB6254:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6254:
	.size	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut_EEERSt13basic_ostreamIT_T0_ESB_RKT1_, .-_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut_EEERSt13basic_ostreamIT_T0_ESB_RKT1_
	.type	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut0_EEERSt13basic_ostreamIT_T0_ESB_RKT1_, @function
_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut0_EEERSt13basic_ostreamIT_T0_ESB_RKT1_:
.LFB6255:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut0_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6255:
	.size	_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut0_EEERSt13basic_ostreamIT_T0_ESB_RKT1_, .-_ZN7testing9internal2lsIcSt11char_traitsIcEN6Memory3._4Ut0_EEERSt13basic_ostreamIT_T0_ESB_RKT1_
	.section	.text._ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_,"axG",@progbits,_ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_,comdat
	.weak	_ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_
	.type	_ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_, @function
_ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_:
.LFB6256:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6256:
	.size	_ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_, .-_ZN7testing9internal2lsIcSt11char_traitsIcEtEERSt13basic_ostreamIT_T0_ES8_RKT1_
	.text
	.type	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut1_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo, @function
_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut1_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo:
.LFB6257:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEx@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6257:
	.size	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut1_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo, .-_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut1_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo
	.type	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo, @function
_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo:
.LFB6258:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	movswq	%ax, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEx@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6258:
	.size	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo, .-_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo
	.type	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut0_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo, @function
_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut0_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo:
.LFB6259:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	movswq	%ax, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEx@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6259:
	.size	_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut0_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo, .-_ZN7testing9internal220TypeWithoutFormatterIN6Memory3._4Ut0_ELNS0_8TypeKindE1EE10PrintValueERKS4_PSo
	.section	.text._ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo,"axG",@progbits,_ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo,comdat
	.weak	_ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo
	.type	_ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo, @function
_ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo:
.LFB6260:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEx@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6260:
	.size	_ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo, .-_ZN7testing9internal220TypeWithoutFormatterItLNS0_8TypeKindE1EE10PrintValueERKtPSo
	.weak	_ZTV20Memory_overflow_Test
	.section	.data.rel.ro._ZTV20Memory_overflow_Test,"awG",@progbits,_ZTV20Memory_overflow_Test,comdat
	.align 8
	.type	_ZTV20Memory_overflow_Test, @object
	.size	_ZTV20Memory_overflow_Test, 64
_ZTV20Memory_overflow_Test:
	.quad	0
	.quad	_ZTI20Memory_overflow_Test
	.quad	_ZN20Memory_overflow_TestD1Ev
	.quad	_ZN20Memory_overflow_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN20Memory_overflow_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN20Memory_overflow_TestD2Ev,"axG",@progbits,_ZN20Memory_overflow_TestD5Ev,comdat
	.align 2
	.weak	_ZN20Memory_overflow_TestD2Ev
	.type	_ZN20Memory_overflow_TestD2Ev, @function
_ZN20Memory_overflow_TestD2Ev:
.LFB6283:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV20Memory_overflow_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6283:
	.size	_ZN20Memory_overflow_TestD2Ev, .-_ZN20Memory_overflow_TestD2Ev
	.weak	_ZN20Memory_overflow_TestD1Ev
	.set	_ZN20Memory_overflow_TestD1Ev,_ZN20Memory_overflow_TestD2Ev
	.section	.text._ZN20Memory_overflow_TestD0Ev,"axG",@progbits,_ZN20Memory_overflow_TestD5Ev,comdat
	.align 2
	.weak	_ZN20Memory_overflow_TestD0Ev
	.type	_ZN20Memory_overflow_TestD0Ev, @function
_ZN20Memory_overflow_TestD0Ev:
.LFB6285:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN20Memory_overflow_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6285:
	.size	_ZN20Memory_overflow_TestD0Ev, .-_ZN20Memory_overflow_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED2Ev:
.LFB6287:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6287:
	.size	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED1Ev,_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED0Ev:
.LFB6289:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6289:
	.size	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestED0Ev
	.weak	_ZTV23Memory_minimalSize_Test
	.section	.data.rel.ro._ZTV23Memory_minimalSize_Test,"awG",@progbits,_ZTV23Memory_minimalSize_Test,comdat
	.align 8
	.type	_ZTV23Memory_minimalSize_Test, @object
	.size	_ZTV23Memory_minimalSize_Test, 64
_ZTV23Memory_minimalSize_Test:
	.quad	0
	.quad	_ZTI23Memory_minimalSize_Test
	.quad	_ZN23Memory_minimalSize_TestD1Ev
	.quad	_ZN23Memory_minimalSize_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN23Memory_minimalSize_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN23Memory_minimalSize_TestD2Ev,"axG",@progbits,_ZN23Memory_minimalSize_TestD5Ev,comdat
	.align 2
	.weak	_ZN23Memory_minimalSize_TestD2Ev
	.type	_ZN23Memory_minimalSize_TestD2Ev, @function
_ZN23Memory_minimalSize_TestD2Ev:
.LFB6291:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV23Memory_minimalSize_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6291:
	.size	_ZN23Memory_minimalSize_TestD2Ev, .-_ZN23Memory_minimalSize_TestD2Ev
	.weak	_ZN23Memory_minimalSize_TestD1Ev
	.set	_ZN23Memory_minimalSize_TestD1Ev,_ZN23Memory_minimalSize_TestD2Ev
	.section	.text._ZN23Memory_minimalSize_TestD0Ev,"axG",@progbits,_ZN23Memory_minimalSize_TestD5Ev,comdat
	.align 2
	.weak	_ZN23Memory_minimalSize_TestD0Ev
	.type	_ZN23Memory_minimalSize_TestD0Ev, @function
_ZN23Memory_minimalSize_TestD0Ev:
.LFB6293:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN23Memory_minimalSize_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6293:
	.size	_ZN23Memory_minimalSize_TestD0Ev, .-_ZN23Memory_minimalSize_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED2Ev:
.LFB6295:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6295:
	.size	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED1Ev,_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED0Ev:
.LFB6297:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6297:
	.size	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestED0Ev
	.weak	_ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test
	.section	.data.rel.ro._ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test,"awG",@progbits,_ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test,comdat
	.align 8
	.type	_ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test, @object
	.size	_ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test, 64
_ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test:
	.quad	0
	.quad	_ZTI44Memory_ConversionToIntDoesNotBreakEnums_Test
	.quad	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD1Ev
	.quad	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN44Memory_ConversionToIntDoesNotBreakEnums_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD2Ev,"axG",@progbits,_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD5Ev,comdat
	.align 2
	.weak	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD2Ev
	.type	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD2Ev, @function
_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD2Ev:
.LFB6299:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV44Memory_ConversionToIntDoesNotBreakEnums_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6299:
	.size	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD2Ev, .-_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD2Ev
	.weak	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD1Ev
	.set	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD1Ev,_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD2Ev
	.section	.text._ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD0Ev,"axG",@progbits,_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD5Ev,comdat
	.align 2
	.weak	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD0Ev
	.type	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD0Ev, @function
_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD0Ev:
.LFB6301:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6301:
	.size	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD0Ev, .-_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED2Ev:
.LFB6303:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6303:
	.size	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED1Ev,_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED0Ev:
.LFB6305:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6305:
	.size	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestED0Ev
	.weak	_ZTV21Memory_totalSize_Test
	.section	.data.rel.ro._ZTV21Memory_totalSize_Test,"awG",@progbits,_ZTV21Memory_totalSize_Test,comdat
	.align 8
	.type	_ZTV21Memory_totalSize_Test, @object
	.size	_ZTV21Memory_totalSize_Test, 64
_ZTV21Memory_totalSize_Test:
	.quad	0
	.quad	_ZTI21Memory_totalSize_Test
	.quad	_ZN21Memory_totalSize_TestD1Ev
	.quad	_ZN21Memory_totalSize_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN21Memory_totalSize_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN21Memory_totalSize_TestD2Ev,"axG",@progbits,_ZN21Memory_totalSize_TestD5Ev,comdat
	.align 2
	.weak	_ZN21Memory_totalSize_TestD2Ev
	.type	_ZN21Memory_totalSize_TestD2Ev, @function
_ZN21Memory_totalSize_TestD2Ev:
.LFB6307:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV21Memory_totalSize_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6307:
	.size	_ZN21Memory_totalSize_TestD2Ev, .-_ZN21Memory_totalSize_TestD2Ev
	.weak	_ZN21Memory_totalSize_TestD1Ev
	.set	_ZN21Memory_totalSize_TestD1Ev,_ZN21Memory_totalSize_TestD2Ev
	.section	.text._ZN21Memory_totalSize_TestD0Ev,"axG",@progbits,_ZN21Memory_totalSize_TestD5Ev,comdat
	.align 2
	.weak	_ZN21Memory_totalSize_TestD0Ev
	.type	_ZN21Memory_totalSize_TestD0Ev, @function
_ZN21Memory_totalSize_TestD0Ev:
.LFB6309:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN21Memory_totalSize_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6309:
	.size	_ZN21Memory_totalSize_TestD0Ev, .-_ZN21Memory_totalSize_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED2Ev:
.LFB6311:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6311:
	.size	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED1Ev,_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED0Ev:
.LFB6313:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6313:
	.size	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestED0Ev
	.weak	_ZTV34Memory_twoArrayAreConsecutive_Test
	.section	.data.rel.ro._ZTV34Memory_twoArrayAreConsecutive_Test,"awG",@progbits,_ZTV34Memory_twoArrayAreConsecutive_Test,comdat
	.align 8
	.type	_ZTV34Memory_twoArrayAreConsecutive_Test, @object
	.size	_ZTV34Memory_twoArrayAreConsecutive_Test, 64
_ZTV34Memory_twoArrayAreConsecutive_Test:
	.quad	0
	.quad	_ZTI34Memory_twoArrayAreConsecutive_Test
	.quad	_ZN34Memory_twoArrayAreConsecutive_TestD1Ev
	.quad	_ZN34Memory_twoArrayAreConsecutive_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN34Memory_twoArrayAreConsecutive_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN34Memory_twoArrayAreConsecutive_TestD2Ev,"axG",@progbits,_ZN34Memory_twoArrayAreConsecutive_TestD5Ev,comdat
	.align 2
	.weak	_ZN34Memory_twoArrayAreConsecutive_TestD2Ev
	.type	_ZN34Memory_twoArrayAreConsecutive_TestD2Ev, @function
_ZN34Memory_twoArrayAreConsecutive_TestD2Ev:
.LFB6315:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV34Memory_twoArrayAreConsecutive_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6315:
	.size	_ZN34Memory_twoArrayAreConsecutive_TestD2Ev, .-_ZN34Memory_twoArrayAreConsecutive_TestD2Ev
	.weak	_ZN34Memory_twoArrayAreConsecutive_TestD1Ev
	.set	_ZN34Memory_twoArrayAreConsecutive_TestD1Ev,_ZN34Memory_twoArrayAreConsecutive_TestD2Ev
	.section	.text._ZN34Memory_twoArrayAreConsecutive_TestD0Ev,"axG",@progbits,_ZN34Memory_twoArrayAreConsecutive_TestD5Ev,comdat
	.align 2
	.weak	_ZN34Memory_twoArrayAreConsecutive_TestD0Ev
	.type	_ZN34Memory_twoArrayAreConsecutive_TestD0Ev, @function
_ZN34Memory_twoArrayAreConsecutive_TestD0Ev:
.LFB6317:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN34Memory_twoArrayAreConsecutive_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6317:
	.size	_ZN34Memory_twoArrayAreConsecutive_TestD0Ev, .-_ZN34Memory_twoArrayAreConsecutive_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED2Ev:
.LFB6319:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6319:
	.size	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED1Ev,_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED0Ev:
.LFB6321:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6321:
	.size	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestED0Ev
	.weak	_ZTV31Memory_innerAndOuterArrays_Test
	.section	.data.rel.ro._ZTV31Memory_innerAndOuterArrays_Test,"awG",@progbits,_ZTV31Memory_innerAndOuterArrays_Test,comdat
	.align 8
	.type	_ZTV31Memory_innerAndOuterArrays_Test, @object
	.size	_ZTV31Memory_innerAndOuterArrays_Test, 64
_ZTV31Memory_innerAndOuterArrays_Test:
	.quad	0
	.quad	_ZTI31Memory_innerAndOuterArrays_Test
	.quad	_ZN31Memory_innerAndOuterArrays_TestD1Ev
	.quad	_ZN31Memory_innerAndOuterArrays_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN31Memory_innerAndOuterArrays_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN31Memory_innerAndOuterArrays_TestD2Ev,"axG",@progbits,_ZN31Memory_innerAndOuterArrays_TestD5Ev,comdat
	.align 2
	.weak	_ZN31Memory_innerAndOuterArrays_TestD2Ev
	.type	_ZN31Memory_innerAndOuterArrays_TestD2Ev, @function
_ZN31Memory_innerAndOuterArrays_TestD2Ev:
.LFB6323:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV31Memory_innerAndOuterArrays_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6323:
	.size	_ZN31Memory_innerAndOuterArrays_TestD2Ev, .-_ZN31Memory_innerAndOuterArrays_TestD2Ev
	.weak	_ZN31Memory_innerAndOuterArrays_TestD1Ev
	.set	_ZN31Memory_innerAndOuterArrays_TestD1Ev,_ZN31Memory_innerAndOuterArrays_TestD2Ev
	.section	.text._ZN31Memory_innerAndOuterArrays_TestD0Ev,"axG",@progbits,_ZN31Memory_innerAndOuterArrays_TestD5Ev,comdat
	.align 2
	.weak	_ZN31Memory_innerAndOuterArrays_TestD0Ev
	.type	_ZN31Memory_innerAndOuterArrays_TestD0Ev, @function
_ZN31Memory_innerAndOuterArrays_TestD0Ev:
.LFB6325:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN31Memory_innerAndOuterArrays_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6325:
	.size	_ZN31Memory_innerAndOuterArrays_TestD0Ev, .-_ZN31Memory_innerAndOuterArrays_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED2Ev:
.LFB6327:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6327:
	.size	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED1Ev,_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED0Ev:
.LFB6329:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6329:
	.size	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestED0Ev
	.weak	_ZTV15Memory_NIL_Test
	.section	.data.rel.ro._ZTV15Memory_NIL_Test,"awG",@progbits,_ZTV15Memory_NIL_Test,comdat
	.align 8
	.type	_ZTV15Memory_NIL_Test, @object
	.size	_ZTV15Memory_NIL_Test, 64
_ZTV15Memory_NIL_Test:
	.quad	0
	.quad	_ZTI15Memory_NIL_Test
	.quad	_ZN15Memory_NIL_TestD1Ev
	.quad	_ZN15Memory_NIL_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN15Memory_NIL_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN15Memory_NIL_TestD2Ev,"axG",@progbits,_ZN15Memory_NIL_TestD5Ev,comdat
	.align 2
	.weak	_ZN15Memory_NIL_TestD2Ev
	.type	_ZN15Memory_NIL_TestD2Ev, @function
_ZN15Memory_NIL_TestD2Ev:
.LFB6331:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV15Memory_NIL_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6331:
	.size	_ZN15Memory_NIL_TestD2Ev, .-_ZN15Memory_NIL_TestD2Ev
	.weak	_ZN15Memory_NIL_TestD1Ev
	.set	_ZN15Memory_NIL_TestD1Ev,_ZN15Memory_NIL_TestD2Ev
	.section	.text._ZN15Memory_NIL_TestD0Ev,"axG",@progbits,_ZN15Memory_NIL_TestD5Ev,comdat
	.align 2
	.weak	_ZN15Memory_NIL_TestD0Ev
	.type	_ZN15Memory_NIL_TestD0Ev, @function
_ZN15Memory_NIL_TestD0Ev:
.LFB6333:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN15Memory_NIL_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6333:
	.size	_ZN15Memory_NIL_TestD0Ev, .-_ZN15Memory_NIL_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED2Ev:
.LFB6335:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6335:
	.size	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED1Ev,_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED0Ev:
.LFB6337:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6337:
	.size	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestED0Ev
	.weak	_ZTV25Memory_PrimitiveSizs_Test
	.section	.data.rel.ro._ZTV25Memory_PrimitiveSizs_Test,"awG",@progbits,_ZTV25Memory_PrimitiveSizs_Test,comdat
	.align 8
	.type	_ZTV25Memory_PrimitiveSizs_Test, @object
	.size	_ZTV25Memory_PrimitiveSizs_Test, 64
_ZTV25Memory_PrimitiveSizs_Test:
	.quad	0
	.quad	_ZTI25Memory_PrimitiveSizs_Test
	.quad	_ZN25Memory_PrimitiveSizs_TestD1Ev
	.quad	_ZN25Memory_PrimitiveSizs_TestD0Ev
	.quad	_ZN7testing4Test5SetUpEv
	.quad	_ZN7testing4Test8TearDownEv
	.quad	_ZN25Memory_PrimitiveSizs_Test8TestBodyEv
	.quad	_ZN7testing4Test5SetupEv
	.section	.text._ZN25Memory_PrimitiveSizs_TestD2Ev,"axG",@progbits,_ZN25Memory_PrimitiveSizs_TestD5Ev,comdat
	.align 2
	.weak	_ZN25Memory_PrimitiveSizs_TestD2Ev
	.type	_ZN25Memory_PrimitiveSizs_TestD2Ev, @function
_ZN25Memory_PrimitiveSizs_TestD2Ev:
.LFB6339:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV25Memory_PrimitiveSizs_Test(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing4TestD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6339:
	.size	_ZN25Memory_PrimitiveSizs_TestD2Ev, .-_ZN25Memory_PrimitiveSizs_TestD2Ev
	.weak	_ZN25Memory_PrimitiveSizs_TestD1Ev
	.set	_ZN25Memory_PrimitiveSizs_TestD1Ev,_ZN25Memory_PrimitiveSizs_TestD2Ev
	.section	.text._ZN25Memory_PrimitiveSizs_TestD0Ev,"axG",@progbits,_ZN25Memory_PrimitiveSizs_TestD5Ev,comdat
	.align 2
	.weak	_ZN25Memory_PrimitiveSizs_TestD0Ev
	.type	_ZN25Memory_PrimitiveSizs_TestD0Ev, @function
_ZN25Memory_PrimitiveSizs_TestD0Ev:
.LFB6341:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN25Memory_PrimitiveSizs_TestD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6341:
	.size	_ZN25Memory_PrimitiveSizs_TestD0Ev, .-_ZN25Memory_PrimitiveSizs_TestD0Ev
	.weak	_ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE
	.section	.data.rel.ro.local._ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE, @object
	.size	_ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE, 40
_ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE
	.quad	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED1Ev
	.quad	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED0Ev
	.quad	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED2Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED2Ev
	.type	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED2Ev, @function
_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED2Ev:
.LFB6343:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryBaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6343:
	.size	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED2Ev, .-_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED2Ev
	.weak	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED1Ev
	.set	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED1Ev,_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED2Ev
	.section	.text._ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED0Ev,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED5Ev,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED0Ev
	.type	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED0Ev, @function
_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED0Ev:
.LFB6345:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6345:
	.size	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED0Ev, .-_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestED0Ev
	.weak	_ZTVN7testing8internal15TestFactoryBaseE
	.section	.data.rel.ro._ZTVN7testing8internal15TestFactoryBaseE,"awG",@progbits,_ZTVN7testing8internal15TestFactoryBaseE,comdat
	.align 8
	.type	_ZTVN7testing8internal15TestFactoryBaseE, @object
	.size	_ZTVN7testing8internal15TestFactoryBaseE, 40
_ZTVN7testing8internal15TestFactoryBaseE:
	.quad	0
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.quad	0
	.quad	0
	.quad	__cxa_pure_virtual
	.weak	_ZTIN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE, 61
_ZTSN7testing8internal15TestFactoryImplI20Memory_overflow_TestEE:
	.string	"N7testing8internal15TestFactoryImplI20Memory_overflow_TestEE"
	.weak	_ZTI20Memory_overflow_Test
	.section	.data.rel.ro._ZTI20Memory_overflow_Test,"awG",@progbits,_ZTI20Memory_overflow_Test,comdat
	.align 8
	.type	_ZTI20Memory_overflow_Test, @object
	.size	_ZTI20Memory_overflow_Test, 24
_ZTI20Memory_overflow_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS20Memory_overflow_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS20Memory_overflow_Test
	.section	.rodata._ZTS20Memory_overflow_Test,"aG",@progbits,_ZTS20Memory_overflow_Test,comdat
	.align 16
	.type	_ZTS20Memory_overflow_Test, @object
	.size	_ZTS20Memory_overflow_Test, 23
_ZTS20Memory_overflow_Test:
	.string	"20Memory_overflow_Test"
	.weak	_ZTIN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE, 64
_ZTSN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE:
	.string	"N7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEE"
	.weak	_ZTI23Memory_minimalSize_Test
	.section	.data.rel.ro._ZTI23Memory_minimalSize_Test,"awG",@progbits,_ZTI23Memory_minimalSize_Test,comdat
	.align 8
	.type	_ZTI23Memory_minimalSize_Test, @object
	.size	_ZTI23Memory_minimalSize_Test, 24
_ZTI23Memory_minimalSize_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS23Memory_minimalSize_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS23Memory_minimalSize_Test
	.section	.rodata._ZTS23Memory_minimalSize_Test,"aG",@progbits,_ZTS23Memory_minimalSize_Test,comdat
	.align 16
	.type	_ZTS23Memory_minimalSize_Test, @object
	.size	_ZTS23Memory_minimalSize_Test, 26
_ZTS23Memory_minimalSize_Test:
	.string	"23Memory_minimalSize_Test"
	.weak	_ZTIN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE, 85
_ZTSN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE:
	.string	"N7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEE"
	.weak	_ZTI44Memory_ConversionToIntDoesNotBreakEnums_Test
	.section	.data.rel.ro._ZTI44Memory_ConversionToIntDoesNotBreakEnums_Test,"awG",@progbits,_ZTI44Memory_ConversionToIntDoesNotBreakEnums_Test,comdat
	.align 8
	.type	_ZTI44Memory_ConversionToIntDoesNotBreakEnums_Test, @object
	.size	_ZTI44Memory_ConversionToIntDoesNotBreakEnums_Test, 24
_ZTI44Memory_ConversionToIntDoesNotBreakEnums_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS44Memory_ConversionToIntDoesNotBreakEnums_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS44Memory_ConversionToIntDoesNotBreakEnums_Test
	.section	.rodata._ZTS44Memory_ConversionToIntDoesNotBreakEnums_Test,"aG",@progbits,_ZTS44Memory_ConversionToIntDoesNotBreakEnums_Test,comdat
	.align 32
	.type	_ZTS44Memory_ConversionToIntDoesNotBreakEnums_Test, @object
	.size	_ZTS44Memory_ConversionToIntDoesNotBreakEnums_Test, 47
_ZTS44Memory_ConversionToIntDoesNotBreakEnums_Test:
	.string	"44Memory_ConversionToIntDoesNotBreakEnums_Test"
	.weak	_ZTIN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE, 62
_ZTSN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE:
	.string	"N7testing8internal15TestFactoryImplI21Memory_totalSize_TestEE"
	.weak	_ZTI21Memory_totalSize_Test
	.section	.data.rel.ro._ZTI21Memory_totalSize_Test,"awG",@progbits,_ZTI21Memory_totalSize_Test,comdat
	.align 8
	.type	_ZTI21Memory_totalSize_Test, @object
	.size	_ZTI21Memory_totalSize_Test, 24
_ZTI21Memory_totalSize_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS21Memory_totalSize_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS21Memory_totalSize_Test
	.section	.rodata._ZTS21Memory_totalSize_Test,"aG",@progbits,_ZTS21Memory_totalSize_Test,comdat
	.align 16
	.type	_ZTS21Memory_totalSize_Test, @object
	.size	_ZTS21Memory_totalSize_Test, 24
_ZTS21Memory_totalSize_Test:
	.string	"21Memory_totalSize_Test"
	.weak	_ZTIN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE, 75
_ZTSN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE:
	.string	"N7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEE"
	.weak	_ZTI34Memory_twoArrayAreConsecutive_Test
	.section	.data.rel.ro._ZTI34Memory_twoArrayAreConsecutive_Test,"awG",@progbits,_ZTI34Memory_twoArrayAreConsecutive_Test,comdat
	.align 8
	.type	_ZTI34Memory_twoArrayAreConsecutive_Test, @object
	.size	_ZTI34Memory_twoArrayAreConsecutive_Test, 24
_ZTI34Memory_twoArrayAreConsecutive_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS34Memory_twoArrayAreConsecutive_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS34Memory_twoArrayAreConsecutive_Test
	.section	.rodata._ZTS34Memory_twoArrayAreConsecutive_Test,"aG",@progbits,_ZTS34Memory_twoArrayAreConsecutive_Test,comdat
	.align 32
	.type	_ZTS34Memory_twoArrayAreConsecutive_Test, @object
	.size	_ZTS34Memory_twoArrayAreConsecutive_Test, 37
_ZTS34Memory_twoArrayAreConsecutive_Test:
	.string	"34Memory_twoArrayAreConsecutive_Test"
	.weak	_ZTIN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE, 72
_ZTSN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE:
	.string	"N7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEE"
	.weak	_ZTI31Memory_innerAndOuterArrays_Test
	.section	.data.rel.ro._ZTI31Memory_innerAndOuterArrays_Test,"awG",@progbits,_ZTI31Memory_innerAndOuterArrays_Test,comdat
	.align 8
	.type	_ZTI31Memory_innerAndOuterArrays_Test, @object
	.size	_ZTI31Memory_innerAndOuterArrays_Test, 24
_ZTI31Memory_innerAndOuterArrays_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS31Memory_innerAndOuterArrays_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS31Memory_innerAndOuterArrays_Test
	.section	.rodata._ZTS31Memory_innerAndOuterArrays_Test,"aG",@progbits,_ZTS31Memory_innerAndOuterArrays_Test,comdat
	.align 32
	.type	_ZTS31Memory_innerAndOuterArrays_Test, @object
	.size	_ZTS31Memory_innerAndOuterArrays_Test, 34
_ZTS31Memory_innerAndOuterArrays_Test:
	.string	"31Memory_innerAndOuterArrays_Test"
	.weak	_ZTIN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE, 56
_ZTSN7testing8internal15TestFactoryImplI15Memory_NIL_TestEE:
	.string	"N7testing8internal15TestFactoryImplI15Memory_NIL_TestEE"
	.weak	_ZTI15Memory_NIL_Test
	.section	.data.rel.ro._ZTI15Memory_NIL_Test,"awG",@progbits,_ZTI15Memory_NIL_Test,comdat
	.align 8
	.type	_ZTI15Memory_NIL_Test, @object
	.size	_ZTI15Memory_NIL_Test, 24
_ZTI15Memory_NIL_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS15Memory_NIL_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS15Memory_NIL_Test
	.section	.rodata._ZTS15Memory_NIL_Test,"aG",@progbits,_ZTS15Memory_NIL_Test,comdat
	.align 16
	.type	_ZTS15Memory_NIL_Test, @object
	.size	_ZTS15Memory_NIL_Test, 18
_ZTS15Memory_NIL_Test:
	.string	"15Memory_NIL_Test"
	.weak	_ZTIN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE, @object
	.size	_ZTIN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE, 24
_ZTIN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE
	.quad	_ZTIN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE
	.section	.rodata._ZTSN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE, @object
	.size	_ZTSN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE, 66
_ZTSN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE:
	.string	"N7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEE"
	.weak	_ZTI25Memory_PrimitiveSizs_Test
	.section	.data.rel.ro._ZTI25Memory_PrimitiveSizs_Test,"awG",@progbits,_ZTI25Memory_PrimitiveSizs_Test,comdat
	.align 8
	.type	_ZTI25Memory_PrimitiveSizs_Test, @object
	.size	_ZTI25Memory_PrimitiveSizs_Test, 24
_ZTI25Memory_PrimitiveSizs_Test:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS25Memory_PrimitiveSizs_Test
	.quad	_ZTIN7testing4TestE
	.weak	_ZTS25Memory_PrimitiveSizs_Test
	.section	.rodata._ZTS25Memory_PrimitiveSizs_Test,"aG",@progbits,_ZTS25Memory_PrimitiveSizs_Test,comdat
	.align 16
	.type	_ZTS25Memory_PrimitiveSizs_Test, @object
	.size	_ZTS25Memory_PrimitiveSizs_Test, 28
_ZTS25Memory_PrimitiveSizs_Test:
	.string	"25Memory_PrimitiveSizs_Test"
	.weak	_ZTIN7testing8internal15TestFactoryBaseE
	.section	.data.rel.ro._ZTIN7testing8internal15TestFactoryBaseE,"awG",@progbits,_ZTIN7testing8internal15TestFactoryBaseE,comdat
	.align 8
	.type	_ZTIN7testing8internal15TestFactoryBaseE, @object
	.size	_ZTIN7testing8internal15TestFactoryBaseE, 16
_ZTIN7testing8internal15TestFactoryBaseE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN7testing8internal15TestFactoryBaseE
	.weak	_ZTSN7testing8internal15TestFactoryBaseE
	.section	.rodata._ZTSN7testing8internal15TestFactoryBaseE,"aG",@progbits,_ZTSN7testing8internal15TestFactoryBaseE,comdat
	.align 32
	.type	_ZTSN7testing8internal15TestFactoryBaseE, @object
	.size	_ZTSN7testing8internal15TestFactoryBaseE, 37
_ZTSN7testing8internal15TestFactoryBaseE:
	.string	"N7testing8internal15TestFactoryBaseE"
	.section	.rodata
.LC52:
	.string	"PrimitiveSizs"
.LC53:
	.string	"Memory"
.LC54:
	.string	"innerAndOuterArrays"
.LC55:
	.string	"twoArrayAreConsecutive"
.LC56:
	.string	"totalSize"
	.align 8
.LC57:
	.string	"ConversionToIntDoesNotBreakEnums"
.LC58:
	.string	"minimalSize"
.LC59:
	.string	"overflow"
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB6382:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6382
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$112, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movl	%edi, -132(%rbp)
	movl	%esi, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -132(%rbp)
	jne	.L929
	cmpl	$65535, -136(%rbp)
	jne	.L929
	leaq	_ZN6MemoryL3allE(%rip), %rdi
	call	_ZN6Memory3._4C1Ev
	leaq	_ZStL8__ioinit(%rip), %rdi
.LEHB215:
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
	movl	$8, %edi
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestEC1Ev
	movl	$118, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$118, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE215:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB216:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE216:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$118, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB217:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE217:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC52(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB218:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE218:
	addq	$32, %rsp
	movq	%rax, _ZN25Memory_PrimitiveSizs_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movl	$8, %edi
.LEHB219:
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestEC1Ev
	movl	$127, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$127, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE219:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB220:
	.cfi_escape 0x2e,0
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE220:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$127, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB221:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE221:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC12(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB222:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE222:
	addq	$32, %rsp
	movq	%rax, _ZN15Memory_NIL_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movl	$8, %edi
.LEHB223:
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestEC1Ev
	movl	$134, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$134, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE223:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB224:
	.cfi_escape 0x2e,0
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE224:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$134, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB225:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE225:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC54(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB226:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE226:
	addq	$32, %rsp
	movq	%rax, _ZN31Memory_innerAndOuterArrays_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movl	$8, %edi
.LEHB227:
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestEC1Ev
	movl	$140, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$140, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE227:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB228:
	.cfi_escape 0x2e,0
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE228:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$140, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB229:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE229:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC55(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB230:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE230:
	addq	$32, %rsp
	movq	%rax, _ZN34Memory_twoArrayAreConsecutive_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movl	$8, %edi
.LEHB231:
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestEC1Ev
	movl	$148, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$148, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE231:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB232:
	.cfi_escape 0x2e,0
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE232:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$148, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB233:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE233:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC56(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB234:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE234:
	addq	$32, %rsp
	movq	%rax, _ZN21Memory_totalSize_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movl	$8, %edi
.LEHB235:
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestEC1Ev
	movl	$155, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$155, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE235:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB236:
	.cfi_escape 0x2e,0
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE236:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$155, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB237:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE237:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC57(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB238:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE238:
	addq	$32, %rsp
	movq	%rax, _ZN44Memory_ConversionToIntDoesNotBreakEnums_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movl	$8, %edi
.LEHB239:
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestEC1Ev
	movl	$163, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$163, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE239:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB240:
	.cfi_escape 0x2e,0
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE240:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$163, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB241:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE241:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC58(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB242:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE242:
	addq	$32, %rsp
	movq	%rax, _ZN23Memory_minimalSize_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movl	$8, %edi
.LEHB243:
	call	_Znwm@PLT
	movq	%rax, %r14
	movq	%r14, %rdi
	call	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestEC1Ev
	movl	$170, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE22GetTearDownCaseOrSuiteEPKci
	movq	%rax, %r12
	movl	$170, %esi
	leaq	.LC3(%rip), %rdi
	call	_ZN7testing8internal16SuiteApiResolverINS_4TestEE19GetSetUpCaseOrSuiteEPKci
	movq	%rax, %rbx
	call	_ZN7testing8internal13GetTestTypeIdEv@PLT
.LEHE243:
	movq	%rax, %r13
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-113(%rbp), %rdx
	leaq	-112(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB244:
	.cfi_escape 0x2e,0
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE244:
	leaq	-112(%rbp), %rcx
	leaq	-80(%rbp), %rax
	movl	$170, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB245:
	call	_ZN7testing8internal12CodeLocationC1ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEi
.LEHE245:
	leaq	-80(%rbp), %rax
	subq	$8, %rsp
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	movq	%r13, %r9
	movq	%rax, %r8
	movl	$0, %ecx
	movl	$0, %edx
	leaq	.LC59(%rip), %rsi
	leaq	.LC53(%rip), %rdi
.LEHB246:
	.cfi_escape 0x2e,0x20
	call	_ZN7testing8internal23MakeAndRegisterTestInfoEPKcS2_S2_S2_NS0_12CodeLocationEPKvPFvvES7_PNS0_15TestFactoryBaseE@PLT
.LEHE246:
	addq	$32, %rsp
	movq	%rax, _ZN20Memory_overflow_Test10test_info_E(%rip)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	jmp	.L929
.L958:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L932
.L957:
	endbr64
	movq	%rax, %rbx
.L932:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L933
.L956:
	endbr64
	movq	%rax, %rbx
.L933:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB247:
	call	_Unwind_Resume@PLT
.L961:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L935
.L960:
	endbr64
	movq	%rax, %rbx
.L935:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L936
.L959:
	endbr64
	movq	%rax, %rbx
.L936:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L964:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L938
.L963:
	endbr64
	movq	%rax, %rbx
.L938:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L939
.L962:
	endbr64
	movq	%rax, %rbx
.L939:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L967:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L941
.L966:
	endbr64
	movq	%rax, %rbx
.L941:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L942
.L965:
	endbr64
	movq	%rax, %rbx
.L942:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L970:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L944
.L969:
	endbr64
	movq	%rax, %rbx
.L944:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L945
.L968:
	endbr64
	movq	%rax, %rbx
.L945:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L973:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L947
.L972:
	endbr64
	movq	%rax, %rbx
.L947:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L948
.L971:
	endbr64
	movq	%rax, %rbx
.L948:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L976:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L950
.L975:
	endbr64
	movq	%rax, %rbx
.L950:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L951
.L974:
	endbr64
	movq	%rax, %rbx
.L951:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.L979:
	endbr64
	movq	%rax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7testing8internal12CodeLocationD1Ev
	jmp	.L953
.L978:
	endbr64
	movq	%rax, %rbx
.L953:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L954
.L977:
	endbr64
	movq	%rax, %rbx
.L954:
	leaq	-113(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE247:
.L929:
	movq	-40(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L955
	call	__stack_chk_fail@PLT
.L955:
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6382:
	.section	.gcc_except_table
.LLSDA6382:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6382-.LLSDACSB6382
.LLSDACSB6382:
	.uleb128 .LEHB215-.LFB6382
	.uleb128 .LEHE215-.LEHB215
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB216-.LFB6382
	.uleb128 .LEHE216-.LEHB216
	.uleb128 .L956-.LFB6382
	.uleb128 0
	.uleb128 .LEHB217-.LFB6382
	.uleb128 .LEHE217-.LEHB217
	.uleb128 .L957-.LFB6382
	.uleb128 0
	.uleb128 .LEHB218-.LFB6382
	.uleb128 .LEHE218-.LEHB218
	.uleb128 .L958-.LFB6382
	.uleb128 0
	.uleb128 .LEHB219-.LFB6382
	.uleb128 .LEHE219-.LEHB219
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB220-.LFB6382
	.uleb128 .LEHE220-.LEHB220
	.uleb128 .L959-.LFB6382
	.uleb128 0
	.uleb128 .LEHB221-.LFB6382
	.uleb128 .LEHE221-.LEHB221
	.uleb128 .L960-.LFB6382
	.uleb128 0
	.uleb128 .LEHB222-.LFB6382
	.uleb128 .LEHE222-.LEHB222
	.uleb128 .L961-.LFB6382
	.uleb128 0
	.uleb128 .LEHB223-.LFB6382
	.uleb128 .LEHE223-.LEHB223
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB224-.LFB6382
	.uleb128 .LEHE224-.LEHB224
	.uleb128 .L962-.LFB6382
	.uleb128 0
	.uleb128 .LEHB225-.LFB6382
	.uleb128 .LEHE225-.LEHB225
	.uleb128 .L963-.LFB6382
	.uleb128 0
	.uleb128 .LEHB226-.LFB6382
	.uleb128 .LEHE226-.LEHB226
	.uleb128 .L964-.LFB6382
	.uleb128 0
	.uleb128 .LEHB227-.LFB6382
	.uleb128 .LEHE227-.LEHB227
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB228-.LFB6382
	.uleb128 .LEHE228-.LEHB228
	.uleb128 .L965-.LFB6382
	.uleb128 0
	.uleb128 .LEHB229-.LFB6382
	.uleb128 .LEHE229-.LEHB229
	.uleb128 .L966-.LFB6382
	.uleb128 0
	.uleb128 .LEHB230-.LFB6382
	.uleb128 .LEHE230-.LEHB230
	.uleb128 .L967-.LFB6382
	.uleb128 0
	.uleb128 .LEHB231-.LFB6382
	.uleb128 .LEHE231-.LEHB231
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB232-.LFB6382
	.uleb128 .LEHE232-.LEHB232
	.uleb128 .L968-.LFB6382
	.uleb128 0
	.uleb128 .LEHB233-.LFB6382
	.uleb128 .LEHE233-.LEHB233
	.uleb128 .L969-.LFB6382
	.uleb128 0
	.uleb128 .LEHB234-.LFB6382
	.uleb128 .LEHE234-.LEHB234
	.uleb128 .L970-.LFB6382
	.uleb128 0
	.uleb128 .LEHB235-.LFB6382
	.uleb128 .LEHE235-.LEHB235
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB236-.LFB6382
	.uleb128 .LEHE236-.LEHB236
	.uleb128 .L971-.LFB6382
	.uleb128 0
	.uleb128 .LEHB237-.LFB6382
	.uleb128 .LEHE237-.LEHB237
	.uleb128 .L972-.LFB6382
	.uleb128 0
	.uleb128 .LEHB238-.LFB6382
	.uleb128 .LEHE238-.LEHB238
	.uleb128 .L973-.LFB6382
	.uleb128 0
	.uleb128 .LEHB239-.LFB6382
	.uleb128 .LEHE239-.LEHB239
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB240-.LFB6382
	.uleb128 .LEHE240-.LEHB240
	.uleb128 .L974-.LFB6382
	.uleb128 0
	.uleb128 .LEHB241-.LFB6382
	.uleb128 .LEHE241-.LEHB241
	.uleb128 .L975-.LFB6382
	.uleb128 0
	.uleb128 .LEHB242-.LFB6382
	.uleb128 .LEHE242-.LEHB242
	.uleb128 .L976-.LFB6382
	.uleb128 0
	.uleb128 .LEHB243-.LFB6382
	.uleb128 .LEHE243-.LEHB243
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB244-.LFB6382
	.uleb128 .LEHE244-.LEHB244
	.uleb128 .L977-.LFB6382
	.uleb128 0
	.uleb128 .LEHB245-.LFB6382
	.uleb128 .LEHE245-.LEHB245
	.uleb128 .L978-.LFB6382
	.uleb128 0
	.uleb128 .LEHB246-.LFB6382
	.uleb128 .LEHE246-.LEHB246
	.uleb128 .L979-.LFB6382
	.uleb128 0
	.uleb128 .LEHB247-.LFB6382
	.uleb128 .LEHE247-.LEHB247
	.uleb128 0
	.uleb128 0
.LLSDACSE6382:
	.text
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.section	.text._ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv:
.LFB6409:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6409
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB248:
	call	_Znwm@PLT
.LEHE248:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB249:
	call	_ZN20Memory_overflow_TestC1Ev
.LEHE249:
	movq	%rbx, %rax
	jmp	.L984
.L983:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB250:
	call	_Unwind_Resume@PLT
.LEHE250:
.L984:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6409:
	.section	.gcc_except_table
.LLSDA6409:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6409-.LLSDACSB6409
.LLSDACSB6409:
	.uleb128 .LEHB248-.LFB6409
	.uleb128 .LEHE248-.LEHB248
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB249-.LFB6409
	.uleb128 .LEHE249-.LEHB249
	.uleb128 .L983-.LFB6409
	.uleb128 0
	.uleb128 .LEHB250-.LFB6409
	.uleb128 .LEHE250-.LEHB250
	.uleb128 0
	.uleb128 0
.LLSDACSE6409:
	.section	.text._ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI20Memory_overflow_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv:
.LFB6410:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6410
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB251:
	call	_Znwm@PLT
.LEHE251:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB252:
	call	_ZN23Memory_minimalSize_TestC1Ev
.LEHE252:
	movq	%rbx, %rax
	jmp	.L989
.L988:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB253:
	call	_Unwind_Resume@PLT
.LEHE253:
.L989:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6410:
	.section	.gcc_except_table
.LLSDA6410:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6410-.LLSDACSB6410
.LLSDACSB6410:
	.uleb128 .LEHB251-.LFB6410
	.uleb128 .LEHE251-.LEHB251
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB252-.LFB6410
	.uleb128 .LEHE252-.LEHB252
	.uleb128 .L988-.LFB6410
	.uleb128 0
	.uleb128 .LEHB253-.LFB6410
	.uleb128 .LEHE253-.LEHB253
	.uleb128 0
	.uleb128 0
.LLSDACSE6410:
	.section	.text._ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI23Memory_minimalSize_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv:
.LFB6411:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6411
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB254:
	call	_Znwm@PLT
.LEHE254:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB255:
	call	_ZN44Memory_ConversionToIntDoesNotBreakEnums_TestC1Ev
.LEHE255:
	movq	%rbx, %rax
	jmp	.L994
.L993:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB256:
	call	_Unwind_Resume@PLT
.LEHE256:
.L994:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6411:
	.section	.gcc_except_table
.LLSDA6411:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6411-.LLSDACSB6411
.LLSDACSB6411:
	.uleb128 .LEHB254-.LFB6411
	.uleb128 .LEHE254-.LEHB254
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB255-.LFB6411
	.uleb128 .LEHE255-.LEHB255
	.uleb128 .L993-.LFB6411
	.uleb128 0
	.uleb128 .LEHB256-.LFB6411
	.uleb128 .LEHE256-.LEHB256
	.uleb128 0
	.uleb128 0
.LLSDACSE6411:
	.section	.text._ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI44Memory_ConversionToIntDoesNotBreakEnums_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv:
.LFB6412:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6412
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB257:
	call	_Znwm@PLT
.LEHE257:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB258:
	call	_ZN21Memory_totalSize_TestC1Ev
.LEHE258:
	movq	%rbx, %rax
	jmp	.L999
.L998:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB259:
	call	_Unwind_Resume@PLT
.LEHE259:
.L999:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6412:
	.section	.gcc_except_table
.LLSDA6412:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6412-.LLSDACSB6412
.LLSDACSB6412:
	.uleb128 .LEHB257-.LFB6412
	.uleb128 .LEHE257-.LEHB257
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB258-.LFB6412
	.uleb128 .LEHE258-.LEHB258
	.uleb128 .L998-.LFB6412
	.uleb128 0
	.uleb128 .LEHB259-.LFB6412
	.uleb128 .LEHE259-.LEHB259
	.uleb128 0
	.uleb128 0
.LLSDACSE6412:
	.section	.text._ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI21Memory_totalSize_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv:
.LFB6413:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6413
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB260:
	call	_Znwm@PLT
.LEHE260:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB261:
	call	_ZN34Memory_twoArrayAreConsecutive_TestC1Ev
.LEHE261:
	movq	%rbx, %rax
	jmp	.L1004
.L1003:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB262:
	call	_Unwind_Resume@PLT
.LEHE262:
.L1004:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6413:
	.section	.gcc_except_table
.LLSDA6413:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6413-.LLSDACSB6413
.LLSDACSB6413:
	.uleb128 .LEHB260-.LFB6413
	.uleb128 .LEHE260-.LEHB260
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB261-.LFB6413
	.uleb128 .LEHE261-.LEHB261
	.uleb128 .L1003-.LFB6413
	.uleb128 0
	.uleb128 .LEHB262-.LFB6413
	.uleb128 .LEHE262-.LEHB262
	.uleb128 0
	.uleb128 0
.LLSDACSE6413:
	.section	.text._ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI34Memory_twoArrayAreConsecutive_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv:
.LFB6414:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6414
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB263:
	call	_Znwm@PLT
.LEHE263:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB264:
	call	_ZN31Memory_innerAndOuterArrays_TestC1Ev
.LEHE264:
	movq	%rbx, %rax
	jmp	.L1009
.L1008:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB265:
	call	_Unwind_Resume@PLT
.LEHE265:
.L1009:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6414:
	.section	.gcc_except_table
.LLSDA6414:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6414-.LLSDACSB6414
.LLSDACSB6414:
	.uleb128 .LEHB263-.LFB6414
	.uleb128 .LEHE263-.LEHB263
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB264-.LFB6414
	.uleb128 .LEHE264-.LEHB264
	.uleb128 .L1008-.LFB6414
	.uleb128 0
	.uleb128 .LEHB265-.LFB6414
	.uleb128 .LEHE265-.LEHB265
	.uleb128 0
	.uleb128 0
.LLSDACSE6414:
	.section	.text._ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI31Memory_innerAndOuterArrays_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv:
.LFB6415:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6415
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB266:
	call	_Znwm@PLT
.LEHE266:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB267:
	call	_ZN15Memory_NIL_TestC1Ev
.LEHE267:
	movq	%rbx, %rax
	jmp	.L1014
.L1013:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB268:
	call	_Unwind_Resume@PLT
.LEHE268:
.L1014:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6415:
	.section	.gcc_except_table
.LLSDA6415:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6415-.LLSDACSB6415
.LLSDACSB6415:
	.uleb128 .LEHB266-.LFB6415
	.uleb128 .LEHE266-.LEHB266
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB267-.LFB6415
	.uleb128 .LEHE267-.LEHB267
	.uleb128 .L1013-.LFB6415
	.uleb128 0
	.uleb128 .LEHB268-.LFB6415
	.uleb128 .LEHE268-.LEHB268
	.uleb128 0
	.uleb128 0
.LLSDACSE6415:
	.section	.text._ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI15Memory_NIL_TestE10CreateTestEv
	.section	.text._ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv,comdat
	.align 2
	.weak	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv
	.type	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv, @function
_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv:
.LFB6416:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA6416
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movl	$16, %edi
.LEHB269:
	call	_Znwm@PLT
.LEHE269:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB270:
	call	_ZN25Memory_PrimitiveSizs_TestC1Ev
.LEHE270:
	movq	%rbx, %rax
	jmp	.L1019
.L1018:
	endbr64
	movq	%rax, %r12
	movl	$16, %esi
	movq	%rbx, %rdi
	call	_ZdlPvm@PLT
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB271:
	call	_Unwind_Resume@PLT
.LEHE271:
.L1019:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6416:
	.section	.gcc_except_table
.LLSDA6416:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6416-.LLSDACSB6416
.LLSDACSB6416:
	.uleb128 .LEHB269-.LFB6416
	.uleb128 .LEHE269-.LEHB269
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB270-.LFB6416
	.uleb128 .LEHE270-.LEHB270
	.uleb128 .L1018-.LFB6416
	.uleb128 0
	.uleb128 .LEHB271-.LFB6416
	.uleb128 .LEHE271-.LEHB271
	.uleb128 0
	.uleb128 0
.LLSDACSE6416:
	.section	.text._ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv,"axG",@progbits,_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv,comdat
	.size	_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv, .-_ZN7testing8internal15TestFactoryImplI25Memory_PrimitiveSizs_TestE10CreateTestEv
	.text
	.type	_GLOBAL__sub_I__ZN6Memory1PE, @function
_GLOBAL__sub_I__ZN6Memory1PE:
.LFB6495:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6495:
	.size	_GLOBAL__sub_I__ZN6Memory1PE, .-_GLOBAL__sub_I__ZN6Memory1PE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN6Memory1PE
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
