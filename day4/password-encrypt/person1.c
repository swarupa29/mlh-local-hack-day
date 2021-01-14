#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
/*TO MIMIC THE RSA ALGORITHM  THE PUBLIC KEY AND THE ENCRYPTED PASSWORD HAVE 
BEEN WRITTEN AND READ INTO 2 LOCAL FILES*/
//THE BASIC ENCRYPTION OF THE PASSWORD IS USING CEASER CIPHER AND ITS KEY IS ENCRYPTED USING RSA

FILE *fp;
char mes[100];
double n,e;
int main()
{
    int ch,i;
    printf("PERSON 1- WANTS TO ENCRYPT PASSWORD\n");
    printf("Waiting for public key\nenter 1 to continue  \n");
    scanf("%d",&ch);
    // program starts only when the public key is got
    if(ch==1)
    {
         // getting the password to be encrypted
        printf("Enter message to be encrypted\n");
                    while(mes[i]!='\n')
            {
                scanf("%c",&mes[i]);
                i++;
                if(i>1&&mes[i-1]=='\n')
                {
                    break;
                }
             }
            mes[i]='\0';


        //to generate a random number from 1 to 26
        srand(time(0));
        int key=(rand()%(25));
       // printf("key is %d\n",key);

        // to encrypt the password.
        //shifting letters according to the key
        int i,as;
        for(i=0;mes[i]!='\0';i++)
    {
        as=mes[i];
         if(as>=97&&as<=122)
       {
           as=as+key;
           if(as>122)
           {
               as=as-26;
           }
       }
       else if(as>=65 && as<=90)
       {
           as=as+key;
           if(as>90)
           {
               as=as-26;
           }
       }

       mes[i]=as;

    }
    //printf("Encrypted password:  %s\n",mes);

    // START OF RSA ALGORITHIM FOR EXCHANGE OF PASSWORD FROM ONE PLACE TO ANOTHER
    // obtaining the value of public key from file which the target writes into.

    fp=fopen("./key1.txt","r");
    fscanf(fp,"%lf",&n);
    printf("public key: %lf\n",n);
    // to get the value of e
    char s[256];
    int k=0;
    while(fgets(s,sizeof(s),fp))
    {
        k++;
        if(k==2)
        {
            printf("%s\n",s);
            e=atoi(s);
            printf("e value: %lf\n",e);
        }
    }
    fclose(fp);


    //encrypting the cipher key using public key
    // encrypted key= key^e mod(n)
    double enc_key=fmod(pow(key,e),n);
    printf("Encrypted key:  %lf",enc_key);

    // writing this encrypted key into a file. to be read by target
    fp=fopen("./key.txt","w");
    fprintf(fp,"%lf",enc_key);
    fclose(fp);

    // writing the encrypted password into a different file
    fp=fopen("./password.txt","w");
    fprintf(fp,"%s",mes);
    fclose(fp);
    }
}
