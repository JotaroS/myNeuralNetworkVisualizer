

M=csvread('out.csv');
xlabel("number of interm layer")
ylabel("iteration")
plot(M(1,:),M(2,:),"linewidth",3.0,'color',[1.0 0 0])
legend('0%')
hold on;
plot(M(1,:),M(3,:),"linewidth",3.0,'color',[0.9 0 0])
hold on;
plot(M(1,:),M(4,:),"linewidth",3.0,'color',[0.8 0 0])
hold on;
plot(M(1,:),M(5,:),"linewidth",3.0,'color',[0.7 0 0])
hold on;
plot(M(1,:),M(6,:),"linewidth",3.0,'color',[0.6 0 0])
hold on;
plot(M(1,:),M(7,:),"linewidth",3.0,'color',[0.5 0 0])
hold on;
plot(M(1,:),M(8,:),"linewidth",3.0,'color',[0.4 0 0])
hold on;
plot(M(1,:),M(9,:),"linewidth",3.0,'color',[0.3 0 0])
hold on;
plot(M(1,:),M(10,:),"linewidth",3.0,'color',[0.2 0 0])
hold on;
plot(M(1,:),M(11,:),"linewidth",3.0,'color',[0.1 0 0])
hold off;
L=legend({'10%','20%','30%','40%','50%','60%','70%','80%','90%'},'location','northeastoutside');
title("Iteration count for different interm layer and input noise rate",'FontSize',15);
xlabel('Number of interm layer','FontSize',15)
ylabel('Count of iteration','FontSize',15)
input('quit')
print -dpdf file.pdf
