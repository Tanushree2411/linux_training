#include<unistd.h>
#include<sys/types.h>



int fds[2];



void parent_code()
{
char *buf1="aaaaaaaaaaaaaaaaaaa";
char *buf="bbbbbbbbbbbbbbbbbbbb";
close(fds[0]);
write(fds[1],buf,20);
write(fds[1],buf1,20);
printf("end of parent\n");
}



void child_code()
{
char buf[100];
int n,i;
close(fds[1]);
n=read(fds[0],buf,100);
printf("no of chars read=%d\n",n);
for(i=0;i<n;i++)
{
printf("%c",buf[i]);
}



printf("End of child");
}



int main()
{
int res,i;
pid_t p;
res=pipe(fds);
if(res==-1)
{
perror("pipe");
exit(1);
}



p=fork();
if(p==0)
{
child_code();
}
else
{
parent_code();
}
}
