function [xd,yd,zd] = Q3_F(x,y,z)
    alpha = 0.05;
    beta = 0.1;

    u = alpha*x + beta*y.*z;
    v = alpha*y + beta*z.*x;
    w = alpha*z + beta*x.*y;
    xd = x + u;
    yd = y + v;
    zd = z + w;
end
