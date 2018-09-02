## 这个文件是matplot绘图的示例

import matplotlib.pylab as plt
import numpy as np

epoch_list = range(100)
gloss_list = [x*0.8+1 for x in epoch_list]
dloss_list = [x*x*0.8 + 0.5*x for x in epoch_list]

f1 = plt.figure(1)
plt.plot(epoch_list,gloss_list,'r-',label='gloss')
plt.plot(epoch_list,dloss_list,'b-',label='dloss')
plt.legend()

f2 = plt.figure(2)
plt.plot(epoch_list,gloss_list/np.max(gloss_list),'r-',label='G_loss')
plt.plot(epoch_list,dloss_list/np.max(dloss_list),'b-',label='D_loss')
plt.legend()

plt.show()