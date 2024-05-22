#include "driverEP1.h"
#include <stdbool.h>
#include <inttypes.h>

typedef enum
{
  NO_OP = 0b0000,        //fiz
  STORE_A = 0b0010,     //fiz
  LOAD_A = 0b0001,     //fiz
  JUMP = 0b0111,      //fiz
  JUMP_NZ = 0b1010,  //fiz
  RET = 0b1110,     
  ARIT = 0b1100,
  HALT = 0b1111
} Opcode;

// ctrl shift b para compilar sem rodar

int processa(short int *M, int memSize)
{

  unsigned short int *memoria = (unsigned short int *)M;

  // registrodores
  // conteudo de memória na posição pc
  unsigned short int ri = 0;
  unsigned short int pc = 0;
  unsigned short int a = 0;
  unsigned short int b = 0;
  unsigned short int c = 0;
  unsigned short int d = 0;
  unsigned short int r = 0;
  unsigned short int psw = 0;

  // começa a execução
  pc = 0;
  while (true)
  {
    // busca a instrução
    ri = memoria[pc];

    // extrai o opcode da instrução (os 4 bits mais significativos)
    Opcode opcode = (ri & 0xF000) >> 12;
    unsigned int arg = (ri & 0x0FFF);

    if (opcode == 0b000)
    {
      printf("NOP");
    }

    if (opcode == LOAD_A)
    {
      a = memoria[arg];
    }
    if (opcode == STORE_A)
    {
      memoria[arg] = a;
    }
    if (opcode == JUMP)
    {
      pc = arg - 1;
    }

    if(opcode ==JUMP_NZ){
      if(a!=0){
        pc = arg - 1;
      }
    }

    // sai do loop se a instrução for HALT
    // 0xF é o opcode de HALT agora ou 0b111
    // 0 sem nada é octal, 0b binário e 0x hexadecimal
    if (opcode == 0b111)
    {
      break;
    }

    printf("Ensine-me a fazer algo com %hx\n", ri);
    // incrementa o pc
    pc++;
    // decodifica a instrução
    if (pc >= memSize)
      pc = 0;
  }
}
