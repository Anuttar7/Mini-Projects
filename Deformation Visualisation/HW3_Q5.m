l = 2;              %Half length of Square
n = 11;             %Number of points considered on a line
nh = 101;

[x0,y0] = meshgrid(linspace(0,2*l,n), linspace(0,2*l,n));
[r, theta] = meshgrid(linspace(0,1,nh), linspace(0,2*pi,nh));
xh = l*ones(nh,nh) + r.*cos(theta);
yh = l*ones(nh,nh) + r.*sin(theta);

[x0d, y0d] = Q4_F(x0,y0);
[xhd, yhd] = Q4_F(xh,yh);

%gradU Tensor
gradU = Q4_gradU(x0d-x0, y0d-y0, n);
gradUh = Q4_gradU(xhd-xh,yhd-yh,nh);

%Normal Strain Matrix
C0 = sqrt((x0d-x0).^2 + (y0d-y0).^2);

%Temporary Matrix Initialisation
A = zeros(n,n);
B = zeros(nh,nh);

hold on;
% surf(x, y, zeros(n,n));
% surf(xh, yh, 0.5*ones(nh,nh), zeros(nh,nh));
surf(x0d, y0d, ones(n,n), C0);
surf(xhd, yhd, 2*ones(nh,nh), zeros(nh,nh));
% A(:,:) = gradU(1,1,:,:);
% B(:,:) = gradUh(1,1,:,:);
% surf(x0,y0,A);
% surf(xh,yh,B,zeros(nh,nh));

hold off;
