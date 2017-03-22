numTrainDocs = 700;
numTokens = 2500;
M = dlmread('C:\Users\Aron Hajnal\Documents\Data\Naive Bayes\train-features.txt', ' ');
spmatrix = sparse(M(:,1), M(:,2), M(:,3), numTrainDocs, numTokens);
train_matrix = full(spmatrix);
train_labels = dlmread('C:\Users\Aron Hajnal\Documents\Data\Naive Bayes\train-labels.txt');
one = ones(numTokens, 1);
one1 = ones(numTrainDocs, 1);
phi = sum(train_labels)/numTrainDocs;
phi1 = ((train_matrix' * train_labels)+1)/(one' * train_matrix' * train_labels + numTokens);
phi0 = (train_matrix' * (one1-train_labels)+1)/(one' * train_matrix' * (one1-train_labels) + numTokens);

test = dlmread('C:\Users\Aron Hajnal\Documents\Data\Naive Bayes\test-features.txt', ' ');
labels = dlmread('C:\Users\Aron Hajnal\Documents\Data\Naive Bayes\test-labels.txt');
m = size(labels, 1);
spmatrix = sparse(test(:,1), test(:,2), test(:,3), m, numTokens);
testmatrix = full(spmatrix);

    p1 = testmatrix*log(phi1)+log(phi);
    p0 = testmatrix*log(phi0)+log(1-phi);
    
    class = p1 > p0;

numdocs_wrong = sum(xor(class, labels));

fraction_wrong = numdocs_wrong/m
