#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Checks for correct user input
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Opens the image file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open raw file.\n");
        return 2;
    }

    typedef uint8_t BYTE;
    // Initialize buffer
    BYTE buffer[BLOCK_SIZE];
    // Inititalize img pointer
    FILE *img;
    // Makes a filename array of characters
    char filename[8];
    // Keeps track of what file number the loop is on
    int filename_number = 0;
    // Keeps track of whether a file is already open, 0 means no and 1 means yes
    int x = 0;
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // If a file has already been opened (x = 1) and the current buffer shows
        // the start of a new jpeg close the previous img pointer and decrement x by one
        // to signify this and increase the file number by one
        if (x == 1 && buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255)
        {
            fclose(img);
            x--;
            filename_number++;
        }
        // If a file has already been opened (x = 1) and the current buffer
        // does not show the start of a new jpeg then write the current
        // buffer to the file that is open
        else if (x == 1)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
        // If a file is not already opended (x = 0) then open a new file and name it the current
        // file number and increment x by one to signify the opening of a new file
        if (x == 0 && buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255)
        {
            // Prints a string of format %03i.jpg to the char array filename with the current
            // file number as i
            sprintf(filename, "%03i.jpg", filename_number);
            img = fopen(filename, "wb");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            x++;
        }
    }
    // Closes the raw file and the img pointer
    fclose(raw_file);
    fclose(img);
}