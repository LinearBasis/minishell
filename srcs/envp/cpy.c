#include "envp.h"

int	_fill_one_export(t_envp *out, char *env, int i)
{
	size_t	len;
	char	*a2;
	char	*a3;

	len = 0;
	while (env[len] != '=')
	{
		len++;
	}
	a2 = ft_substr_from_to(env, 0, len);
	if (len != ft_strlen(env) - 1)
		a3 = ft_substr_from_to(env, len + 1, (int)ft_strlen(env));
	else
		a3 = ft_strdup("");
	out->envp_key_value[0][i] = NULL;
	out->envp_key_value[1][i] = NULL;
	if (!a2 || !a3)
	{
		free(a2);
		free(a3);
		return (-1);
	}
	out->envp_key_value[0][i] = a2;
	out->envp_key_value[1][i] = a3;
	return (0);
}

int	_envp_copy(t_envp *out, char **envp, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (_fill_one_export(out, envp[j], j) != 0)
		{
			envp_clear(out);
			return (-1);
		}
		j++;
	}
	out->envp_key_value[0][i] = 0;
	out->envp_key_value[1][i] = 0;
	return (0);
}

int	_copy_envp_orig(t_envp *out, char **envp, int i)
{
	char	*add_to;
	int		j;

	j = 0;
	while (j < i)
	{
		add_to = ft_strdup(envp[j]);
		if (!add_to)
			return (MALLOC_ERROR);
		out->envp_cpy[j] = add_to;
		++j;
	}
	return (GOOD_RETURN);
}
