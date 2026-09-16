#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int time = 0;
    
    while (1) {
        char buffer[6];
        int minutes = time / 60;
        int seconds = time % 60;
        snprintf(buffer, 6, "%02d:%02d", minutes, seconds);
        printf("Time: %s\n", buffer);
        time++;
        sleep(1);
    }
}
