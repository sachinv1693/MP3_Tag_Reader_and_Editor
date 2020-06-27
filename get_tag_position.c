#include "main.h"

long get_tag_position(const char* tag_name)
{
	//We know that all ouer tags are 4 byte long + 1 NUL byte in the end
	char get_tag[5];
        get_tag[4] = '\0';
        long seek_from = 0;//Position of tag in the file initially at 0
        fseek(mp3_fptr, 0L, SEEK_SET);//Get back to the beginning of the file
        seek_from = ftell(mp3_fptr);
        while (ftell(mp3_fptr) != eof - 3)//Search till it's 3 bytes short of eof
        {
                fread(get_tag, 4, 1, mp3_fptr);
                if (!strcmp(get_tag, tag_name))
                {
                        //printf("TAG Found!\n");
                        break;
                }
                fseek(mp3_fptr, -3L, SEEK_CUR);//Find from next consecutive byte
                seek_from++;//Increment seek count
        }
        if (seek_from == eof - 3)
        {
                //printf("TAG not found!!\n");//Reaching to the eof, TAG not found
		return -1;
        }
	//printf("Seek from = %ld\n", seek_from);
	return seek_from;
}

