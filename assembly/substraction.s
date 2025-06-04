/*
 * int main()
 * {
 * int x = 100;
 * x = x - 58;
 * x = 60 - x
 * return x;
 * }*/

.global main
main:
  MOV R0, #100 // R0 is always the return value function
  SUB R0, R0, #58 // x = x - 58
  RSB R0, R0, #60 // x = 60 - x
  BX LR
