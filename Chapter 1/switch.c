//通过blockptr知道stackptr从间接的知道stackbuffer的位置
// 主要作用是为了实现任务的切换功能
__asm_void PendSV_Handler(void){
	IMPORT blockPtr; 		
	LDR R0, =blockPtr;	// 加载的是指针变量的地址
	LDR R0,[R0] 		// 获得指针变量的值 也就是blockPtr的起始地址
	LDR R0,[R0]			// 获得blockPtr起始四个字节的地址

	// 保存这些个寄存器
	STMDB R0!,{R4-R11}		// 批量 递减 写寄存器，
	// 因为寄存器的增长方向是向下的 R0! 表示寄存器地址递减
	LDR R1,=blockPtr		// 更新获得一下blockPtr指针的地址
	LDR R1,[R1]				// 获得blockPtr指针
	STR R0,[R1]				// 更新stackBuffer的值 
	// Block_t** -> Block_t* ->  首元素地址

	ADD R4,R4
	ADD R5,R5

	// 恢复这些个寄存器
	LDMIA R0!, {R4-R11} 	// 中断异常等回复
	BX LR; 		// 退出中断
}
