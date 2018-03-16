#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

#define SHMSZ     4 // shared memory size

int main()
{
	int x = 0;
	int shmid;
   	key_t key;
    	volatile int *shm;
	
	volatile int *node_pointer;
	
	 /*
     * We need to get the segment 
     * created by the server.
     */
	printf("Enter segment key for the node please: 6746\n");
	//scanf("%d", &x);
	printf("\n");
	key = 6747; //(key_t)x;
	
    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
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
     * Now read what the server put in the memory.
     */
     node_pointer = shm;
     printf("Value of the connected node: %d\n", *node_pointer);
	 printf("Address of the connected node node: %p\n", node_pointer);
	 printf("\n");
	
	/* changing the node value */
	while(1)
	{
	printf("Enter new value of node (overflow at 2147483647):\n");
	scanf("%d",node_pointer);	
	printf("Now look into the original process :-)\n");
	}
}
