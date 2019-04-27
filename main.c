#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

/*
 * prototype of all functions used. The rotation cypher takes the array, key, size, and a variable called "Choice", which is wether the user wants
 * encryption or decryption. these functions all return void since they modify the array, with the exception of the makeFiles function, which
 * makes the read/write files for the message to be placed in.
 */


void rotCyph(char *array, int key,int size, int choice);
void makeFiles(void);
void subCyph(char *array, char *keyStr, int size, int choice);
void forceRot(char *array, int size); //doesn't take the key or the choice, since it is always a decryption, and there is no key since it is forced.
void forceSub(char *array, int size, char *dictionaryArr); //same as forceRot, except it needs a dictionary for a comparison.

/*
 * The main function, where all decisions are implemented and all functions are called. This is where the c program runs from.
 */


int main(){
    int size = 4000; //arbitrary length. Needs to DEFINITELY be larger than message, since this is how many characters will be changed.
    int wordsLength = 721; //length of the dictionary text which is being used.
    char preDecrypt[size]; //this is the array which contains the message to be encoded or decoded. Not declared yet as it is to be read in from a file.
    char DictionaryArr[wordsLength]; //this is where the dictionary will be stored in the program.
    int key; //not declared as this is read in by the user. This variable determines how many "rotations" are performed, or how far a letter will be from its original position.
    char keyStr[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int choice, specific,force=1; //choice and specific determine wether it will be encryption or decryption, and specific is rotation or substitution.
                                  //force is initialised to 1 since it is assumed they have the key. if they don't that can easily be changed further down.
    int alreadyWritten; //another variable used for logic. used to decide wether new files should be created.

    printf("Is read.txt already populated with the text to be encrypted/decrypted? \n(0/1)\n");
    scanf("%d",&alreadyWritten); //first set of logic implemented. 

        if (alreadyWritten==0){ //makes the files if they aren't there. If they are, this is stepped over as otherwise the file would be overwritten.
            makeFiles(); //this is the function which creates the files.
            printf("Please write text to read.txt and save it. Press enter when done.\n"); //guides the user to act as the program expects.
            getchar(); getchar(); //waits for the user to press enter before continuing.
        }

    printf("Would you like to encrypt or decrypt?\n(0/1)\n"); //More directions so program can perform the task that the user wants it to.
    scanf("%d",&choice); //variable used to decide which function to execute.
    printf("Substitution or Rotation?\n(0/1)\n"); 
    scanf("%d",&specific); //variable used to decide which part of the function executes.
    if (choice==1){ //only executes if the user wants decryption.
        printf("Do you have the key? (0/1)\n"); //needed so the program knows wether or not it has to force the decryption.
        scanf("%d",&force);
    }

    if (specific==1&&force==1){ //only needs to run if the user wants a rotation cipher with the key. also used for decryption which is why force is initialised.
        printf("Please select a key value for rotation:\n");
        scanf("%d",&key);
    }
    if (specific==0&&force==1){ //same as rotation above except for substitution.
        printf("Please type key for substition (Capital letters only):\n");
        scanf("%s",keyStr);
    }

        for (int zeros=0;zeros<size;zeros++){
            preDecrypt[zeros]=0; //for loop which sets every value of the array to zero. goes from 0 - (size-1) because that is how arrays are indexed.
            }
/*
 * opens the files to be used. needs two strings, the path to the file and the "argument" which dictates how the file will be modified.
 * r is for reading the file, used for the dictionary and original text, and w is for writing. Overwrites any previous data in the file.
 */
    FILE *read; //pointers to the files
    FILE *write;
    read = fopen("read.txt","r");
    write = fopen("write.txt", "w");

    fgets(preDecrypt, size, (FILE *)read); //stores the data from the "read" file in the string preDecrypt.
        if (specific==1&&force==1){ //menu for the user, IF statements used instead of switch case because there are 2 variables to be evaluated.
        rotCyph(preDecrypt, key, size, choice); //sends 4 arguments to the rotCyph function. needs choice to either encrypt or decrypt.
        }
        if (specific==0&&force==1){
        subCyph(preDecrypt, keyStr, size, choice); //this function and the one above does encryption and decryption with a key of both types of ciphers.
        }
        if (specific==1&&force==0){
        forceRot(preDecrypt, size); //doesnt need key or choice, since it is a DECRYPTION with NO KEY
            fgets(preDecrypt, size, (FILE*)read); //this stores the original message in the string, since the string was modified by the program. ensures correct decryption after key is found.
            printf("Which Line contained the correct string?\n");
            scanf("%d",&key); //key is now known by user.
            rotCyph(preDecrypt,key,size,1); //choice is to decrypt, so can be hard coded.
            printf("%s \nWritten to file.\n",preDecrypt); //informs user that the string was copied to the file.
        }
        if (specific==0&&force==0){
        forceSub(preDecrypt, size, DictionaryArr);//needs the ditionary for word comparison.
        }
    fprintf(write, "%s\n", preDecrypt); //writes the string to the file.
    printf("%s\n", preDecrypt); //prints the string to the console.
}

/*
 * Function which makes the files. Only run if files do not exist since "w" overwrites any existing data. both files accessed as "w" since this will create file
 * if it doesn't already exist, and will overwrite data if it does.
 */

void makeFiles(void){
    FILE *read;
    FILE *write;
    read = fopen("read.txt","w");
    write = fopen("write.txt","w");
    fclose(read); //closes both files since they are no longer needed.
    fclose(write);
}

/*
 * following function does encryption and decryption of a message using a rotation cypher and a key.
 */

void rotCyph(char *array, int key, int size, int choice){
    for (int x=0;x<size;x++){ //FOR loop starts at zero since that array[0] is the first element of the array.
        if (choice == 1){ //decryption.
            if (array[x]>=97&&array[x]<=122){
                array[x]=array[x]-32; //if the values are between the bounds of lowercase ASCII letters, they are capitalised.
            }
            if (array[x]>=65&&array[x]<=90){ //IF statement so that only the letters are modified. Punctuation and symbols stay the same.
                for (int a=0;a<(key%26);a++){ //loop that depends on the value of the key as to how many times it is run.
                    array[x]--; //decremented since encryption is incremented. Gets back original message. Each position is decremented a set amount depending on key value.
                    if (array[x]<65){ //if the value of the letter is below any letters, it loops around to the highest letter, ie A-1 becomes Z, so it is cyclic.
                    array[x]=90;
                    }
                }
            }

        }

        else if (choice == 0){
            if (array[x]>=97&&array[x]<=122){
                array[x]=array[x]-32;//if the values are between the bounds of lowercase ASCII letters, they are capitalised.
            }
            if (array[x]>=65&&array[x]<=90){//IF statement so that only the letters are modified. Punctuation and symbols stay the same.
                for (int a=0;a<(key%26);a++){//loop that depends on the value of the key as to how many times it is run.
                    array[x]++; //incremented a set amount for each element of the array, to implement a rotation cypher.
                        if (array[x]>90){//if the value exceeds the maximum value for an ASCII letter,
                            array[x]=65;//the value is set to the lowest for that letter.
                        }
                }
            }

        }

    }
}

/*
 * performs encryption and decryption of a substitution cipher, given a key.
 */

void subCyph(char *array, char *keyStr, int size, int choice){
    int keyDistance; //not initialised since it is assigned a value later.
        for (int x=0;x<size;x++){ //loop that acts on every element of the array
            if (choice==0){ //encryption
                if (array[x]>=97&&array[x]<=122){
                    array[x]=array[x]-32;//if the values are between the bounds of lowercase ASCII letters, they are capitalised.
                }
                if (array[x]>=65&&array[x]<=90){//IF statement so that only the letters are modified. Punctuation and symbols stay the same.
                    keyDistance=array[x]-65; //variable which determines how far along the array to look for the new letter, ie A is in position 0, B=1 etc.
                    array[x]=keyStr[keyDistance]; //assigns the string a new value to encrypt it, depends on what letter is at that position on the string.
                    }
                }
            if (choice==1){ //decryption
                if (array[x]>=97&&array[x]<=122){
                    array[x]=array[x]-32;//if the values are between the bounds of lowercase ASCII letters, they are capitalised.
                }
                if (array[x]>=65&&array[x]<=90){//IF statement so that only the letters are modified. Punctuation and symbols stay the same.
                    keyDistance=0; //needs to be zero, so it is incremented until a match is found.
                    while (array[x]!=keyStr[keyDistance]){ //while loop since endpoint is not known.
                        keyDistance++; //incremented because substitution cypher relies on position of letter in string.
                    }
                    array[x]=keyDistance+65; //opposite of encryption, finds original letter.
                }
            }
        }


}

/*
 * decrypts rotation cipher with no key.
 */

void forceRot (char *array, int size){
    for (int count=1;count<27;count++){ //for loop starts at 1, and stops at 26, since each number corresponds to how many rotations have been performed.
        for (int x=0; x<size;x++){ //loop that acts on every element of the array so needs to start at 0.
            if (array[x]>=97&&array[x]<=122){
                array[x]=array[x]-32;//if the values are between the bounds of lowercase ASCII letters, they are capitalised.
            }
            if (array[x]>=65&&array[x]<=90){//IF statement so that only the letters are modified. Punctuation and symbols stay the same.
                for (int a=0;a<1;a++){
                    array[x]--; //decrements every value of the array by 1, 26 times to check all possible rotations.
                        if (array[x]<65){
                            array[x]=90; //ensures the only result of decrementing is letters, loops the values.
                        }
                }
            }
        }
    printf("Key || String\n  %d: %s\n",count,array); //prints in a readable format to easily find key.
    sleep(1); //gives the user time to read each line. need to #include <unistd.h>, sleeps for 1 second.
    }
}

/*
 * decrypts substitution cipher with no key.
 */

void forceSub(char *array, int size, char *dictionaryArr){
    printf("Not Implemented :(\n");
}
