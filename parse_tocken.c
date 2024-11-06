#include "minishell.h"

// void 	tocken_error(char *line, t_lexer **lexer, char *p)
// {
// 	write(2,"bash: syntax error near unexpected token", 41);
// 	return (0);
// }


int it_is_a_token(char c)
{

    if (c == '<')
        return (1);
    if (c == '>')
        return (2);
    if (c == '|')
        return (5);
    return (0);
}
int it_is_white_space(char c)
{
    if ((c >= 9 && c <= 13) || c == ' ')
        return (1);
    return (0);
}

int it_is_valid_token(char *s)
{
	int tocken;

	tocken = it_is_a_token(s[0]);
	if (tocken == 5)
	{
		if (it_is_a_token(s[1]) != 0)
			return (-5);
		return (5);
	}
	if (it_is_a_token(s[1]) == 0)
		return (tocken);
	if (tocken == it_is_a_token(s[1]))
	{
		if (it_is_a_token(s[2]) != 0)
			return (-1);
		if (tocken == 1)
			return (4);
		if (tocken == 2)
			return (3);
			
	}
	return (-2);
}
