import matplotlib.pyplot as plt
import csv

if __name__ == "__main__":
    x = []
    y = []

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

    x = []
    y = []

    with open('csv/parallel_time_6_threads.csv', 'r') as csvfile:
        lines = csv.reader(csvfile, delimiter=',')
        for idx, row in enumerate(lines):
            if idx == 0:
                continue
            x.append(int(row[0]))
            y.append(int(row[1]))

    plt.plot(x, y, color='b', linestyle='dashed',
             marker='o', label="Time taken by Parallel (6 threads)")

    plt.xticks(rotation=25)
    plt.xlabel('Number of nodes')
    plt.ylabel('Time Taken')
    plt.title(
        'Dijkstra\'s Algortihm - Serial vs Parallel Execution Time ', fontsize=20)
    plt.grid()
    plt.legend()
    plt.show()
