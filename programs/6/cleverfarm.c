#include <stdio.h>
#include <math.h>
/* Константа M_PI может быть не определена в вашей системе, в этом случае добавьте
   -D_DEFAULT_SOURCE (GCC/glibc) или -D_USE_MATH_DEFINES (MSVC/MinGW) в параметры
   компилятора или переопределите эту переменную */

#define DAY_LIGHT 300
int timer = 0;

/* функция открывает и закрывает окно */
void set_window(int open)
{
    if (open) {
        printf("Time %d: Window opened!\n", timer);
    } else {
        printf("Time %d: Window closed!\n", timer);
    }
}

/* функция возвращает уровень освещенности */
int get_light()
{
    float s = sin((float)timer * M_PI / 180.0);
    return (int)(1000 * s * s);
}

#include <unistd.h>

/* увеличиваем счетчик и ждем секунду */
void next_second(int* time)
{
	(*time)++;
	sleep(1);
}

#define STATE_INIT  0
#define STATE_DAY   1
#define STATE_NIGHT 2

int main(int argc, char** argv)
{
    int state = STATE_INIT;

    timer = 0;
    while (timer < 600) {
        /* этот цикл будет выполняться раз в секунду 10 минут */        
        switch (state) {
        case STATE_INIT:
            state = STATE_DAY;
            set_window(1);
            break;
        case STATE_DAY:
            if (get_light() < DAY_LIGHT) {
                set_window(0);
                state = STATE_NIGHT;
            }
            break;
        case STATE_NIGHT:
            if (get_light() > DAY_LIGHT) {
                state = STATE_DAY;
                set_window(1);
            }
            break;
        default:
            printf("Unknown state %d!\n", state);
            return 1;
        }
        next_second(&timer);
    }
    return 0;
}
