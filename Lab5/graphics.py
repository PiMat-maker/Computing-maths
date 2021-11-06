import matplotlib.pyplot as plt


def make_graph(x, y):
    step = max(1, len(x)//10)
    plt.scatter(x[::step], y[::step], color="red")
    plt.plot(x, y)
    plt.show()
