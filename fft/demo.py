import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft, fftfreq, ifft

n = 1000
Lx = 100

omg = 2.0*np.pi/Lx

x = np.linspace(0, Lx, n)
y1 = 1.0*np.cos(5.0*omg*x)
y2 = 2.0*np.cos(10.0*omg*x)
y3 = 0.5*np.cos(20.0*omg*x)


y = y1 + y2 + y3

freqs = fftfreq(n)

mask = freqs > 0

print(mask)

fft_vals = fft(y)

fft_theo = 2.0*np.abs(fft_vals/n)

plt.figure(1)
plt.title('original signal')
plt.plot(x,y, color="xkcd:salmon", label="original")

plt.figure(2)
plt.plot(freqs[mask], fft_theo[mask], label="true fft values")
plt.title("True FFT values")

#plt.show()