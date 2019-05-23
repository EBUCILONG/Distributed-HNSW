import sys
import matplotlib.pyplot as plt
import seaborn as sns

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: [input file] [output file] [bin width]")
        sys.exit(0)
    if not str.isdigit(sys.argv[3]):
        print("Input bin width is \"" + sys.argv[3] + "\", expected integer.")
        sys.exit(0)
    log_file = sys.argv[1]
    output_file = sys.argv[2]
    bin_width = int(sys.argv[3])
    data = []
    max_data = 0
    with open(log_file, 'r') as f:
        for line in f:
            this_data = int(line)
            data.append(this_data)
            if this_data > max_data:
                max_data = this_data

    # plt.title("Title")
    # plt.xlabel("X")
    # plt.ylabel("Y")
    plt.xticks(range(0, max_data + bin_width + 1, bin_width))
    sns.set_style('darkgrid')
    sns.distplot(data, bins=range(0, max_data + bin_width + 1, bin_width), kde=False)
    # plt.show()
    plt.savefig(output_file)
