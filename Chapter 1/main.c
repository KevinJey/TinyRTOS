#define NVIC_INT_CTRL 		0XE000Ed04
#define NVIC_PENDSVSET 		0X10000000
#define NVIC_SYSPRI2		0XE000ED22
#define NVIC_PENDSV_PRI	0X000000FF

#define MEM32(addr)		*(volatile unsigned long*)(addr)
#define MEM8(addr)		*(volatile unsigned long*)(addr)

void triggerPendSVC(void){
	// 这是触发PendSVC的方式，要在NVIC_SYSPRI2寄存器中写入NVIC_PENDSV_PRI的值
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}
typedef struct _BlockType_t{
    unsigned long* _stackPtr;   // stack pointer
}BlockType_t;
BlockType_t *blockPtr;

void delay (int count) 
{
    while (--count > 0);
}

int flag;
unsigned long stackBuffer[1024]; 
BlockType_t block;
int main () 
{
	// 指向最后一个单元
	block._stackPtr = &stackBuffer[1024]; 
	blockPtr = &block;
    for (;;) {
        flag = 0;
        delay(100);
        flag = 1;
        delay(100);

		triggerPendSVC();
    }
    
    return 0;
}
