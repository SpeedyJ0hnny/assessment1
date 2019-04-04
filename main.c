#include <stdio.h>
#include <stdlib.h>

void rotCyph(char *array, int key,int size, int choice);
void makeFiles(void);

int main(){
    int size = 400;
    char preDecrypt[size];
    int key;
    int choice;
    int alreadyWritten;

    printf("Is read.txt already populated with text? (0/1)\n");
    scanf("%d",&alreadyWritten);
        if (alreadyWritten==0){
            makeFiles();
            printf("Please write text to read.txt and save it. Press enter when done.\n");
            getchar(); getchar();
        }
    printf("Would you like to encrypt or decrypt? (0/1)\n");
    scanf("%d",&choice);
    printf("Please select a key value:\n");
    scanf("%d",&key);

        for (int zeros=0;zeros<size;zeros++){
            preDecrypt[zeros]=0;
        }
    FILE *read;
    FILE *write;
    read = fopen("read.txt","r");
    write = fopen("write.txt", "w");

    fgets(preDecrypt, size, (FILE *)read);
    rotCyph(preDecrypt, key, size, choice);
    fprintf(write, "%s\n", preDecrypt);
}
void makeFiles(void){
    FILE *read;
    FILE *write;
    read = fopen("read.txt","w");
    write = fopen("write.txt","w");
    fclose(read);
    fclose(write);
}
void rotCyph(char *array, int key, int size, int choice){
    for (int x=0;x<size;x++){
        if (choice == 1){
            if (array[x]>=97&&array[x]<=122){
                array[x]=array[x]-32;
            }
            if (array[x]>=65&&array[x]<=90){
                for (int a=0;a<(key%26);a++){
                    array[x]--;
                    if (array[x]<65){
                    array[x]=90;
                    }
                }
            }

        }

        else if (choice == 0){
            if (array[x]>=97&&array[x]<=122){
                array[x]=array[x]-32;
            }
            if (array[x]>=65&&array[x]<=90){
                for (int a=0;a<(key%26);a++){
                    array[x]++;
                        if (array[x]>90){
                            array[x]=65;
                        }
                }
            }

        }

    }
}

