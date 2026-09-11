function [x1,x2,x3] = Q2_F(x,y,z)
    k1 = 0.08;
    k2 = 0.01;
    k3 = 0.12;
    
    u1 = k1 * (x.^2 + y.^2);
    u2 = k2 * (2*x - y);
    u3 = k3 * (2*z);
    
    % u1 = k1*(x.*cos(y) + z.^2);
    % u2 = k2*(exp(x));
    % u3 = k3*(x.*y.*z);
    
    x1 = x + u1;
    x2 = y + u2;
    x3 = z + u3;
end
