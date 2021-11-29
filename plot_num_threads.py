import matplotlib.pyplot as plt
import csv
from itertools import cycle
cycol = cycle('bgrcmk')


def get_cmap(n, name='hsv'):
    '''Returns a function that maps each index in 0, 1, ..., n-1 to a distinct 
    RGB color; the keyword argument name must be a standard mpl colormap name.'''
    return plt.cm.get_cmap(name, n)


if __name__ == "__main__":
    x = []
    y = []

    START_NUM_THREADS = 2
    END_NUM_THREADS = 12
    STEP_NUM_THREADS = 2

    num_threads = [i for i in range(
        START_NUM_THREADS, END_NUM_THREADS + 1, STEP_NUM_THREADS)]

    cmap = get_cmap(100)

    with open('csv/serial_time.csv', 'r') as csvfile:
        lines = csv.reader(csvfile, delimiter=',')
        for idx, row in enumerate(lines):
            if idx == 0:
                continue
            x.append(int(row[0]))
            y.append(int(row[1]))
    # print(x, y)
    plt.plot(x, y, color='r', linestyle='dashed',
             marker='o', label="Time taken by Serial")

    for i in num_threads:
        x = []
        y = []
        with open(f'csv/parallel_time_{i}_threads.csv', 'r') as csvfile:
            lines = csv.reader(csvfile, delimiter=',')
            for idx, row in enumerate(lines):
                if idx == 0:
                    continue
                x.append(int(row[0]))
                y.append(int(row[1]))
        # print(x, y)
        plt.plot(x, y, color=next(cycol), linestyle='solid',
                 marker='o', label=f"Time taken by Parallel ({i} threads)")

    plt.xticks(rotation=25)
    plt.xlabel('Number of nodes')
    plt.ylabel('Time Taken')
    plt.title(
        'Dijkstra\'s Algortihm - Time taken for different number of threads', fontsize=20)
    plt.grid()
    plt.legend()
    plt.show()
