n = 20;
x=[0:1/(n-1):1]';
y = x;
z = cos(2*pi*x)*sin(2*pi*y');
%disp(z);
%plotar(x,y,z);

N = 2*n;
x1=[0:1/(N-1):1]';
y1 = x1;
for (i=1:1:N)
  for (j=1:1:N)
    % Encontra as coordenadas dos pontos vizinhos nas matriz antiga
    a = floor((n-1)*x1(i))+1;
    b = a+1;
    c = floor((n-1)*y1(j))+1;
    d = c+1;
    
    % Tratamento de fronteira para linhas
    if (i == N)
      a -= 1;
      b -= 1;
    end;
    
    % Tratamento de fronteira para colunas
    if (j == N)
      c -= 1;
      d -= 1;
    end;
    
    I(i, j) = bilinear(x1(i),y1(j),x(a),x(b),y(c),y(d),z(a,c),z(a,d),z(b,c),z(b,d));
  end;
end;

%disp(I);
plotar(x1,y1,I);

