# Orange-S

## Environment

```
x86_64 GNU/Linux
gcc version 12.3.0
GNU ld 2.41
GNU Make 4.3
NASM version 2.16.01
Bochs x86 Emulator 2.6.8
```

## Make

```shell
$ make image
```

## Run

```shell
$ bochs -f bochsrc
```

## Debug

Run this command in first shell. Then choose [6] to begin the simulation.

```shell
$ make debug
```

Then open a new shell and run the command below.

```shell
$ gdb -x gdbinit
```
