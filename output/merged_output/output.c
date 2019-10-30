#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <errno.h>

ssize_t func1()
{	
	char buffer[1024];
  	if(fgets(buffer, 1024, stdin)!=NULL)
  	{
  		if (!isalpha(buffer[0]))
  		{
    	 	char errormsg[1044];
     		strlcpy(errormsg, buffer,1024);
     		strlcat(errormsg, " is not a valid ID",sizeof(errormsg));
				fprintf(stderr,"%s\n",errormsg);
				return -1;
 			}
			
  	}
  
  	if(ferror(stdin))
  	{
  		fprintf(stderr,"%s\n",strerror(errno));
  		return -1;
  	}
  	
  	return 0;
  		
  	
  	
}

ssize_t func2(int f2d)
{
	char *buf2 = NULL;
	size_t len = 0;
	size_t limit = 1024;
	ssize_t ret = 0;
  	//false positive: this fnction read sizeof(len) bytes from f2d and store them in len.
  	// space is enough: false positive
  	/* Flawfinder: ignore */
  	ret = read(f2d, &len, sizeof(len));
  	if(ret < 0)
  	{
  		/* error handling */
		fprintf(stderr,"%s.\n",strerror(errno));
  		return -1;
  	}
  	//assigned a max length to len. This is useful because if an attacker manage to set  the value of len as the max integer value
  	// this causes an integer overflow in the malloc function (len +1). max_int +1 = 0.
  	// this integer overflow causes a buffer overflow in the last read function. (the program try to read
	//and store len bytes into a buffer of size 0) 
  	if(len > limit)
	{
		fprintf(stderr,"%s.\n",strerror(errno));
		return -1;
  	}
 	buf2 = calloc(len+1,sizeof(char));
  	if(buf2==NULL)
  	{
  		/*error handling */
		fprintf(stderr,"%s.\n",strerror(errno));
		return -1;
  	}
   
 	/* Flawfinder: ignore */
  	ret = read(f2d, buf2,len);
  	if(ret < 0)
  	{
    	/*error handling */
    	fprintf(stderr,"%s.\n",strerror(errno));
    	free(buf2);
    	return -1;
  	} 
  	buf2[ret] = '\0';
  	free(buf2);
  	return 0;
}


ssize_t func3(int f3d)
{
	char *buf3 = NULL;
	size_t len = 0;
  	ssize_t ret = 0;
  	/* Flawfinder: ignore */
  	ret = read(f3d, &len, sizeof(len));
  	if(ret < 0)
  	{
  		/*error handling*/
		fprintf(stderr,"%s.\n",strerror(errno));
  		return -1;
  	}
  	if (len > 8000) 
  	{ 
		printf("error len > 8000:\n");
  		fprintf(stderr,"too large length\n");
  		return -1; 
  	}
  
  	buf3 = malloc(len+1,sizeof(char));
  	if(buf3==NULL)
 	{
		/* error handling */
		fprintf(stderr,"%s.\n",strerror(errno));
  		return -1;
  	}
  	/* Flawfinder: ignore */
  	ret = read(f3d, buf3,len);
  	if(ret < 0)
  	{
  		/*error handling */
		fprintf(stderr,"%s.\n",strerror(errno));
  		free(buf3);
  		return -1;
  	}
  	buf3[ret] = '\0';
  	free(buf3);
  	return 0;     
}



int  main()
{
	char *foo = "fooooooooooooooooooooooooooooooooooooooooooooooooooo";
	char *buffer = (char *)malloc(10 * sizeof(char));
	ssize_t ret = 0;
	if(buffer==NULL)
	{
		/*error handling */
		fprintf(stderr,"%s.\n",strerror(errno));
		return -1;
	}
	strlcpy(buffer,foo,sizeof(buffer));
	ret = func1();
	exit(0);
	if(ret < 0)
	{
		free(buffer);
		fprintf(stderr,"%s.\n",strerror(errno));
		return -1;
	}
	ret = func3((int)sizeof(*foo));
	if(ret <0)
	{
		free(buffer);
		fprintf(stderr,"%s.\n",strerror(errno));
		return -1;
	}
	free(buffer);
	return 0;
}



