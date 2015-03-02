/* tinygraph -- exploring graph conjectures on small graphs
   Copyright (C) 2015  Falk Hüffner

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.  */

#ifndef TINYGRAPH_WORDSIZE_H_INCLUDED
#define TINYGRAPH_WORDSIZE_H_INCLUDED

// change to 64 for larger range of n, or 16 for possibly faster processing
#define WORDSIZE 16

#if WORDSIZE != 16 && WORDSIZE != 32 && WORDSIZE != 64
#error WORDSIZE must be 16, 32, or 64
#endif

#define MAXN WORDSIZE

#endif // TINYGRAPH_WORDSIZE_H_INCLUDED
