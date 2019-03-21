/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:08:36 by nrechati          #+#    #+#             */
/*   Updated: 2019/03/21 18:43:27 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"
#include <stdio.h>
#define MAP_SIZE 128
									//TODO : Insertion multiple time same key
void	del_hnode(t_list	*node)
{
	free(((t_hnode*)node->data)->key);
	((t_hnode*)node->data)->key = NULL;
	free(((t_hnode *)node->data)->data);
	((t_hnode *)node->data)->data = NULL;
	free(node->data);
	free(node);
}

void	print_hashmap(t_hash *hashmap)
{
	ft_printf("\n		. . . Printing . . .\n\n");
	size_t		i;
	t_list		*ptr;

	i = 0;
	while (i < hashmap->map_size)
	{
		if (hashmap->map[i] != NULL)
		{
			ft_printf("| %zu | :", i);
			ptr = hashmap->map[i];
			while (ptr != NULL)
			{
				ft_printf(" | Key = %s -> Data = %s | -"
				, ((t_hnode*)ptr->data)->key, ((t_hnode*)ptr->data)->data);
				ptr = ptr->next;
			}
			ft_printf(" NULL\n");
		}
		i++;
	}
}

int		create_hnode(t_list **alst, char *key, void *data)
{
	t_hnode h_node;
	t_list *newdir;

	if (key == NULL)
		return (0);
	ft_bzero(&h_node, sizeof(t_hnode));
	h_node.key = ft_strdup(key);
	h_node.data = data;
	if (h_node.key == NULL || h_node.data == NULL)
		return (0);
	if (!(newdir = ft_lstnew(&h_node, sizeof(t_hnode))))
		return (0);
	ft_lstaddend(alst, newdir);
	return (1);
}

t_hash	ft_init_hashmap(void)
{
	t_hash data;

	data.used = 0;
	data.map_size = MAP_SIZE;
	data.map = ft_memalloc(data.map_size * sizeof(t_list*));
	return (data);
}

int		ft_hash_remove(t_hash *hashmap, char *key) //CHECK FIRST
{
	uint32_t	hash;
	t_list		*ptr;
	t_list		*tmp;

	hash = ft_norm_hash(ft_hash_str(key), hashmap->map_size);
	ptr = hashmap->map[hash];
	while (ptr->next != NULL)
	{
		if (!ft_strcmp(((t_hnode*)ptr->next->data)->key, key))
		{
			tmp = ptr->next->next;
			del_hnode(ptr->next);
			ptr->next = tmp;
		}
		ptr = ptr->next;
	}
	if (hashmap->used > 0)
		hashmap->used -= 1;
	return (1);
}

int		ft_hash_insert(t_hash *hashmap, char *key, void *data)
{
	uint32_t hash;

	hash = ft_norm_hash(ft_hash_str(key), hashmap->map_size);
	ft_printf("%s Hash = %u\n", key, hash);
	if (!create_hnode(&hashmap->map[hash], key, data))
		return (0);
	hashmap->used += 1;
	return (1);
}

int		main(int ac, char **av)
{
	int		i;
	t_hash	hashmap;

	i = 1;
	hashmap = ft_init_hashmap();
	if (!hashmap.map)
	{
		return (0);
	}
	if (ac < 2)
		return (0);
	while (av[i] != NULL)
	{
		ft_printf("Adding %s Key with %s Data\n", av[i], av[i + 1]);
		ft_hash_insert(&hashmap, av[i], av[i + 1]);
		i += 2;
	}
	print_hashmap(&hashmap);
	ft_hash_remove(&hashmap, "ls");
	ft_hash_remove(&hashmap, "echo");
	print_hashmap(&hashmap);
	return (0);
}