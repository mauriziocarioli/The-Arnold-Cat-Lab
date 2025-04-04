/* Subprograms to calculate character of quadratic fields, T J Dekker, 2003. */
/* disfactors calculates discriminant of given field and its prime factors,  */
/* quadres and quadchar calculate the character of given quadratic field.    */

# include <stdlib.h>

void disfactors (int rad, int *dis, int *nf, int factor[])
/*  Given:   integer rad, radicand of a quadratic field. 
    Results: dis = discriminant of the field,
             nf = number of distinct prime factors of 2 * dis,
             factor[0] = the (unique) even prime norm in the field, i.e.
                 if dis modulo 8 = 5 then 4, otherwise 2
                 (in behalf ofinitialization of the sieve process),      
             factor[1: nf-1] = odd prime factors of dis increasingly.  */
{	
  int n = rad, k = 0, a, p, pp;
  while (n != 0 && n % 4 == 0) 
    n /= 4; // remove factors 4 
  a = abs (n);
  if ((n-1) % 4 != 0) // discriminant not congruent 1 modulo 4 
    {	
      n *= 4; 
      if (a % 2 == 0) 
	a /= 2; 
    } // dis == 4 * radicand
  factor[k++] = ((n-5) % 8 == 0) ? 4 : 2; // to initialize sieve
  for (p = 3; (pp = p * p) <= a; p += 2)
    {	
      while (a % pp == 0) 
	{ 
	  a /= pp; 
	  n /= pp; 
	} // remove squares
      if (a % p == 0) 
	{ 
	  a /= p; 
	  factor[k++] = p; 
	} // factor p
    }	/* end for p */
  if (a > 1) 
    factor[k++] = a;
  *dis = n; *nf = k;
}   /*  end discrifactors  */

void quadres (int p, int qchar[])
/*  Given: odd natural prime p. Result qchar[0: p-1] = quadratic character.  */
{	
  int x; 
  qchar[0] = 0;
  for (x = 1; x < p; x++) 
    qchar[x] = -1;
  for (x = 1; x * 2 < p; x++) 
    qchar[x * x % p] = 1;
}   /*  end quadres  */

void quadchar (int dis, int nf, int factor[], int *per, int qchar[])
/*  Given:   discriminant dis of a quadratic field,
             number nf of distinct prime factors of 2 * dis,
             factor[1: nf-1] prime factors of dis increasingly.
    Results: per = period of quadratic character of the field,
             qchar[0: per-1] = quadratic character of the field.  */
{	
  int p, q, pq, k, n, *pchar, qchar48[]= {0,1,0,1,0,-1,0,-1,0,1};
  pq = 1; 
  qchar[0] = 1;
  for (k = 1; k < nf; k++)
    {	
      p = factor[k]; 
      q = pq; 
      pq = p * q; 
      pchar = qchar + ((k == 1) ? 0 : pq); 
      quadres(p, pchar);
      if (k > 1)  // multiply characters:
	for (n = pq-1; n >= 0; n--)
	  qchar[n] = pchar[n % p] * qchar[n % q]; 
    }	/* end for k */
  if (dis % 4 != 0) // double period
    {	
      for (n = 0; n < pq; n++) 
	qchar[n + pq] = qchar[n]; 
      pq *= 2;
    }      
  else 
    {	
      switch ((abs(2 * dis) + dis / 4) % 8) // radicand modulo 8
	{	
	case 3: 
	case 7: 
	  p = 4; 
	  pchar = qchar48 + 2; 
	  break;
	case 2: 
	  p = 8; 
	  pchar = qchar48 + 2; 
	  break;
	case 6: 
	  p = 8; 
	  pchar = qchar48; 
	  break;
	default: 
	  p = 0; 
	  break;
	}	/* end switch */
      q = pq; 
      pq = p * q; // multiply characters:
      for (n = pq-1; n >=0; n--) 
	qchar[n] = pchar[n % p] * qchar[n % q];
    }
  *per = pq; 
}   /*  end quadchar  */
