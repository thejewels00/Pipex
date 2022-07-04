#include "pipex.h"

void	err(char *str)
{
	perror(str);
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	vars;
	int i;
	int	j;
	int	l;

	if (argc == 5)
	{
		i = pipe(vars.fileds);
		vars.pid = fork();

		if (vars.pid == 0)
		{
			vars.infile = open(argv[1], O_RDONLY);
			if (vars.infile == -1)
				err("infile");///errno
			j = dup2(vars.infile, 0);
			l = dup2(vars.fileds[1], 1); // dupi output m3a pipe
			if (j  == -1 || l == -1)
				err("dup2");// errno
			//execve();
			//child 2 ================================================================
			vars.pid_2 = fork();
			if (vars.pid_2 == 0)
			{
				// implementation de premiere commande 
				vars.outfile = open("outfile", O_CREAT | O_RDONLY | O_TRUNC);
				if (vars.outfile == -1)
					err("outfile");
				int o = dup2(vars.fileds[0], 0); // dupi output m3a pipe
				int q = dup2(vars.outfile, 1); // dupi output m3a pipe
				if (o == -1 || q == -1)
					err("dup2");
			}
		}
	}
	else 
		exit(write(1, "Error : nombre d'argument different a 4 \n", 41));
}