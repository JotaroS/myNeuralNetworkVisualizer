#!/usr/bin/env python2

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

def main(path):
    t = np.loadtxt(path, delimiter=',')
    fig = plt.figure();
    ax = fig.add_subplot(111);
    ax.set_title('');
    ax.set_xlabel('xlabel');
    ax.set_ylabel('ylabel');
    plt.subplot(1,2,1);
    print(t)
    for i in range(1,11):
        plt.plot(t[0], t[i], color=cm.jet(float(i) / 10), label=str(20+20*(i-1)), alpha=0.5)
    plt.legend(bbox_to_anchor=(1.05,1), loc=2,borderaxespad=0.)
    plt.show()
    fig.savefig('plot1.eps');

if __name__ == '__main__':
    if len(sys.argv) == 2:
        path = sys.argv[1]
        main(path)
    else:
        print 'Usage: csv2graph.py FILE'
