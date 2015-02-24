/* quadprim1mod4.c for quadratic fields, d = 1 mod 4, T J Dekker, 2007-2013. */
/* Include in quadprimes.c to draw pictures of primes and units in colors.   */
/* Optionally also prime non-principal ideals (co-ideals) are drawn.         */
/* The programs use subprograms from files quadchar.c and quadsiev.c         */
/* and programming environment of Xcode system.                              */

# define SMAX         89          //  (113)  maximum length character to draw	
# define CMIN         30          //  length of heading text

# define AMAX         470         //  (56) getallen x + y tau voor |x| <= AMAX	
# define BMAX         470         //  (50)                 en voor |y| <= BMAX					
# define QNORM(x, y)  abs(x*(x+y)+y*y*(1-discriminant)/4) // norm of x + y tau
# define peri         period/2+1  //  to draw chi over half double period +1

# define ideal                    //  empty if no co-ideals are drawn
# define testx                    //  empty test
		   		
/*  Select class number either 1, 2, or 3, and corresponding radicand row.
Moreover, optional include to draw prime co-ideals.
*/

int clas = 1, radicand[] = {-163,-67,-43,-19,-11,-7,-3,5,13,17,21,29,0};
//int clas = 2, radicand[] = {-427,-403,-123,-115,-91,-51,-35,-15,65,85,0};
//# include "quadideal2.c"
//int clas = 3, radicand[] = {-907,-211,-139,-107,-83,-59,-31,-23,229,257,0};
//# include "quadideal3.c"

void printnumber(int x, int y, char c)
{
  printf("\t\t\t{{%d,%d}, \"%c\"},\n",x,y,c);
}

void picture() /* draws picture of primes, units and option prime ideals */
{   
  int a, b, norm;
  char c;
  for (b = -BMAX; b <= BMAX; b++) 
    for (a = -(2*AMAX+b)/2; a <= (2*AMAX-b)/2; a++)  
      {	
	norm = QNORM(a, b);	
	if (norm < maxnorm)
	  {	
	    if (inset(norm, prinorm)) 
	      IsPrime;
	    else if (norm == 1) 
	      IsUnit;
	    testx  // optional extra test for co-ideals
	    else goto nodraw; 
	   // draw diamond at given central coordinates:
	    printnumber(a,b,c);
	  }
      nodraw: ;
      }
  printf("\t\t}\n");
  printf("\t},\n");
}   /*  end picture  */



