x=[0:1/4:1]';
y = x;
z = cos(2*pi*x)*sin(2*pi*y');
%plot3(x,y,z,'rx');
%surf(x,y,z);
plotar(x,y,z);