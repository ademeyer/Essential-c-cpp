/*
 * int main()
 * {
 * int x = 10;
 * int y = 89;
 * x = x + y;
 * x += 42;
 * return x;
 * }
 * */

.global main
main:
  MOV R0, #10 // R0 is always the return register from a function
  MOV R1, #89
  ADD R0, R0, R1 // x = x + always
  /* Almost every three parameter command (ADD, SUB, etc.) have
   * a flexible third parameter. The third parameter can either
   * be a register or a constant int */
  ADD R0, R0, #42 // x += 42
  BX LR // Return from function, R0 is return value
