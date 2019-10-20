import argparse
import matplotlib.pyplot as plt


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-i', '--input',
        help='file with input values'
    )
    args = parser.parse_args()
    return args


if __name__ == "__main__":
    args = parse_args()

    with open(args.input) as f:
        mode = f.readline().rstrip()
        size = int(f.readline().rstrip())

        inputs = []
        outputs = []

        if mode == 'IN_OUT':
            for i, line in enumerate(f):
                if i == size:
                    break
                single_input, single_output = line.rstrip().split(' ')
                inputs.append(float(single_input))
                outputs.append(float(single_output))

            plt.plot(inputs, outputs)

        elif mode == 'OUT':
            for i, line in enumerate(f):
                if i == size:
                    break
                outputs.append(float(line.rstrip()))

            plt.plot(outputs)

        plt.show()
