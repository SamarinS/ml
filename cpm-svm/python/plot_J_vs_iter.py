import os
import re
import sys

import matplotlib
import matplotlib.pyplot as plt
import argparse


def _config_matplotlib_backend() -> None:
    if os.environ.get("DISPLAY", "") == "":
        matplotlib.use("Agg")


def parse_J_vs_iteration(log_path: str):
    iter_nums = []
    j_values = []

    current_iter = None
    with open(log_path, "r") as f:
        for line in f:
            m_iter = re.match(r"Iteration\s+(\d+)", line)
            if m_iter:
                current_iter = int(m_iter.group(1))
                continue

            m_j = re.search(r"J\(w\)\s*=\s*([0-9.eE+-]+)", line)
            if m_j and current_iter is not None:
                iter_nums.append(current_iter)
                j_values.append(float(m_j.group(1)))
                current_iter = None

    return iter_nums, j_values


def plot_J_vs_iteration(log_path: str, output_path: str | None = None, log_scale: bool = False) -> None:
    _config_matplotlib_backend()

    iters, j_vals = parse_J_vs_iteration(log_path)
    if not iters:
        raise RuntimeError(f"No (iteration, J(w)) data found in log: {log_path}")

    plt.figure()
    plt.plot(iters, j_vals, marker="o")
    if log_scale:
        plt.yscale("log")
    plt.xlabel("Iteration")
    plt.ylabel("J(w)")
    plt.title("BMRM objective J(w) vs iteration")
    plt.grid(True)
    plt.tight_layout()

    if output_path is None and os.environ.get("DISPLAY", "") != "":
        plt.show()
    else:
        if output_path is None:
            output_path = "J_vs_iteration.png"
        plt.savefig(output_path, dpi=150, bbox_inches="tight")
        plt.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog = 'plot_J_vs_iter',
        description = 'Prints the plot of J function depending on iteration number')
    parser.add_argument('log_file')
    parser.add_argument('--log', action='store_true', help='whether to use logarithmic scale')
    args = parser.parse_args()
    plot_J_vs_iteration(args.log_file, log_scale=args.log)
