#include "driverEP1.h"
#include <stdbool.h>
#include <inttypes.h>

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

typedef enum
{
  NO_OP = 0b0000,   // fiz
  STORE_A = 0b0010, // fiz
  LOAD_A = 0b0001,  // fiz
  JUMP = 0b0111,    // fiz
  JUMP_NZ = 0b1010, // fiz
  RET = 0b1110,     // fiz
  ARIT = 0b1100,
  HALT = 0b1111
} Opcode;

typedef enum
{
  set0 = 0b000,
  setF = 0b001,
  NOT = 2,
  AND = 3,
  OR = 4,
  XOR = 5,
  ADD = 6,
  SUB = 7
} Arit;

// ctrl shift b para compilar sem rodar

int aritt(int i, int dest, int Op1, int Op2)
{
  // Faz destino apontar para o registrador certo, de acordo com os bits em dest
  unsigned short int *destino = NULL;

  switch (dest)
  {
  case 0b000:
    destino = &a;
    break;
  case 0b001:
    destino = &b;
    break;
  case 0b010:
    destino = &c;
    break;
  case 0b011:
    destino = &d;
    break;
  case 0b110:
    destino = &r;
    break;
  case 0b111:
    destino = &psw;
    break;
  default:
    printf("Destino nao deu certo :( ");
  }

  int valor1;
  switch (Op1)
  {
  case 0b000:
    valor1 = a;
    break;
  case 0b001:
    valor1 = b;
    break;
  case 0b010:
    valor1 = c;
  case 0b011:
    valor1 = d;
  case 0b110:
    valor1 = r;
  case 0b111:
    valor1 = psw;
  default:
    printf("Op1 nao deu certo :( ");
  }

  int valor2;
  if (Op2 == 0b000)
  {
    valor2 = 0;
  }
  else if (Op2 == 0b001)
  {
    valor2 = 0;
  }
  else if (Op2 == 0b010)
  {
    valor2 = 0;
  }
  else if (Op2 == 0b011)
  {
    valor2 = 0;
  }
  else
  {
    switch (Op2)
    {
    case 0b000:
      valor2 = a;
      break;
    case 0b001:
      valor2 = b;
      break;
    case 0b010:
      valor2 = c;
    case 0b011:
      valor2 = d;
    default:
      printf("Op2 nao deu certo :( ");
    }
  }

  // verifica o registrador que deseja
  if (i == set0)
  {
    printf("set0 \n");
    *destino = 0;
  }
  if (i == setF)
  {
    printf("setF \n");
    *destino = 0xFFFF;
  }
  if (i == NOT)
  {
    printf("NOT \n");
    *destino = ~valor1;
  }
  if (i == AND)
  {
    printf("AND \n");
    *destino = valor1 & valor2;
  }
  if (i == OR)
  {
    printf("OR \n");
    *destino = valor1 | valor2;
  }
  if (i == XOR)
  {
    printf("XOR \n");
    *destino = valor1 ^ valor2;
  }
  if (i == ADD)
  {
    printf("ADD \n");
    *destino = valor1 + valor2;
  }
  if (i == SUB)
  {
    printf("SUB \n");
    *destino = valor1 + valor2;
  }
}

int processa(short int *M, int memSize)
{

  unsigned short int *memoria = (unsigned short int *)M;

  // começa a execução
  while (true)
  {
    // busca a instrução
    ri = memoria[pc];

    // extrai o opcode da instrução (os 4 bits mais significativos)
    Opcode opcode = (ri & 0xF000) >> 12;
    unsigned int arg = (ri & 0x0FFF);

    if (opcode == 0b000)
    {
      printf("NOP [%i] \n", pc);
    }

    if (opcode == LOAD_A)
    {
      a = memoria[arg];

      printf("[%i] o que foi carregado %x \n", pc, a);
    }
    if (opcode == STORE_A)
    {
      memoria[arg] = a;

      printf("o que foi armazenado %x \n", memoria[arg]);
    }
    if (opcode == JUMP)
    {
      printf("posição que pulou [%i]\n", pc);
      pc = arg - 1;
    }

    if (opcode == JUMP_NZ)
    {
      if (a != 0)
      {
        pc = arg - 1;
        printf("[%i] o pulo deu certo \n", pc);
      }
    }

    if (opcode == RET)
    {
      unsigned short int aux = pc;
      pc = r;
      r = aux + 1;

      printf(" pc recebeu esse valor [%i] de r", pc);
      printf("[%i] r recebeu o proximo endereço sequencial%x", pc, r);
    }

    unsigned int AR = (ri & 0b0000111000000000) >> 9;
    unsigned int Res = (ri & 0b0000000111000000) >> 6;
    unsigned int Op1 = (ri & 0b0000000000111000) >> 3;
    unsigned int Op2 = (ri & 0b0000000000000111);

    if (opcode == ARIT)
    {
      aritt(AR, Res, Op1, Op2);
    }

    if (opcode == HALT)
    {
      break;
    }

    getchar();

    printf("Ensine-me a fazer algo com %hx\n", ri);
    // incrementa o pc
    pc++;
    // decodifica a instrução
    if (pc >= memSize)
      pc = 0;
  }
}
