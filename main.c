#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void rotCyph(char *array, int key,int size, int choice);
void makeFiles(void);
void subCyph(char *array, char *keyStr, int size, int choice);
void forceRot(char *array, int size);

int main(){
    int size = 400;
    char preDecrypt[size];
    int key;
    char keyStr[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int choice, specific,force=1;
    int alreadyWritten;

    printf("Is read.txt already populated with the text to be encrypted/decrypted? \n(0/1)\n");
    scanf("%d",&alreadyWritten);

        if (alreadyWritten==0){
            makeFiles();
            printf("Please write text to read.txt and save it. Press enter when done.\n");
            getchar(); getchar();
        }

    printf("Would you like to encrypt or decrypt?\n(0/1)\n");
    scanf("%d",&choice);
    printf("Substitution or Rotation?\n(0/1)\n");
    scanf("%d",&specific);
    if (choice==1){
        printf("Do you have the key? (0/1)\n");
        scanf("%d",&force);
    }

    if (specific==1&&force==1){
        printf("Please select a key value for rotation:\n");
        scanf("%d",&key);
    }
    /*if (specific==0){
        printf("Please type key for substition:\n");
        scanf("%s",keyStr);
    }*/

        for (int zeros=0;zeros<size;zeros++){
            preDecrypt[zeros]=0;
            }

    FILE *read;
    FILE *write;
    read = fopen("read.txt","r");
    write = fopen("write.txt", "w");

    fgets(preDecrypt, size, (FILE *)read);
        if (specific==1&&force==1){
        rotCyph(preDecrypt, key, size, choice);
        }
        if (specific==0&&force==1){
        subCyph(preDecrypt, keyStr, size, choice);
        }
        if (specific==1&&force==0){
        forceRot(preDecrypt, size);
            fgets(preDecrypt, size, (FILE*)read);
            printf("Which Line contained the correct string?\n");
            scanf("%d",&key);
            rotCyph(preDecrypt,key,size,1);
            printf("%s \nWritten to file.\n",preDecrypt);
        }
    fprintf(write, "%s\n", preDecrypt);
    printf("%s\n", preDecrypt);
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



void subCyph(char *array, char *keyStr, int size, int choice){
    int keyDistance;
        for (int x=0;x<size;x++){
            if (choice==0){
                if (array[x]>=97&&array[x]<=122){
                    array[x]=array[x]-32;
                }
                if (array[x]>=65&&array[x]<=90){
                    keyDistance=array[x]-65;
                    array[x]=keyStr[keyDistance];
                    }
                }
            if (choice==1){
                if (array[x]>=97&&array[x]<=122){
                    array[x]=array[x]-32;
                }
                if (array[x]>=65&&array[x]<=90){
                    keyDistance=0;
                    while (array[x]!=keyStr[keyDistance]){
                        keyDistance++;
                    }
                    array[x]=keyDistance+65;
                }
            }
        }


}



void forceRot (char *array, int size){
    for (int count=1;count<27;count++){
        for (int x=0; x<size;x++){
            if (array[x]>=97&&array[x]<=122){
                array[x]=array[x]-32;
            }
            if (array[x]>=65&&array[x]<=90){
                for (int a=0;a<1;a++){
                    array[x]--;
                        if (array[x]<65){
                            array[x]=90;
                        }
                }
            }
        }
    //compare to dictionary, find match
    printf("Key || String\n  %d: %s\n",count,array);
    sleep(1);
    }
}

