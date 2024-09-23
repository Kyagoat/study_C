#include <fcntl.h>  // For 'open'
#include <unistd.h> // For 'write'
#include <string.h> // For 'strlen'
#include <stdio.h>  // For 'snprintf'

int main(int argc, char const *argv[]){

    int fd = open("gradientPPM.ppm", O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR);

    char* en_tete = "P3\n200 100\n";

    write(fd, en_tete, strlen(en_tete));

    char buf[255];
    int red, green, blue;

    red = 0;
    green = 0;
    blue = 255;

    snprintf(buf, 255, "%ld \n", sizeof(buf));
    write(fd, buf, strlen(buf));


    for(int i=0; i<=200; i++){
        for(int j=0; j<=100; j++){
            snprintf(buf, 255, "%d %d %d ", red, green, blue);
            write(fd, buf, strlen(buf));
        }
        blue-=1;
    }

    write(fd, "\n", 1);

    close(fd); // close the file to free resources

    return 0;
}