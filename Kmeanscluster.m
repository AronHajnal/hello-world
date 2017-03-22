A = double(imread('C:\Users\Aron Hajnal\Documents\Data\bird_small.tiff'));
mu = zeros(1,16,3);
n = 128;
for i=1:16
mu(1, i,:) = A(randi(n), randi(n), :);
end
distv = zeros(n, n, 16, 3);
dist = zeros (n, n, 16);
c = zeros(n,n);


for r =1:200

for i=1:n
    for j=1:n
        for k=1:16
            distv(i,j,k,:) = A(i,j,:) - mu(1, k,:);
            dist(i,j,k) = (distv(i,j,k,1))^2+(distv(i,j,k,2))^2+(distv(i,j,k,3))^2;
        end
        [maki, c(i,j)] = (min(dist(i,j,:)));
    end
end

ave = zeros(1, 16, 3);
x = zeros(16, 1);
for i=1:16
    for j=1:n
        for k=1:n
            if c(j,k)== i
                ave(1, i,:) = ave(1, i,:) + A(j,k,:);
                x(i) = x(i)+1;
            end
        end
    end
end

for i=1:16
    mu(1,i, :) = ave(1, i, :)./ x(i);
end

end

B = double(imread('C:\Users\Aron Hajnal\Documents\Data\bird_large.tiff'));
m = 538;
distvl = zeros(m,m, 16, 3);
distl = zeros (m,m, 16);
d = zeros(m,m);
for i=1:m
    for j=1:m
        for k=1:16
            distvl(i,j,k,:) = B(i,j,:) - mu(1, k,:);
            distl(i,j,k) = (distvl(i,j,k,1))^2+(distvl(i,j,k,2))^2+(distvl(i,j,k,3))^2;
        end
        [maki, d(i,j)] = (min(distl(i,j,:)));
        B(i,j,:) = mu(1,d(i,j),:);
    end
end

%Display
imshow(uint8(round(B)))

% Save image
imwrite(uint8(round(B)), 'bird_kmeans.tiff');

figure; hold on
 for i=1:k
    col = (1/255).*mu(1,i,:);
    rectangle('Position', [i, 0, 1, 1], 'FaceColor', col, 'EdgeColor', col);
 end
 axis off
