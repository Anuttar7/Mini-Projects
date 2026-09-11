function [gradU] = Q4_gradU(u,v,n)
    gradU = zeros(2,2,n,n);
    [gradU(1,1,:,:), gradU(1,2,:,:)] = gradient(u,1/n,1/n);
    [gradU(2,1,:,:), gradU(2,2,:,:)] = gradient(v,1/n,1/n);
end
