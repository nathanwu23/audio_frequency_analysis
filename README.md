# audio_frequency_analysis

Analysis of frequency content in an audio file (spectral analysis).
Uses Discrete Fourier Transform (using FFT) to convert sample data from time domain to frequency domain.

Usage:
  
  ./freq <audio_file>
produces a txt data file.

  ./plot.py <data_file>
will plot the results.

freq uses the libsndfile library to read audio data. A number of common file formats are supported. See http://www.mega-nerd.com/libsndfile/ for a complete list.
