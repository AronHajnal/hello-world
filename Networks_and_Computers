import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib
from __future__ import division
import random
%matplotlib inline

#G = nx.erdos_renyi_graph(100, 0.3)
G = nx.barabasi_albert_graph(100, 4)

a = 30
T = np.linspace(0,2,a)
S = np.linspace(1,-1,a)
TS =  [(t,s) for s in S for t in T]

ratios = np.zeros([len(TS), 100]) #Store ratios of cooperators compared to the whole population

for k in range(len(TS)):

    #True is cooperation, False is defection - we initialize strategies randomly

    for i in range(len(G.node)):
        if(np.random.random()>0.5):
            G.node[i] = True
        else:
            G.node[i] = False

    #repeat this whole cell a lot of times

    for j in range(100):

        #getting the payoffs
        payoff = {key: 0 for (key) in G.node} #store the payoffs of the players in a separate dictionary

        for i in G.edges(): #for each element of the edgelist
            payoff[i[0]]+=pay_off(G.node[i[0]], G.node[i[1]], k)[0] #payoff of guy 1 is the output of payoff function given strategies
            payoff[i[1]]+=pay_off(G.node[i[0]], G.node[i[1]], k)[1] #same for guy 2 (second guy in current element of edgelist)

        #update

        for i in G.node: #go through all nodes
            neighbor = random.choice(G.neighbors(i)) #we choose a neighbor of our current node randomly
            if (payoff[i] < payoff[neighbor]): #if this neighbor has higher payoff than our current node
                kmax = max(len(G.neighbors(i)), len(G.neighbors(neighbor))) #normalisation constant from paper (not so important)
                Dmax = max(TS[k][0],1) - min(TS[k][1],0) #another constant - not too important for the algorithm
                threshold = (payoff[neighbor] - payoff[i])/(kmax*Dmax) #proportional to payoff difference
                if(threshold > np.random.random()): #our nodes switches to neighbors strategy with threshold probability
                    G.node[i] = G.node[neighbor] #switch to neighbors strategy

        #record strategy ratios

        coop = np.zeros(len(TS))

        for i in G.node:
            if(G.node[i]):
                coop += 1 #count number of True values among the nodes
        ratios[k][j] = coop[k]/len(G.node) #append the ratio of True values to a list that we will plot

plt.plot(ratios[13])
plt.xlabel("Time")
plt.ylabel("Number of nodes playing strategy 1")

picture = np.zeros([a,a])
for i in range(len(TS)):
    j = i%a
    picture[(i-j)/a][j] = ratios[i][-1]
    
plt.imshow(picture)
plt.title("Ratio of cooperators in total population")
plt.xlabel("T")
plt.ylabel("S")
#plt.savefig("barabasi.png")

#payoff function assigns a tuple of 2 payoffs for the two players for each strategy combination

def pay_off(s1, s2, i):
    if(s1 and s2):
        return (1,1)
    if(s1 and not s2):
        return (TS[i][1],TS[i][0])
    if(not s1 and s2):
        return (TS[i][0],TS[i][1])
    if(not s1 and not s2):
        return (0,0)
