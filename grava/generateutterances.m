clear all

x1 = [1 3 5;2 4 6;7 8 9];
x2 = [10 30 50 70 90;20 40 60 80 100; 100 300 500 700 900];

fid=fopen("loc1a.dat","wb");
fwrite(fid,x1,"double");
fclose(fid);

fid=fopen("loc2a.dat","wb");
fwrite(fid,x2,"double");
fclose(fid);

