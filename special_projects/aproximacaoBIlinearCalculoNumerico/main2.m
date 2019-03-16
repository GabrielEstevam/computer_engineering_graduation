n = 4;
x=[0:1/(n-1):1]';
y = x;
z = cos(2*pi*x)*sin(2*pi*y');
disp(z);
%plotar(x,y,z);

N = 2*n;
x1=[0:1/(N-1):1]'
y1 = x1

a = 1;
b = 2;
c = 1;
d = 2;

disp("x(a): ");
disp(x(a));
disp("x(b): ");
disp(x(b));
disp("y(c): ");
disp(y(c));
disp("y(d): ");
disp(y(d));
disp("z(a,c): ");
disp(z(a,c));
disp("z(a,d): ");
disp(z(a,d));
disp("z(b,c): ");
disp(z(b,c));
disp("z(b,d): ");
disp(z(b,d));
e = bilinear (0.14286,0.14286,x(a),x(b),y(c),y(d),z(a,c),z(a,d),z(b,c),z(b,d))
%I(i, j) = bilinear(x1(i),y1(j),x(a),x(b),y(c),y(d),z(a,c),z(a,d),z(b,c),z(c,d));


%disp(I);
%z = bilinear(x,y,x1,x2,y1,y2,z1,z2,z3,z4);
%plotar(x1,y1,I);

