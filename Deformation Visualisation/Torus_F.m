function [xd,yd,zd] = Torus_F(x,y,z)
    u = 0;
    v = 0;
    w = 1*cos(z);

    xd = x + u;
    yd = y + v;
    zd = z + w;
end
