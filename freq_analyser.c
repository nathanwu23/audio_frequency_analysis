#include <stdio.h>
#include <stdlib.h>

#include <sndfile.h>
#include "fft.h"

#define SAMPLE_LENGTH 4

/*
* Usage: /freq_analyser <audio_file>
*/
int main (int argc, char *argv[]) 
{
    // file = argv[1]

    char *inFileName = argv[1];
    SNDFILE *inFile = NULL;
    SF_INFO sfInfo;
    memset (&sfInfo, 0, sizeof (sfInfo));

    if ((inFile = sf_open (inFileName, SFM_READ, &sfInfo)) == NULL) 
    {	
        printf ("Not able to open input file %s.\n", inFileName) ;
		puts (sf_strerror (NULL)) ;
		return 1 ;
    } 

    printf("After open file\n");

    int numChannels = sfInfo.channels;
    int sampleRate = sfInfo.samplerate;
    sf_count_t numItems = (sf_count_t) numChannels * sampleRate;

    double samplesBuf[numItems];
    // = malloc(numItems * sizeof(double));
    sf_count_t readItems = sf_read_double (inFile, samplesBuf, numItems);
  

    
    int numSamples = numItems/2;
    // 65536;
    // int numSamples = 4096;
    // v is next highest power of 2
    int v = numSamples;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    int pad = v - numSamples;
    printf("v is %d\n", v);
    printf("pad is %d\n", pad);
    printf("Before creating fftInput\n");

    // fftInput take half numSamples 
    cplx fftInput[v];
    // for (int i = 0; i < numSamples; i++) {
    // Take only one channel of samples (every second sample)
    int index = 0;
    for (int i = 0; i < numItems; i += 2) {
        fftInput[index] = (cplx) samplesBuf[i];
        index++;
    }
    printf("before padding\n");
    // pad with zeros till v (so input array is power of 2)
    for (int i = index; i < v; i ++) {
        fftInput[i] = 0;
    }
    // memset(fftInput + numSamples * sizeof(cplx), 0, pad * sizeof(cplx));
    
    cplx fftOutput[v];

    printf("Before FFT\n");

    fft(fftInput, fftOutput, v);

    printf("After FFT\n");

    FILE *fptr = fopen("readData.txt", "w");
    for (int i = 0; i < numSamples; i++) {
        fprintf(fptr, "%f\n", (float) fftOutput[i]);

    }
    
    // free (samplesBuf);
    // showN("Data: ", fftInput, n);
    // showN("\nFFT : ", fftOutput, n);
    // printf("\n");
    return 0;

}