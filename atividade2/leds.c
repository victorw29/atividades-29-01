#include <stdio.h>    
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_AZUL 11
#define LED_VERMELHO 12
#define LED_VERDE 13
#define BOTAO 5

// Estados dos LEDs
enum estado_leds {TRES_LIGADOS, DOIS_LIGADOS, UM_LIGADO};
volatile enum estado_leds estado_atual = TRES_LIGADOS;

// Variável para debouncing do botão
volatile bool botao_pressionado = false;

// Função de callback do temporizador para alterar o estado dos LEDs
bool leds_callback(struct repeating_timer *t) {
    switch (estado_atual) {
        case TRES_LIGADOS:
            // Acende todos os LEDs
            gpio_put(LED_AZUL, 1);
            gpio_put(LED_VERMELHO, 1);
            gpio_put(LED_VERDE, 1);
            estado_atual = DOIS_LIGADOS;
            break;
        case DOIS_LIGADOS:
            // Desliga o LED verde
            gpio_put(LED_VERDE, 0);
            estado_atual = UM_LIGADO;
            break;
        case UM_LIGADO:
            // Desliga o LED vermelho
            gpio_put(LED_VERMELHO, 0);
            estado_atual = TRES_LIGADOS; // Volta para o estado inicial
            break;
    }
    return true; // Mantém o temporizador repetindo
}

// Função para verificar o estado do botão com debouncing
void verificar_botao() {
    static uint32_t ultima_leitura = 0;
    uint32_t leitura_atual = gpio_get(BOTAO);

    // Verifica se o botão foi pressionado e se passou tempo suficiente (debounce)
    if (leitura_atual == 0 && (time_us_32() - ultima_leitura) > 200000) {
        botao_pressionado = true;
        ultima_leitura = time_us_32();
    }
}

int main() {
    stdio_init_all();

    // Inicializa os pinos dos LEDs
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicializa o pino do botão
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);  // Configura o botão com resistor de pull-up

    // Configura o temporizador repetitivo para chamar a função de callback
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, leds_callback, NULL, &timer);

    // Loop principal
    while (true) {
        verificar_botao(); // Verifica se o botão foi pressionado
        if (botao_pressionado) {
            // Aciona a troca de estado dos LEDs
            estado_atual = TRES_LIGADOS;
            botao_pressionado = false; // Reseta o estado do botão
        }
        sleep_ms(100); // Aguarda um pouco antes de verificar o botão novamente
    }

    return 0;
}
