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

    // Create buffer for header
    uint8_t header[HEADER_SIZE];
    // Read header into buffer
    fread(&header, sizeof(uint8_t), HEADER_SIZE, input);
    // Transfer header from buffer to output
    fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    for (;;)
    {
        // Create new buffer for sample
        int16_t sample;
        // Read sample into buffer from input file
        size_t amtRead = fread(&sample, sizeof(sample), 1, input);
        // If nothing read, we are at the end of the file
        if (amtRead == 0)
        {
            // Break out of infinite loop
            break;
        }
        // Multiply sample by factor
        sample *= factor;
        // Write new sample to output file
        fwrite(&sample, sizeof(sample), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}