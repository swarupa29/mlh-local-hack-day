#include<stdio.h>
#include<stdlib.h>
#include<math.h>
FILE *fp;
// two random values of p,q
double p=73, q=11;
double k=2;
int e=2;

//

//to find gcd of two numbers (to check if e is co-prime with phi)
int gcd(int a, int b)
{
    int temp;
    while(1)
    {
        temp=a%b;
        if(temp==0)
        {
            return b;
        }
        a=b;
        b=temp;
    }
}

int main()
{   double n=p*q, phi=(p-1)*(q-1);
// to find the value of e satisfying the condition :e is chosen such that e is co-prime with phi and 1<e<phi
     while(e<phi)
     {
         if(gcd(e,phi)==1)
            break;
         else e++;
     }
     //printf("e  %d\n",e);
    double key,dec_key;
    double d;int c;
    printf("PERSON 2- RECIEVES THE ENCRYPTED MESSAGE AND DECRYPTS IT\n");

    //writing the public key
    fp=fopen("./key1.txt","w");
    fprintf(fp,"%lf\n",n);
    fprintf(fp,"%d",e);

    fclose(fp);
    //program continues only when the encrypted key and password is obtained
    printf("waiting for encrypted message and key\npress 1 when obtained");
    scanf("%d",&c);
    if(c==1)
    {
        // calculating d(private key) by using e*d= 1 mod(phi)
        int j=1,check=1;double no;
        while(check!=0)
    {
        no=(phi*j)+1;
        if(fmod(no,e)==0)
        {check=0;}
        j++;
    }
    d=no/e;
   // printf("%lf",d);

   //obtaining the encrypted key
        fp=fopen("./key.txt","r");
        fscanf(fp,"%lf",&dec_key);
        printf("Encrypted key :  %lf\n",dec_key);
        fclose(fp);

        //obtaining the encrypted text
        fp=fopen("./password.txt","r");
        char mes[100];int g;
        while(mes[g]!='\n')
            {
                fscanf(fp,"%c",&mes[g]);
                g++;
                if(g>1&&mes[g-1]=='\n')
                {
                    break;
                }
             }
            mes[g]='\0';
        fclose(fp);


        // decrypting the encrypted key using key= enc_key^d mod(n)
        key=fmod(pow(dec_key,d),n);
        printf("Decrypted key: %lf\n",key);

        //decrypting the password
        int i,as;
        for(i=0;mes[i]!='\0';i++)
    {
        as=mes[i];
         if(as>=97&&as<=122)
       {
           as=as-key;
           if(as<97)
           {
               as=as+26;
           }
       }
       else if(as>=65 && as<=90)
       {
           as=as-key;
           if(as<65)
           {
               as=as+26;
           }
       }

       mes[i]=as;



    }
printf("Decrypted password:  %s",mes);
    }
}
