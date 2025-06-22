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

    // Copy header from input file to output file
    char *header_buffer = malloc(HEADER_SIZE);
    if (header_buffer == NULL) {
        printf("memory error\n");
        return 1;

    }    
    if (fread(header_buffer, 1, HEADER_SIZE, input) < HEADER_SIZE) {
        printf("Error reading file header.\n");
        return 1;
    }
    if (fwrite(header_buffer, 1, HEADER_SIZE, output) < HEADER_SIZE) {
        printf("Error writing file header.\n");
        return 1;
    }    

    // TODO: Read samples from input file and write updated data to output file
    short sample_buffer;
    while(fread(&sample_buffer, sizeof(short), 1, input) != 0) {
        sample_buffer *= factor;
        if(fwrite(&sample_buffer, sizeof(short), 1, output) < 1) {
            printf("Error writing to file.\n");
            return 1;
        }
    }

    // Close files
    fclose(input);
    fclose(output);

    //free memory
    free(header_buffer);
}
