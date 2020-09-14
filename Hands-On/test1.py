print([1,2,3]+['a','b','c'])
print(type(lambda x: x+1))
import numpy as np
a = np.array(range(36)).reshape(6,6)
print(a.reshape(36))
print(a[1:4,2:3])
print(a.reshape(36)[::7])