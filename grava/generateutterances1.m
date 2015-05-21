clear all


nAmostras = 100000;

x1 = [normrnd(1,1,1,nAmostras);normrnd(2,1,1,nAmostras);normrnd(3,1,1,nAmostras)];
x2 = [normrnd(4,1,1,nAmostras);normrnd(5,1,1,nAmostras);normrnd(6,1,1,nAmostras)];
x3 = [normrnd(7,1,1,nAmostras);normrnd(8,1,1,nAmostras);normrnd(9,1,1,nAmostras)];
x4 = [normrnd(10,1,1,nAmostras);normrnd(11,1,1,nAmostras);normrnd(12,1,1,nAmostras)];

fid=fopen("loc1.dat","wb");
fwrite(fid,x1,"float");
fclose(fid);

fid=fopen("loc2.dat","wb");
fwrite(fid,x2,"float");
fclose(fid);

fid=fopen("loc3.dat","wb");
fwrite(fid,x3,"float");
fclose(fid);

fid=fopen("loc4.dat","wb");
fwrite(fid,x4,"float");
fclose(fid);
