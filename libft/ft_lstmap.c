

#include "libft.h"


t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *ad;
	t_list *ap;

	ad = NULL;
	while (lst)
	{
		ap = ft_lstnew(f(lst->content));
		if (!ap)
		{
			ft_lstclear(&ad, del);
			return (NULL);
		}
		ft_lstadd_back(&ad, ap);
		lst = lst->next;
	}
	return (ad);
}
