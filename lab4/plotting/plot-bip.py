import os
import matplotlib.pyplot as plt
import pandas as pd


data_dir = "output"


def plot_size_vs_i():
    size_files = [f for f in os.listdir(data_dir) if f.startswith("bip-size-")]

    plt.figure(figsize=(10, 6))
    for file in sorted(size_files):
        k = file.split("-")[2].split(".")[0]
        file_path = os.path.join(data_dir, file)

        df = pd.read_csv(file_path, sep=" ", header=None, names=["i", "matching_size"])

        plt.plot(df["i"], df["matching_size"], label=f"k={k}")

    plt.xlabel("i")
    plt.ylabel("Matching Size")
    plt.title("Matching Size vs i for Different k")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(data_dir, "matching_size_vs_i.png"))
    plt.show()


def plot_time_vs_k():
    time_files = [f for f in os.listdir(data_dir) if f.startswith("bip-time-")]

    plt.figure(figsize=(10, 6))
    for file in sorted(time_files):
        i = file.split("-")[2].split(".")[0]
        file_path = os.path.join(data_dir, file)

        df = pd.read_csv(file_path, sep=" ", header=None, names=["k", "execution_time"])

        plt.plot(df["k"], df["execution_time"], label=f"i={i}")

    plt.xlabel("k")
    plt.ylabel("Execution Time (ms)")
    plt.title("Execution Time vs k for Different i")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(data_dir, "execution_time_vs_k.png"))
    plt.show()


if __name__ == "__main__":
    plot_size_vs_i()
    plot_time_vs_k()
