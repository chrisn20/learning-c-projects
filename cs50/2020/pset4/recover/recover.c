#include <stdio.h>
#include <stdlib.h>

int check_jpg(unsigned char *buffer);

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover <file>\n");
        return 1;
    }

    // Open File
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Keep reading 512 bytes until end of card
    unsigned char buffer[512];
    int read_bytes = 0, is_jpg = 0, num_jpgs = 0, count = 0;
    char *filename = malloc(sizeof("%03i.jpg"));

    do
    {
        read_bytes = fread(buffer, 1, 512, file);
        count ++;
        if (check_jpg(buffer) == 1)
        {
            sprintf(filename, "%03i.jpg", num_jpgs);
            FILE *img = fopen(filename, "w");
            do
            {
                fwrite(buffer, 1, 512, img);
                read_bytes = fread(buffer, 1, 512, file);
                if (read_bytes != 512)
                {
                    break;
                }
            }
            while (check_jpg(buffer) != 1);

            num_jpgs ++;
            fclose(img);

            //printf("File is at position %li\n", ftell(file));
            fseek(file, -512, SEEK_CUR);
            //printf("File is now at position %li\n", ftell(file));
        }
    }
    while (read_bytes == 512);
    // printf("Reached end of card. Looped %i times, found %i jpegs\n", count, num_jpgs);

    // Clean up
    fclose(file);
    //fclose(img);
    free(filename);

}

int check_jpg(unsigned char *buffer)
{


    // Check first four bytes of buffer
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

