#include <stdio.h>
#include <math.h>

#define DAY_LIGHT 330
int time = 0;

/* функция открывает и закрывает окно */
void set_window(int open)
{
    if (open) {
        printf("Time %d: Window opened!\n", time);
    } else {
        printf("Time %d: Window closed!\n", time);
    }
}

/* функция возвращает уровень освещенности */
int get_light()
{
    float s = sin((float)time * M_PI / 180.0);
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
    int state;

    time = 0;
    while (time < 300) {
        /* этот цикл будет выполняться раз в секунду */        
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
        next_second(&time);
    }
    return 0;
}

