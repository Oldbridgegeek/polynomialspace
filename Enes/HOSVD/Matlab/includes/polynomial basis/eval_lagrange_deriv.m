function y = eval_lagrange_deriv(i,x,vertex)    y = eval_lagrange(i,x,vertex);    val = 0;    for k=1:size(vertex)        if(k!=i)            val = val + 1/(x-vertex(k));        endif    endfor        y = y * val;    endfunction