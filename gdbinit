# for My-Minix

file kernel.bin
target remote localhost:1234
set disassembly-flavor intel

b kernel/start.c:15
b kernel/main.c:64
c

define lsproc
    set $count = 16
    set $idx = 0
    printf "The first %d TASKS/PROCS:\n",$count
    while($idx < $count)
        if(proc_table[$idx].p_flags != 0x20)
            if($idx < 5)
                printf "[%2d] TASK: %8s",$idx,proc_table[$idx].name
                printf "\t p_flags: %8Xh\n",proc_table[$idx].p_flags
            else
                printf "[%2d] PROC: %8s",$idx,proc_table[$idx].name
                printf "\t p_flags: %8Xh\n",proc_table[$idx].p_flags
            end
        end
        set $idx++
    end
end
