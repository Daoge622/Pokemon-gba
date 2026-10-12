
ldr r1, [r0, #8]
ldrb r2, [r1]
adds r1, #1
str r1, [r0, #8]
ldrb r1, [r0, #3]
lsls r1, r1, #31
bpl done
adds r3, r2, r2
adds r3, r3, r2
ldrb r2, [r0, #2]
adds r3, r3, r2
adr r1, conditions
ldrb r1, [r1, r3]
cmp r1, #1
bne done
movs r1, #0
strb r1, [r0, #1]
str r1, [r0, #8]
done:
bx lr
.balign 4
conditions:
.byte 1,0,0, 0,1,0, 0,0,1, 1,1,0, 0,1,1, 1,0,1
