
#include "minishell.h"

int	start_unset(char **cmd, t_env_var *env_var)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if ((int)ft_two_strlen(cmd) - 1 >= 1)
	{
		infile_make(cmd);
		while (cmd[++i])
		{
			if (!((65 <= cmd[i][0] && cmd[i][0] <= 90) || cmd[i][0] == 95
				|| (97 <= cmd[i][0] && cmd[i][0] <= 122)))
			{
				ft_putstr_fd("bash: unset: `", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				status = 1;
				continue ;
			}
			del_env(cmd[i], env_var);
			del_exp(cmd[i], env_var);
		}
	}
	return (status);
}
