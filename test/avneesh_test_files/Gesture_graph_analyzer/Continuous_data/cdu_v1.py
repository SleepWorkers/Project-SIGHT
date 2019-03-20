from matplotlib import pyplot as plt
from matplotlib import animation as animation
import random

fig = plt.figure()
ax1 = fig.add_subplot(2,2,1)
ax2 = fig.add_subplot(2,2,2)
ax3 = fig.add_subplot(2,2,3)
ax4 = fig.add_subplot(2,2,4)

numbers1 = []
numbers2 = []
numbers3 = []
numbers4 = []

def update_axis(fnum):
    print(fnum)
    numbers1.append(random.randint(0, 255))
    if (len(numbers1) > 10):
        del numbers1[0]
    numbers2.append(random.randint(0, 255))
    if (len(numbers2) > 10):
        del numbers2[0]
    numbers3.append(random.randint(0, 255))
    if (len(numbers3) > 10):
        del numbers3[0]
    numbers4.append(random.randint(0, 255))
    if (len(numbers4) > 10):
        del numbers4[0]
    ax1.clear()
    ax1.plot(numbers1)
    ax1.set_title("1")
    ax2.clear()
    ax2.plot(numbers2)
    ax2.set_title("2")
    ax3.clear()
    ax3.plot(numbers3)
    ax3.set_title("3")
    ax4.clear()
    ax4.plot(numbers4)
    ax4.set_title("4")

try:
    ani = animation.FuncAnimation(fig, update_axis, interval=10)
    plt.show()
except KeyboardInterrupt:
    print("Exit received...")
