#include <sys/types.h>
#include <sys/sem.h>
#include <time.h>
#include "main_headers.h"
int main(int argc, char *argv[])
{
 struct semid_ds ds;
 union semun {
        int val; /* val for SETVAL */
        struct semid_ds *buf; /* Buffer for IPC_STAT and IPC_SET */
        unsigned short *array; /* Buffer for GETALL and SETALL */
        struct seminfo *__buf; /* Buffer for IPC_INFO and SEM_INFO*/
        };

 union semun arg, dummy; /* Fourth argument for semctl() */
 int semid, j;
 if (argc != 2 || strcmp(argv[1], "--help") == 0)
	 printf("%s semid\n", argv[0]);
 semid = atoi(argv[1]);
 arg.buf = &ds;
 if (semctl(semid, 0, IPC_STAT, arg) == -1)
 	printf("error in semctl");
 printf("Semaphore changed: %s", ctime(&ds.sem_ctime));
 printf("Last semop(): %s", ctime(&ds.sem_otime));
 /* Display per-semaphore information */
 arg.array = calloc(ds.sem_nsems, sizeof(arg.array[0]));
 if (arg.array == NULL)
	 printf("error in calloc");
 if (semctl(semid, 0, GETALL, arg) == -1)
 	printf("error in semctl-GETALL");
 printf("Sem # Value SEMPID SEMNCNT SEMZCNT\n");
 for (j = 0; j < ds.sem_nsems; j++)
 	printf("%3d %5d %5d %5d %5d\n", j, arg.array[j],
 	semctl(semid, j, GETPID, dummy),
	 semctl(semid, j, GETNCNT, dummy),
	 semctl(semid, j, GETZCNT, dummy));
 exit(1);
}
