/* Implementation of memory_object_init for pager library
   Copyright (C) 1994 Free Software Foundation

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

/* This is called by a kernel to initialize the memory object;
   this routine is a dual of seqnos_memory_object_terminate.  */
kern_return_t
seqnos_memory_object_init (mach_port_t object, 
			   mach_port_seqno_t seqno,
			   mach_port_t control,
			   mach_port_t name,
			   vm_size_t pagesize)
{
  struct pager *p;

  if (!(p = check_port_type (object, pager_port_type)))
    return EOPNOTSUPP;

  mutex_lock (&p->interlock);

  if (p->pager_state != NOTINIT)
    {
      printf ("pager dup init");
      goto out;
    }
  if (pagesize != __vm_page_size)
    {
      printf ("incg init: bad page size");
      goto out;
    }

  _pager_wait_for_seqno (p, seqno);

  p->memobjcntl = control;
  p->memobjname = name;
  if (p->pagemap || p->pagemapsize)
    panic ("pagemap failure");

  /* Tell the kernel we're ready */
  /* XXX Don't cache for now. */
  memory_object_ready (control, 0, MEMORY_OBJECT_COPY_NONE);

  p->pager_state = NORMAL;
  mutex_unlock (&p->interlock);

 out:
  _pager_done_with_port (p);
  return 0;
}
