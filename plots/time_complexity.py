import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math

name = 'linearRecursive'

name_to_title = {
    'linear' : 'Linear',
    'linearRecursive': 'Recursive Linear',
    'binary' : 'Binary',
    'jump' : 'Jump',
    'random' : 'Random'
}

recursive_c = 3.3
random_c = 9

name_to_func_dict = {
    'linear' : {
        'near_start': lambda x: x/20,
        'near_middle': lambda x: x/2,
        'near_end': lambda x: 19*x/20,
        'not_in_collection': lambda x: x
    },
    'linearRecursive' : {
        'near_start': lambda x:recursive_c*x/20,
        'near_middle': lambda x:recursive_c*x/2,
        'near_end': lambda x:recursive_c*19*x/20,
        'not_in_collection': lambda x:recursive_c*x
    },
    'binary': {
        'near_start': lambda x: math.log2(x),
        'near_middle': lambda x: math.log2(x),
        'near_end': lambda x: math.log2(x),
        'not_in_collection': lambda x: math.log2(x),
    },
    'jump': {
        'near_start': lambda x: 11*math.sqrt(x)/20,
        'near_middle': lambda x: math.sqrt(x),
        'near_end': lambda x: 29*math.sqrt(x)/20,
        'not_in_collection': lambda x: math.sqrt(x),
    },
    'random': {
        'near_start': lambda x: random_c*x + x/2,
        'near_middle': lambda x: random_c*x + x/2,
        'near_end': lambda x: random_c*x + x/2,
        'not_in_collection': lambda x: random_c*x + x,
    }
}


df = pd.read_csv('data.csv', index_col = None)

df['a'] = df.apply(lambda row:name_to_func_dict[row['algorithm']]['near_start'](row['n']), axis=1)
df['b'] = df.apply(lambda row:name_to_func_dict[row['algorithm']]['near_middle'](row['n']), axis=1)
df['c'] = df.apply(lambda row:name_to_func_dict[row['algorithm']]['near_end'](row['n']), axis=1)
df['d'] = df.apply(lambda row:name_to_func_dict[row['algorithm']]['not_in_collection'](row['n']), axis=1)

max_n = df['n'].max()
max_t = df[['a','b','c','d']].max().max()
print(f"{max_n=}, {max_t=}")

current_rows = df[df['algorithm'] == name]
df = current_rows


fig, ax = plt.subplots()


plt.xscale('log')
plt.yscale('log')

plt.plot(df['n'], df['a'], label='Near Start', marker='o', alpha = 1)
plt.plot(df['n'], df['b'], label='Near Middle', marker='x', alpha = 1)
plt.plot(df['n'], df['c'], label='Near End', marker='s', alpha = 1)
plt.plot(df['n'], df['d'], label='Not In Collection', marker='^', alpha = 1)

plt.xlabel('Array Size')
plt.ylabel('Time Units')
# plt.title('Runtime vs Array Size For ' + name_to_title[name] + ' Search (Smaller Y Axis Range)')
plt.title('Time Complexity For ' + name_to_title[name] + ' Search')
plt.legend(title='Keys Searched For', loc=2)

ax.set_xlim(1, max_n*1.5)
ax.set_ylim(10**-2, max_t*1.5)
# ax.set_ylim(1, max_t*1.5/10000)
with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
    print(df)
plt.savefig('time_complexity_plots/'+ name_to_title[name])
plt.show()

