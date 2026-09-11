function [gradU] = Q3_gradU(u,v,w,n)
    gradU = zeros(3,3,n,n,n);
    [gradU(1,1,:,:,:), gradU(1,2,:,:,:), gradU(1,3,:,:,:)] = gradient(u,1/n,1/n,1/n);
    [gradU(2,1,:,:,:), gradU(2,2,:,:,:), gradU(2,3,:,:,:)] = gradient(v,1/n,1/n,1/n);
    [gradU(3,1,:,:,:), gradU(3,2,:,:,:), gradU(3,3,:,:,:)] = gradient(w,1/n,1/n,1/n);
end
