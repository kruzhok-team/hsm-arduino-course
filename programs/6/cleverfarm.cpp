#include <cstdio>
#include <cmath>

// класс управления окном
class Window {
public:
    Window(const int* t):
        time(t)
    {
    }

    void open()
    {
        printf("Time %d: Window opened!\n", *time);
    }

    void close()
    {
        printf("Time %d: Window closed!\n", *time);
    }
    
private:
    const int* time;
};

// класс датчика освещенности
class LightSensor {
public:
    const int DAY_LIGHT = 330;

    LightSensor(const int* t):
        time(t)
    {
    }
    
    bool is_day()
    {
        return get_level() > DAY_LIGHT;
    }
    bool is_night()
    {
        return get_level() < DAY_LIGHT;
    }

private:
    int get_level()
    {
        float s = sin(float(*time) * M_PI / 180.0);
        return int(1000 * s * s);
    }
    const int* time;
};

// продолжение программы

const int STATE_INIT = 0;
const int STATE_DAY = 1;
const int STATE_NIGHT = 2;

// класс машины состояний
class StateMachine {
public:
    StateMachine(const int* t, Window* w, LightSensor* ls):
        state(STATE_INIT), time(t), window(w), light_sensor(ls)
    {
    }
    
    void step_sec()
    {
        switch (state) {
        case STATE_INIT:
            set_state(STATE_DAY);
            window->open();
            break;
        case STATE_DAY:
            if (light_sensor->is_night()) {
                window->close();
                set_state(STATE_NIGHT);
            }
            break;
        case STATE_NIGHT:
            if (light_sensor->is_day()) {
                set_state(STATE_DAY);
                window->open();
            }
            break;
        default:
            throw "Unknown state!";
        }
    }
    
private:

    void set_state(int s) { state = s; }

    int state;
    const int* time;
    Window* window;
    LightSensor* light_sensor;
};

#include <unistd.h>

int main(int argc, char** argv)
{
    int time = 0;
    Window window(&time);
    LightSensor sensor(&time);
    StateMachine sm(&time, &window, &sensor);

    while (time < 300) {
        /* этот цикл будет выполняться раз в секунду */
        try {
            sm.step_sec();
        } catch(const char* e) {
            printf("Ошибка в программе: %s\n", e);
            return 1;
        }
        sleep(1);
        time++;
    }
    return 0;
}

