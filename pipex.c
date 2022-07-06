#include "pipex.h"

void	err(char *str)
{
	perror(str);
	exit(0);
}

int main(int argc, char **argv,char **env)
{
	t_data	vars;
	int		i;
	int 	j;

	if (argc == 5)
	{
		i = 0;
		printf("Pipex\n"); // rm
		if (pipe(vars.pip_fds) == -1)
			err("PIPE");
		vars.cmd1 = ft_split(argv[2], ' ');
		vars.cmd2 = ft_split(argv[3], ' ');
		vars.path = NULL;
		while (env[i] && vars.path == NULL)
		{
			vars.path = ft_strnstr(env[i], "PATH", 5);
			i++;
		}
		printf("%s\n",vars.path);// rm  pour verifier que Path est vrai :D
		vars.path = ft_substr(vars.path, 5, ft_strlen(vars.path) - 5);
		printf("%s\n",vars.path); //  rm verier path is cleaar :)
		vars.env = ft_split(vars.path, ':');
		i = 0;//rm
		printf("my split path\n");// remove
		while (vars.env[i]) //  remove 
		{
			printf("%s\n", vars.env[i]); //rm
			i++;//rm
		} //rm
		// Now i'm forking :) for first child :D
		vars.pid = fork(); // RFM
		if (vars.pid == 0)
		{
			printf("i'm a first child :D\n");
			vars.infile = open(argv[1], O_RDONLY);// open file
			printf("my infile FD %d\n",vars.infile);//rm
			printf("my pip in :D %d\n",vars.pip_fds[1]); // rm
			if (vars.infile == -1)
				err("infile");//with errno :D RFM
			if (dup2(vars.infile, 0) == -1 || dup2(vars.pip_fds[1], 1) == -1)
				err("Dup2"); // Dup 2 error
			close(vars.infile);
			close(vars.pip_fds[1]);
			//fprintf(stderr, "my infile FD %d\n",vars.infile);//rm
			//fprintf(stderr, "my pip in :D %d\n",vars.pip_fds[1]); // rm
			vars.cmd = ft_strjoin("/", vars.cmd1[0]); // join  ma commande avec /
			fprintf(stderr, "my cmd join %s \n", vars.cmd); //rm
			// join commande avec PATH qui correspond
			j = -1;
			i = 0;
			while (j == -1 && vars.env[i])
			{
				vars.jn = ft_strjoin(vars.env[i], vars.cmd);
				j = access(vars.jn, X_OK);
				i++;
			}
			fprintf(stderr,"commande path :%s \n",vars.jn); // rm
	
			
			vars.cmd1[0] = ft_strdup(vars.jn);
			fprintf(stderr,"%s+++++\n", vars.cmd1[0]); //rm
			if (execve(vars.cmd1[0], vars.cmd1, env) == -1)  // swli wach ghire f cas success fach ket blocki execve lkmala ?
				err("execve");
			fprintf(stderr, "Ma3amrni maghada ntprinta :P");//rm
		}
		else
		{
			printf("i'm a father :D  1\n"); 
			wait(NULL);
		}
		close(vars.infile);
		printf("im a father after cmde 1\n");
		vars.pid_2 = fork();
		if (vars.pid_2 == 0)
		{
			// i'm in child
			printf("i'm a child 2\n");
			vars.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC,  0644);// open file
			printf("my outfile FD %d\n",vars.outfile);//rm
			printf("my pip in :D %d\n",vars.pip_fds[0]); // rm
			if (vars.outfile == -1)
				err("outfile");//with errno :D RFM
			if (dup2(vars.outfile, 1) == -1 || dup2(vars.pip_fds[0], 0) == -1)
				err("Dup2"); // Dup 2 error
			close(vars.pip_fds[0]);
			close(vars.outfile);
			//fprintf(stderr, "my infile FD %d\n",vars.infile);//rm
			//fprintf(stderr, "my pip in :D %d\n",vars.pip_fds[1]); // rm
			vars.cmd = ft_strjoin("/", vars.cmd2[0]); // join  ma commande avec /
			fprintf(stderr, "my cmd 2 join %s \n", vars.cmd); //rm
			// join commande avec PATH qui correspond
			j = -1;
			i = 0;
			while (j == -1 && vars.env[i])
			{
				vars.jn = ft_strjoin(vars.env[i], vars.cmd);
				j = access(vars.jn, X_OK);
				i++;
			}
			fprintf(stderr,"commande path :%s \n",vars.jn); // rm
			if (execve(vars.jn, vars.cmd1, env) == -1)  // swli wach ghire f cas success fach ket blocki execve lkmala ?
				err("execve");
			fprintf(stderr, "Ma3amrni maghada ntprinta :P");//rm
		}
		else 
		{
			printf("i'm a father :D  2\n"); 
		}
	}
	else
	{
		write(2, "usage : infile \"cmd1 -options\" \"cmd2 - option\" outfile\n", 56);
	}
			waitpid(vars.pid, 0, 0); //here
			//waitpid(vars.pid_2, 0, 0); //here
}