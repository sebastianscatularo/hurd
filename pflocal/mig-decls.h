/* Type decls for mig-produced server stubs

   Copyright (C) 1995 Free Software Foundation, Inc.

   Written by Miles Bader <miles@gnu.ai.mit.edu>

   This file is part of the GNU Hurd.

   The GNU Hurd is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   The GNU Hurd is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include "sock.h"

/* For mig */

typedef struct sock_user *sock_user_t;
typedef struct addr *addr_t;

extern inline
sock_user_t begin_using_sock_user_port(mach_port_t port)
{
  return (sock_user_t)ports_lookup_port (0, port, sock_user_port_class);
}

extern inline void
end_using_sock_user_port (sock_user_t sock_user)
{
  if (sock_user != NULL)
    ports_port_deref (sock_user);
}

extern inline
addr_t begin_using_addr_port(mach_port_t port)
{
  return (addr_t)ports_lookup_port (0, port, addr_port_class);
}

extern inline void
end_using_addr_port (addr_t addr)
{
  if (addr != NULL)
    ports_port_deref (addr);
}
