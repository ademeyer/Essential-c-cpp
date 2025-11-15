/*
 * int main()
 * {
 * int x = 21;
 * int y = 3;
 * int z = x * y;
 * return z;
 * }*/

.global main
  main:
  MOV R1, #21 // x = 21
  MOV R2, #3 // y = 3
  /* MUL does not allow a flexible third parameter*/
  MUL R0, R1, R2
  BX LR
