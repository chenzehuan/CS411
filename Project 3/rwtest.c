/*
 * Simple test for read+write on osurd device driver
 * Based on example found at: 
 * http://iacoma.cs.uiuc.edu/~nakano/dd/drivertut15.html
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char *buf = "1234567890";

	int fp = open("/dev/osurda1", O_RDWR);

	int wcount = write(fp, &buf[0], 10);
	printf("wrote %d bytes\n", wcount); 
 	
	int rcount = read(fp, &buf[0], 10);
	printf("read %d bytes\n", rcount);


}
