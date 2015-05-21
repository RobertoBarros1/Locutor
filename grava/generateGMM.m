fid=fopen("gmmteste.dat","wb");

x=2;
fwrite(fid,x,"int"); % nGaussians
fwrite(fid,x,"int"); % dim

x=0.4;
fwrite(fid,x,"double"); % l[0].p
x=[1 3];
fwrite(fid,x,"double"); % l[0].m
x=[1.5 1];
fwrite(fid,x,"double"); % l[0].s

x=0.6;
fwrite(fid,x,"double"); % l[1].p
x=[2 4];
fwrite(fid,x,"double"); % l[1].m
x=[2.5 2];
fwrite(fid,x,"double"); % l[1].s

fclose(fid);

