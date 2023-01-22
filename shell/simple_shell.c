#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>

void
print_line_start ()
{
  char cwd[100];
  getcwd (cwd, sizeof (cwd));

  char *user;
  user = getenv ("USER");

  //applying colors green, blue, white
  //for BOLD just replace the initial 0 before the ; with a 1. BOLD 
  printf ("\033[1;32m%s:\033[1;34m%s\033[0;37m$ ", user, cwd);
}

int
check_dir_content (char *cmd, char *dir_tok)
{
  DIR *d = opendir (dir_tok);
  struct dirent *dir;

  if (d)
    {
      while ((dir = readdir (d)) != NULL)
      {
        for (int i = 0; dir->d_name[i] == cmd[i]; i++)
          {
            if (cmd[i] == '\0')
            {
              //printf ("found it!!");
              return 1;
            }
	        }
	    }
      closedir (d);
    }
  return 0;
}

char *
find_cmd (char *cmd)
{
  const char *sep = ":";
  char *str =getenv ("PATH");
  char *token;
  int result = 0;

  //printf ("Splitting string \"%s\" into tokens:\n",str);
  token = strtok (str, sep);
  while (token != NULL)
    {
      if  (check_dir_content (cmd, token) == 1)
      {
        //printf ("found");
        return token;
      }
      token = strtok (NULL, sep);
    }
  return NULL;
}

int
app_child_space(char *buf)
{
  char *cmd = strtok (buf, " ");
  char *exe_argv = strtok (NULL, " -");
  char *exe_argenv[] = {NULL};

  //search for first word token only
  char *path = find_cmd (cmd);
  if (path == NULL)
  {
    printf("Command not found!");
    return -1;
  }
  strcat (path, "/");
  strcat(path, cmd);
  execve (path, (char* const*)exe_argv, exe_argenv);

  return -1;
}

int
main (int argc, char *argv[])
{
  while (1)
  {
    print_line_start ();

    char buf[100];
    fgets (buf, 100, stdin);
    int len = strlen (buf);
    buf[len - 1] = 0;		// remove null pointer count

    if (len == 0)
	    continue;

    int pid = fork ();

    if (pid < 0)
    {
      printf ("Error forking");
      return -1;
    }
    //child
    else if (pid == 0)
	  {
      app_child_space(buf);
    }
    //parent
    else if (pid > 0)
    {
      int status;
      wait ( /*getpid (), */ &status);
      // printf ("Parent: child status is %d\n", WEXITSTATUS (status));
    }
  }
  return 0;
}
