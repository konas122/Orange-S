typedef struct stackframe {
    u32 gs;
    u32 fs;
    u32 es;
    u32 ds;
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 kernel_esp;             // `popad` will ignore it
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    u32 retaddr;                // return address for assembly code save()
    u32 eip;
    u32 cs;
    u32 eflags;
    u32 esp;
    u32 ss;
} STACK_FRAME;


typedef struct proc {
	struct stackframe		regs;	    /* process' registers saved in stack frame */

	u16				ldt_sel;		    /* selector in gdt giving ldt base and limit*/
	DESCRIPTOR		ldts[LDT_SIZE];	    /* local descriptors for code and data */
								        /* 2 is LDT_SIZE - avoid include protect.h */

    int             ticks;              /* remained ticks */
    int             priority;

    u32				pid;			    /* process id passed in from MM */
	char			name[16];		    /* name of the process */

    int  p_flags;                       /**
				                         * process flags.
                                         * A proc is runnable if p_flags==0
                                         * 
                                         * 用于标明进程的状态，取值有3种：
                                         *  -0：进程正在运行或准备运行
                                         *  -SENDING：进程处于发送消息的状态。
                                         *      由于消息还未送达，进程被阻塞了。
                                         *  -RECEIVING：进程处于接受消息的状态。
                                         *      由于消息还未收到，进程被阻塞了。
                                         */

    MESSAGE *       p_msg;              /* 指向消息体的指针 */

    int             p_recvfrom;         /* 假设进程p想要接收消息，但目前没有进程发消息给它，
                                         * 该成员变量则用来记录p想要从谁那儿接收消息。 */

    int             p_sendto;           /* 假设进程p想要发送消息，但目前没有进程接收它，
                                         * 该成员变量则用来记录p要发消息给谁。 */

	int             has_int_msg;        /**
                                         * nonzero if an INTERRUPT occurred when
                                         * the task is not ready to deal with it.
                                         * 
                                         * 如果有一个中断需要某进程来处理，或换句话说，
                                         * 某进程正在等待一个中断发生——比如硬盘驱动可能会等待硬盘中断的发生，
                                         * 系统在得知中毒案发生后会将此位置设为1。
                                         */

	struct proc * q_sending;            /**
                                         * queue of procs sending messages to
                                         * this proc
                                         * 
                                         * 消息队列
                                         */

	struct proc * next_sending;         /**
                                         * next proc in the sending
                                         * queue (q_sending)
                                         * 
                                         * 消息队列(链表)的next指针
                                         */

    int nr_tty;
} PROCESS;

typedef struct task {
    task_f      initial_eip;
    int         stacksize;
    char        name[32];
} TASK;


#define proc2pid(x) (x - proc_table)


/* Number of tasks & procs */
#define NR_TASKS	2
#define NR_PROCS	3
#define FIRST_PROC	proc_table[0]
#define LAST_PROC	proc_table[NR_TASKS + NR_PROCS - 1]

/* stacks of tasks */
#define STACK_SIZE_TTY		0x8000
#define STACK_SIZE_SYS		0x8000
#define STACK_SIZE_HD		0x8000
#define STACK_SIZE_FS		0x8000
#define STACK_SIZE_TESTA	0x8000
#define STACK_SIZE_TESTB	0x8000
#define STACK_SIZE_TESTC	0x8000

#define STACK_SIZE_TOTAL	(STACK_SIZE_TTY + \
				STACK_SIZE_SYS + \
				STACK_SIZE_HD + \
				STACK_SIZE_FS + \
				STACK_SIZE_TESTA + \
				STACK_SIZE_TESTB + \
				STACK_SIZE_TESTC)


