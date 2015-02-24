/* quadprim0mod4.c for quadratic fields, d = 0 mod 4, T J Dekker, 2007-2013. */
/* Include in quadprimes.c to draw pictures of primes and units in colors.   */
/* Optionally also prime non-principal ideals (co-ideals) are drawn.         */
/* The programs use subprograms from files quadchar.c and quadsiev.c         */
/* and programming environment of Xcode system.                              */

# define FONTSIZE       14        //  size of font for heading
# define SMAX           79        //  (113) maximum length character to draw	
# define CMIN           28        //  length of heading text

# define AMAX           47        //  (67) getallen x + y Ã rad, |x| <= AMAX	
# define BMAX           47        //  (49)                    en |y| <= BMAX	
# define DXY             7        //  (5) spacing in x and y direction					
# define H               3        //  (2) half size of square 	
# define QNORM(x, y)	abs(x*x-(discriminant/4)*y*y)  // norm of x + y Ãrad 
# define peri           period    //  to draw chi over one period

# define ideal                    //  empty if no co-ideals are drawn
# define testx                    //  empty test

/*  Select class number either 1, 2, or 3, and corresponding radicand row
    Moreover, optional include to draw prime co-ideals.
*/

 int clas = 1, radicand[] = {-1, -2, 2, 3, 6, 7, 11, 14, 19, 22, 23, 31};

// int clas = 2, radicand[] = {-5, -6,-10,-13,-22,-37,-58, 10, 15, 26, 30};
// # include "quadideal2.c"

// int clas = 3, radicand[] = {79, 142, 223, 254, 326};
// # include "quadideal3.c"

void drawsquare(int x, int y) /* draws square of size 2H, center (x, y) */
{	CGContextMoveToPoint(c, x-H, y-H); 
	AddLineToPoint(x-H, y+H); AddLineToPoint(x+H, y+H);
	AddLineToPoint(x+H, y-H); AddLineToPoint(x-H, y-H);
	CGContextFillPath(c); 	
}   /*  end drawsquare  */

void picture() /* draws picture of primes, units and option prime ideals */
{	int xo, yo, a, b, norm;	 // start picture at (X00, Y00)
	xo = X00 + DXY * AMAX; yo = yheight - Y00 - DXY * BMAX;	 
	for (b = -BMAX; b <= BMAX; b++) 
		for (a = -AMAX; a <= AMAX; a++)
		{	norm = QNORM(a, b);	
			if (norm < maxnorm)
			{	if (inset(norm, prinorm)) FillBlue; // primes
				else if (norm == 1) FillRed; // units
				testx  // optional extra test for co-ideals
				else goto nodraw; 
				// draw square at given central coordinates:
				drawsquare(DXY * a + xo, DXY * b + yo);  
			}
		nodraw: ;
		}
}   /*  end picture  */
