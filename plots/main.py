import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

name = 'binary'
name_to_title = {
    'linear' : 'Linear',
    'linearRecursive': 'Recursive Linear',
    'binary' : 'Binary',
    'jump' : 'Jump',
    'random' : 'Random'
}

df = pd.read_csv('data.csv', index_col = None)
max_n = df['n'].max()
max_t = df[['near_start','near_middle','near_end','not_in_collection']].max().max()
print(f"{max_n=}, {max_t=}")

current_rows = df[df['algorithm'] == name]
df = current_rows

fig, ax = plt.subplots()

plt.xscale('log')
plt.yscale('log')

plt.plot(df['n'], df['near_start'], label='Near Start', marker='o')
plt.plot(df['n'], df['near_middle'], label='Near Middle', marker='x')
plt.plot(df['n'], df['near_end'], label='Near End', marker='s')
plt.plot(df['n'], df['not_in_collection'], label='Not In Collection', marker='^')

plt.xlabel('Array Size')
plt.ylabel('Runtime (ms)')
plt.title('Runtime vs Array Size For ' + name_to_title[name] + ' Search (Smaller Y Axis Range)')
# plt.title('Runtime vs Array Size For ' + name_to_title[name] + ' Search')
plt.legend(title='Keys Searched For', loc=2)


ax.set_xlim(1, max_n*1.5)
# ax.set_ylim(1, max_t*1.5)
ax.set_ylim(1, max_t*1.5/10000)

# plt.savefig('plots/'+ name_to_title[name] + " Smaller Y Axis")
# plt.savefig('plots/'+ name_to_title[name])
plt.show()