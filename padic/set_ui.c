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

    Copyright (C) 2011 Sebastian Pancratz
 
******************************************************************************/

#include "padic.h"

void _padic_set_ui(padic_t rop, ulong op, const padic_ctx_t ctx)
{
    if (op == 0)
    {
        padic_zero(rop);
    }
    else if (fmpz_cmp_ui(ctx->p, op) > 0)
    {
        fmpz_set_ui(padic_unit(rop), op);
        padic_val(rop) = 0;
    }
    else
    {
        ulong p = fmpz_get_ui(ctx->p), q, r;

        /* Remove factors of p */
        padic_val(rop) = 0;
        r = n_divrem2_precomp(&q, op, p, ctx->pinv);
        while (r == 0)
        {
            op = q;
            padic_val(rop)++;
            r = n_divrem2_precomp(&q, op, p, ctx->pinv);
        }

        fmpz_set_ui(padic_unit(rop), op);
    }
}

void padic_set_ui(padic_t rop, ulong op, const padic_ctx_t ctx)
{
    _padic_set_ui(rop, op, ctx);
    _padic_reduce(rop, ctx);
}

