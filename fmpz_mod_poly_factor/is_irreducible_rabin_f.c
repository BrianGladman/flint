/*
    Copyright (C) 2007 David Howden
    Copyright (C) 2007, 2008, 2009, 2010 William Hart
    Copyright (C) 2008 Richard Howell-Peak
    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 Lina Kulakova
    Copyright (C) 2014 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz.h"
#include "fmpz_mod_poly.h"
#include "ulong_extras.h"

int
fmpz_mod_poly_is_irreducible_rabin_f(fmpz_t fac, const fmpz_mod_poly_t f,
                                                      const fmpz_mod_ctx_t ctx)
{
    int res = 1;
    
    if (fmpz_mod_poly_length(f, ctx) > 2)
    {
        const slong n = fmpz_mod_poly_degree(f, ctx);
        fmpz_mod_poly_t a, x, x_p, finv;
        fmpz_mod_poly_frobenius_powers_2exp_t pow;

        fmpz_mod_poly_init(a, ctx);
        fmpz_mod_poly_init(x, ctx);
        fmpz_mod_poly_init(x_p, ctx);
        fmpz_mod_poly_init(finv, ctx);

        fmpz_mod_poly_set_coeff_ui(x, 1, 1, ctx);

        /* Compute x^q mod f */
        fmpz_mod_poly_reverse(finv, f, f->length, ctx);

        fmpz_mod_poly_inv_series_newton_f(fac, finv, finv, f->length, ctx);
           
        if (!fmpz_is_one(fac))
           goto cleanup;
        
        fmpz_mod_poly_frobenius_powers_2exp_precomp(pow, f, finv, n, ctx);
        
        fmpz_mod_poly_frobenius_power(x_p, pow, f, n, ctx);

        if (!fmpz_mod_poly_is_zero(x_p, ctx))
        {
           fmpz_mod_poly_make_monic_f(fac, x_p, x_p, ctx);

           if (!fmpz_is_one(fac))
              goto cleanup;
        }

        /* Now do the irreducibility test */
        if (!fmpz_mod_poly_equal(x_p, x, ctx))
        {
           res = 0;
        }
        else
        {
            n_factor_t factors;
            slong i;

            n_factor_init(&factors);
            n_factor(&factors, n, 1);

            for (i = 0; i < factors.num; i++)
            {
                fmpz_mod_poly_frobenius_power(a, pow, f, n / factors.p[i], ctx);

                fmpz_mod_poly_sub(a, a, x, ctx);

                if (!fmpz_mod_poly_is_zero(a, ctx))
                {
                   fmpz_mod_poly_make_monic_f(fac, a, a, ctx);

                   if (!fmpz_is_one(fac))
                      goto cleanup;
                }

                fmpz_mod_poly_gcd(a, a, f, ctx);

                if (a->length != 1)
                   res = 0;
            }
        }

cleanup:

        fmpz_mod_poly_frobenius_powers_2exp_clear(pow, ctx);
        fmpz_mod_poly_clear(finv, ctx);
        fmpz_mod_poly_clear(a, ctx);
        fmpz_mod_poly_clear(x, ctx);
        fmpz_mod_poly_clear(x_p, ctx);
    }

    return res;
}
