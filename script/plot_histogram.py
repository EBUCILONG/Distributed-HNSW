import sys
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
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
    with open(log_file, 'r') as f:
        for line in f:
            this_data = int(line)
            data.append(this_data)
    max_data = max(data)
    min_data = min(data)
    print(max_data)
    # plt.title("Title")
    # plt.xlabel("X")
    # plt.ylabel("Y")
    # plt.xticks(range(bin_width*(min_data // bin_width), max_data + bin_width + 1, bin_width))
    sns.set_style('whitegrid')
    sns.distplot(data, bins=range(bin_width*(min_data // bin_width), max_data + bin_width + 1, bin_width), kde=False, rug=False)
    plt.gca().get_xaxis().set_major_formatter(ticker.FuncFormatter(lambda x, p: format(int(x/60000), ',')))
    plt.show()
    # plt.savefig(output_file)
