#define _POSIX_SOURCE
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <dos.h>


#define TRUE 1
#define FALSE 0
#define MAX 256

int exitMainProg = FALSE;//GLOBAL INITIALIZATION
int incorrectUser = FALSE;
int switchUser ;


// FUNCTION DECLARATION
void mainProg();
void dispOption();
void userDispOption();
void switchOption();
void userSwitchOption();
int createUser();
void deleteUser();
void viewFiles();
void modifyFiles();
void filecreate();
void rolecreate();





int main()
{   
   rolecreate();
   filecreate();
   mainProg();

    return 0;
}


void rolecreate()
{
	int rollSize;
	FILE *role;
	role=fopen("role.txt","a+");
	fseek (role, 0, SEEK_END);
    rollSize = ftell(role);

    if (rollSize == 0) 
	{   
        fputs("1001 admin USER-CREATION,USER-DELETION,READ,WRITE,SIGNOUT\n",role);
        fputs("1002 user FILE-OPERATION,SIGNOUT",role);
    }
	fclose(role);
}  




void filecreate()
{   
    int userSize;
	FILE *fp;
	fp=fopen("users.txt","a+");
	fseek (fp, 0, SEEK_END);
    userSize = ftell(fp);

    if (userSize == 0) 
	{
        fputs("1 admin admin 1001 READ/WRITE\n",fp);
    }
	fclose(fp);
}





void mainProg()
     {   
       int choice;
    
       printf("******************* Welcome*************************\n");
       printf("----Make your choice----\n\n1.Sign in\t2.Exit\n");
       scanf("%d",&choice);
       switch(choice)
        {
          case 1:
          	{   
			    int loop=1;
			   do
          	      {
			      FILE *fp;
		          printf("\n=================Signing in====================\n");
		           char username[50];
                  char password[50];
                  char repassword[50];
                  char x[50],y[50],z[50],p[50],l[50];
                  char a[50],b[50],c[50];
                  printf("\nEnter your username:\n");
                  scanf("%s",&username);
                  printf("Enter your password:\n");
                  scanf("%s",&password);
                  fp=fopen("users.txt","r+");
                  while (!feof(fp))
                  {  
                  	fscanf(fp,"%s%s%s%s%s",x,y,z,p,l);
                  	if(strcmp("admin",username)==0&&strcmp("admin",password)==0) 
                  	{   fclose(fp);
					     FILE *role;
					     loop++;
                  	     incorrectUser = TRUE;
                  	     switchUser = TRUE;
                  	     printf("\nWelcome!!..Signin Success..You are an admin!!!!!\n\n");
                  	     role=fopen("role.txt","a+");
                  	     fscanf(role,"%s%s%s",a,b,c);
                         fp=fopen("users.txt","a+");
                         while (!feof(fp))
                               {  
                                   fscanf(fp,"%s%s%s%s%s",x,y,z,p,l);
                                  
                                   if(strcmp(a,p)==0)
                                       {  
								        fclose(fp);
									        do     
						                        {
						                           printf("%s\n",c); 
   	                                               dispOption();
                                                   switchOption();
                                                }while (!exitMainProg);
                  	                             break;
								        }
						        }
						        fclose(role);
                  }
                  else if(strcmp(username,y)==0&&strcmp(password,z)==0)
                    {     
                          char x[50],y[50],z[50],p[50],l[50];
					      loop++;
                          incorrectUser = TRUE;
                          switchUser = FALSE;
                          printf("\nWelcome!!..Signin Success..You are an user!!!!!\n");
                            userDispOption();
                            userSwitchOption();
                          fp=fopen("users.txt","r+");
                           while (!feof(fp))
                               {  
                          fscanf(fp,"%s%s%s%s%s",x,y,z,p,l);
                          if(strcmp(username,y)==0&&strcmpi("READ",l)==0)
                          {
                          	 printf("\nAdmin have assigned only READ permission\n");
                                	viewFiles();
									userDispOption();
                                    userSwitchOption();	
						  }
						  else if(strcmp(username,y)==0&&strcmpi("WRITE",l)==0)
						  {
						  	printf("\nAdmin have assigned both READ and WRITE permission\n");
	 	                           modifyFiles();
	 	                           userDispOption();
                                   userSwitchOption();
	 	                     
						  }
					}
                          
						  break;	
					}
					
			       }
			       if(!incorrectUser)
			       {
			       	printf("\nSorry!!..Either the Username or Password is incorrect. Please try again..\n");
			       	
				   }
			    }while(loop==1);
			    
			    
		}		 
		  case 2:
			{
				exit(0);
				}       
    }
 }
 
 
 
 
void dispOption()
     { 
     
    FILE *role;
    char a[50],b[50],c[50];
    role=fopen("role.txt","r+");
    fscanf(role,"%s%s%s",a,b,c);
    char delim[100] = ",";
	char *ptr = strtok(c, delim); 
	fclose(role);
	printf("===========================");  
	while(ptr != NULL)
	{    
		if(strcmp(ptr,"USER-CREATION")==0)
		   {
		   	  printf("\n1. Create an user \n"); 
		   }
		if(strcmp(ptr,"USER-DELETION")==0)
		   {
		   	   printf("2.Delete an user \n");
		   }
		if(strcmp(ptr,"READ")==0)
		   {
		   	  printf("3.View files  \n");
		   }
		if(strcmp(ptr,"WRITE")==0)
		   {
		   	  printf("4.Rename or delete a file  \n");
		   }  
		if(strcmp(ptr,"SIGNOUT")==0)
		   {
		   	  printf("5.Signout \n");
		   }                   
		ptr = strtok(NULL, delim);
    }
    

	
	printf("===========================");
	
   }





void userDispOption()
{
    FILE *role;
    role=fopen("role.txt","r+");
    while(!feof(role))	
    {
	
    char r1[50],r2[50],r3[50];
    fscanf(role,"%s%s%s",r1,r2,r3);
    if (strcmp(r1,"1002")==0)
    {
    printf("%s",r3);
    char delim1[100] = ",";
	char *ptr1 = strtok(r3, delim1); 
	printf("\n===========================\n");  
	while(ptr1 != NULL)
	{    
		if(strcmp(ptr1,"FILE-OPERATION")==0)
		   {
		   	  printf("1. File Operation \n"); 
		   }
		if(strcmp(ptr1,"SIGNOUT")==0)
		   {
		   	   printf("2.Sign Out ");
		   }
		   ptr1 = strtok(NULL, delim1);
    }
    printf("\n===========================\n");
    }

	
	
	
}
	
}



void userSwitchOption()
{     
  FILE *role;
  role=fopen("role.txt","r+");
  while(!feof(role))	
        {	
	int option;	
    char u1[50],u2[50],u3[50];
    fscanf(role,"%s%s%s",u1,u2,u3);
    if(strcmp(u1,"1002")==0)
    {
    char delimSwitch[100] = ",";
	char *ptr = strtok(u3, delimSwitch); 
	
	printf("\nPlease choose any option..\n");
	scanf("%d",&option);

    switch(option)
        {

          case 1:
          	{   int dummy1=1;
			   	while(ptr != NULL)
                {    
          	    if(strcmp(ptr,"FILE-OPERATION")==0)
		           { 
		             dummy1++;
		             return;
                      
                    }
                    ptr = strtok(NULL, delimSwitch);
                }
                 if(dummy1==1)
          	    {
				    printf("\nThis Option doesnt exist for user..Please choose any other option !!!\n");
				    userDispOption();
                    userSwitchOption();
				   
				}
				break;
            }
          case 2: 
            { 
			  int dummy1=1; 
              while(ptr != NULL)
                {    
              if(strcmp(ptr,"SIGNOUT")==0)
		     {  
		        printf("\nSigning out...Please wait!!!");  
				printf("\nSigned Out Successfully...Bye :(\n"); 
                mainProg();
                dummy1++;
                   
             }
             ptr = strtok(NULL, delimSwitch);
         }
             if(dummy1==1)
          	    {
				    printf("\nThis Option doesnt exist for user..Please choose any other option !!!\n");
				    userDispOption();
                    userSwitchOption();
				   
				}
				break;
            }
          default :
                    printf("\nPlease enter one of the options above only\n");
                    break;
        }
}
}
}










void switchOption()
{   	
	int option;
	FILE *role;
    char a[50],b[50],c[50];
    role=fopen("role.txt","r+");
    fscanf(role,"%s%s%s",a,b,c);
    fclose(role);
    char delim[100] = ",";
	char *ptr = strtok(c, delim); 
	fclose(role);
	
	printf("\nPlease choose any option..\n");
	scanf("%d",&option);

    switch(option)
        {

          case 1:
          	{ int dummy=1;
			   	while(ptr != NULL)
                {    
          	    if(strcmp(ptr,"USER-CREATION")==0)
		           {
		             createUser();
		             dummy++;
                      
                    }
                    ptr = strtok(NULL, delim);
                }
                 if(dummy==1)
          	    {
				    printf("\nThis Option doesnt exist for admin..Please choose any other option !!!\n");
				    break;
				   
				}
				    break;
            }
          case 2: 
            {  int dummy=1;
              while(ptr != NULL)
                {    
              if(strcmp(ptr,"USER-DELETION")==0)
		     {
                deleteUser();
                dummy++;
                   
             }
             ptr = strtok(NULL, delim);
         }
            if(dummy==1)
          	    {
				    printf("\nThis Option doesnt exist for admin..Please choose any other option !!!\n");
				    break;
				}
				     break;
            }
          case 3: 
            {   int dummy=1;
            	 while(ptr != NULL)
                {    
            	if(strcmp(ptr,"READ")==0)
		       {
                viewFiles();
                dummy++;
                    
                }
                ptr = strtok(NULL, delim);
            }
            if(dummy==1)
          	    {
				    printf("\nThis Option doesnt exist for admin..Please choose any other option !!!\n");
				    break;
				}
            break;
            }
          case 4:
          	{   int dummy=1; 
          	     while(ptr != NULL)
                {    
          		if(strcmp(ptr,"WRITE")==0)
		         {
          	    modifyFiles();
          	    dummy++;
          	    
          	     }
          	     ptr = strtok(NULL, delim); 
          	 }
          	 
          	    if(dummy==1)
          	    {
				    printf("\nThis Option doesnt exist for admin..Please choose any other option !!!\n");
				    break;
				}
				break;
          	 }
          
          case 5:
          	{   int dummy=1; 
          	
          	    while(ptr != NULL)
                {    
          	  if(strcmp(ptr,"SIGNOUT")==0)
		     {
			  printf("\nSigning out from admin..please wait\n");
             exitMainProg = TRUE;
              printf("\nAdmin signed out successfully!!bye..\n");
              mainProg();
              dummy++;
                    
                }
              ptr = strtok(NULL, delim);   
            }
                if(dummy==1)
                {
				    printf("\nThis Option doesnt exist for admin..Please choose any other option !!!\n");
				    break;
				}
				break;
            }
          default :
                    printf("\nPlease enter one of the options above only\n");
                    break;
        }

}





int createUser()
{   
    int access;
    char username[50];
    char pass[50]; 
    char repass[50];
	char a[50],b[50],c[50];
	char x[50],y[50],z[50],p[50],l[50];
    FILE *fp;
    FILE *role;
    printf("\n********Creating an User*********\n");
    printf("\nEnter username :\n");
    scanf("%s",username);
    
     
      do
    	{
    		
    printf("\nEnter the password :\n");
    scanf("%s",pass);
    printf("\nRe-Enter the password :\n");
    scanf("%s",repass);
    static int userID=1;
    int id = 1002;
    int jump=0;
    fp=fopen("users.txt","a+");
    while (!feof(fp))
        {  
            fscanf(fp,"%s%s%s%s%s",x,y,z,p,l);
            if(strcmp(username,y)==0)
                {    
                    printf("\nUser already exist..please try again!!!\n\n\n");
                    jump=1;
                    return;
                }
        }
	                fclose(fp);        
	   if(jump==0)             
           {
           	 fp=fopen("users.txt","a+");
           	 userID++;
             fprintf(fp, "%d %s %s %d ",userID,username,pass,id);
             fclose(fp);
		   }
    if(strcmp(pass,repass)==0)
    
		{
			printf("\n%s User created successfully\n",username);
		}
	else
       {
       	
       	printf("\npassword re-enterred did not match\n");
	   }
	  
    }while(strcmp(pass,repass)!=0);
    
   
    
    
        fp=fopen("users.txt","a+");
    while (!feof(fp))
     {   
        fscanf(fp,"%s%s%s%s%s",x,y,z,p,l);
         
            fclose(fp);
            printf("\nWhat access you need to give the user---\t 1.Read\t2.Write\n");
            scanf("%d",&access);
            if(access == 1)
            {
        	fp=fopen("users.txt","a+");
        	fputs("READ\n",fp);
        	fclose(fp);
        	printf("\nREAD permission assigned to the user successfully!!!!\n");
            }
            else
            {
               fp=fopen("users.txt","a+");
        	   fputs("WRITE\n",fp);
        	   fclose(fp);	
        	   printf("\nWRITE permission assigned to the user successfully!!!!\n");
			}
        	break;
        
		}
	
}


void deleteUser()
{       
        int lno, ctr = 0;
        int n1;
        char c;
        FILE *fp, *fptr2;
		char fname[MAX];
        char str[MAX], temp[] = "user.txt";	
        fp = fopen("users.txt", "r");
        fptr2 = fopen(temp, "w"); 
        c = fgetc(fp); 
               while (c != EOF) 
                  { 
                      printf ("%c", c); 
                      c = fgetc(fp); 
                  } 
        printf("\nEnter the User ID of the user you want to delete :\n ");
        scanf("%d", &lno);
        rewind(fp);
        if(lno != 1)
        {
        while (!feof(fp)) 
        {
            strcpy(str, "\0");
            fgets(str, MAX, fp);
            if (!feof(fp)) 
            {
                ctr++;
                if (ctr != lno) 
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
             fclose(fp);
        	printf("\nUser deleted successfully!! \n");
    }
        else
        {
        	printf("\nAdmin cannot be deleted\n");
		}
	
        
        fclose(fptr2);
        remove("users.txt");  
        rename(temp, "users.txt");
  }






void viewFiles()
{  
    int repeat1;
    do
    {
	char dirPath[100];
	int siNo;
	printf("enter the driectory..for ex(C:\\) to view :");
	scanf("%s",&dirPath);
	struct dirent *de;
	DIR *dr=opendir(dirPath);
	if(dr)
	{  	
	  
		while((de=readdir(dr))!=NULL)
		{ 
			printf("%d  %s\n",siNo,de->d_name);
			siNo++;
	
		}
    }
    printf ("\nDo you want to repeat the operation Y/N:\n1-yes\t2-no\n ");
    scanf ("%d",&repeat1);
    }while(repeat1 == 1);	
			}	

void modifyFiles()
{

	int selectNo,option;
	char dirPath[100],dupli[10],dupli1[100];
	char userFile[100],sysFile[100];
	int repeat;
	
	do
	    {	
		int siNo=0,count=0;
	    
	printf("enter the driectory..for ex(C:\\) to view :");
	scanf("%s",&dirPath);
	struct dirent *de;
	DIR *dr=opendir(dirPath);
	if(dr)
	{  	
	  
		while((de=readdir(dr))!=NULL)
		{ 
			printf("%d  %s\n",siNo,de->d_name);
			siNo++;
	
		}
	
		rewinddir(dr);
    	printf("Enter the serial number of the file :");
		scanf("%d",&selectNo);
    
    
    while((de=readdir(dr))!=NULL)
		{
			count++;
			if(selectNo==(count-1))
	    { 
	        printf("======choose any option======\n 1.delete \t 2.rename\n");
	        scanf("%d",&option);
	        switch (option)
	        {
	        	case 1:
	        		{ 
					strcpy(dupli1,dirPath);
	        		if(remove(strcat(dirPath,de->d_name))==0)
	        		{
	        		printf("\nThe file deleted successfully\n");
	        	}
	        	else if(rmdir(strcat(dupli1,de->d_name))==0)
	        	{
	        		printf("\nThe folder is deleted\n");
				}
				else
	        	{   
	        	    printf(dupli1);
                    printf(dirPath);
	        		printf("\nThe entered serial no. is a non empty folder\n");
				}
	        		break;
	        	}
	        	case 2:
	        		{  
					    char statName[50];
					    struct stat info;
	        			printf("enter the new filename:\n");
		                scanf("%s",userFile);
		                strcpy(sysFile,de->d_name);
		                strcpy(dupli,dirPath);
	        			rename(strcat(dirPath,sysFile), strcat(dupli,userFile));
	                     if (stat(dupli, &info) == 0)
                            {
    	                       printf("\nThe file renamed successfully\n");
	                        }
                         else 
						    {
                               printf("\nThe file is being used by another application\n");
                            }
	        			
	        			break;
					}
			}
	        
		}
		
}
closedir(dr);
}
printf ("\nDo you want to repeat the operation Y/N:\n1-yes\t2-no\n ");
scanf ("%d",&repeat);
}while(repeat == 1 );
printf ("\n\n\n");
system("pause");


}
	   



 
 
 
