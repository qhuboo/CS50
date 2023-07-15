// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44; 

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {   
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }   

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {   
        printf("Could not open file.\n");
        return 1;
    }   

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {   
        printf("Could not open file.\n");
        return 1;
    }   

    float factor = atof(argv[3]);

	// Calculate number of bytes of the samples
    int bytes, sample_bytes, final_bytes;
    for (bytes = 0; getc(input) != EOF; bytes++);
	sample_bytes = (bytes - HEADER_SIZE) / sizeof(int16_t);

	// Creates buffer and reads into it from the input file
    uint8_t buffer[bytes];
	int16_t samples[sample_bytes];
    fseek(input, 0, SEEK_SET);
    fread(buffer, sizeof(uint8_t), HEADER_SIZE, input);
	fread(samples, sizeof(int16_t), sample_bytes, input);
	
	// Multiplies samples from the buffer by the factor
    for (int i = 0; i < sample_bytes; i++)
    {   
        samples[i] *= factor; 
    }   

	// Writes the buffer to the output file
    fwrite(buffer, sizeof(uint8_t), HEADER_SIZE, output);
  	fwrite(samples, sizeof(int16_t), sample_bytes, output);
	
    // Close files
    fclose(input);
    fclose(output);
}
