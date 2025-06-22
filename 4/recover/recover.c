#include <stdio.h>
#include <stdlib.h>

int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    FILE *card = NULL;
    FILE *new_jpg = NULL;

    int images_found = 0;

    if (argc != 2) {
        printf("Usage: ./recover <file>\n");
        return 1;
    }

    card = fopen(argv[1], "r");
    if (card == NULL) {
        printf("Error opening file\n");
        return 1;
    }    

    //read through card
    unsigned char buffer[BLOCK_SIZE];
    while (fread(buffer, sizeof(unsigned char), BLOCK_SIZE, card) == BLOCK_SIZE) {        
        
        //check for start of jpg
        unsigned char fourth_byte_masked_MSBs = buffer[3] & 0xf0;
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && fourth_byte_masked_MSBs == 0xe0) {
            //close any opened file
            if (new_jpg != NULL) {
                fclose(new_jpg);
            }
            //open new jpg
            char file_name[8];
            sprintf(file_name, "%03d.jpg", images_found++);            
            new_jpg = fopen(file_name, "w");
            
            if (new_jpg == NULL) {
                printf("Error opening new JPEG\n");
                return 1;
            }           
        }
        //skip to next block if no current jpg found
        if (new_jpg == NULL) {
            continue;
        }
        //write data to new jpg
        if (fwrite(&buffer, sizeof(unsigned char), BLOCK_SIZE, new_jpg) != BLOCK_SIZE) {
            printf("Error writing to file\n");
            return 1;
        }
    }

    fclose(card);
    fclose(new_jpg);
 
}