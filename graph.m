M=csvread('out.csv');
xlabel("number of interm layer")
ylabel("iteration")
plot(M(1,:),M(2,:),"linewidth",3.0)

hold on;
input('quit')
print -deps file.eps
