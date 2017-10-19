//Знаю, что уже поздно, но у меня были проблемы с ноутбуком - он достаточно долго был в ремонте.



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main () {

	int  i = 0, n;
	int* processNames;
        pid_t pid;
	printf ("how many processes? ");
	scanf ("%d", &n);
        processNames = (int*) calloc (n, sizeof (int));
	printf ("I am process № %d, the first process\n", getpid());
        while (i != n)
        {
                pid = fork ();
                if (pid == -1)
                {
                        printf ("error");
                        exit (0);
                        break;
                }
                else if (pid == 0)
                {
                        printf ("i am procces № %d  my father %d\n", getpid (), getppid ());
                        processNames[i] = getpid ();
                        i++;
                }
                else
                {
                	waitpid (pid, &i, 0);
                        printf ("I am process № %d,  my child %d finished\n", getpid (),  pid);
                        break;
                }
        }
        for (i = 0; i < n; i++)
        {
                if (processNames[i] == getpid ())
                        exit (i);
        }
        return 0;
}
      
