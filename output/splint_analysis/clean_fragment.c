#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>





static void func1()
{	
	char buffer[1024];
  printf("Please enter your user id :");
 if(fgets(buffer, 1024, stdin)!=NULL){
 
  if (!isalpha(buffer[0]))
  {

     char errormsg[1044];
     strncpy(errormsg, buffer,1024);
     strcat(errormsg, " is not  a valid ID");
 	}
 }
}

/*@unused@*/
static void func2(int f2d)
{
	char *buf2 = NULL;;
	size_t len = 0;
        ssize_t ret = 0;
        if((ret = read(f2d, &len, sizeof(len)))> 0){
  		buf2 = calloc(len+1,sizeof(char));
		if(buf2 == NULL)
		{
			/*error handling */
			return;
		} 
  		if((ret = read(f2d,buf2, len))>0){ 
  		  buf2[ret] = '\0';
		  
		}
		else
		{
		  free(buf2);
		  /*error handling */
		  return;
		}
	}
	else
	{
		/* error handling */
	}
	free(buf2);

}


static void func3(int f3d)
{
	

char *buf3;
  int len = 0;
  ssize_t ret = 0;
  if((ret=read(f3d, &len, sizeof(len)))<0){
        /*error_handling*/
	return;
  }
  if (len > 8000) 
  { 
  	perror("too large length");
  	return; 
	}
  buf3 = calloc((size_t)len,sizeof(char));
  if(buf3==NULL)
  {
     /*error_handling*/
     return;
  }
  if((ret=read(f3d, buf3,(size_t)len))<0)
  {
     /*error handling */
     free(buf3);
     return;
  }
  free(buf3);        
}



int  main()
{
	char *foo = "fooooooooooooooooooooooooooooooooooooooooooooooooooo";
	
	char *buffer = (char *)malloc(10 * sizeof(char));
        if(buffer==NULL)
	{
	    /*error handling*/
     	    return -1;
	}
	strcpy(buffer, foo);
	func1();
   
	func3(sizeof(*foo));
	
	free(buffer);
	return 0;
}



