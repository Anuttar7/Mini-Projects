n = 11;         %Number of points considered on a line

%Underformed coordinates:
[x, y, z] = meshgrid(linspace(0,3,n), linspace(0,3,n), linspace(0,3,n));

%Deformed coordinates:
[xd, yd, zd] = Q2_F(x,y,z);

%Grad U Tensor
gradU = Q2_gradU(xd-x,yd-y,zd-z,n);

%Normal Strain Matrix for all points
C = sqrt((xd-x).^2 + (yd-y).^2 + (zd-z).^2);

%Temporary Matrices
X = zeros(n,n); Y = zeros(n,n); Z = zeros(n,n); C1 = zeros(n,n);


hold on;
% Plot of undeformed Cube
% surf(x(:,:,1),y(:,:,1),z(:,:,1), zeros(n,n),'FaceAlpha',0.8);
% surf(x(:,:,n),y(:,:,n),z(:,:,n),zeros(n,n),'FaceAlpha',0.8);
% X(:,:) = x(:,1,:); Y(:,:) = y(:,1,:); Z(:,:) = z(:,1,:);
% surf(X,Y,Z,zeros(n,n),'FaceAlpha',0.8);
% X(:,:) = x(:,n,:); Y(:,:) = y(:,n,:); Z(:,:) = z(:,n,:);
% surf(X,Y,Z,zeros(n,n),'FaceAlpha',0.8);
% X(:,:) = x(1,:,:); Y(:,:) = y(1,:,:); Z(:,:) = z(1,:,:);
% surf(X,Y,Z,zeros(n,n),'FaceAlpha',0.8);
% X(:,:) = x(n,:,:); Y(:,:) = y(n,:,:); Z(:,:) = z(n,:,:);
% surf(X,Y,Z,zeros(n,n),'FaceAlpha',0.8);
% 
% Plot of Deformed Cube
surf(xd(:,:,1),yd(:,:,1),zd(:,:,1),C(:,:,1));
surf(xd(:,:,n),yd(:,:,n),zd(:,:,n),C(:,:,n));
X(:,:) = xd(:,1,:); Y(:,:) = yd(:,1,:); Z(:,:) = zd(:,1,:); C1(:,:) = C(:,1,:);
surf(X,Y,Z,C1);
X(:,:) = xd(:,n,:); Y(:,:) = yd(:,n,:); Z(:,:) = zd(:,n,:); C1(:,:) = C(:,n,:);
surf(X,Y,Z,C1);
X(:,:) = xd(1,:,:); Y(:,:) = yd(1,:,:); Z(:,:) = zd(1,:,:); C1(:,:) = C(1,:,:);
surf(X,Y,Z,C1);
X(:,:) = xd(n,:,:); Y(:,:) = yd(n,:,:); Z(:,:) = zd(n,:,:); C1(:,:) = C(n,:,:);
surf(X,Y,Z,C1);
% %
% Strain Exx Variations
% X(:,:) = x(:,:,1); Y(:,:) = y(:,:,1); C1(:,:) = gradU(1,1,:,:,1); 
% surf(X, Y, C1);
%
hold off;
