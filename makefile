BIN= $(GDK)/bin
LIB= $(GDK)/lib

DEMO_SRC= demo
SRC= sdk
RES= res

SHELL=$(BIN)/sh
RM= $(BIN)/rm
AR= $(BIN)/ar
CC= $(BIN)/gcc
LD= $(BIN)/ld
ECHO=echo
OBJCPY= $(BIN)/objcopy
ASMZ80= $(BIN)/sjasm
MACCER= $(BIN)/mac68k
SIZEBND= $(BIN)/sizebnd
BINTOC= $(BIN)/bintoc
BINTOS= $(BIN)/bintos
WAVTORAW= $(BIN)/wavtoraw
PCMTORAW= $(BIN)/pcmtoraw
NM= $(BIN)/nm
MKDIR= $(BIN)/mkdir
NM2WCH= $(BIN)/nm2wch
ADDR2LINE=$(BIN)/addr2line
OUT2GSRC=$(BIN)/out2gsrc

OPTION=

SRC_C= $(wildcard *.c)
SRC_C+= $(wildcard $(SRC)/*.c)
SRC_C+= $(wildcard $(DEMO_SRC)/*.c)
SRC_S= $(wildcard *.s)
SRC_S+= $(wildcard $(SRC)/*.s)
SRC_SZ80= $(wildcard *.s80)
SRC_SZ80+= $(wildcard $(SRC)/*.s80)
SRC_SZ80+= $(wildcard $(DEMO_SRC)/*.s80)

RES_S= $(wildcard $(RES)/*.s)
RES_BMP= $(wildcard *.bmp)
RES_BMP+= $(wildcard $(RES)/*.bmp)
RES_WAV= $(wildcard *.wav)
RES_WAV+= $(wildcard $(RES)/*.wav)
RES_DAT= $(wildcard *.dat)
RES_DAT+= $(wildcard $(RES)/*.dat)
RES_RAW= $(wildcard *.raw)
RES_RAW+= $(wildcard $(RES)/*.raw)
RES_PCM= $(wildcard *.pcm)
RES_PCM+= $(wildcard $(RES)/*.pcm)
RES_EIF= $(wildcard *.eif)
RES_EIF+= $(wildcard $(RES)/*.eif)
RES_ESF= $(wildcard *.esf)
RES_ESF+= $(wildcard $(RES)/*.esf)
RES_RC= $(wildcard *.rc)
RES_RC+= $(wildcard $(RES)/*.rc)
RES_ASM= $(wildcard *.asm)
RES_ASM+= $(wildcard $(RES)/*.asm)

OBJ= $(RES_BMP:.bmp=.o)
OBJ+= $(RES_WAV:.wav=.o)
OBJ+= $(RES_RC:.rc=.o)
OBJ+= $(RES_ASM:.asm=.o)
OBJ+= $(RES_DAT:.dat=.o)
OBJ+= $(RES_RAW:.raw=.o)
OBJ+= $(RES_PCM:.pcm=.o)
OBJ+= $(RES_EIF:.eif=.o)
OBJ+= $(RES_ESF:.esf=.o)
OBJ+= $(RES_S:.s=.o)
OBJ+= $(SRC_SZ80:.s80=.o)
OBJ+= $(SRC_S:.s=.o)
OBJ+= $(SRC_C:.c=.o)

OBJS = $(addprefix out/, $(OBJ))

INCS= -I$(SRC) -I$(DEMO_SRC) -I$(RES)
#FLAGS= $(OPTION) -g3 -m68000 -Wall -O1 -fomit-frame-pointer -fno-builtin-memset -fno-builtin-memcpy $(INCS)
FLAGS= $(OPTION) -m68000 -Wall -O1 -fomit-frame-pointer -fno-builtin-memset -fno-builtin-memcpy $(INCS)
#FLAGS= $(OPTION) -m68000 -Wall -O3 -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -fno-builtin-memset -fno-builtin-memcpy $(INCS)
FLAGSZ80= -i$(SRC) -i$(DEMO_SRC) -i$(RES)

all: out/rom.bin

default: all

.PHONY: clean

clean:
	$(RM) -f $(OBJS) out.lst out/cmd_ out/sega.o out/rom_head.bin out/rom_head.o out/rom.nm out/rom.wch out/rom.out out/rom.bin

cleanobj:
	$(RM) -f $(OBJS) out/sega.o out/rom_head.bin out/rom_head.o out/rom.out

out/rom.bin: out/rom.out
	$(NM) -n -S -t x out/rom.out >out/rom.nm
	$(NM2WCH) out/rom.nm out/rom.wch
	$(OBJCPY) -O binary out/rom.out out/rom.bin
	$(SIZEBND) out/rom.bin -sizealign 131072

out/tmp:
	$(OUT2GSRC) i out/rom.bin out/rom.addr
	$(ADDR2LINE) -e out/rom.out < out/rom.addr > out/rom.gsrc

out/rom.out: out/sega.o out/cmd_
	$(CC) -n -T $(GDK)/md.ld -nostdlib out/sega.o @out/cmd_ $(LIB)/libgcc.a -o out/rom.out
	$(RM) out/cmd_

out/cmd_: $(OBJS)
	$(ECHO) "$(OBJS)" > out/cmd_

out/sega.o: $(SRC)/boot/sega.s out/rom_head.bin
	$(MKDIR) -p out
	$(CC) $(FLAGS) -c $(SRC)/boot/sega.s -o $@

out/rom_head.bin: out/rom_head.o
	$(LD) -T $(GDK)/md.ld -nostdlib --oformat binary -o $@ $<

out/rom_head.o: $(SRC)/boot/rom_head.c
	$(MKDIR) -p out
	$(CC) $(FLAGS) -c $< -o $@


out/%.o: %.c
	$(MKDIR) -p out
	$(MKDIR) -p out/sdk
	$(MKDIR) -p out/demo
	$(MKDIR) -p out/res
	$(CC) $(FLAGS) -c $< -o $@

out/%.o: %.s
	$(MKDIR) -p out
	$(MKDIR) -p out/sdk
	$(MKDIR) -p out/demo
	$(MKDIR) -p out/res
	$(CC) $(FLAGS) -c $< -o $@

%.s: %.asm
	$(MACCER) -o $@ $<

%.s: %.bmp
	$(BINTOS) -bmp $<

%.raw: %.wav
	$(WAVTORAW) $<

%.rawpcm: %.pcm
	$(PCMTORAW) $< $@

%.o80: %.s80
	$(ASMZ80) $(FLAGSZ80) $< $@ out.lst

%.s: %.tfc
	$(BINTOS) -align 32768 $<

%.s: %.mvs
	$(BINTOS) -align 256 $<

%.s: %.esf
	$(BINTOS) -align 32768 $<

%.s: %.eif
	$(BINTOS) -align 256 $<

%.s: %.raw
	$(BINTOS) -align 256 -sizealign 256 $<

%.s: %.rawpcm
	$(BINTOS) -align 128 -sizealign 128 -nullfill 136 $<

%.s: %.dat
	$(BINTOS) -align 256 -sizealign 256 $<

%.s: %.o80
	$(BINTOS) $<
