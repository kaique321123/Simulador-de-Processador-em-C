#include "driverEP1.h"
#include <stdbool.h>
#include <stdint.h>

void printCurrentInstruction();

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
	JUMP = 0b0011,    // fiz
	JUMP_NZ = 0b0100, // fiz
	RET = 0b0101,     // fiz
	ARIT = 0b0110,    // fiz
	HALT = 0b1111     // fiz
} Opcode;

typedef enum
{
	set0 = 0b000, // 0
	setF = 0b001, // 1
	NOT = 0b010,  // 2
	AND = 0b011,  // 3
	OR = 0b100,   // 4
	XOR = 0b101,  // 5
	ADD = 0b110,  // 6
	SUB = 0b111   // 7
} Arit;

// ctrl shift b para compilar sem rodar

int aritt(int i, int dest, int Op1, int Op2)
{

	// Faz destino apontar para o registrador certo, de acordo com os bits em dest
	unsigned short int *destino = NULL;
	bool overflow = false;
	bool under = false;

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
		printf("Destino nao deu certo :( \n");
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
		break;
	case 0b011:
		valor1 = d;
		break;
	case 0b110:
		valor1 = r;
		break;
	case 0b111:
		valor1 = psw;
		break;
	default:
		printf("Op1 nao deu certo :( \n");
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
		case 0b100:
			valor2 = a;
			break;
		case 0b101:
			valor2 = b;
			break;
		case 0b110:
			valor2 = c;
			break;
		case 0b111:
			valor2 = d;
			break;
		default:
			printf("Op2 nao deu certo :( \n");
		}
	}

	// verifica o registrador que deseja
	if (i == set0)
	{
		printf("set0 \n");
		*destino = 0x0000;
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
		//valor2 com problema
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
		if (valor1 + valor2 > 0xFFFF) {
			overflow = true;
		}
	}
	if (i == SUB)
	{
		printf("SUB \n");
		*destino = valor1 - valor2;
		if (valor1 - valor2 < 0) {
			under = true;
		}
	}

	psw = 0;
	if (overflow) {
		psw |= 0b1000000000000000;
	}
	if (under) {
		psw |= 0b0100000000000000;
	}
	if (valor1 < valor2) {
		psw |= 0b0010000000000000;
	}
	if (valor1 == valor2) {
		psw |= 0b0001000000000000;
	}
	if (valor1 > valor2) {
		psw |= 0b0000100000000000;
	}
}

int processa(short int *M, int memSize)
{

	// conteúdo do acumulador
	unsigned short int *memoria = (unsigned short int *)M;

	// começa a execução
	while (true)
	{
		// busca a instrução
		ri = memoria[pc];

		// extrai o opcode da instrução (os 4 bits mais significativos)
		Opcode opcode = (ri & 0xF000) >> 12;
		unsigned int arg = (ri & 0x0FFF);

		// Imprime a posição, instrução atual, e mnemônico da instrução a ser executada
		printCurrentInstruction();

		if (opcode == 0b000)
		{
			printf("NOP [%i] \n", pc);
		}

		if (opcode == LOAD_A)
		{
			a = memoria[arg];

			printf("[%i] LDA %x \n", pc, a);
			// printf("LDA (%i) \n", arg);
		}

		if (opcode == STORE_A)
		{
			memoria[arg] = a;

			printf("STA %hx \n", memoria[arg]);
			// printf("STA (%i) \n", arg);
		}

		if (opcode == JUMP)
		{

			printf("JMP [%i]\n", pc);
			//  printf("JMP (%i) \n", arg);
			pc = arg - 1;
		}

		if (a == 0)
		{
			printf("%i \n", a);
		}
		if (opcode == JUMP_NZ)
		{
			if (a != 0)
			{
				pc = arg - 1;
				printf("[%i] JNZ \n", pc);
				//  printf("JNZ (%i) \n", arg);
			}
		}

		if (opcode == RET)
		{
			unsigned short int aux = pc;
			pc = r;
			r = aux + 1;

			printf(" RET [%i]", pc);
			//      printf("RET (%i) \n", arg);
		}

		unsigned int AR = (ri & 0b0000111000000000) >> 9;
		unsigned int Res = (ri & 0b0000000111000000) >> 6;
		unsigned int Op1 = (ri & 0b0000000000111000) >> 3;
		unsigned int Op2 = (ri & 0b0000000000000111);

		if (opcode == ARIT)
		{
			printf("ARITT ");
			printAritInstruction();
			aritt(AR, Res, Op1, Op2);
		}

		if (opcode == HALT)
		{
			printf("HALT \n");
			break;
		}

		// Espera o usuário pressionar uma tecla
		getchar();

		//printf("Ensine-me a fazer algo com %hx\n", ri);
		// incrementa o pc
		pc++;
		// decodifica a instrução
		if (pc >= memSize)
			pc = 0;
	}
}

/**
 * @brief Imprime no console em cores a posição atual do PROGRAM COUNTER, o código da instrução
 * (opcode) e o mnemônico que esse opcode representa.
 */
void printCurrentInstruction()
{
	const char *const OPCODES[] = {
			"NOP", "LDA", "STA", "JMP",
			"JNZ", "RET", "ARIT", "??7",
			"??8", "??9", "??A", "??B",
			"??C", "??D", "??E", "HLT"};

	int opcode = (ri & 0xF000) >> 12;

	// Imprime a posição, instrução e mnemônico atuais
	printf("::\033[33m [%03Xh] %04X: %s\033[0m\n", (uint32_t)pc, (uint32_t)ri, OPCODES[opcode]);
}

uint16_t getRegisterValue(uint8_t code) {
	switch(code) {
		case 0: return a;
		case 1: return b;
		case 2: return c;
		case 3: return d;
		case 6: return r;
		case 7: return psw;
		default:
			printf("[ERR] Registrador inválido!\n");
	}

}

/// @brief Imprime a instrução ARIT com os operandos e valores em cada registrador, para facilitar a
/// depuração
void printAritInstruction() {
	const char* const REGISTERS[] = {
		"A", "B", "C", "D", "??", "?", "R", "PSW"
	};

	const char* const OPERATIONS[] = {
		"SET0", "SETF", "NOT", "AND", "OR", "XOR", "+", "-"
	};

	int operando = ri & 0x0FFF;

	uint8_t oper = (ri & 0b0000111000000000) >> 9;
	uint8_t res = (ri & 0b0000000111000000) >> 6;
	uint8_t op1 = (ri & 0b0000000000111000) >> 3;
	uint8_t op2 = (ri & 0b0000000000000111);

	// Imprime o destino da operação
	printf("%s = ", REGISTERS[res]);

	// Imprime o regisstrador e o valor do registrador do operando 1
	printf("%s", REGISTERS[op1]);
	printf("[%Xh]", (unsigned int)getRegisterValue(op1));

	// Imprime a operação que vai ser feita
	printf(" %s ", OPERATIONS[oper]);

	if ((op2 & 0b100) == 0) {
		printf("0");
	} else {
		printf("%s", REGISTERS[op2 & 0b11]);
		printf("[%Xh]", (unsigned int) getRegisterValue(op2 & 0b11));
	}

	printf("\n");
}