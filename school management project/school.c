#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Function prototypes
int password();
void addrecord();
void viewrecord();
void editrecord();
void editpassword();
void deleterecord();

// Portable function to clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Portable clear screen function (prints newlines)
void clear_screen() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// Portable password input function
int password()
{
    char pass[15]={0}, check[15]={0};
    FILE *fpp;
    int i, j;
    
    printf("::FOR SECURITY PURPOSE::");
    printf("::ONLY THREE TRIALS ARE ALLOWED::");
    
    for(j=0; j<3; j++)
    {
        printf("\n\n\tENTER THE PASSWORD:");
        
        if (fgets(pass, sizeof(pass), stdin) == NULL) {
            printf("\nInput error.\n");
            return 1;
        }
        pass[strcspn(pass, "\n")] = 0;
        
        fpp=fopen("SE","r");
        
        if (fpp==NULL)
        {
            printf("\nERROR WITH THE SYSTEM FILE...[FILE MISSING]\n");
            printf("\nPRESS ENTER TO CONTINUE...");
            getchar();
            return 1;
        }
        
        i=0;
        int ch_val;
        while((ch_val = fgetc(fpp)) != EOF)
        {
            check[i] = ch_val - 5;
            i++;
        }
        check[i] = '\0';
        
        fclose(fpp);
        
        if(strcmp(pass, check)==0)
        {
            printf("\n\n\tACCESS GRANTED...\n");
            return 0;
        }
        else
        {
            printf("\n\n\tWRONG PASSWORD..\n\n\tACCESS DENIED...\n");
        }
    }
    
    printf("\n\n\t::YOU ENTERED WRONG PASSWORD::YOU ARE NOT ALLOWED TO ACCESS ANY FILE::\n\n\tPRESS ENTER TO GO BACK...");
    getchar();
    return 1;
}

struct record
{
    char time[6];
    char name[30];
    char place[25];
    char duration[10];
    char note[500];
} ;

int main()
{
    int ch;
    printf("\n\n\t***********************************\n");
    printf("\t*PASSWORD PROTECTED PERSONAL DIARY*\n");
    printf("\t***********************************");

    while(1)
    {
        printf("\n\n\t\tMAIN MENU:");
        printf("\n\n\tADD RECORD\t[1]");
        printf("\n\tVIEW RECORD\t[2]");
        printf("\n\tEDIT RECORD\t[3]");
        printf("\n\tDELETE RECORD\t[4]");
        printf("\n\tEDIT PASSWORD\t[5]");
        printf("\n\tEXIT\t\t[6]");
        printf("\n\n\tENTER YOUR CHOICE:");
        
        if (scanf("%d", &ch) != 1) {
            clear_input_buffer();
            ch = 0;
        } else {
            clear_input_buffer();
        }

        switch(ch)
        {
            case 1:
                addrecord();
                break;
            case 2:
                viewrecord();
                break;
            case 3:
                editrecord();
                break;
            case 4:
                deleterecord();
                break;
            case 5:
                editpassword();
                break;
            case 6:
                printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE BY:\n\n\tBIJAY PURI\n\n\tBHANU POUDEL\n\n\tNRIPASH AYER...");
                printf("\n\n\tPRESS ENTER TO EXIT...");
                getchar();
                exit(0);
            default:
                printf("\nYOU ENTERED WRONG CHOICE..");
                printf("\nPRESS ENTER TO TRY AGAIN");
                getchar();
                break;
        }
        clear_screen();
    }
    return 0;
}

void addrecord( )
{
    clear_screen();
    FILE *fp ;
    char another = 'Y';
    struct record e ;
    char filename[15];
    int choice;
    char time_input[10];
    
    printf("\n\n\t\t***************************\n");
    printf("\t\t* WELCOME TO THE ADD MENU *");
    printf("\n\t\t***************************\n\n");
    
    printf("\n\n\tENTER DATE OF YOUR RECORD:[yyyy-mm-dd]:");
    if (fgets(filename, sizeof(filename), stdin) == NULL) return;
    filename[strcspn(filename, "\n")] = 0;
    
    fp = fopen (filename, "ab+" ) ;
    
    if ( fp == NULL )
    {
        fp=fopen(filename,"wb+");
        if(fp==NULL)
        {
            printf("\nSYSTEM ERROR...");
            printf("\nPRESS ENTER TO EXIT");
            getchar();
            return ;
        }
    }
    
    while ( another == 'Y'|| another=='y' )
    {
        choice=0;
        
        printf ( "\n\tENTER TIME:[hh:mm]:");
        if (fgets(time_input, sizeof(time_input), stdin) == NULL) break;
        time_input[strcspn(time_input, "\n")] = 0;
        
        rewind(fp);
        
        while(fread(&e,sizeof(e),1,fp)==1)
        {
            if(strcmp(e.time,time_input)==0)
            {
                printf("\n\tTHE RECORD ALREADY EXISTS.\n");
                choice=1;
            }
        }
        
        if(choice==0)
        {
            strcpy(e.time,time_input);
            
            printf("\tENTER NAME:");
            if (fgets(e.name, sizeof(e.name), stdin) == NULL) break;
            e.name[strcspn(e.name, "\n")] = 0;
            
            printf("\tENTER PLACE:");
            if (fgets(e.place, sizeof(e.place), stdin) == NULL) break;
            e.place[strcspn(e.place, "\n")] = 0;
            
            printf("\tENTER DURATION:");
            if (fgets(e.duration, sizeof(e.duration), stdin) == NULL) break;
            e.duration[strcspn(e.duration, "\n")] = 0;
            
            printf("\tNOTE:");
            if (fgets(e.note, sizeof(e.note), stdin) == NULL) break;
            e.note[strcspn(e.note, "\n")] = 0;
            
            fwrite ( &e, sizeof ( e ), 1, fp ) ;
            
            printf("\nYOUR RECORD IS ADDED...\n");
        }
        
        printf ( "\n\tADD ANOTHER RECORD...(Y/N) " ) ;
        another = getchar( ) ;
        clear_input_buffer();
    }
    
    fclose ( fp ) ;
    
    printf("\n\n\tPRESS ENTER TO EXIT...");
    getchar();
}

void viewrecord( )
{
    FILE *fpte ;
    clear_screen();
    struct record customer ;
    char time_input[6], choice, filename[15];
    int ch;
    
    printf("\n\n\t\t*******************************\n");
    printf("\t\t* HERE IS THE VIEWING MENU *");
    printf("\n\t\t*******************************\n\n");
    
    choice=password();
    
    if(choice!=0)
    {
        return ;
    }
    
    do
    {
        printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]:");
        if (fgets(filename, sizeof(filename), stdin) == NULL) break;
        filename[strcspn(filename, "\n")] = 0;
        
        fpte = fopen ( filename, "rb" ) ;
        
        if ( fpte == NULL )
        {
            puts ( "\nTHE RECORD DOES NOT EXIST...\n" ) ;
            printf("PRESS ENTER TO EXIT...");
            getchar();
            return ;
        }
        
        clear_screen();
        printf("\n\tHOW WOULD YOU LIKE TO VIEW:\n");
        printf("\n\t1.WHOLE RECORD OF THE DAY.");
        printf("\n\t2.RECORD OF FIX TIME.");
        printf("\n\t\tENTER YOUR CHOICE:");
        
        if (scanf("%d", &ch) != 1) {
            clear_input_buffer();
            ch = 0;
        } else {
            clear_input_buffer();
        }
        
        switch(ch)
        {
            case 1:
                printf("\nTHE WHOLE RECORD FOR %s IS:",filename);
                while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
                {
                    printf("\n");
                    printf("\nTIME: %s",customer.time);
                    printf("\nMEETING WITH: %s",customer.name);
                    printf("\nMEETING AT: %s",customer.place);
                    printf("\nDURATION: %s",customer.duration);
                    printf("\nNOTE: %s",customer.note);
                    printf("\n");
                }
                break;
            case 2:
                printf("\nENTER TIME:[hh:mm]:");
                if (fgets(time_input, sizeof(time_input), stdin) == NULL) break;
                time_input[strcspn(time_input, "\n")] = 0;
                
                while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
                {
                    if(strcmp(customer.time,time_input)==0)
                    {
                        printf("\nYOUR RECORD IS:");
                        printf("\nTIME: %s",customer.time);
                        printf("\nMEETING WITH: %s",customer.name);
                        printf("\nMEETING AT: %s",customer.place);
                        printf("\nDURATION: %s",customer.duration);
                        printf("\nNOTE: %s",customer.note);
                    }
                }
                break;
            default: printf("\nYOU TYPED SOMETHING ELSE...\n");
                break;
        }
        
        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N):");
        choice = getchar();
        clear_input_buffer();
        
    }while(choice=='Y'||choice=='y');
    
    fclose ( fpte ) ;
    return ;
}

void editrecord()
{
    clear_screen();
    FILE *fpte ;
    struct record customer ;
    char time_input[6], choice, filename[15];
    int num,count=0;
    
    printf("\n\n\t\t*******************************\n");
    printf("\t\t* WELCOME TO THE EDITING MENU *");
    printf("\n\t\t*******************************\n\n");
    
    choice=password();
    
    if(choice!=0)
    {
        return ;
    }
    
    do
    {
        printf("\n\tENTER THE DATE OF RECORD TO BE EDITED:[yyyy-mm-dd]:");
        if (fgets(filename, sizeof(filename), stdin) == NULL) break;
        filename[strcspn(filename, "\n")] = 0;
        
        printf("\n\tENTER TIME:[hh:mm]:");
        if (fgets(time_input, sizeof(time_input), stdin) == NULL) break;
        time_input[strcspn(time_input, "\n")] = 0;
        
        fpte = fopen ( filename, "rb+" ) ;
        
        if ( fpte == NULL )
        {
            printf( "\nRECORD DOES NOT EXISTS:" ) ;
            printf("\nPRESS ENTER TO GO BACK");
            getchar();
            return;
        }
        
        while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
        {
            if(strcmp(customer.time,time_input)==0)
            {
                printf("\nYOUR OLD RECORD WAS AS:");
                printf("\nTIME: %s",customer.time);
                printf("\nMEETING WITH: %s",customer.name);
                printf("\nMEETING AT: %s",customer.place);
                printf("\nDURATION: %s",customer.duration);
                printf("\nNOTE: %s",customer.note);
                printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");
                
                printf("\n1.TIME.");
                printf("\n2.MEETING PERSON.");
                printf("\n3.MEETING PLACE.");
                printf("\n4.DURATION.");
                printf("\n5.NOTE.");
                printf("\n6.WHOLE RECORD.");
                printf("\n7.GO BACK TO MAIN MENU.");
                
                do
                {
                    printf("\n\tENTER YOUR CHOICE:");
                    
                    if (scanf("%d", &num) != 1) {
                        clear_input_buffer();
                        num = 0;
                    } else {
                        clear_input_buffer();
                    }
                    
                    switch(num)
                    {
                        case 1: printf("\nENTER THE NEW DATA:");
                            printf("\nNEW TIME:[hh:mm]:");
                            if (fgets(customer.time, sizeof(customer.time), stdin) == NULL) break;
                            customer.time[strcspn(customer.time, "\n")] = 0;
                            break;
                        case 2: printf("\nENTER THE NEW DATA:");
                            printf("\nNEW MEETING PERSON:");
                            if (fgets(customer.name, sizeof(customer.name), stdin) == NULL) break;
                            customer.name[strcspn(customer.name, "\n")] = 0;
                            break;
                        case 3: printf("\nENTER THE NEW DATA:");
                            printf("\nNEW MEETING PLACE:");
                            if (fgets(customer.place, sizeof(customer.place), stdin) == NULL) break;
                            customer.place[strcspn(customer.place, "\n")] = 0;
                            break;
                        case 4: printf("\nENTER THE NEW DATA:");
                            printf("\nDURATION:");
                            if (fgets(customer.duration, sizeof(customer.duration), stdin) == NULL) break;
                            customer.duration[strcspn(customer.duration, "\n")] = 0;
                            break;
                        case 5: printf("ENTER THE NEW DATA:");
                            printf("\nNOTE:");
                            if (fgets(customer.note, sizeof(customer.note), stdin) == NULL) break;
                            customer.note[strcspn(customer.note, "\n")] = 0;
                            break;
                        case 6:  printf("\nENTER THE NEW DATA:");
                            printf("\nNEW TIME:[hh:mm]:");
                            if (fgets(customer.time, sizeof(customer.time), stdin) == NULL) break;
                            customer.time[strcspn(customer.time, "\n")] = 0;
                            
                            printf("\nNEW MEETING PERSON:");
                            if (fgets(customer.name, sizeof(customer.name), stdin) == NULL) break;
                            customer.name[strcspn(customer.name, "\n")] = 0;
                            
                            printf("\nNEW MEETING PLACE:");
                            if (fgets(customer.place, sizeof(customer.place), stdin) == NULL) break;
                            customer.place[strcspn(customer.place, "\n")] = 0;
                            
                            printf("\nDURATION:");
                            if (fgets(customer.duration, sizeof(customer.duration), stdin) == NULL) break;
                            customer.duration[strcspn(customer.duration, "\n")] = 0;
                            
                            printf("\nNOTE:");
                            if (fgets(customer.note, sizeof(customer.note), stdin) == NULL) break;
                            customer.note[strcspn(customer.note, "\n")] = 0;
                            break;
                        case 7: printf("\nPRESS ENTER TO GO BACK...\n");
                            getchar();
                            return ;
                        default: printf("\nYOU TYPED SOMETHING ELSE...TRY AGAIN\n");
                            break;
                    }
                }while(num<1||num>7);
                
                fseek(fpte,-sizeof(customer),SEEK_CUR);
                fwrite(&customer,sizeof(customer),1,fpte);
                fseek(fpte,-sizeof(customer),SEEK_CUR);
                fread(&customer,sizeof(customer),1,fpte);
                choice=5;
                break;
            }
        }
        
        if(choice==5)
        {
            clear_screen();
            printf("\n\t\tEDITING COMPLETED...\n");
            printf("--------------------\n");
            printf("THE NEW RECORD IS:\n");
            printf("--------------------\n");
            printf("\nTIME: %s",customer.time);
            printf("\nMEETING WITH: %s",customer.name);
            printf("\nMEETING AT: %s",customer.place);
            printf("\nDURATION: %s",customer.duration);
            printf("\nNOTE: %s",customer.note);
            
            fclose(fpte);
            
            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD.(Y/N)");
            choice = getchar();
            clear_input_buffer();
            count++;
        }
        else
        {
            printf("\nTHE RECORD DOES NOT EXIST::\n");
            printf("\nWOULD YOU LIKE TO TRY AGAIN...(Y/N)");
            choice = getchar();
            clear_input_buffer();
        }
        
    }while(choice=='Y'||choice=='y');
    
    fclose ( fpte ) ;
    
    if(count==1)
        printf("\n%d FILE IS EDITED...\n",count);
    else if(count>1)
        printf("\n%d FILES ARE EDITED..\n",count);
    else
        printf("\nNO FILES EDITED...\n");
    
    printf("\tPRESS ENTER TO EXIT EDITING MENU.");
    getchar();
}

void editpassword()
{
    clear_screen();
    printf("\n");
    char pass[15]={0}, confirm[15]={0};
    int choice, i, check;
    FILE *fp;
    
    fp=fopen("SE","rb");
    
    if(fp==NULL)
    {
        fp=fopen("SE","wb");
        if(fp==NULL)
        {
            printf("SYSTEM ERROR...");
            getchar();
            return ;
        }
        fclose(fp);
        printf("\nSYSTEM RESTORED...\nYOUR PASSWORD IS 'ENTER'\n PRESS ENTER TO CHANGE PASSWORD\n\n");
        getchar();
    }
    else
    {
        fclose(fp);
    }
    
    check=password();
    
    if(check==1)
    {
        return ;
    }
    
    do
    {
        if(check==0)
        {
            choice=0;
            
            printf("\n\n\tENTER THE NEW PASSWORD:");
            if (fgets(pass, sizeof(pass), stdin) == NULL) return;
            pass[strcspn(pass, "\n")] = 0;
            
            printf("\n\tCONFIRM PASSWORD:");
            if (fgets(confirm, sizeof(confirm), stdin) == NULL) return;
            confirm[strcspn(confirm, "\n")] = 0;
            
            if(strcmp(pass, confirm)==0)
            {
                fp=fopen("SE","wb");
                
                if(fp==NULL)
                {
                    printf("\n\t\tSYSTEM ERROR");
                    getchar();
                    return ;
                }
                
                i=0;
                while(pass[i]!='\0')
                {
                    int ch_val = pass[i];
                    putc(ch_val+5, fp);
                    i++;
                }
                
                fclose(fp);
            }
            else
            {
                printf("\n\tTHE NEW PASSWORD DOES NOT MATCH.");
                choice=1;
            }
        }
        
    }while(choice==1);
    
    printf("\n\n\tPASSWORD CHANGED...\n\n\tPRESS ENTER TO GO BACK...");
    getchar();
}

void deleterecord( )
{
    clear_screen();
    FILE *fp,*fptr ;
    struct record file ;
    char filename[15], another = 'Y', time_input[10];
    int choice;
    
    printf("\n\n\t\t*************************\n");
    printf("\t\t* WELCOME TO DELETE MENU*");
    printf("\n\t\t*************************\n\n");
    
    choice=password();
    
    if(choice!=0)
    {
        return ;
    }
    
    while ( another == 'Y' || another == 'y' )
    {
        printf("\n\n\tHOW WOULD YOU LIKE TO DELETE.");
        printf("\n\n\t#DELETE WHOLE RECORD\t\t\t[1]");
        printf("\n\t#DELETE A PARTICULAR RECORD BY TIME\t[2]");
        
        do
        {
            printf("\n\t\tENTER YOU CHOICE:");
            
            if (scanf("%d", &choice) != 1) {
                clear_input_buffer();
                choice = 0;
            } else {
                clear_input_buffer();
            }
            
            switch(choice)
            {
                case 1:
                    printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");
                    if (fgets(filename, sizeof(filename), stdin) == NULL) break;
                    filename[strcspn(filename, "\n")] = 0;
                    
                    fp = fopen (filename, "rb" ) ;
                    if ( fp == NULL )
                    {
                        printf("\nTHE FILE DOES NOT EXISTS");
                        printf("\nPRESS ENTER TO GO BACK.");
                        getchar();
                        return ;
                    }
                    fclose(fp);
                    
                    if (remove(filename) == 0) {
                        printf("\nDELETED SUCCESSFULLY...");
                    } else {
                        printf("\nERROR DELETING FILE.");
                    }
                    break;
                    
                case 2:
                    printf("\n\tENTER THE DATE OF RECORD:[yyyy-mm-dd]:");
                    if (fgets(filename, sizeof(filename), stdin) == NULL) break;
                    filename[strcspn(filename, "\n")] = 0;
                    
                    fp = fopen (filename, "rb" ) ;
                    
                    if ( fp == NULL )
                    {
                        printf("\nTHE FILE DOES NOT EXISTS");
                        printf("\nPRESS ENTER TO GO BACK.");
                        getchar();
                        return ;
                    }
                    
                    fptr=fopen("temp","wb");
                    
                    if(fptr==NULL)
                    {
                        printf("\nSYSTEM ERROR");
                        printf("\nPRESS ENTER TO GO BACK");
                        getchar();
                        fclose(fp);
                        return ;
                    }
                    
                    printf("\n\tENTER THE TIME OF RECORD TO BE DELETED:[hh:mm]:");
                    if (fgets(time_input, sizeof(time_input), stdin) == NULL) break;
                    time_input[strcspn(time_input, "\n")] = 0;
                    
                    while(fread(&file,sizeof(file),1,fp)==1)
                    {
                        if(strcmp(file.time,time_input)!=0)
                            fwrite(&file,sizeof(file),1,fptr);
                    }
                    
                    fclose(fp);
                    fclose(fptr);
                    
                    remove(filename);
                    rename("temp",filename);
                    
                    printf("\nDELETED SUCCESSFULLY...");
                    break;
                    
                default:
                    printf("\n\tYOU ENTERED WRONG CHOICE");
                    break;
            }
            
        }while(choice<1||choice>2);
        
        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");
        another = getchar();
        clear_input_buffer();
    }
    
    printf("\n\n\tPRESS ENTER TO EXIT...");
    getchar();
}
