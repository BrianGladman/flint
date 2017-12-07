/*
    Copyright (C) 2017 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "mpoly.h"


void mpoly_gen_fields_ui(ulong * exp, slong var, const mpoly_ctx_t mctx)
{
    slong nvars = mctx->nvars;
    slong nfields = mctx->nfields;
    int deg = mctx->deg;
    int rev = mctx->rev;
    slong i;

    for (i = 0; i < nfields; i++)
        exp[i] = WORD(0);

    if (rev)
        exp[deg + nvars - 1 - var] = WORD(1);
    else
        exp[deg + var] = WORD(1);

    if (deg)
        exp[0] = WORD(1);

}

