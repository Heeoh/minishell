/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:42 by heson             #+#    #+#             */
/*   Updated: 2023/03/15 21:51:19 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// export = -> bash: export: `=': not a valid identifier (error)
// export hhh -> nothing
// export hhh= -> make nex env 'hhh' but value is empty

// export water="삼다수"
// export TEMP_DIR=/tmp
// export BASE_DIR=$TEMP_DIR/backup

/*
1. main에서 받아온 환경변수를 복사해서 minishell에서 쓰는 환경변수를 따로 만들어야 함
2. parameter로 커스텀된 환경변수와 (전역변수로 안만든다면) 추가할 환경변수 문자열을 받음
3. 환경변수 문자열이 valid 한지 확인
	- name=value 형태로 되어 있어야 함
	- name, = 사이에 공백이 있을 수 없음, = , value 사이에 공백이 있을 경우 공백만 value로 인식됨
	- value는 없을 수 있으며, 이 때에도 =은 반드시 있어야 됨 -> = 없으면 무시됨
	- value는 "", ''로 쌓여져 있을 수 있으며, value에 공백이 포함되어 있을 경우 반드시 ""/'' 안에 있어야 함
	- ""/'' 안에 포함되지 않은 공백 이후 값은 무시됨
	- value에 환경변수를 사용할 수 있음, 이때 ' ' 안에 포함된 $환경변수는 값이 치환되지 않음
4. 이미 존재하는 환경변수인지 확인
	- 이미 존재한다면 새로운 값으로 업데이트
	- 없다면 새로 추가
*/

#include "../../library/libft/libft.h"
#include <stdio.h>
typedef struct s_env_var {
    char    *key;
    char    *value;
	char	is_tmp;
}   t_env_var;

// int check_right_var_key(char *key)
// {
// 	if (!key)
// 		return (-1);
// 	if (!ft_isalpha(*key))
// 		return (-1);
// 	return (0);
// }

// int	check_right_var_val(char *val)
// {
// 	char	quote_flag;

// 	// '' || "" 안에 둘러싸여져 있는지 확인
// 	// quote o -> " " || ' ' 사이에 있는 문자는 하나의 문자열로 인식
// 	// quote 나올 때가지 포인터 이동, 나오면 quote전까지 strcat, close quote 나올때까지 다시 이동 quote 사이 통채로 strcat
// 	if (!val)
// 		return (-1);
	
// }

// void	add_an_env_var(t_list **env_lst, char *arg)
// {
// 	t_env_var	*new_var;
// 	if (!arg || !*arg)
// 		return ;
// 	new_var = create_env_var(arg);
// 	if (!check_right_var_key(new_var->key) || !check_right_var_val(new_var->value))
// 		return ;
// 	ft_lstadd_back(env_lst, ft_lstnew(new_var));
// }

t_list	*sort_env_lst(t_list *org_lst)
{
	t_list	*sorted
}

void	print_env_lst(t_list *env_lst)
{
	t_list	*p;

	p = env_lst;
	while(p)
	{
		printf("%s=%s\n", ((t_env_var *)p->content)->key, ((t_env_var *)p->content)->value);
		p = p->next;
	}
}

int ft_export(t_cmd *cmd, t_list **env_lst) {
	char	*p;

	p = cmd->av + 1;
	if (cmd->ac == 1) // 전체 출력
	{
		// 오름차순 정렬 
		// 출력
	}
	else // 추가
	{
		// 알맞은 형태인지 체크
		// 리스트에 추가
		while (p && *p)
			add_an_env_var(env_lst, *p);
	}
}


void	free_env_var(t_env_var	*arg)
{
	if (arg->key)
		free(arg->key);
	if (arg->value)
		free(arg->value);
	free(arg);
}

t_env_var	*create_env_var_struct(char *key, char *val, char is_tmp)
{
	t_env_var	*ret;

	ret = (t_env_var *)malloc(sizeof(t_env_var *));
	if (!ret)
		return (NULL);
	ret->is_tmp = is_tmp;
	ret->key = key;
	ret->value = val;
	return (ret);
}

t_env_var	*create_env_var(char *arg)
{
	char		*eq_pos;
	char		*key;
	char		*val;
	int			key_len;
	int			val_len;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
	{
		key_len = ft_strlen(arg);
		val_len = 0;
	}
	else
	{
		key_len = ft_strlen(eq_pos - arg);
		val_len = ft_strlen(arg) - (eq_pos - arg) - 1;
	}
	key = (char *)malloc(key_len + 1);
	val = (char *)malloc(val_len + 1);
	ft_strlcpy(key, arg, key_len + 1);
	*val = '\0';
	if (eq_pos)
		ft_strlcpy(val, eq_pos + 1, val_len + 1);
	return (create_env_var_struct(key, val, !eq_pos));
}

// t_list	*init_env(char *org_env[])
// {
// 	t_list	*mini_env;

// 	mini_env = NULL;
// 	while (org_env && *org_env)
// 		// ft_lstadd_back(&mini_env, *org_env++);
// 		// ft_lstadd_back(&mini_env, ft_lstnew((void *)create_env_var(*org_env++)));
// 		// ft_lstadd_back(&mini_env, *org_env++));

// 	return (mini_env);
// }

int main(int ac, char *av[], char *env[]){

	t_list	*mini_env;

	t_env_var *a = create_env_var("");
	a ? printf("%s, %s\n", a->key, a->value) : printf("(null)\n");
	// mini_env = init_env(env);
	// t_list	*p = mini_env;
	// while (p)
	// {
	// 	printf("key: %s, name: %s\n", ((t_env_var*)p->content)->key, ((t_env_var*)p->content)->value);
	// 	p = p->next;
	// }


	// printf("%s\n", getenv("water"));
	// ft_export("water=삼다수");
	// printf("%s\n", getenv("water"));
}