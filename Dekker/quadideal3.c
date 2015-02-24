/* quadideal3.c for quadratic fields of class nr 3.  T J Dekker, 2012-2013. */
/* Include in quadprim0mod4.c and quadprim1mod4.c to draw prime co-ideals.  */
/* The programs use subprograms from files quadchar.c and quadsiev.c        */
/* and programming environment of Xcode system.                             */


int bynorm, shift, natp[] = {2, 3, 5, 7, 11, 13};

# undef   CMIN
# define  CMIN       55 

# undef  ideal
# define ideal       param(); 

# undef  testx
# define testx  else if (norm % bynorm==0 && inset(norm/bynorm, prinorm)) \
    if ((a - shift * b) % bynorm == 0) IsCoIdeal; else IsIdeal;

void param()  /*  calculates and draws bynorm (1st chi > 0) and shift  */
{	
  int k; 
  char q[50];
  for (k = 0; qchar[natp[k]] <= 0; k++) 
    ; 
  bynorm = natp[k];
  for (k = 0; QNORM(k, 1) % bynorm != 0 && k < 9; k++)
    ; 
  shift = k;
  printf("\"bynorm\",%d,\"shift\",%d,\n\t\t", bynorm, shift); 
}   /*  end param  */
