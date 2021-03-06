/* -----------------------------------------------------------------------
   ffi_powerpc.h - Copyright (C) 2013 IBM
                   Copyright (C) 2011 Anthony Green
                   Copyright (C) 2011 Kyle Moffett
                   Copyright (C) 2008 Red Hat, Inc
                   Copyright (C) 2007, 2008 Free Software Foundation, Inc
                   Copyright (c) 1998 Geoffrey Keating

   PowerPC Foreign Function Interface

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   ``Software''), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
   ----------------------------------------------------------------------- */

enum {
  /* The assembly depends on these exact flags.  */
  /* These go in cr7 */
  FLAG_RETURNS_SMST	= 1 << (31-31), /* Used for FFI_SYSV small structs.  */
  FLAG_RETURNS_NOTHING  = 1 << (31-30),
  FLAG_RETURNS_FP       = 1 << (31-29),
  FLAG_RETURNS_64BITS   = 1 << (31-28),

  /* This goes in cr6 */
  FLAG_RETURNS_128BITS  = 1 << (31-27),

  FLAG_COMPAT		= 1 << (31- 8), /* Not used by assembly */

  /* These go in cr1 */
  FLAG_ARG_NEEDS_COPY   = 1 << (31- 7), /* Used by sysv code */
  FLAG_ARG_NEEDS_PSAVE  = FLAG_ARG_NEEDS_COPY, /* Used by linux64 code */
  FLAG_FP_ARGUMENTS     = 1 << (31- 6), /* cr1.eq; specified by ABI */
  FLAG_4_GPR_ARGUMENTS  = 1 << (31- 5),
  FLAG_RETVAL_REFERENCE = 1 << (31- 4)
};

typedef union
{
  float f;
  double d;
} ffi_dblfl;

void FFI_HIDDEN ffi_closure_SYSV (void);
void FFI_HIDDEN ffi_call_SYSV(extended_cif *, unsigned, unsigned, unsigned *,
			      void (*)(void));

void FFI_HIDDEN ffi_prep_types_sysv (ffi_abi);
ffi_status FFI_HIDDEN ffi_prep_cif_sysv (ffi_cif *);
int FFI_HIDDEN ffi_closure_helper_SYSV (ffi_closure *, void *, unsigned long *,
					ffi_dblfl *, unsigned long *);

void FFI_HIDDEN ffi_call_LINUX64(extended_cif *, unsigned long, unsigned long,
				 unsigned long *, void (*)(void));
void FFI_HIDDEN ffi_closure_LINUX64 (void);

void FFI_HIDDEN ffi_prep_types_linux64 (ffi_abi);
ffi_status FFI_HIDDEN ffi_prep_cif_linux64 (ffi_cif *);
ffi_status FFI_HIDDEN ffi_prep_cif_linux64_var (ffi_cif *, unsigned int,
						unsigned int);
void FFI_HIDDEN ffi_prep_args64 (extended_cif *, unsigned long *const);
int FFI_HIDDEN ffi_closure_helper_LINUX64 (ffi_closure *, void *,
					   unsigned long *, ffi_dblfl *);
