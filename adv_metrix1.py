from numpy import random, sqrt, zeros, vstack, ones, dot, linalg, array, mean
import matplotlib.pyplot as plt
%matplotlib inline
low = -1
high = 1
beta_1 = 0.5
SS = 100
rho = 1
sigma = sqrt(0.5)
N = 10000
rho_bias = []
beta_bias = []
beta = array([rho, beta_1])

for i in range(N):
    x = random.uniform(low,high, SS)
    u = random.normal(0,sigma, SS)
    y = zeros(SS)
    y_1 = zeros(SS)
    for t in range(1,SS):
        y[t] = rho*y[t-1]+beta_1*x[t]+u[t]
        y_1[t] = y[t-1]
    X = vstack((y_1,x))
    beta_hat = dot(linalg.inv(dot(X, X.T)),dot(X,y.T))
    rho_bias.append(beta[0]-beta_hat[0])
    beta_bias.append(beta[1]-beta_hat[1])

plt.hist(rho_bias)
plt.hist(beta_bias)
print mean(rho_bias)
print mean(beta_bias)
