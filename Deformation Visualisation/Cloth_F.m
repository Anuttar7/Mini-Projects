function [z] = Cloth_F(x,y)
    k = 0.01;
    r = sqrt(x.^2 + y.^2);
    z = k*exp(-0.1*r).*cos(r);
end
