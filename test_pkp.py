import pkp
import numpy as np
import matplotlib.pyplot as plt

reactor = pkp.Reactor('SFOR', [1e6, 50e6, 0.5])

print(reactor.parameters)

reactor.parameters = [1e5, 45e6, 0.45]

print(reactor.parameters)

reactor.solve(0.01, 1200, 1e-6, verbose=False)

times = np.array(reactor.times)
states = np.array(reactor.states)

reactor.dump('state.csv')

plt.plot(times, states[:, 0], marker='x')
plt.show()
# reactor._set_parameters()
