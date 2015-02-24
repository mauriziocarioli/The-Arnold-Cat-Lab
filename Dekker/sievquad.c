/* Subprograms and bit handling for sieve of prime norms, T J Dekker 2003. */

# define   WORD 16  // number of bits per word used	
# define  INDEX(i) i >> 4  // i divided by 16
# define    BIT(i) (1 << (i & 15))  // 2 power(i % 16)
# define  INSET(i, prinorms) (prinorms[INDEX(i)] &  BIT(i)) != 0  
# define    ADD(i, prinorms) prinorms[INDEX(i)] |=  BIT(i)  
# define REMOVE(i, prinorms) prinorms[INDEX(i)] &= ~BIT(i)  
	
int capacity(int size) /* returns size times number of bits per word used */
{	
  return size * WORD;	
}  /*  end capacity  */
	
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
  extern int period; 
  extern int deltac[]; 
  return k + deltac[k % period]; 
}   /*  end qnext  */
	
int inset(int i, short prinorm[])
/*  returns value 1 (true) or 0 (false) of the i-th bit in prinorm[] */
{	
  return INSET(i, prinorm); 
}	/*  end inset  */

void sieve(int size, int nf, int max, int fac[], int next(), short prinorm[])
/*  sieve calculates a set containing all norms < max of prime ideals
            of a quadratic field, excluding norms of composite numbers.
    The method is a sieve algorithm akin to sieve of Eratosthenes;
    size must not exceed the size of prinorm, and nf that of fac;
    fac[0..nf-1] must contain the prime factors of the discriminant and
            number 2 or 4 if discriminant == 1 or 5 modulo 8 respectively;
    next must generate the successive odd numbers of positive character;
    max must not exceed size times number of bits per word used.
    The result is delivered in prinorm[0..size-1].  
    (In particular, one would get natural primes for discriminant == 1, 
            i.e. putting nf == 1 and fac[0] == 2.)  */
{	
  int i, k, m, im, maxim;
/*  Initialize prinorm  */
  for (i = 0; i < size; i++) 
    prinorm[i] = 0; 
  for (k = 0; k < nf; k++)  
    { 
      i = fac[k]; 
      ADD(i, prinorm); 
    } 
  for (i = next(1); i < max; i = next(i)) 
    ADD(i, prinorm);
/*  Initialisation completed; prinorm ready to start sieve process.  */
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
