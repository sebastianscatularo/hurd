/* Reboot the system
   Copyright (C) 1994, 1996 Free Software Foundation, Inc.
   Written by Michael I. Bushnell.

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


#include <sys/reboot.h>
#include <unistd.h>
#include <stdio.h>
#include <argp.h>
#include <hurd.h>

char *argp_program_version = "reboot 1.1 (GNU " HURD_RELEASE ")";

int
main (int argc, char *argv[])
{
  struct argp argp = {0, 0, 0, "Reboot the system"};
  argp_parse (&argp, argc, argv, 0, 0, 0);
  reboot (0);
  perror ("reboot");
  return 1;
}
