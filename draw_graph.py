import matplotlib.pyplot as plt

F = open('data.txt', 'r')

plot_x = []
plot_y1 = []
plot_y2 = []
plot_y3 = []

#x = 0
for line in F:
    #x += 1
    #print(line)
    x, y1, y2, y3 = line.split()
    plot_x.append(int(x))
    plot_y1.append(float(y1)*1000)
    plot_y2.append(float(y2)*1000)
    plot_y3.append(float(y3)*1000)

plt.xlabel('N(size of array)')
plt.ylabel('time(ms)')

plt.plot(plot_x, plot_y1, label='std')
plt.plot(plot_x, plot_y2, label='quick')
plt.plot(plot_x, plot_y3, label='mysort')
plt.show()
