import argparse
from pathlib import Path

import numpy as np


def read_matrix_from_text(file_path: Path) -> np.ndarray:
    rows = []

    with file_path.open("r", encoding="utf-8") as f:
        for line_number, line in enumerate(f, start=1):
            stripped = line.strip()
            if not stripped:
                continue

            try:
                row = [float(value) for value in stripped.split()]
            except ValueError as exc:
                raise ValueError(
                    f"Failed to parse line {line_number}: {stripped!r}"
                ) from exc

            rows.append(row)

    if not rows:
        raise ValueError(f"Input file {file_path} does not contain matrix rows.")

    expected_cols = len(rows[0])
    for idx, row in enumerate(rows, start=1):
        if len(row) != expected_cols:
            raise ValueError(
                f"Row {idx} has {len(row)} columns, expected {expected_cols}."
            )

    matrix = np.array(rows, dtype=np.float64)
    return matrix


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Read a whitespace-separated matrix from a text file."
    )
    parser.add_argument(
        "input_file",
        type=Path,
        help="Path to text file with matrix values (same format as H_n_10.txt).",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    matrix = read_matrix_from_text(args.input_file)
    print("matrix shape:", matrix.shape)
    if matrix.shape[0] != matrix.shape[1]:
        print('Ошибка: матрица не квадратная')
    # print(matrix)
    trace = 0.0
    for i in range(matrix.shape[0]):
        trace += matrix[i, i]
    print(f'След матрицы: {trace}')
    eigenvalues = np.linalg.eigvals(matrix)
    print(f'Собственные значения: {eigenvalues}')
    print(f'Сумма собственных значений: {np.sum(eigenvalues)}')


if __name__ == "__main__":
    main()
