n = 101;
R = 5;
[r, theta, phi] = meshgrid(linspace(0,1,n), linspace(0,2*pi,n), linspace(0,2*pi,n));
x = (R*ones(n,n,n) + r.*cos(theta)).*cos(phi);
y = (R*ones(n,n,n) + r.*cos(theta)).*sin(phi);
z = r.*sin(theta);
[xd, yd, zd] = Q3_F(x,y,z);

C = sqrt((xd-x).^2 + (yd-y).^2 + (zd-z).^2);

E = Torus_E(xd-x,yd-y,zd-z,n);

X = zeros(n,n); Y = zeros(n,n); Z = zeros(n,n); C1 = zeros(n,n);

hold on;
%Plot of undeformed Torus
% X(:,:) = x(:,n,:); Y(:,:) = y(:,n,:); Z(:,:) = z(:,n,:);
% surf(X,Y,Z,zeros(n,n));

%Plot of deformed Torus
X(:,:) = xd(:,n,:); Y(:,:) = yd(:,n,:); Z(:,:) = zd(:,n,:); C1(:,:) = C(:,n,:);
surf(X,Y,Z,C1);
hold off;
