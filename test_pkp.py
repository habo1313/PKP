import pkp
import numpy as np
import matplotlib.pyplot as plt
from dualplot import DualPlot

reactor = pkp.Reactor('SFOR', [1e6, 50e6, 0.5])

print(reactor.parameters)

reactor.parameters = [1e5, 45e6, 0.45]

print(reactor.parameters)

oc = [[0, 500], [0.1, 1000], [0.2, 1000]]
reactor.operating_conditions = oc

reactor.solve(1e-6, verbose=False)

times = np.array(reactor.times)
states = np.array(reactor.states)

reactor.dump('state.csv')

# plt.plot(times, states[:, 0], marker='x')
dp = DualPlot()
dp.plot_left(times, states[:, 0], marker='x')
dp.plot_right(times, states[:, 1])
dp.set_xlabel('Times, s')
dp.set_ylabel_left('Yields')
dp.set_ylabel_right('Temperature, K')
plt.show()
# reactor._set_parameters()
