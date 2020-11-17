#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ACTUAL_MEMO ((const char *)"/home/oem/.config/i3/resources/scripts/statusBar/keep/statusBarMessage.dat")
#define OLDS_MEMO ((const char *)"/home/oem/.config/i3/resources/scripts/statusBar/keep/olds.dat")
#define BUFFER 49
const char *arguments[5] = { "-h", "--help", "--ip", "--list", "--new" };
const int argcMax = 5;

int saveInOld(const char messagePassed[])
{
	char message[BUFFER];
	for (int i = 0; i < 49; ++i)
	{
		if(messagePassed[i] != '\0')
		{
			message[i] = messagePassed[i];
		}
		else
		{
			message[i] = '\0';
		}
	}
	FILE *fic = fopen(OLDS_MEMO, "a");
	if (fic == NULL)
	{
		printf("ERROR: can't generate file: \n");
		return 0;
	}

	for(int i = 0; i < 49; i++)
	{
		if(message[i] != '\0')
		{
			fputc(message[i], fic);
		}
		else
		{
			fputc(' ', fic);
		}
	}
	printf("The message: %s, has sucessfully been registered\n", message);
	fputc('\n', fic);
	fclose(fic);
	return 1;
}

int printOld() 
{
	int unSurDeux = 0;
	int line = 1;
	char lettre;
	FILE *fic = fopen(OLDS_MEMO, "r");
	if (fic == NULL)
	{
		printf("ERROR: can't open file: \n");
		return 0;
	}
	printf("%d: ", line);
	while((lettre = fgetc(fic)) != EOF)
	{		
		if (lettre == '\n')
		{
			line++;
			if (unSurDeux)
			{
				putchar(lettre);
				printf("%d: ", line);
				unSurDeux = 0;

			}
			else
			{
				printf("	|	%d: ", line);
				unSurDeux = 1;
			}
		}
		else
		{
			putchar(lettre);
		}
	}
	printf("[blank]\n");
	fclose(fic);
	return 1;
}



int showIp()
{
    printf("montrera l'ip un jour\n");
    return 1;
}

int showHelp()
{
    printf("\nmissing arguments\nYou may try\n -h or --help: to show this page BtW.\n --list: to list ur old custom messages and mabe reuse them\n --ip: to print ur IP as a memo\n --new: to create a brand new custom message as memo\n");
    return 1;
} 


int newMessage()
{  

    char result1, result2;
    printf("are u sure to change it ? (Y/n)\n");
    scanf("%c", &result1);
    if (result1 == 'Y')
    {
        remove(ACTUAL_MEMO);		//forced to remove the file instead to modify it to not have a conky failure
        char message[BUFFER];
        for (int i = 0; i < BUFFER; ++i)
        {
        	message[i] = '\0';
        }
        printf("enter message then press enter:         (Max is 48 including spaces)\n");
        scanf("\n%[^\n]", message);

        FILE *fp = fopen(ACTUAL_MEMO, "w");
        if(fp == NULL)
        {
            printf("oups\n");
            exit(1);
        }

        fprintf(fp, "%s", message);
        fclose(fp);
        printf("New message has been saved sucessfully\nDid you want to save it [Y/n]: ");
        scanf("\n%c", &result2);
        if (result2 == 'Y')
        {
        	printf("%s\n", message);
        	saveInOld(message);
        }
        return 1;
    }
    printf("Error: failed to generate the keep\n");
    return 0;
}

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            for (int j = 0; j < argcMax; ++j)
            {
                if(strcmp(argv[i], arguments[j]) == 0)
                    {
                    switch (j)
                    {
                        case 0:      showHelp();          break;
                        case 1:      showHelp();          break;
                        case 2:      showIp();            break;
                        case 3:      printOld();		  break;
                        case 4:      newMessage();        break;            
                        default:          
                        break;
                    }
                }
            }
        }
    }
    else
    {   
        printf("error no arguments, may this help\n");
        showHelp();
    }

    return 1;
}