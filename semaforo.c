#include <stdio.h>                                                                                               #include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

// Estados do semáforo
enum estado_semaforo {VERMELHO, AMARELO, VERDE};
volatile enum estado_semaforo estado_atual = VERMELHO;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de alternar o estado
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Alterna o estado do semáforo
    switch (estado_atual) {
        case VERMELHO:
            gpio_put(LED_VERMELHO, 1);
            estado_atual = AMARELO;
            break;
        case AMARELO:
            gpio_put(LED_AMARELO, 1);
            estado_atual = VERDE;
            break;
        case VERDE:
            gpio_put(LED_VERDE, 1);
            estado_atual = VERMELHO;
            break;
    }
    return true; // Mantém o temporizador repetindo
}

int main() {
    // Inicializa a comunicação serial
    stdio_init_all();
    
    // Configura os pinos dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_init(LED_AMARELO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configura e inicia o temporizador repetitivo
    struct repeating_timer timer;
    add_repeating_timer_ms(-3000, repeating_timer_callback, NULL, &timer);
    
    // Loop principal
    while (true) {
        printf("Sistema do semáforo rodando...\n");
        sleep_ms(1000);
    }
}
