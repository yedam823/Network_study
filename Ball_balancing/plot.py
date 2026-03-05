import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('log.csv')


plt.figure()
plt.plot(data['time'], data['position'])
plt.xlabel('Time (s)')
plt.ylabel('Position (m)')
plt.title('ball state')
plt.grid()
plt.show()

