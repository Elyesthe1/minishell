/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:06:46 by erahal            #+#    #+#             */
/*   Updated: 2024/11/04 15:58:48 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int quote(char *loc, char *ligne)
{
	
	int qote;
	int simple;

	simple  = 0;
	qote =  0;
	int i = 0;
	while (&ligne[i] != loc)
	{
		if (ligne[i] == '\'' && simple == 0)
			simple = 1;
		if (ligne[i] == '\'' && simple == 1)
			simple = 0;
		if (ligne[i] == '\"' && qote == 0)
			qote = 1;
		if (ligne[i] == '\'' && qote == 1)
			qote = 0;
	}
	return (qote + simple);
}

int main(int ac, char **av)
{
	int i = 0;
	char *s = " 'C'est un beau jour !'";
	printf("la phrase =%s\n", s);
	while (s[i])
	{
		printf("suis entre qote = %c %d\n", s[i] , quote(s[i]));
		i++;	
	}
}
