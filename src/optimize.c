#include "../incl/malloc.h"

 void	convert_to_tiny( t_slab *slb)
{
	t_block *s;
	t_block *t;

	s = slb->small;
	t = slb->tiny;
	if (slb->tiny_avail == 0 && slb->small_avail >= BLKCNT * .50)
	{
		while (s->next && !s->avail)
			s = s->next;
		while (t->next)
			t = t->next;
		if (!s->prev)
			slb->small = s->next;
		else if (s->prev && s->next)
		{
			s->prev->next = s->next;
			s->next->prev = s->prev;
		}
		link_blocks(slb, s, SMLSZ / (SBLKSZ + TNYSZ), TNYSZ);
		t->next = s;
		s->prev = t;
		slb->small_avail -= 1;
		slb->tiny_avail += SMLSZ / (SBLKSZ + TNYSZ);
	}
}

static t_block *find_tiny_grouping(t_slab *slb, size_t len)
{
	t_block *i;
	t_block *ret;
	size_t 	cnt;

	cnt = 0;
	i = slb->tiny;
	ret = i;
	while (i)
	{
		if (i->avail && cnt == 0)
			ret = i;
		cnt = i->avail ? cnt + 1: 0;
		if (cnt == len)
			return(ret);
		i = i->next;
	}
	return(NULL);
}

void convert_to_small(t_slab *slb)
{
	t_block *t;
	t_block *s;

	t = NULL;
	s = slb->small;
	if (slb->small_avail == 0 && slb->tiny_avail >= BLKCNT * .50)
	{
		if (!(t = find_tiny_grouping(slb, 8)))
			return;
		while (s->next)
			s = s->next;
		if (t->prev && (t_block*)((char*)t + ((SBLKSZ + TNYSZ) * 8)))
		{
			t->prev->next = (t_block *)((char *)t + ((SBLKSZ + TNYSZ) * 8));
			((t_block *)((char *)t + ((SBLKSZ + TNYSZ) * 8)))->prev = t->prev;
		}
		init_block(t);
		s->next = t;
		t->prev = s;
		slb->tiny_avail -= 8;
		slb->small_avail += 1;
		if (!slb->small_que)
			slb->small_que = t;
	}
}



t_block	*check_queue(t_slab *slb, size_t blksz)
{
	t_block *p;

	p = NULL;
	if (blksz == SMLSZ && slb->small_que){
		p = slb->small_que;
		slb->small_avail -= 1;
		if (p && p->next && p->next->avail == TRUE)
			slb->small_que = p->next;
		else
			slb->small_que = NULL;
	}
	if (blksz == TNYSZ && slb->tiny_que){
		p = slb->tiny_que;
		slb->tiny_avail -= 1;
		if (p && p->next && p->next->avail == TRUE)
			slb->tiny_que = p->next;
		else
			slb->tiny_que = NULL;
	}
	return (p);
}
