n = 101;                 %Number of points considered on a line

% Undeformed polar coordinates
[r, theta, phi] = meshgrid(linspace(0,1,n), linspace(0, 2*pi, n), linspace(0, pi, n));

% Undeformed Cartesian coordinates
x = r.*cos(theta).*sin(phi);
y = r.*sin(theta).*sin(phi);
z = r.*cos(phi);

% Deformed Cartesian Coordinates
[xd, yd, zd] = Q3_F(x,y,z);

%grad U Tensor
gradU = Q3_gradU(xd-x,yd-y,zd-z,n);

% Normal Strain Matrix
C = sqrt((xd-x).^2 + (yd-y).^2 + (zd-z).^2);

%Temporary Matrices
X = zeros(n,n); Y = zeros(n,n); Z = zeros(n,n); C1 = zeros(n,n);

hold on;
%Plot of Undeformed Sphere
% X(:,:) = xd(:,n,:); Y(:,:) = yd(:,n,:); Z(:,:) = zd(:,n,:);
% surf(X,Y,Z,zeros(n,n));

%Plot of Deformed Sphere
X(:,:) = xd(:,n,:); Y(:,:) = yd(:,n,:); Z(:,:) = zd(:,n,:); C1(:,:) = C(:,n,:);
surf(X,Y,Z, C1);

% Plot of Exx Variation with fixed phi
% X(:,:) = x(:,:,10); Y(:,:) = y(:,:,10); C1(:,:) = gradU(1,1,:,:,10);
% surf(X,Y,C1);

%Plot of Exx Variation with fixed radius
% X(:,:) = x(:,n,:); Y(:,:) = y(:,n,:); C1(:,:) = gradU(1,1,:,10,:);
% surf(X,Y,C1);

%Plot of Exx Variation with fixed theta
% X(:,:) = x(10,:,:); Y(:,:) = y(10,:,:); C1(:,:) = gradU(1,1,10,:,:);
% surf(X,Y,C1);

hold off;
