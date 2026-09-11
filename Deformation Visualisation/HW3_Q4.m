l = 2;              % Half length of square
n = 101;             % Number of points considered on a line

%Undeformed Coordinates
[x, y] = meshgrid(linspace(0,2*l,n), linspace(0,2*l,n));

%Deformed Coordinates
[xd, yd] = Q4_F(x,y);

%grad U Tensor
gradU = Q4_gradU(xd-x,yd-y,n);

%Normal Strain Matrix
C = sqrt((xd-x).^2 + (yd-y).^2);

%Temporary Matrices Initialisation
A = zeros(n,n);

hold on;
%Plot of Undeformed Square
% surf(x, y, zeros(n,n));

%Plot of Deformed Square
surf(xd, yd, ones(n,n),C);

% Plot of Exx variation
% A(:,:) = gradU(1,1,:,:);
% surf(x, y, A);
hold off;
