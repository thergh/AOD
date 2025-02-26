import matplotlib.pyplot as plt

# Data
sizes = [10**1, 10**2, 10**3, 10**4, 10**5, 10**6]

dfs_times = [0.032, 0.048, 0.341, 5.708, 44.721, 378.641]
bfs_times = [0.009, 0.047, 0.336, 5.563, 43.594, 356.955]
toposort_times = [0.007, 0.114, 0.394, 2.505, 41.376, 290.298]
scc_times = [0.060, 0.085, 0.697, 6.757, 71.077, 852.924]
bipartite_times = [0.008, 0.036, 0.244, 6.775, 50.193, 363.856]

# Plotting function
def plot_algorithm(name, times):
    plt.figure()
    plt.plot(sizes, times, marker='o')
    plt.xscale('log')
    plt.yscale('log')
    plt.title(f'{name} Execution Time')
    plt.xlabel('Input Size (V + E)')
    plt.ylabel('Time (ms)')
    plt.grid(True)
    plt.savefig("./plots/" + name + ".jpg")
    # plt.show()

# Plot for each algorithm
plot_algorithm('DFS', dfs_times)
plot_algorithm('BFS', bfs_times)
plot_algorithm('Topological Sort', toposort_times)
plot_algorithm('SCC', scc_times)
plot_algorithm('Bipartite Check', bipartite_times)
