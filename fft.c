/* 
* Implementation of a Fast Fourier Transform
*
* Nathan Wu 2020
*
*/


#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <string.h>

double PI;
typedef double complex cplx;

void show(const char * s, cplx buf[]) {
	printf("%s", s);
	for (int i = 0; i < 8; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
    printf("\n");
}

void showN(const char * s, cplx buf[], int n) {
	printf("%s", s);
	for (int i = 0; i < n; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
    printf("\n");
}
 

/* 
*  Take a sequence, transform to DFT
*  Assumes length of input is power of 2
*/
void fft(cplx input[], cplx output[], int n) {
    
    /* RECURSIVE LOGIC */
    // printf("n = %i\n", n );
    // n = length[input]

    if (n == 1) {
        output[0] = input[0];
        return;
    }
   

    // input0 <- even indicies of input
    cplx input0[n/2];
    // memset( input0, 0, (n/2) * sizeof(cplx) );
    int index = 0;
    for (int i = 0; i < n; i += 2) {
        input0[index] = input[i];
        index++;
    }
    // showN("\ninput0 : ", input0, n/2);

    // input1 <- odd indicies of input
    cplx input1[n/2];
    // memset( input1, 0, (n/2) * sizeof(cplx) );
    index = 0;
    for (int i = 1; i < n; i += 2) {
        input1[index] = input[i];
        index++;
    }
    // showN("\ninput1 : ", input1, n/2);

    // output0 = FFT(input0)
    cplx output0[n/2];
    // memset( output0, 0, (n/2) * sizeof(cplx) );
    fft(input0, output0, n/2);

    // showN("\noutput0 : ", output0, n/2);

    // output1 = FFT(input1)
    cplx output1[n/2];
    // memset( output1, 0, (n/2) * sizeof(cplx) );
    fft(input1, output1, n/2);

    // showN("\noutput1 : ", output1, n/2);

    /* TRANSFORM LOGIC */
    
    // nthRootUnity <- e^(i2Pi/n)
    cplx wn = cexp( ((2*PI)/n) * I );

    // rootUnity <- 1
    cplx w = 1;

    for (int k = 0; k <= (n/2) - 1; k++) {
        output[k] = output0[k] + w * output1[k];
        output[n/2 + k] = output0[k] - w * output1[k];
        w = w * wn;
    }
    // showN("\noutput : ", output, n);
    // printf("\n");
    
    return;
}



// int main(void) {
//     PI = atan2(1, 1) * 4;

//     /* Check if input is power of 2*/
//     int n = 8;
//     cplx input[] = {1, 1, 1, 1, 0, 0, 0, 0};
//     cplx output[n];
//     // memset( output, 0, n * sizeof(cplx) );

//     fft(input, output, n);

//     showN("Data: ", input, n);
//     showN("\nFFT : ", output, n);
//     printf("\n");

//     return 0;
// }