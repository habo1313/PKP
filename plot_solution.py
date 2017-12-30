import matplotlib.pyplot as plt
import pandas as pd
from dualplot import DualPlot

if __name__ == '__main__':
    data = pd.read_csv('solution.csv')
    #plt.plot('time', 'y0', data=data, marker='x')
    dplot = DualPlot()
    dplot.plot_left('time', 'y0', data=data, marker='x')
    dplot.plot_right('time', 'Temperature',  data=data)
    dplot.set_ylabel_left('Volatile yield')
    dplot.set_ylabel_right('Temp, K')
    dplot.set_xlabel('Time')
    plt.show()
