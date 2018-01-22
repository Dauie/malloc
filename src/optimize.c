#include "../incl/malloc.h"

 void	optimize_slab( t_slab *slb)
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


t_block	*check_queue(t_slab *mgr, size_t blksz)
{
	t_block *p;

	p = NULL;
	if (blksz == SMLSZ && mgr->small_que){
		p = mgr->small_que;
		mgr->small_avail -= 1;
		if (p->next && p->next->avail == TRUE)
			mgr->small_que = p->next;
		else
			mgr->small_que = NULL;
	}
	if (blksz == TNYSZ && mgr->tiny_que){
		p = mgr->tiny_que;
		mgr->tiny_avail -= 1;
		if (p->next && p->next->avail == TRUE)
			mgr->tiny_que = p->next;
		else
			mgr->tiny_que = NULL;
	}
	return (p);
}
