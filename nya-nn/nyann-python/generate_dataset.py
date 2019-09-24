import numpy as np
import csv
import argparse


def generate_linear_dataset(size, deviation=0.2, input_size=1):
    """
    Generate a dataset for the formula:

        y = k_1 * x_1 + k_2 * x_2 + ... + b

    with noise with a given deviation
    """

    coeffs = [np.random.rand() for _ in range(input_size)]
    bias = np.random.rand() * np.random.randint(1, 100)

    generated_values = []
    for _ in range(size):
        input_value = [np.random.rand() * np.random.randint(1, 20)
                       for _ in range(input_size)]
        output_value = sum(
            [x * coeff for (x, coeff) in zip(input_value, coeffs)])
        output_value += bias
        # noise
        output_value += np.random.normal(loc=0, scale=deviation * size)
        generated_values.append((input_value, [output_value]))

    return generated_values


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-s', '--size',
        help='size of the dataset',
        type=int
    )
    parser.add_argument(
        '-l', '--linear',
        help='generation of a linear dataset',
        action='store_true'
    )
    parser.add_argument(
        '-d', '--deviation',
        help='deviation of a generated dataset (percentage)',
        default=0.2,
        type=float
    )
    parser.add_argument(
        '-o', '--output',
        help='path to file for an output',
        default='dataset.csv'
    )
    parser.add_argument(
        '-i', '--input-size',
        help='number of variables as input',
        default=1,
        type=int
    )
    args = parser.parse_args()
    return args


if __name__ == "__main__":
    args = parse_args()
    if args.linear:
        dataset = generate_linear_dataset(
            args.size, args.deviation, args.input_size)
        writer = csv.writer(open(args.output, 'w+'), lineterminator='\n')
        for data in dataset:
            writer.writerow(data[0])
            writer.writerow(data[1])
