/*
   Copyright (C) 1994,95,96,2002 Free Software Foundation, Inc.

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

#include "priv.h"
#include <fcntl.h>


/* Create a and return new node structure with DN as its physical disknode.
   The node will have one hard reference and no light references.  */
struct node *
diskfs_make_node (struct disknode *dn)
{
  struct node *np = malloc (sizeof (struct node));

  if (np == 0)
    return 0;

  np->dn = dn;
  np->dn_set_ctime = 0;
  np->dn_set_atime = 0;
  np->dn_set_mtime = 0;
  np->dn_stat_dirty = 0;

  mutex_init (&np->lock);
  np->references = 1;
  np->light_references = 0;
  np->owner = 0;
  np->sockaddr = MACH_PORT_NULL;

  np->dirmod_reqs = 0;
  np->filemod_reqs = 0;

  fshelp_transbox_init (&np->transbox, &np->lock, np);
  iohelp_initialize_conch (&np->conch, &np->lock);
  fshelp_lock_init (&np->userlock);

  return np;
}
