function z = bilinear(x,y,x1,x2,y1,y2,z1,z2,z3,z4)
z5 = linear(x,x1,x2,z1,z2);
z6 = linear(x,x1,x2,z3,z4);
z = (z5*(y-y2)+z6*(y1-y))/(y1-y2);