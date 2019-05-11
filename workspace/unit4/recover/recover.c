//Layout of program:
//open memory card file
//find beginning of JPEG file
//open a new JPEG file
//write 512 bytes until new JPEG ins found
//detect end of file

 #include <stdint.h>
 #include <stdio.h>

 const int BLOCK_SIZE = 512; //const cannot change value

 int main(int argc, char *agrv[])
 {
    FILE *f;

    if ((f = fopen("card.raw", "r")) == NULL)
    {
        return 1;
    }

    uint8_t contents[512];

    int iterate = 0;
    FILE *temp = NULL;

    while (fread(contents, BLOCK_SIZE, 1, f))
    {

        if (contents[0] == 0xff && contents[1] == 0xd8 && contents[2] == 0xff && (contents[3] == 0xe1 || contents[3] == 0xe0))
        {
            if (temp != NULL)
                fclose(temp);

            char filename[8];
            sprintf(filename, "%03d.jpg", iterate);

            temp = fopen(filename, "w");
            iterate++;
        }

        if (temp != NULL)
            fwrite(contents, BLOCK_SIZE, 1, temp);
    }

    if (temp != NULL)
	{
        fclose(temp);
	}
    fclose(f);
}