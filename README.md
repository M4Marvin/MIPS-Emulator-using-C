# MIPS-Emulator-using-C

Emulator for MIPS-32-bit architecture using C. It has limited functionality, it can currently excecute the folowing instructions:

1. nop
2. add
3. addi
4. andi
5. srl
6. sll
7. blez
8. bne
9. jal
10. jr

To run the emulator, you need excecute the following command:

```powershell
gcc -o mips_emulator mips_emulator.c
./mips-emulator <input_file>
```
