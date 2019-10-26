#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <bsd/string.h>
void func1()
{	/* Flawfinder: ignore */
	char buffer[1024];
  printf("Please enter your user id :");
  fgets(buffer, 1024, stdin);
 
  if (!isalpha(buffer[0]))
  {
     /* Flawfinder: ignore */
     char errormsg[1044];
     strlcpy(errormsg, buffer,1024);
     // deleted one space char
     strlcat(errormsg, " is not a valid ID",sizeof(errormsg));
 	}
}


void func2(int f2d)
{
	char *buf2;
	size_t len;
	size_t limit = 1024;
  //false positive: this fnction read sizeof(len) bytes from f2d and store them in len.
  // space is enough: false positive
  /* Flawfinder: ignore */
  read(f2d, &len, sizeof(len));
  //assigned a max length to len. This is useful because if an attacker manage to set  the value of len  as the max integer value
  // this causes an integer overflow in the malloc function (len +1). max_int +1 = 0.
 // this integer overflow causes a buffer overflow in the last read function. (the program try to read and store len bytes into a buffer of size 0) 
  if(len > limit) return;
  buf2 = malloc(len+1); 
 /* Flawfinder: ignore */
  read(f2d, buf2, len); 
  buf2[len] = '\0';

}


void func3(int f3d)
{
  char *buf3;
  int len;
  /* Flawfinder: ignore */
  read(f3d, &len, sizeof(len));
  if (len < 0 || len > 8000) 
  { 
  	perror("too large length");
  	return; 
  }
  buf3 = malloc(len+1);
  /* Flawfinder: ignore */
  read(f3d, buf3,len);
  buf3[len] = '\0';        
}



int  main()
{
	char *foo = "fooooooooooooooooooooooooooooooooooooooooooooooooooo";
	char *buffer = (char *)malloc(10 * sizeof(char));
	strlcpy(buffer,foo,sizeof(buffer));
	func1();
	//func3(sizeof(*foo));
}



