import numpy as np
import matplotlib.pyplot as plt
import json

print(np.log(5))

# with open('/tmp/output.json') as f:
#     data = json.load(f)
# 
# print(data[0])

#print(sum([m['treated'] for m in data])/sum([m['total'] for m in data]))

# # Plot the extreme parameter conditions
# plt.plot([m['value'] for m in data if m['parameter'] == 0.0])
# plt.plot([m['value'] for m in data if m['parameter'] == 1.0])
# plt.show()

# Get the parameters
# parameters = sorted({m['parameter'] for m in data})
# print(parameters)
# parameter = parameters[len(parameters)*3//4]
# print(parameter)
# value = sum([m['value'] for m in data if m['parameter']==parameter])/sum([m['total'] for m in data if m['parameter']==parameter])
# control = sum([m['control'] for m in data if m['parameter']==parameter])/sum([m['total'] for m in data if m['parameter']==parameter])
# cov = sum([m['control_x_value'] for m in data if m['parameter']==parameter]) - sum([m['control'] for m in data if m['parameter']==parameter])*sum([m['value'] for m in data if m['parameter']==parameter])/sum([m['total'] for m in data if m['parameter']==parameter])
# var = sum([m['control_x_control'] for m in data if m['parameter']==parameter]) - sum([m['control'] for m in data if m['parameter']==parameter])**2/sum([m['total'] for m in data if m['parameter']==parameter])
# print('value = {} + {}.(control-{})'.format(value, cov/var, control))
# print('value full treatment = {}'.format(value + cov/var*(1-control)))
# 
# def plot(data, fun=lambda m: m['value'], cond=lambda m: True, color='tab:blue'):
#     parameters = sorted({m['parameter'] for m in data if cond(m)})
#     distribs = [[fun(m) for m in data if m['parameter']==p and cond(m)] for p in parameters]
#     plt.plot(parameters, [np.mean(d) for d in distribs], color=color)
#     plt.fill_between(parameters, [np.percentile(d, 10) for d in distribs], [np.percentile(d, 90) for d in distribs], color=color, alpha=0.2)
# 
# plot(data, lambda m: m['value']/m['total'], lambda m: True, 'tab:red')
# plot(data, lambda m: m['treated_x_value']/m['treated'], lambda m: m['parameter']>0.5, 'tab:green')
# plot(data, lambda m: (m['value']-m['treated_x_value'])/(m['total']-m['treated']), lambda m: m['parameter']<0.8, 'tab:blue')
# 
# plt.plot([control, 1], [value, value + cov/var*(1-control)], color="black", linestyle='--', linewidth=1, marker='o')
# 
# plt.show()



