/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 William Hart
    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <mpir.h>
#include <stdlib.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"

void fmpq_poly_init(fmpq_poly_t poly)
{
    poly->coeffs = NULL;
    fmpz_init(poly->den);
    fmpz_set_ui(poly->den, 1UL);
    poly->alloc  = 0;
    poly->length = 0;
}

void fmpq_poly_init2(fmpq_poly_t poly, long alloc)
{
    if (alloc)  /* Allocate space for alloc small coeffs */
    {
        poly->coeffs = (fmpz *) calloc(alloc, sizeof(fmpz));
    }
    else
    {
        poly->coeffs = NULL;
    }
    
    fmpz_init(poly->den);
    fmpz_set_ui(poly->den, 1UL);
    poly->alloc  = alloc;
    poly->length = 0;
}

