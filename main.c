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
		vars.cmd1 = ft_split(argv[2], ' ');
		vars.cmd2 = ft_split(argv[3], ' ');
		vars.path  = NULL;
		// extration de path  from envirenoment
		while (env[i] && vars.path == NULL)
		{
			vars.path = ft_strnstr(env[i], "PATH", 5);
			i++;
		}
		vars.path = ft_substr(vars.path, 4, ft_strlen(vars.path) - 4);
		vars.env = ft_split(vars.path, ':');
		if (vars.pid == 0)
		{ //  child 1 ===========================
			vars.infile = open(argv[1], O_RDONLY);
			if (vars.infile == -1)
				err("infile");///errno
			j = dup2(vars.infile, 0);
			l = dup2(vars.fileds[1], 1); // dupi output m3a pipe
			if (j  == -1 || l == -1)
				err("dup2");// errno
			j = -1;
			i = 0;
			vars.cmd = ft_strjoin("/", vars.cmd1[0]);
			while (j == -1 && vars.env[i])
			{
				vars.jn = ft_strjoin(vars.env[i], vars.cmd);
				j = access(vars.jn, X_OK);
				i++;
			}
			j = execve(vars.jn, vars.cmd1, env);
			if (j == -1)
				err("execve");
			//child 2 ================================================================
			vars.pid_2 = fork();
			if (vars.pid_2 == 0)
			{
				// implementation de premiere commande 
				vars.outfile = open(argv[5], O_CREAT | O_RDONLY | O_TRUNC); // trunk :D 
				if (vars.outfile == -1)
					err("outfile");
				int o = dup2(vars.fileds[0], 0); // dupi output m3a pipe
				int q = dup2(vars.outfile, 1); // dupi output m3a pipe
				if (o == -1 || q == -1)
					err("dup2");
					// seconde commande 
				j = -1;
				i = 0;
				vars.cmd = ft_strjoin("/", vars.cmd2[0]);
				while (j == -1 && vars.env[i])
				{
					vars.jn = ft_strjoin(vars.env[i], vars.cmd);
					j = access(ft_strjoin(vars.env[i], vars.cmd), X_OK);
					i++;
				}
				j = execve(vars.jn, vars.cmd2, env);
				if (j == -1)
					err("execve");
			}
		}
	}
	else 
		exit(write(1, "Error : nombre d'argument different a 4 \n", 41));
}