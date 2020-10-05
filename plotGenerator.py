import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import csv
import glob

dataSetFileNames = glob.glob("./export/*.csv")

for filename in dataSetFileNames:
    data = np.genfromtxt(filename, delimiter=',')
    fig, ax = plt.subplots()

    ax.plot(data[0], data[1], color='gray', label='Susceptible')
    ax.plot(data[0], data[2], color='red', label='Infected')
    ax.plot(data[0], data[3], color='limegreen', label='Cured')
    ax.plot(data[0], data[4], color='black', label='Dead')
    ax.plot(data[0], data[5], color='magenta', label='Hospitalized')

    ax.set(xlabel='Tick', ylabel='n', title=filename)
    ax.grid()

    ax.legend()

    fig.savefig(filename + ".png")
    plt.show()
