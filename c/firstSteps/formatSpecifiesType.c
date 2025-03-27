#include <stdio.h>

int main() {
   int num = 255;

   printf("Decimal: %d\n", num);    // Saída: Decimal: 255
   printf("Hexadecimal: %x\n", num); // Saída: Hexadecimal: ff
   printf("Hexadecimal (maiúsculas): %X\n", num); // Saída: Hexadecimal (maiúsculas): FF
   printf("Hexadecimal (tres digitos): %03x\n", num); // Saída: Hexadecimal (maiúsculas): FF
   printf("Hexadecimal (prefixo 0x): %#x\n", num); // Saída: Hexadecimal (maiúsculas): FF

   return 0;
}