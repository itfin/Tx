.module.handy:2017.01.25;

typefill:{[x;y]$[0<=type y;x;null y;x;y]};sfill:typefill[`];ifill:typefill[0Ni];ffill:typefill[0n];rfill:typefill[0ne];jfill:typefill[0Nj];tfill:typefill[0Nt];dfill:typefill[0Nd];pfill:typefill[0Np];chfill:typefill[" "];
cfill:{[x]$[10h=abs type x;x;""]};tostring:{[x]$[10h=abs type x;x;string x]};

padx:{[f;n;x]an:abs[n];n#$[n>0;x,(0|n-count[x])#f;((0|an-count[x])#f),x]}; /[pad atom;total len(>0 pad on right;<0 pad on left);list to be padded]
pad:padx[" "];pad0:padx["0"];padf:padx[0n];

mirror:{(value x)!key x};
map2vars:{[x;y](key y) ({.[x;enlist y;:;z]}[x])' value y;};

tkey:{key[x] except `};
weekday:{x-`week$x:`date$x}; /[日期]取当前为星期几:0->星期一,4->星期五,5->星期六,6->星期日
dictstr:{[x]{"|" sv (string key x),'"=",/:(-3!)each value x} ` _x};
strdict:{[x] value each (!/)"S=|" 0: x};
unixdate:{08:00+`datetime$-10957+x%86400};

unmap_helper:{$[(type x)or not count x;1;t:type first x;all t=type each x;0]};
unmap_column:{[]select from (raze {([]table:enlist x;columns:enlist where not unmap_helper each flip .Q.en[`:.]`. x)} each tables[]) where 0<count each columns};

httpget1:{[host;location] r:(`$":http://",host)"GET ",location," HTTP/1.1\r\nHost:",host,"\r\n\r\n";i:first r ss "\r\n\r\n";(i+4) _ r}; /对于包含"\n"的二进制

quote:{[x]"\"",(ssr[;"\\";"\\\\"] ssr[;"\"";"\\\""] x),"\""};