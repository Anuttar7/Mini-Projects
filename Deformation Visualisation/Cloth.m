n = 101;
[x,y] = meshgrid(linspace(-10,10,n), linspace(-10,10,n));
z = Cloth_F(x,y);
C = abs(z);
surf(x,y,z);
