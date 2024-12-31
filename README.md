# Simulador de Processador em Linguagem C

Este projeto implementa um simulador de processador básico em linguagem C, capaz de executar instruções armazenadas na memória. Ele utiliza registradores para armazenamento de dados, possui suporte para operações aritméticas e lógicas, e implementa um conjunto de instruções com controle de fluxo.

## Funcionalidades

- **Instruções Suportadas**:
  - `NO_OP`: Instrução de espera sem operação.
  - `LOAD_A`: Carrega o valor da memória para o registrador A.
  - `STORE_A`: Armazena o valor do registrador A na memória.
  - `JUMP`: Altera o valor do program counter (PC).
  - `JUMP_NZ`: Salta condicionalmente se o valor de A não for zero.
  - `RET`: Retorna ao endereço armazenado no registrador R.
  - `ARIT`: Executa operações aritméticas e lógicas (como AND, OR, XOR, ADD, SUB, etc.).
  - `HALT`: Finaliza a execução.

- **Registradores**:
  - A: Registrador de uso geral.
  - B, C, D: Registradores auxiliares.
  - R: Registrador de retorno.
  - PSW: Registrador de status de programa (flags como overflow, underflow, igualdade, etc.).

- **Operações Aritméticas e Lógicas**:
  - `SET0`, `SETF`, `NOT`, `AND`, `OR`, `XOR`, `ADD`, `SUB`.

## Arquitetura

### Estruturas Principais
- **Registradores**: Usados para armazenar valores temporários e resultados de operações.
- **Memória**: Representada por um vetor de 16 bits onde as instruções e os dados residem.
- **Program Counter (PC)**: Aponta para a próxima instrução a ser executada.

### Fluxo de Execução
1. **Busca**: A instrução é carregada da memória para o registrador de instrução (`RI`).
2. **Decodificação**: O opcode e os argumentos são extraídos.
3. **Execução**: A operação é realizada de acordo com o opcode.
4. **Atualização**: O PC é incrementado para a próxima instrução.

## Como Compilar e Executar

1. **Pré-requisitos**: Certifique-se de ter um compilador C, como `gcc`, instalado em seu sistema.
2. **Compilação**:
   ```bash
   gcc -o simulador main.c -Wall
   ```
3. **Execução**:
   ```bash
   ./simulador
   ```

## Exemplo de Memória

```c
short int memoria[] = {
    0x1001, // LOAD_A 1
    0x2102, // STORE_A 2
    0x3003, // JUMP 3
    0xF000  // HALT
};
int tamanhoMemoria = sizeof(memoria) / sizeof(short int);
processa(memoria, tamanhoMemoria);
```

## Detalhes de Implementação

### Funções Principais
- `processa`: Controla o ciclo de busca, decodificação e execução das instruções.
- `aritt`: Executa operações aritméticas e lógicas, atualizando os registradores de destino.
- `printCurrentInstruction`: Exibe a instrução atual com detalhes no console.
- `printAritInstruction`: Mostra as instruções aritméticas em formato legível.

### Registro de Status (PSW)
O registrador PSW é atualizado após operações aritméticas para refletir estados como:
- **Overflow**: Soma excede o valor máximo permitido (0xFFFF).
- **Underflow**: Subtração resulta em valor negativo.
- **Igualdade**: Operandos são iguais.
- **Comparações**: Valores comparados.

## Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir um pull request ou reportar problemas.

## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).
