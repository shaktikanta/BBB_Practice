#include <stdio.h>
#include <string.h>
#include <unistd.h>

int led_blink(int pin) {

    // char led_files[i][10];
    // //open the sysfs file entry in appending and binary mode
    // char path_str_led[200];
    // char led_direction[100];
    // char led_brightness0[100];
    // char led_brightness1[100];
    // char led_brightness2[100];
    // char led_brightness3[100];

    // // sprintf(path_str_led, "/sys/class/leds/beaglebone:green:usr%d", pin);
    // // sprintf(led_direction, "/sys/class/leds/beaglebone\:green\:usr%d/direction", pin);
    // sprintf(led_brightness0, "/sys/class/leds/beaglebone:green:usr%d/brightness", pin);
    // sprintf(led_brightness1, "/sys/class/leds/beaglebone:green:usr%d/brightness", pin);
    // sprintf(led_brightness2, "/sys/class/leds/beaglebone:green:usr%d/brightness", pin);
    // sprintf(led_brightness3, "/sys/class/leds/beaglebone:green:usr%d/brightness", pin);


    // FILE *LED_0 = NULL;
    // FILE *LED_1 = NULL;
    // FILE *LED_2 = NULL;
    // FILE *LED_3 = NULL;

    // if((LED_0 = fopen(led_brightness0, "rb+")) == NULL) {
    //     printf("NOT ABLE TO ACCESS THE LED PIN\n");
    //     return -1;
    // }

    // if((LED_1 = fopen(led_brightness1, "rb+")) == NULL) {
    //     printf("NOT ABLE TO ACCESS THE LED PIN\n");
    //     return -1;
    // }

    // if((LED_2 = fopen(led_brightness2, "rb+")) == NULL) {
    //     printf("NOT ABLE TO ACCESS THE LED PIN\n");
    //     return -1;
    // }

    // if((LED_3 = fopen(led_brightness3, "rb+")) == NULL) {
    //     printf("NOT ABLE TO ACCESS THE LED PIN\n");
    //     return -1;
    // }

    FILE *led_files[4];
    char led_paths[4][100];

    for (int i = 0; i < 4; i++) {
        sprintf(led_paths[i], "/sys/class/leds/beaglebone:green:usr%d/brightness", i);
        led_files[i] = fopen(led_paths[i], "rb+");
        if (led_files[i] == NULL) {
            printf("Failed to open LED %d\n", i);
            return -1;
        }
    }

    while(1){
        for(int i=0; i < 4; i++){
            for (int j = 0; j < 10; j++) {
                // sprinf(led_files[i], "LED_%d", i);
                fseek(led_files[i], 0, SEEK_SET);
                fwrite("1", sizeof(char), 1, led_files[i]);
                fflush(led_files[i]);
                usleep(50000);

                fseek(led_files[i], 0, SEEK_SET);
                fwrite("0", sizeof(char), 1, led_files[i]);
                fflush(led_files[i]);
                usleep(50000);
            }
        }
                 
    }
    for (int i = 0; i < 4; i++) {
        fclose(led_files[i]);
    }
    return 0;
}

int led_sweep_indicator() {
    FILE *led_files[4];
    char led_paths[4][100];

    // Setup LED file paths and open handles
    for (int i = 0; i < 4; i++) {
        sprintf(led_paths[i], "/sys/class/leds/beaglebone:green:usr%d/brightness", i);
        led_files[i] = fopen(led_paths[i], "rb+");
        if (led_files[i] == NULL) {
            printf("Failed to open LED %d\n", i);
            return -1;
        }
    }

    while (1) {
        // Turn on LEDs progressively like a fluid sweep
        for (int i = 0; i < 4; i++) {
            fseek(led_files[i], 0, SEEK_SET);
            fwrite("1", sizeof(char), 1, led_files[i]);
            fflush(led_files[i]);
            usleep(150000);  // Adjust for visual speed
        }

        // Short hold after full sweep
        usleep(300000);

        // Turn all LEDs off
        for (int i = 0; i < 4; i++) {
            fseek(led_files[i], 0, SEEK_SET);
            fwrite("0", sizeof(char), 1, led_files[i]);
            usleep(150000);  // Adjust for visual speed
            fflush(led_files[i]);
        }

        usleep(300000);  // Pause before next sweep
    }

    // Cleanup
    for (int i = 0; i < 4; i++) {
        fclose(led_files[i]);
    }

    return 0;
}


int main() {
    int p;
    printf("Hello, BeagleBone Black!!!\n");
    // printf("Enter pin no:\n");
    // scanf("%d", &p);
    // led_blink(p);
    led_sweep_indicator();

    return 0;
}
