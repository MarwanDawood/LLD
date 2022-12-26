#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int
main (int argc, char *argv[])
{

  while (1)
    {
      printf ("waiting command > ");
      char buf[100];
      fgets (buf, 100, stdin);
      int len = strlen (buf);
      buf[len - 1] = 0;		// remove null pointer count

      if (len == 0)
	continue;

      int pid;
      pid = fork ();

      if (pid < 0)
	{
	  printf ("Error forking");
	}
      else if (pid > 0)
	{
	  //parent
	  int status;
	  wait ( /*getpid (), */ &status);
	  //printf ("Parent: child status is %d\n", WEXITSTATUS (status));
	}
      else if (pid == 0)
	{
	  //child
	  char *exe_argv[] = { NULL };
	  char *exe_argenv[] = { NULL };
	  execve (buf, exe_argv, exe_argenv);

	  return -1;
	}
    }
  return 0;
}
