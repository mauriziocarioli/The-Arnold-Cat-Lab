/* Subprograms and bit handling for sieve of prime norms, T.J. Dekker 2003 */
/* Space saving:  pneven for even, prinorm for odd prime norms,   TJD 2005 */

# define   WORD 16  // number of bits per word used
# define  INDEX(i) i >> 5  // i/2 divided by 16
# define    BIT(i) (1 << ((i>>1) & 15))  // 2^(i/2 % 16)
# define  INSET(i, prinorm) (prinorm[INDEX(i)] &  BIT(i)) != 0  
# define    ADD(i, prinorm) prinorm[INDEX(i)] |=  BIT(i)  
# define REMOVE(i, prinorm) prinorm[INDEX(i)] &= ~BIT(i)  
	
int pneven;  /* the only even prime norm, 2 or 4, for space saving */
	
int capacity(int size)  /* returns size times number of bits per word used */
{	
  return 2 * size * WORD;
}  /* end capacity, doubled by space saving */
	
void makedelta(int qchar[])
/*  deltac[period] = difference of odd numbers of positive character */
{	
  int c, cnext; 
  extern int period; 
  extern int deltac[];
  for (c = period -1, cnext = period +1; c > 0; c -= 2)
    if (qchar[c] == 1) 
      { 
	deltac[c] = cnext-c; 
	cnext = c; 
      }
}   /*  end makedelta  */

int qnext(int k)  /* returns next odd number of positive character */
{	
  extern int period; extern int deltac[]; 
  return k + deltac[k % period]; 
}   /*  end qnext  */
	
void addeven(int i)  /* assigns the only even prime norm to pneven */
{	
  extern int pneven; 
  pneven = i;
}  /* end addeven, for space saving */
	
int inset(int i, short prinorm[])
/*  returns 1 (true) if i is a prime norm, or 0 (false) otherwise */
{	
  extern int pneven;
  if (i % 2 == 0) 
    return i == pneven; 
  else 
    return INSET(i, prinorm); 
}   /*  end inset, modified for space saving  */

void sieve(int size, int nf, int max, int fac[], int next(), short prinorm[])
/*  sieve calculates a set containing all norms < max of prime ideals
            of a quadratic field, excluding norms of composite numbers.
    The method is a sieve algorithm akin to sieve of Eratosthenes;
    size must not exceed the size of prinorm, and nf that of fac;
    fac[0..nf-1] must contain the prime factors of the discriminant and
            number 2 or 4 if discriminant == 1 or 5 modulo 8 respectively;
    next must generate the successive odd numbers of positive character.
    max must not exceed size times number of bits per word used.
    The result is delivered in prinorm[0..size-1].  */
{	
  int i, k, m, im, maxim;
  for (i = 0; i < size; i++) 
    prinorm[i] = 0;   /* Initialize prinorm */
  addeven(fac[0]);  /* add the even prime norm, 2 or 4, space saving */
  for (k = 1; k < nf; k++)  
    { 
      i = fac[k]; 
      ADD(i, prinorm); 
    } 
  for (i = next(1); i < max; i = next(i)) 
    ADD(i, prinorm);
/*  Initialisation completed; prinorm is ready to start sieve process. */
  for (i = next(1); i <= (maxim = (max-1)/i); i = next(i))
    {	
      if (INSET(i, prinorm))  /* remove multiples of i */
	for (m = i; m <= maxim; m = next(m)) 
	  {	
	    im = i * m; 
	    REMOVE(im, prinorm); 
	  }
    }
}   /*  end sieve  */
	
void sievquad(int nf, int fac[], int qchar[], int size, int max, short pnrm[])
/*  sievquad delivers a set of all prime ideal norms < max in prinorm[size].
    The quadratic field is determined by fac[nf] and qchar[MAXPERIOD] which
    must contain prime factors of discriminant and character of the field.  */
{	
  makedelta(qchar);
  sieve(size, nf, max, fac, qnext, pnrm);
}   /*  end sievquad  */
