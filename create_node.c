#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

#define SHMSZ     4 // shared memory size

int main()
{
		
	int shmid; 
    	key_t key;
    	volatile int *shm; // handle
	
	volatile int *node_zero;
	
	
    /*
     * We'll name our shared memory segment
     * "6747".
     */
    key = 6747;

	/*
	* Create the segment.
	*/
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return EXIT_FAILURE;
    }

	/*
	* Now we attach the segment to our data space.
	*/
    if ((shm = shmat(shmid, NULL, 0)) == (volatile int *) -1) {
        perror("shmat");
        return EXIT_FAILURE;
    }
    
	/*
	* Now put some things into the memory for the
	* other process to read.
	*/
	node_zero = shm;
	*node_zero = 12345;	
	
	
	
	
	printf("New node created!\n");
	printf("\n");
	printf("Value of node: %d\n", *node_zero);
	printf("Address of node: %p\n", node_zero);
	printf("Smh key of the node: %d", key);
	printf("\n");
	
	
	
	while(1)
	{	
		sleep(1); // waiting time in seconds
		//for(long unsigned int i = 299551615UL; i > 0 ; i--);
		printf("Value of node: %d\n", *node_zero);
	}
	
}
