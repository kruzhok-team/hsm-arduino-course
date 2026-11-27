#include <stdio.h>
// Этот пример потребует для запуска GNU/Linux, UNIX-совместимую ОС или WSL
#include <unistd.h>

int main()
{
    int time = 0;
    
    while (1) {
        char buffer[6];
        int minutes = time / 60;
        int seconds = time % 60;
        snprintf(buffer, 6, "%02d:%02d", minutes % 60, seconds % 60); // по 2 знака на мин и сек
        printf("Time: %s\n", buffer);
        time++;
        if (time >= 3600) {
            time = 0;
        }
        sleep(1);
    }
}
