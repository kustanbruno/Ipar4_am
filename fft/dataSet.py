import numpy as np
import matplotlib.pyplot as plt

class dataSet:
    
    def __init__(self, device):
        self.deviceName = device
        self.xVals = []
        self.yVals = []
        self.zVals = []
        self.times = []
    
    def addData(self,x,y,z,t):
        self.xVals.append(int(x))
        self.yVals.append(int(y))
        self.zVals.append(int(z))
        self.times.append(int(t))

    def __convertTimes(self):
        for i in range(1, len(self.times)):
            self.times[i] = self.times[i] - self.times[0]
        self.times[0] = 0
        #avarage distance between times
        Lx = 0
        for i in range(1, len(self.times)):
            #converting from microseconds to seconds
            self.times[i] = self.times[i] / 1000000
            Lx += self.times[i] - self.times[i-1]
        self.Lx = Lx / len(self.times)
    
    def fft(self):
        self.__convertTimes()
        self.freqs = np.fft.fftfreq(len(self.xVals))
        self.mask = self.freqs > 0
        fft_vals = np.fft.fft(self.xVals)
        self.fft_theo = 2.0*np.abs(fft_vals/len(self.xVals))

    def createPlots(self):
        plt.figure(1)
        plt.title('original signal')
        plt.plot(self.times,self.xVals, color="xkcd:salmon", label="original")

        plt.figure(2)
        plt.plot(self.freqs[self.mask], self.fft_theo[self.mask], label="true fft values")
        plt.title("True FFT values")

    def showPlots(self):
        plt.show()

    def saveOriginalPlot(self, filename):
        plt.figure(1)
        plt.savefig(filename, dpi=500, quality=100)

    def saveFftPlot(self, filename):
        plt.figure(2)
        plt.savefig(filename, dpi=500, quality=100)