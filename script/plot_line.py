import sys
import bisect
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
    with open(log_file, 'r') as f:
        for line in f:
            this_data = int(line)
            data.append(this_data)
    max_data = max(data)
    min_data = min(data)
    # calculate histogram
    bins = [i for i in range((min_data // bin_width - 1)*bin_width, max_data + 2*bin_width, bin_width)]
    hist = [0 for i in bins]
    for point in data:
        hist[bisect.bisect_right(bins, point) - 1] += 1
    accum = []
    add = 0
    for i in hist:
        add += i
        accum.append(add)
    # plt.title("Title")
    # plt.xlabel("X")
    # plt.ylabel("Y")
    # plt.xticks(range(0, max_data + bin_width + 1, bin_width))
    sns.set_style('whitegrid')
    sns.lineplot(bins, accum)
    plt.show()
    # plt.savefig(output_file)
