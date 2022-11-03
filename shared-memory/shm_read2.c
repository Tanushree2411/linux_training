#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>

int main()
{
    char *p,*q;
    int id;

    id = shmget(48,250,IPC_CREAT|0644);
    if(id<0)
    {
        perror("shmget");
        return 0;
    }

    printf("Id: %d\n",id);
    p = shmat(id,0,0); // PAS -- User spcae
    printf("Data is: %s\n",p);
//    printf("Enter the data: ");
  //  scanf("%s",q);
    return 0;
}
