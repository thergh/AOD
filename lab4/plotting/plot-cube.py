import matplotlib.pyplot as plt
import pandas as pd


data_file = 'output/hyp.out'
columns = ['k', 'max_flow', 'execution_time', 'path_count']
data = pd.read_csv(data_file, sep=' ', header=None, names=columns)


plt.plot(data['k'], data['max_flow'], marker='o', linestyle='-', color='b', label='Max Flow')
plt.xlabel('k')
plt.ylabel('Maximum Flow')
plt.title('Maximum Flow vs k')
plt.grid(True)
plt.legend()
plt.savefig('output/hypercube_flow.png')
plt.show()


plt.plot(data['k'], data['execution_time'], marker='o', linestyle='-', color='r', label='Execution Time (ms)')
plt.xlabel('k')
plt.ylabel('Execution Time (ms)')
plt.title('Execution Time vs k')
plt.grid(True)
plt.legend()
plt.savefig('output/hypercube_time.png')
plt.show()


plt.plot(data['k'], data['path_count'], marker='o', linestyle='-', color='g', label='Path Count')
plt.xlabel('k')
plt.ylabel('Path Count')
plt.title('Number of Augmenting Paths vs k')
plt.grid(True)
plt.legend()
plt.savefig('output/hypercube_paths.png')
plt.show()

