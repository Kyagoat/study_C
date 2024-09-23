#include <fcntl.h>  // For 'open'
#include <unistd.h> // For 'write'
#include <string.h> // For 'strlen'
#include <stdio.h>  // For 'snprintf'

int main(int argc, char const *argv[])
{
    int fd = open("firstPPM.ppm", O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR);

    char* en_tete = "P3\n3 2\n";

    write(fd, en_tete, strlen(en_tete));

    char buf[255];
    int red, green, blue;

    red = 255;
    green = 0;
    blue = 0;

    snprintf(buf, 255, "%ld \n", sizeof(buf));
    write(fd, buf, strlen(buf));

    snprintf(buf, 255, "%d %d %d ", red, green, blue); // put ints in buf
    write(fd, buf, strlen(buf)); // Write buf to file

    red = 0;
    green = 255;
    blue = 0;

    snprintf(buf, 255, "%d %d %d ", red, green, blue);
    write(fd, buf, strlen(buf));

    red = 0;
    green = 0;
    blue = 255;

    snprintf(buf, 255, "%d %d %d\n", red, green, blue);
    write(fd, buf, strlen(buf));

    red = 255;
    green = 255;
    blue = 0;

    snprintf(buf, 255, "%d %d %d ", red, green, blue);
    write(fd, buf, strlen(buf));

    red = 255;
    green = 255;
    blue = 255;

    snprintf(buf, 255, "%d %d %d ", red, green, blue);
    write(fd, buf, strlen(buf));

    red = 0;
    green = 0;
    blue = 0;

    snprintf(buf, 255, "%d %d %d", red, green, blue);
    write(fd, buf, strlen(buf));


    write(fd, "\n", 1);

    close(fd); // close the file to free resources

    return 0;
}
