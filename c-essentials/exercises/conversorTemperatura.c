#include <stdio.h>
#include <ctype.h>
#include <math.h>

float celsiusTo(char escale, float value);
float kelvinTo(char escale, float value);
float fahrenheitTo(char escale, float value);

int main(int argc, char* argv[]) {
    int undI, undO;
    float value;

    enum Escale { CELSIUS = 1, FAHRENHEIT = 2, KELVIN = 3 };

    printf("Escala de Entrada (1 - Celsius, 2 - Fahrenheit, 3 - Kelvin): ");
    scanf("%d", &undI);

    printf("\nEscala de Saída (1 - Celsius, 2 - Fahrenheit, 3 - Kelvin): ");
    scanf(" %d", &undO);

    printf("\nValor a ser convertido: ");
    scanf(" %f", &value);

    float result = NAN;

    switch (undI) {
        case CELSIUS:
            if (undO == CELSIUS) {
                printf("As escalas de entrada e saída devem ser diferentes");
                return 1;
            } else if (undO == FAHRENHEIT) {
                result = celsiusTo('f', value);
            } else if (undO == KELVIN) {
                result = celsiusTo('k', value);
            }
            
            break;
        case FAHRENHEIT:
            if (undO == FAHRENHEIT) {
                printf("As escalas de entrada e saída devem ser diferentes");
                return 1;
            } else if (undO == CELSIUS) {
                result = fahrenheitTo('c', value);
            } else if (undO == KELVIN) {
                result = fahrenheitTo('k', value);
            }
            
            break;
        case KELVIN:
            if (undO == KELVIN) {
                printf("As escalas de entrada e saída devem ser diferentes");
                return 1;
            } else if (undO == CELSIUS) {
                result = kelvinTo('c', value);
            } else if (undO == FAHRENHEIT) {
                result = kelvinTo('f', value); 
            }
            
            break;
        default:
            printf("Escala de entrada inválida");
            return 1;
    }

    if (isnan(result)) {
        printf("Escala de saída inválida");
        return 1;  
    }

    printf("\nResultado da conversão: %.2f", result);

    return 0;
}

float celsiusTo(char escale, float value) {
    float equation;

    escale = tolower(escale);

    if (escale == 'k') {
        equation = value + 273.15;
    } else if (escale == 'f') {
        equation = (value * 1.8) + 32;
    } else {
        printf("Escala inválida.");
        return 2;
    }

    return equation;
}

float kelvinTo(char escale, float value) {
    float equation;

    escale = tolower(escale);

    if (escale == 'c') {
        equation = value - 273.15;
    } else if (escale == 'f') {
        equation = (value * 1.8) - 459.67;
    } else {
        printf("Escala inválida.");
        return 2;
    }

    return equation;
}

float fahrenheitTo(char escale, float value) {
    float equation;

    escale = tolower(escale);

    if (escale == 'c') {
        equation = (value - 32) / 1.8;
    } else if (escale == 'k') {
        equation = (value + 459.67) / 1.8;
    } else {
        printf("Escala inválida.");
        return 2;
    }

    return equation;
}