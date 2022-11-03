#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include "main_headers.h"

int main(int argc, char *argv[])
{
	union semun {
   	int val; /* val for SETVAL */
   	struct semid_ds *buf; /* Buffer for IPC_STAT and IPC_SET */
   	unsigned short *array; /* Buffer for GETALL and SETALL */
   	struct seminfo *__buf; /* Buffer for IPC_INFO and SEM_INFO*/
	};
	int semid;
 	if (argc < 2 || argc > 3 || strcmp(argv[1], "--help") == 0)
 		printf("%s init-value\n"
 		" or: %s semid operation\n", argv[0], argv[0]);
 	if (argc == 2) { /* Create and initialize semaphore */
 	union semun arg;
 
	 semid = semget(IPC_PRIVATE, 1, S_IRUSR | S_IWUSR);
 	if (semid == -1)
 		printf("error in semid");
 	arg.val = atoi(argv[1]);
 	if (semctl(semid, /* semnum= */ 0, SETVAL, arg) == -1)
 		printf("error in semctl");
 	printf("Semaphore ID = %d\n", semid);
 	}
       	else
       	{ /* Perform an operation on first semaphore */
 
	
		struct sembuf sop; /* Structure defining operation */
	 	semid = atoi(argv[1]);
 		sop.sem_num = 0; /* Specifies first semaphore in set */
	 	sop.sem_op = atoi(argv[2]);
	 /* Add, subtract, or wait for 0 */
		 sop.sem_flg = 0; /* No special options for operation */
	 	printf("%ld: about to semop \n", (long) getpid());
 		if (semop(semid, &sop, 1) == -1)
 			printf("error in semop");
 		printf("%ld: semop completed\n", (long) getpid());
 	}
	 exit(1);
}
