import matplotlib.pyplot as plt
import pandas as pd
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('solution', action='store')

    argument = parser.parse_args()

    df = pd.read_csv(argument.solution)

    fig, ax = plt.subplots()
    ax.plot('time', 'y0', data=df)

    plt.show()
