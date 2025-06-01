// Name: test.c
// Description: Test file to exercise the MLS polynomial fitting function.
// Author: Henry Forson, Melbourne, Florida USA

//------------------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2020 Henry M. Forson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//------------------------------------------------------------------------------------

#include  <stdio.h>
#include  <string.h>
#include  "polyfit.h"

// Buffer to hold a string representation of a polynomial:
#define POLY_STRING_BF_SZ   (256)
char polyStringBf[POLY_STRING_BF_SZ];

// ---------------- TEST 1 DATA ------------------------
// Create test data to find the closest line to (0,6), (1,0), and (2,0).
// See also page 218 of: https://math.mit.edu/~gs/linearalgebra/ila0403.pdf
double x1[]   = {2010, 2010, 2011 , 2014 , 2014 , 2015 , 2016 , 2016 , 2017 , 2017 , 2017 , 2019 , 2019 , 2020 , 2020 , 2021 , 2021 , 2021 , 2021 , 2022 , 2022 , 2022 , 2023 , 2024 , 2025};
double y1[]   = {122000000, 117000000, 118000000, 120000000, 130000000, 135000000, 165000000, 140000000, 165000000, 140000000, 150000000, 185000000, 180000000, 190000000, 175000000, 200000000, 230000000, 190000000, 220000000, 280000000, 290000000, 275000000, 320000000, 360000000, 400000000};
int pc1       = 25;           					// pointCount
double cr1[]  = {0, 0, 0, 0};                  // coefficientResults (third order)
int cc1       = 4;								// coefficientCount


//--------------------------------------------------------
// main()
// Unit tests the poly() function.
//--------------------------------------------------------
int main()
{
  printf("Tahun\tHarga\n");
  for(int i = 0; i<pc1; i++) {
//	x1[i] += 2000;
//  y1[i] *= 1000;
	printf("%.0lf\tRp. %.0lf\n", x1[i], y1[i]);
  }
	
  int rVal;
  // Call polynomial regression fit function
  rVal = polyfit( pc1, x1, y1, cc1, cr1);
  // Print a0, a1, a2, a3
  printf("\nAngka koefisien fungsi regresi\n");
  for(int i = 0; i<cc1; i++) {
	printf("a%d = %lf\n", i, cr1[cc1-1-i]);
  }	 
  // Convert a0, a1, etc into a string
  if( 0 == rVal)
  { 
    polyToString( polyStringBf, POLY_STRING_BF_SZ, cc1, cr1 );
  }
  else
  {
    snprintf( polyStringBf, POLY_STRING_BF_SZ, "error = %d", rVal );
  }
  printf( "\nFungsi Regresi adalah:\nf(x)=%s\n", polyStringBf);
  
  double SEE = getSEE(pc1, x1, y1, cc1, cr1);
  printf("\nStandard Error of Estimate adalah:\n");
  printf("SEE=%.3lf\n", SEE);
  printf("atau\n");
  printf("SEE=%.3lf juta\n", SEE/1000000);
  getchar();
 
  return( 1 );
}

