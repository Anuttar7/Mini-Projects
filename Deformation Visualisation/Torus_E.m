function [E] = Torus_E(u,v,w,n)
    E = zeros(3,3,n,n,n);
    [E(1,1,:,:,:), E(1,2,:,:,:), E(1,3,:,:,:)] = gradient(u,1/n,1/n,1/n);
    [E(2,1,:,:,:), E(2,2,:,:,:), E(2,3,:,:,:)] = gradient(v,1/n,1/n,1/n);
    [E(3,1,:,:,:), E(3,2,:,:,:), E(3,3,:,:,:)] = gradient(w,1/n,1/n,1/n);
end
