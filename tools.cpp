#include"tools.h"
int bangNum = 0;
void Bang::paintbangs(Node<Bang>*& cur, Node<Bang>*& pre, LinkList<Bang>& bangs)
{
	if (cur->content->countDown > 0)
	{
		cur->content->countDown--;
		transparentImage(NULL, cur->content->x, cur->content->y, &bang);
	}
	pre = cur;
	cur = cur->next;
	if (pre->content->countDown <= 0)
		bangs.DeleteNode(pre->content->No);
}
