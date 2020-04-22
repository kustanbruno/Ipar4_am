import numpy as np
import matplotlib.pyplot as plt

file = open("1v.csv", "r", 1, 'UTF-8-sig')
data = file.readlines()
del data[-1]
i = 0
times = []
yvalues = []


for line in data:
    line = line.split(';')
    if data[0] != 'Data\xa0end':
        if i == 0:
            times.append(int(line[0]))
        else:
            times.append(int(line[0])-times[0])
        yvalues.append(int(line[1]))
        i += 1

times[0] = 0

#Count of points
n = len(times)
#Distance between points in time 
Lx = 0

for i in range (1, len(times)):
    #converting from microseconds to seconds
    times[i] = times[i] / 1000000
    Lx += times[i] - times[i-1]

Lx = Lx / len(times)
freqs = np.fft.fftfreq(n)
mask = freqs > 0
fft_vals = np.fft.fft(yvalues)

fft_theo = 2.0*np.abs(fft_vals/n)

plt.figure(1)
plt.title('original signal')
plt.plot(times,yvalues, color="xkcd:salmon", label="original")


plt.figure(2)
plt.plot(freqs[mask], fft_theo[mask], label="true fft values")
plt.title("True FFT values")

#plt.figure(1)
#plt.savefig('original.png', dpi=500, quality=100)
#
#
#plt.figure(2)
#plt.savefig('originaal.png', dpi=500, quality=100)


plt.show()