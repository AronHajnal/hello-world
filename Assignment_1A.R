set.seed(1)

p=list()  # list for storing the result/results

for ( k in c(0.5, 0.7)){

hit_v = rep(0,1000)

for (i in 1:1000){    # loop for generating 1000   50 long binomial sequences
  #k = 0.5       # unbiased coin
  binom_v = rbinom(50, 1, k)
  countH=0
  countT=0
  hit=0
  for (j in 1:length(binom_v)){   # loop for checking wether a sequence contains a 6 long run
    if (binom_v[j] == 1){
      countH = countH + 1   #if it is head increment the head counter
      countT = 0            #and reset the tail counter
    }else{
      countH = 0            #if it is tail reset the head counter 
      countT = countT + 1   #and increment the tail counter
    }
    if (countH == 6 || countT == 6){  #if one of the counter reaches 6
      hit_v[i] = 1          #put 1 to the corresponding element of the hit vector
      break                 #escape from the inner for loop
    }
  }
}
  if (k == 0.5){
  p["ub"] = sum(hit_v)/1000 #YOU TASK IS TO REWRITE THIS, the p must contain an estimated probability
  }
  else{
    p["b"] = sum(hit_v)/1000
  }
}
       
print( paste('p_ub: ', toString(p["ub"]) ) , quote = F)
print( paste('p_b: ', toString(p["b"]) ) , quote = F)



# # for the 5. part of the exercise A
 
 q=list(ub=0.6, b=0.4)   # biased and unbiased coin proportions in the bag
  
 prob_6seq = p[["ub"]]*q[["ub"]] + p[["b"]]*q[["b"]]
 
 print( paste('prob_6seq: ', toString(prob_6seq) ) , quote = F)
 
 prob_biasG6seq = p[["b"]]*q[["b"]]/prob_6seq  # probability of biased coin Given to the six long sequence
 
 print( paste('prob_biasG6seq: ', toString(prob_biasG6seq) ), quote = F)


