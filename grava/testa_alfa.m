clear all


r=30;
for n=10:10:1000
   alfa(n)=n/(n+r);
end
plot(alfa,'.g')
hold on

r=50;
for n=10:10:1000
   alfa(n)=n/(n+r);
end
plot(alfa,'.b')

r=100;
for n=10:10:1000
   alfa(n)=n/(n+r);
end
plot(alfa,'.r')

hold off