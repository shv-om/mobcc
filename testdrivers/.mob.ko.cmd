cmd_/home/mob/internship/mobcc/testdrivers/mob.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -z noexecstack   --build-id  -T ./scripts/module-common.lds -o /home/mob/internship/mobcc/testdrivers/mob.ko /home/mob/internship/mobcc/testdrivers/mob.o /home/mob/internship/mobcc/testdrivers/mob.mod.o;  true
