#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/types.h>


#define die(str, args...) do { \
        perror(str); \
        exit(EXIT_FAILURE); \
    } while(0)
int main(int argc,char* argv[]){
    	int fd;
    	struct input_event     ev;
	int i=0;
	unsigned key=KEY_D;
	unsigned value=0;//random key and value for initialize
	if (argc < 2){
	printf("Uso del programa: %s <caracter>\n",argv[0]);
	return -1;
	}

	fd = open("/dev/input/event0", O_WRONLY | O_NONBLOCK);//You have to see what is your keyboard file
// write in the terminal-> cat /proc/bus/input/devices
    	if(fd < 0)
        	die("error: open");

	while(*argv[1]!= '\0'){
		if(*argv[1] == 'D'){//You could do a switch for all case
			key=KEY_RIGHT;
			value=1;
		}
		if(*argv[1] == 'd'){
			key=KEY_RIGHT;
			value=0;
		}
		if(*argv[1] == 'I'){
			key=KEY_LEFT;
			value=1;
		}
		if(*argv[1] == 'i'){
			key=KEY_LEFT;
			value=0;
		}if(*argv[1] == 'A'){
			key=KEY_A;
			value=1;
		}if(*argv[1] == 'F'){
			key=KEY_A;
			value=0;
		}

	argv[1]++;
	}//this function search for a key to put in the keyboard file

		memset(&ev,0,sizeof(ev));
		ev.type =EV_KEY;
		ev.code=key;
		ev.value=value;
		write(fd,&ev,sizeof(ev));

		memset(&ev,0,sizeof(ev));
		ev.type =EV_SYN;
		ev.code=0;
		ev.value=0;
		write(fd,&ev,sizeof(ev));
//you have to write a specific struct in the keyboard file (see just above)

close(fd);//Close the keyboard file and the program ends

return 0;
}
