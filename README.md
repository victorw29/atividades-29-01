# Projeto de Controle de LEDs com Pico W

Este projeto utiliza um microcontrolador Raspberry Pi Pico W para controlar dois conjuntos de LEDs com diferentes comportamentos. O primeiro conjunto de LEDs simula um semáforo (vermelho, amarelo e verde), enquanto o segundo conjunto alterna entre três LEDs (azul, vermelho e verde), com um botão de controle para resetar o estado.

## Componentes Utilizados

- **Raspberry Pi Pico W**
- **LEDs:**
  - Semáforo:
    - LED Vermelho (GP11)
    - LED Amarelo (GP12)
    - LED Verde (GP13)
  - LEDs RGB (Azul, Vermelho e Verde):
    - LED Azul (GP11)
    - LED Vermelho (GP12)
    - LED Verde (GP13)
- **Resistores**: 
  - Resistor de 330Ω conectado aos LEDs e à linha GND
- **Botão**:
  - Botão conectado ao GP5, com resistor de pull-up ativo
  - GND 1
- **Conexões**:
  - GND 4: Conexão para aterramento

## Esquema de Pinagem

- **Semáforo**:
  - **LED Vermelho**: GP11
  - **LED Amarelo**: GP12
  - **LED Verde**: GP13
- **LEDs RGB**:
  - **LED Azul**: GP11
  - **LED Vermelho**: GP12
  - **LED Verde**: GP13
- **Botão**: 
  - **Entrada do botão**: GP5 (configurado com pull-up)
  - **GND do botão**: GND 1
- **Resistores**:
  - **Resistor de 330Ω**: GND 4 para todos os LEDs

## Descrição do Projeto

O sistema é dividido em dois comportamentos principais:

### 1. Semáforo (Com LEDs Vermelho, Amarelo e Verde)
Este comportamento simula um semáforo, alternando entre os três estados (vermelho, amarelo e verde) a cada 3 segundos. O LED correspondente ao estado ativo acende, enquanto os outros LEDs são desligados.

### 2. LEDs RGB com Controle de Estado
Os LEDs RGB (azul, vermelho e verde) mudam de estado a cada 3 segundos, alternando entre:
- **Três LEDs ligados** (todos acesos)
- **Dois LEDs ligados** (um LED apagado)
- **Um LED ligado** (dois LEDs apagados)

O botão (GP5) permite resetar o estado dos LEDs, retornando ao estado inicial (três LEDs acesos).

## Diagrama de Funcionamento

### Semáforo:

- **LED Vermelho**: Ligado durante o estado "VERMELHO".
- **LED Amarelo**: Ligado durante o estado "AMARELO".
- **LED Verde**: Ligado durante o estado "VERDE".

### LEDs RGB:

- **LED Azul**: Controlado pelo GP11.
- **LED Vermelho**: Controlado pelo GP12.
- **LED Verde**: Controlado pelo GP13.

### Controle do Botão:

- **Botão**: O botão é utilizado para resetar o ciclo dos LEDs, acionando o estado inicial.

## Pinagem do Raspberry Pi Pico W

| Pino       | Função                  |
|------------|-------------------------|
| **GP11**   | LED Vermelho e Azul     |
| **GP12**   | LED Amarelo e Vermelho  |
| **GP13**   | LED Verde               |
| **GP5**    | Botão de controle       |
| **GND 4**  | GND para os LEDs        |
| **GND 1**  | GND para o Botão        |

## Como Funciona

### Estado do Semáforo:

- O sistema alterna entre três estados:
  - **Vermelho**: Acende o LED vermelho.
  - **Amarelo**: Acende o LED amarelo.
  - **Verde**: Acende o LED verde.
  
  A cada 3 segundos, o estado do semáforo é alterado.

### Estado dos LEDs RGB:

- O sistema alterna entre três estados:
  - **Três LEDs ligados**: Todos os LEDs acesos.
  - **Dois LEDs ligados**: Um LED apagado (verde).
  - **Um LED ligado**: Dois LEDs apagados (vermelho).

- O botão conectado ao pino GP5 permite resetar o ciclo de LEDs para o estado inicial (todos os LEDs acesos).

## Código

O código em C é desenvolvido para ser executado no Raspberry Pi Pico W. Ele utiliza as bibliotecas padrão para controlar os pinos GPIO, temporizadores e verificações de estado.

### Funcionalidade:
1. **Semáforo**: Alterna os LEDs entre os estados de semáforo.
2. **LEDs RGB**: Alterna os LEDs RGB entre três estados e permite a interação com o botão para resetar o ciclo.

## Como Compilar e Rodar

1. Clone o repositório:
    ```bash
    git clone <url-do-repositório>
    cd <diretório-do-repositório>
    ```

2. Configure o ambiente de desenvolvimento para o Raspberry Pi Pico.

3. Compile o código:
    ```bash
    make
    ```

4. Carregue o código para o Raspberry Pi Pico W.

5. Execute o programa e observe o funcionamento dos LEDs e do botão de controle.

