.module.math:2016.12.29;

\d .math
fixop:{tc:{x[{(y[x;y])[z]}[x;y]]};tc[x;tc]}; /����������,tc:�����Ահ�

//��ѧ����
e: exp 1;
pi:acos -1; 
oz:31.10348;

//���Ⱥ���
sinh: {0.5 * (exp x) - exp neg x};
cosh: {0.5 * (exp x) + exp neg x};
tanh: {(e - 1) % (e: exp 2 * x) + 1};
asinh:{log x+sqrt 1+x*x};
acosh:{log x+sqrt (1+x)*(1-x)};
atanh:{0.5*(log 1+x)-(log 1-x)};

//Arthur(http://kx.com/q/stat.q)
nx:{abs(x>0)-(exp[-.5*x*x]%sqrt 2*pi)*t*.31938153+t*-.356563782+t*1.781477937+t*-1.821255978+1.330274429*t:1%1+.2316419*abs x}; /normal from x
xn:{$[.5>x;0-.z.s 1-x;.92>x;(x*2.50662823884+l*-18.61500062529+l*41.39119773534+l*-25.44106049637)%1+l*-8.47351093090+l*23.08336743743+l*-21.06224101826+3.13082909833*l:x*x-:.5;0.3374754822726147+l*0.9761690190917186+l*0.1607979714918209+l*0.0276438810333863+l*0.0038405729373609+l*0.0003951896511919+l*0.0000321767881768+l*0.0000002888167364+0.0000003960315187*l:log 0-log 1-x]}; /x from normal  (chebychev near 0.5 and log for the tails) slow then gi
nor:{$[x=2*n:x div 2;raze sqrt[-2*log n?1f]*/:(sin;cos)@\:(2*pi)*n?1f;-1_.z.s 1+x]}; /random normal distribution, e.g. nor 10
cvm:{(x+flip(not n=\:n)*x:(n#'0.0),'(x$/:'(n:til count x)_\:x)%count first x)-a*\:a:avg each x}; /covariance matrix (8 times faster than x cov/:\:x) 
crm:{cvm[x]%u*/:u:dev each x}; / correlation matrix

//Milan Ondrus:http://homepage.hispeed.ch/milano
k) combn:{(*/1f*y#|!1+x)%*/1f+!y}; /[n;i]�����C[n;i]
g:{abs (neg x>0f)+(1f%sqrt 2f*pi)*(exp -0.5*x*x)*t*0.31938153+t*-0.356563782+t*1.781477937+t*-1.821255978+1.330274429*t:1f%1f+0.2316419*abs x}; /N(0,1) cdf 
gi:{[x]l:r[i:where b:.1764>r:q*q:-.5+x:raze "f"$x];
 x[i]:(q[i]*2.50662823884+l*-18.61500062529+l*41.39119773534+l*-25.44106049637)%(1.0+l*-8.47351093090+l*23.08336743743+l*-21.06224101826+l*3.13082909833);
 l:log neg log r[i]:t+x[i]*1-q:2*t:q[i:where not b]>0;
 x[i]:(q-1)*0.3374754822726147+l*0.9761690190917186+l*0.1607979714918209+l*0.0276438810333863+l*0.0038405729373609+l*0.0003951896511919+l*0.0000321767881768+l*0.0000002888167364+l*0.0000003960315187;x}; /inverse of N(0,1) cdf Moro's algorithm

std:{sqrt (sum l*l:x-avg x)%-1+count x};
varp:{i*i:std x};
covp:{(sum(x-avg x)*y-avg y)%-1+count x};
corrp:{(sum i*j)%sqrt(sum j*j:y-avg y)*sum i*i:x-avg x};
indep:{c*sqrt (-2+count first x)%1-c*c:corrp . x}; 
regr:{(avg y-i*avg x),i:((std y)%std x)*corrp . (x;y)};
regrTest:{((sqrt (-2f+count x)%(a*a:std y)-u*u:t*i))*(i:std x)*abs z-t:last regr . (x;y)};
marg:{sum (t*t:u-raze c)%u:(prd each i cross sum 1f*c:flip x)%sum i:sum x};
hypp:{sum (i*i:y-l)%l:(count y)#x*sum y};
dtt:{((avg y)-avg x)*sqrt (1f%r*((varp x)*u-1f)+(varp y)*v-1f)*(-2f+r:u+v)*(v:count y)*(u:count x)};
bdt: {std y-x};
dsg:{abs (x-avg y)*(sqrt count y)%std y};
regrp:{u:x+1;r:sum each w:(enlist (count y)#1f),prds (2*x)#enlist 1f*y;b:u {1 rotate x}\r;s:u#u#'b;:raze (inv s)$flip enlist 1f*sum flip (u#enlist z)*u#w;};

//BlackScholes
optBS:{[S;X;rf;rd;t;s]d1:((log S%X)+t*((s*s*0.5)+rd-rf))%a:s*sqrt t;(S*(exp neg rf*t)*g d1)-X*(exp neg rd*t)*g d1-a}; /rd=domestic yield(cc),rf=foreign yield(cc),s=implied volatility(s>0:put,s<0:call);call:optBS[50;50;0.1;0;1;0.5],put:neg optBS[50;50;0.1;0;1;-0.5]
bs1:{[x;s;v;t;r;c]vt:v*sqrt t;d1:((log s%x)+t*r+v*v%2.)%vt;d2:d1-vt;?[c=`call;(s*cnd d1)-x*(exp neg r*t)*cnd d2;(x*(exp neg r*t)*cnd neg d2)-s*cnd neg d1]}; /[��Ȩ��;���ɼ�;������;�޷�������;���]Black-Scholes

CDF:PDF:()!();
PDF[`cauchy]:{reciprocal pi * 1 + x * x};
CDF[`cauchy]:{0.5 + (atan x) % pi};
PDF[`gauss]:{(reciprocal sqrt 2 * pi) * exp neg 0.5 * x * x};
CDF[`gauss]:{{ $ [x < 0; 1 - .z.s abs x; 0.5 * 1 + erf x % sqrt 2]} each x};

BSterms:{[cdf;s;k;v;r;t]vt:v*sqrt t;d:((log s%k)+t*r+0.5*v*v)%vt;(d;d-vt)}; /blackscholes cdf terms
BSbinary:{[cdf;s;k;v;r;t]d:BSterms[cdf;s;k;v;r;t];pv:exp neg r*t;`call`put!(pv*cdf d 1;pv*cdf 1-d 1)}; /Binary call and put.
BSeuro:{[cdf;s;k;v;r;t]d:BSterms[cdf;s;k;v;r;t];kt:k*exp neg r*t;`call`put!((s*cdf d 0)-kt*cdf d 1;(kt*cdf neg d 1)-s*cdf neg d 0)}; /European call and put. 

bisec:{[e;f;x]while[(0<>v:f y:avg x)&(e<x[1]-x[0]);$[0>v*f x[0];x:x[0],y;x:y,x[1]]];y}; /[epsilon;f;(x0,x1)] f(x0)*f(x1)<0,find root of f


//gbaker functions
pochhammer: {[x; n] $ [n <= 0; 1; prd x + til `int $ n]};
factorial: {{pochhammer[1; x]} each x};
kummer: {[a; b; z; n] 1 + sum prds (z * a + n) % (1 + n) * b + n: til `int $ abs n}; /http://reference.wolfram.com/mathematica/ref/Hypergeometric1F1.html
abserf: {x: abs x; min (1; (2 * x % sqrt pi) * kummer [0.5; 1.5; neg x * x; 15])};
erf: {{ $ [x = 0; 0f; x < 0; neg abserf abs x; abserf x ]} each x};

mode: {h: count each group x; h ? max h};
zstd:{(x - avg x) % dev x};
Zstd:{[x; m; s] (x - m) % s};
randn:{-6+sum each 0N 12#(12*x)?1f}; /normal random N(0,1) 
empdf:{{(count y) % x}[count x] each group (((max x) - min x) % sqrt count x) xbar asc x}; /Empirical probability distribution function, returning a dictionary of probability keyed on bound.
runstest:{n:count x;f:n-t:count where x;r:count where differ x;p:2f*t*f;e:1+p%n;d:sqrt(p*p-n)%n*n*n-1;`N`runs`mu`z!(n;r;e;(r-e)%d)}; /http://en.wikipedia.org/wiki/Wald-Wolfowitz_runs_test

KMpredict:{[x;pv](first x;pv+last x)}; /[(���ں������;�������Э����������);�������������]->(�����������;�������Э�����������)
KMcorrect:{[x;y;mv]k:lxh%mv+lxh:last x;(fxh+k*y-fxh:first x;(1-k)*lxh)}; /[(�����������;�������Э�����������);���ڹ۲�ֵ;�۲����������]->(���ں������;�������Э����������)
KMfilter:{[x;y]x:`float$x;mv:var x;xh:enlist (first x;mv);i:1;do[-1+count x;xh,:enlist KMcorrect[KMpredict[last xh;y];x[i];mv];i+:1];xh}; /[�۲�����;�������������]kalman�˲�,http://www.cs.unc.edu/~welch/kalman/media/pdf/kalman_intro_chinese.pdf

//
k)diag:{(2##x)#,/x,'(2##x)#0f}; //[x:�Խ�������]���ɶԽǾ���
wlsq:{p:flip pt:1f,'x;w:diag z;c:(inv p mmu w mmu pt) mmu p mmu w mmu y}; //[x;y;w]��Ȩ��С�������
r2:{1e-2*floor 0.5+1e2*x};r3:{1e-3*floor 0.5+1e3*x};r4:{1e-4*floor 0.5+1e4*x};r5:{1e-5*floor 0.5+1e5*x};f2:{1e-2*floor 1e2*x};f3:{1e-3*floor 1e3*x}; //ȡ������:100,1000,0.01,0.001
cnd:{t:reciprocal 1+.2316419*abs x;s:t*.31938153+t*-.356563782+t*1.781477937+t*-1.821255978+1.330274429*t;abs(neg x>0)+(1% sqrt 2*pi)*(exp -.5*x*x)*s}; //[x]c.d.f of N(0,1)
scale:{[x;y]m:x 0;M:x 1;ym:min y;yM:max y;m+(M-m)*(y-ym)%(yM-ym)}; //[(min;max);x]��x�����任��[min,max]����
qth:{[x;y;z]$[()~z;0n;min z where y=x xrank z]}; //[�ܼ���;��λ��;����]ȡ���ݵ�ĳ����λ
qnth:{x:asc 0^x;1_value asc x min each group y xrank x};q200:qnth[;200];q100:qnth[;100];q4:qnth[;4];q5:qnth[;5];q10:qnth[;10];q20:qnth[;20]; //[����;�ּ���]ȡ���ݸ���λ����
predls:{[x]x:`float$x;n:count x;coef:x lsq (n#1f;`float$til n);coef mmu 1f,`float$n}; //��С������Ϻ�����һ��Ԥ��

pldist:{[x;y]k:y 0;((x 1)-(y 1)+k*(x 0))%sqrt 1+k*k}; /�㵽ֱ�߾���x:(t,p),y:(k,b)->d
GSR:0.5*-1+sqrt 5;gsr:GSR xexp;GSR1:GSR;GSR2:gsr 2;GSRn1:gsr -1;GSRn2:gsr -2;   /golden section ratio ������

incometax:{[x]1e-2*floor 0.5+sum 3 10 20 25 30 35 45*deltas 1500 4500 9000 35000 55000 80000 0w&0|x-3500}; /[������]��������˰

loadea:{y:`int$y*12;z%:12;y#x%sum 1%(1+z) xexp 1+til y}; /[�����;��������;������]����(�ȶ��)ÿ�»��������
loadep:{y:`int$y*12;z%:12;p:y#x%y;p+z*(x-sums 0,-1_p)}; /[�����;��������;������]����(�ȱ�����)ÿ�»��������

mdd:{-1+min x %maxs x}; mdds:{neg -1+max x%mins x}; mloss:{-1+(min x)%first x}; //[��ֵ����]mdd:��ֵ���س�;mloss:��󱾽���ʧ
mcov:{mavg[x;y*z] - mavg[x;y] * mavg[x;z]}; /
mcor:{mcov[x;y;z]%mdev[x;y]*mdev[x;z]};     /[k4] Mcor & mcov


//matlab functions
meshgrid:{[x]$[0<type x;[y:x];[y:x[1];x:x[0]]];((count y)#enlist x;flip (count x)#enlist y)};

fix:{signum[x]*floor abs x}; /��ԭ�㷽��ȡ��

magic:{[x]$[mod[x;2];[J:first y:meshgrid[1+til x];I:y[1];A:mod[I+J-`int$(x+3)%2;x];B:mod[-2+I+2*J;x];1+B+x*A];mod[x;4];[p2:p*p:`int$x%2;M:.z.s[p];M:(M,'M+2*p2),((M+3*p2),'M+p2);i:til p;k:`int$(x-2)%4;j:(til k),(1+x-k)+til k-1;M[(i,i+p);j]:M[(i+p),i;j];i:k;j:0,i;M[i,i+p;j]:M[(i+p),i;j];M];[J:first y:meshgrid[1+til x];I:y[1];K:where raze fix[mod[I;4]%2]=fix[mod[J;4]%2];M:1+til z:x*x;M[K]:1+z-M[K];x cut M]]};

ismagic:{[x]y:count x;((1+til y*y)~asc raze x)&1=count distinct (sum each x),(sum each flip x),(sum x ./:{x,'x} til y),sum x ./:{x,'reverse x} til y};

eye:{x:til x;"f"$x=/:\:x};
zeros:{$[not count x;();1=count x;(first x)#0f;reshape[x;(prd x)#0f]]};
ones:{$[not count x;();1=count x;(first x)#1f;reshape[x;(prd x)#1f]]};

//util funcs
filter:{[f;y]y where f y};
foldr:{foldl[x;y;reverse z]};
foldl:{{x[z;y]}[x]/[y;z]};

comb:{asc where each y(distinct raze(rotate[1]\)each 1,')/enlist(x-y)#0}; /[k4]Kevin Lawler 
perm:{asc(enlist()){raze(rotate[1]\)each x,'y}/til x}; /[k4]Kevin Lawler 

combine:{[n;k]$[n >= (count k);:enlist k;];$[n <= 1;:enlist each k;];c:(enlist k[0]),/:combine[n-1;1 _k];c:c,combine[n;1 _k]};
combineAll:{[k]raze combine[;k] each (reverse 1+til count k)}; /[k4]Greg.Watson@barclayscapital.com
subs:(('[;]) over (raze;((-1_(-1_)\)');(-1_(1_)\)));
subs1:{raze mover[::;;x] each 1+til count x};

swin:{[f;n;s] f each{1_x,y}\[n#0#s;s] }; /Flying
swin0:{[f;n;s] f each (n-1)_{1_x,y}\[n#0#s;s]}; /Flying
mover:{[f;n;x]f each x filter['[(0<=);min]'] (til count x)-\:reverse til n};
flatten:,//; 
reshape:{{y cut x}/[y;(reverse 1_x) except 0]}; /[shape;array]J's dyad verb $
levelat:{$[x>=0;x {x'}/ y;::]}; /[level;func]make monad func apply at [level] depth elems.
wheres:{n:count y;where (mover[::;n] x)~\:y};

dim:{-1+count (first\)x};
shape:{-1 _ count each (first\) x};
flipx:{[x;y]L:dim[x];D:count y first/ x;I:(D,L)#(::);I[;y]:til D;x ./: I}; /[array;dim]move dim axe to first dim.
flipxv:{[x;y]flipx/[x;{x+til count x}reverse y]}; /[array;dim array(asc)]move dim array axe to first dims.
filldim:{[x;y]levelat[y[0];{y#enlist x}[;y[1]]] x}; /[array;(level;size)]add a new dim @level by do [size] copy. 
imax:{x?max x};
imin:{x?min x};
.q.allin:(')[all;in];
normalize:{1f^x%(sum/)x}; 

norm2:{sqrt x$x};
norm1:(')[sum;abs];
norminf:(')[max;abs];
norm0:{count where x<>0};
norm:{[x;y](sum (abs y) xexp x) xexp reciprocal x};
normw:{[x;y]sqrt y$x$y};

dist:{[x;y;z]x y-z}; /[normfunc;a;b]

disteucl:dist[norm2]; /Euclidean distance:(')[norm2;-]
distgeuc:{[x;y;z]dist[normw[x];y;z]}; /Generalized Euclidean
distmins:{[x;y;z]dist[norm[x];y;z]}; /Minskowki��s distance
disthell:{[x;y]disteucl[sqrt x;sqrt y]}; /Hellinger distance
distmaha:{[x;y;z]distgeuc[inv {x cov/:\: x} flip x;y;z]};  /Mahalanobis distance
distchi2:{[x;y;z]distgeuc[diag reciprocal normalize sum x;normalize y;normalize z]};  /Chi^2 distance


entropy:{[x]neg x$log x};
entropyrel:{[x;y]sum x*log x%y}; /Kullback�CLeibler divergence,relative entropy
entrenyi:{[x;y](1%1-x)*log sum y xexp x};
enttsallis:{[x;y](1%x-1)*(1-sum y xexp x)};

newton:{[x;y;z] ({z-(x z)%(y z)}[x;y;]/) z}; /[f;f';x0] Newton 

megis:{[x;y]({condp z*prd each (y%z$x) xexp/: x}[x;y;]/) condp ones count x}; /[N*K����g_k(s);1*K����a_k]MaxEnt GIS
meiis:{[x;y]u:sum each x;({[x;y;z;u]x:z*x;condp z*prd each newton[{[x;y;z;u](sum y*x xexp\:/: u)-z}[;x;y;u];{[x;y;u](sum y*u*x xexp\:/: u-1)}[;x;u];ones[count y]] xexp/:x}[x;y;;u]/) condp ones count x}; /[N*K����g_k(s);1*K����a_k]MaxEnt IIS

/megis1:{[x;y;z]N:count y;K:count z;p:condp ones N;do[x;p:condp p*prd each (z%p$y) xexp/: y];p};


//PSO functions
psoctrl:{[c;f;L;U]N:c`step;VM:c`VMAX;wM:c`wmax;dw:wM-wm:c`wmin;c1:c`c1;c2:c`c2;eps:c`eps;sT:c`stable;m:c`size;n:count L;X:L+/:(U-L)*/:(m,0N)#(m*n)?1f;V:(m,n)#0f;oG:(0w;());oL:m#enlist (0w;());k:0;s:0;while[(k<=N)&(s<sT);w:wM-dw*k%N;fV:f each X;oL:?[fV<oL[;0];fV {(x;y)}' X;oL];i:imin oL[;0];$[eps>dg:oG[0]-oL[i;0];s+:1;s:0];oG:oL[i];V:(neg VM)|VM&(w*V)+(c1*(rand 1f)*oL[;1]-X)+c2*(rand 1f)*(oG[1]-/:X);X:L|/:U&/:X+V;k+:1];oG,enlist k,N}; /[����;Ŀ�꺯��;�������½�;�������Ͻ�]
pso:psoctrl[`size`step`VMAX`w`wmax`wmin`c1`c2`eps!(50;1000;1000f;0.729;0.9;0.4;1.49445;1.49445;1e-10)];

infogain:{(log count x)-entropy x};
condp:{levelat[dim[x]-1;normalize] x};
randp:{condp $[1<count x;reshape[x;(prd x)?1f];x?1f]};

ent:('[;]/) (entropy;filter[0<];condp);

ffset:{[x;y;z]if[type y<>0h;y:y x];(x*not y)+y*z x}; /[ԭ����;���˺�����mask����;�任����]

knn:{[x;y]K:x`K;N:count y[0];m0:m:(K#avg y)+(K,N)#1e-3*randn K*N;i:0;ct:1b;while[(i<x`maxit)&ct;g:avg each y group C:imin each d:y disteucl/:\: m;if[(count g)<count m;m0:m0[key g]];m:value g;if[(x`tol)>e:sum m disteucl' m0;ct:0b];m0:m;i+:1];D:d@'C;(C;m;D;i;sum D)}; /[`K`maxit`tol!...;data]->(���ǩ;������;��������;������) m0:m:(neg K)?y;


fnnd2u:{[x](')[condp;xexp[;-2%x-1]]}; /[ģ��ָ��]�����Ⱦ��ຯ��
clufun:{[x;y;z]u:fnnd2u[x] d:y disteucl/:\: z;sum (u xexp x)$' d xexp 2}; /[ģ��ָ��;������;�������ļ�]������С��Ŀ�꺯��
cluent:{[x]n:count x;k:count x[0];(sum entropy each x%n)-(sum entropy each (condp flip x)%k)}; /[N*K�����Ⱦ���]������,ֵԽС˵������Ч��Խ��.N:������,K:������

fnn:{[x;y]K:x`K;b:x`b;N:count y[0];m0:m:(K#avg y)+(K,N)#1e-3*randn K*N;i:0;ct:1b;while[(i<x`maxit)&ct;P:(fnnd2u[b] d:y disteucl/:\: m) xexp b;m:(sum P  */:\:' y)%sum P;if[(x`tol)>e:sum m disteucl' m0;ct:0b];m0:m;i+:1];C:imin each d;D:d@'C;(C;m;D;i;sum D)}; /[`b`K`maxit`tol!...;data]b within 1.01 1.1

pnn:{[x;y]K:x`K;b:x`b;eps:x`eps;psoctrl[x;;raze K#enlist min y;raze K#enlist max y] ('[;]/)(clufun[b;y];(K,0N)#)};

acna:{[x]y:sqrt count i:where 0<first each x[0];m:1;k:2;while[(m<k)&(m<y);m+:1;z:flip x[1][(neg m)#i];z%:norm2 each z;w:imax each abs z;g:count each group (signum z@'w)*1+w;k:count where g>y];m}; /[��ͼ����]->���ž�����.������ͼ�ָ���Զ�ȷ���������ľ����㷨:journal.shouxi.net/upload/pdf/21/1922/105504_2954.pdf
optkclu:{[x;y](key y) imax 1_deltas (value y) xexp neg x}; /[�б�ָ����2;������!�������]���ž�����
clucost:{[x;y;z]g:group z;(sum y disteucl/:avg x)+(sum/) (x value g) disteucl/:' y key g}; /[������N*P;�����ļ�K*P;������N*1]

//HMM functions
hmmfilter:{[x;y]p:x`p;T:x`T;E:x`E;alpha:p*E[;y[0]];(enlist alpha),{[x;y;T;E]E[;y]*x$T}[;;T;E]\[alpha;1_y]}; /[hmm;obs]hmm forward(alpha) to do filter:P(h_T|v_{1:T}) 

hmmbeta:{[x;y]p:x`p;T:x`T;E:x`E;beta:ones[count p];reverse (enlist beta),-1 _ {[x;y;T;E]T$E[;y]*x}[;;T;E]\[beta;reverse y]}; /[hmm;obs]hmm backward(beta):P(v_{t+1:T}|h_t,v_{1:t}) 

hmmsmoothab:{[x;y]normalize each x*y};
hmmsmooth:{[x;y]hmmsmoothab[hmmfilter[x;y];hmmbeta[x;y]]}; /[hmm;obs]hmm smoothing P(h_t|v_{1:T})

hmmgamma:{[x;y]alpha:hmmfilter[x;y];gamma:normalize last alpha;reverse (enlist gamma),{[x;y;T]x$(normalize each flip T*y)}[;;x`T]\[gamma;1_ reverse alpha]}; /hmmgamma~hmmsmooth

hmmmaxlik:{[x;y]p:x`p;T:x`T;E:x`E;mu:ones[count p];mu:reverse (enlist mu),{[x;y;T;E]max (E[;y]*x)*flip T}[;;T;E]\[mu;reverse 1_y];z:E[;y[0]]*p*mu[0];lik:max z;h:z?lik;(h,{[x;y;z;T;E]imax E[;z]*T[x]*y}[;;;T;E]\[h;1_mu;1_y];lik)}; /[hmm;obs]->(�����״̬����;�����״̬������Ȼֵ)viterbi�㷨����������������� 

hmmpredict:{[x;y]alpha:last hmmfilter[x;y];normalize sum (alpha*x`T)$x`E}; /[hmm;obs]->��һ���۲�ֵ�����ֲ�

viterbi:{[x;y]s:key count p:x`p;T:x`T;E:x`E;p*:E[;y[0]];Z:p ,' (enlist each enlist each s) ,' p;i:1;do[-1+count y;d:(flip Z[;0 2])*\:(E[;y[i]]*) each T;v:max d[1];t:sum d[0];k:(flip d[1])?'v;Z:t,'(enlist each Z[k;1],'s),'v;i+:1];v:max d:Z[;2];(Z[d?v;1];v;sum Z[;0])}; /viterbi~hmmmaxlik[hmm;obs]->(֤����Ȼֵ;�����״̬����;�����״̬������Ȼֵ)Z_t:(��ǰ�յ�״̬Ϊi��֤����Ȼֵ;��ǰ�յ�״̬Ϊi������·��;��ǰ�յ�״̬Ϊi������·����������)

hmmsmjointab:{[x;y;a;b]T:x`T;E:x`E;normalize each (-1_a)*flip each ((1_b)* flip E[;1_y])*\:flip T}; 
hmmsmjoint:{[x;y]hmmsmjointab[x;y;hmmfilter[x;y];hmmbeta[x;y]]}; /[hmm;obs] hmm joint smoothing P(h_t,h_{t+1}|v_{1:T})

hmmem:{[x;y;z]N:count z;H:y[0];V:y[1];p:randp[H];T:randp[H,H];E:randp[H,V];do[x`maxit;m:`p`T`E!(p;T;E);c:zeros[H];A:zeros[H,H];B:zeros[H,V];i:0;do[N;o:z[i];a:hmmfilter[m;o];b:hmmbeta[m;o];s:hmmsmjointab[m;o;a;b];r:hmmsmoothab[a;b];c+:first r;A+:sum s;j:0;do[count o;B[;o[j]]+:r[j];j+:1];i+:1];p:condp[c];T:condp[A];E:condp[B]];(p;T;E)}; /[���ƽṹ;(������״̬��;�۲����״̬��);�۲����ݼ�]hmm����ѧϰ

mapreduce:{[x;y;z]y peach `k xgroup raze x peach z}; /[map fun;reduce fun;input]����/�м���/�������2�б�,����Ϊk,v

//J Functional
left:{[x;y]x};
right:{[x;y]y};
at:(')[;]; / f@:g y <=> f g y , x f@:g y <=>f x g y
compose:{[f;g]{[f;g;x;y]f[g[x];g[y]]}[f;g]}; /x f&g y <=>(g x) f (g y)

underm:{[f;g;ginv](at/)(ginv;f;g)}; /f&.g x <=> g^:_1 f g x
underd:{[f;g;ginv]at[ginv;compose[f;g]]}; /x f&.g y <=>g^:_1 (g x) f (g y)

hookm:{[f;g]{[f;g;x]f[x;g x]}[f;g]}; /monad hook (f g) x <=> x f g x
hookd:{[f;g]{[f;g;x;y]f[x;g y]}[f;g]}; /dyad hook x (f g) y <=> x f g y

forkm:{[f;g;h]$[f~();at[g;h];{[f;g;h;x]g[f x;h x]}[f;g;h]]}; /monad fork (f g h) x <=> (f x) g (h x)
forkd:{[f;g;h]$[f~();at[g;h];{[f;g;h;x;y]g[f[x;y];h[x;y]]}[f;g;h]]}; /dyad fork x (f g h) y <=> (x f y) g (x h y)

trainm:{[x]z:last x;x:-1_x;$[1=mod[;2] count x;[y:hookm[first x];x:1_x];[y:(::)]];y {forkm[z;y;x]}/[z;first w;last w:flip 0N 2#reverse x]}; /monad train (f g h i j k) x <=> (f (g h (i j k))) x
traind:{[x]z:last x;x:-1_x;$[1=mod[;2] count x;[y:hookd[first x];x:1_x];[y:(::)]];y {forkd[z;y;x]}/[z;first w;last w:flip 0N 2#reverse x]}; /dyad train x (f g h i j k) y <=> x (f (g h (i j k))) y


//��ֵ����
romberg1:{[x;y;z]h:z[1]-a:z[0];t0:t:enlist h*0.5*sum y z;e:0W;i:0;while[(i<x`N)&(e>x`T);u:0.5*(first t)+h*sum y a+h*0.5+til "i"$2 xexp i;t:u,{((z*x)-y)%(z-1)}\[u;t;4 xexp 1+til count t];h%:2;i+:1;e:abs (last t)-last t0;t0:t];(last t;i;e)}; /[`N`T!..;func;x0,x1]

romberg:{[x;y;z]last first $[-6h=type x;x;at[x<;last]] {v:last t:first x;u:0.5*(first t)+h*sum y z+(h:x[1])*0.5+til "i"$2 xexp i:x[2];t:u,{((z*x)-y)%(z-1)}\[u;t;4 xexp 1+til count t];(t;h%2;i+1;abs v-last t)}[;y;a]/ (enlist h*0.5*sum y z;h:z[1]-a:z[0];0;0w)}; /[(N|T);func;x0,x1]

l2innprd:at[romberg[15;;0 1f];forkm[;*;]];

//�������
steps:{x[0]+(x[1]-x[0])*(0,1+til y)%y};
linfun:{(')[x[1]+;x[0]*]};
polyfun:{[c;x]sum c*x xexp til count c};
fdot:{{sum (0f^y@\:x)*0f^z@\:x}[;x;y]};
xprior:{y[(x _z);(neg x) _ z]}; /[delta;f;y]

knots:{(y#0f),((til x+2)%x+1),y#1f}; /[�ڲ����Ƶ���;����ʽ����]
bsplinebasis:{[x;y]if[0>type x;x:knots[x;y]];b:{{(x>=y[0])&$[z=y[1];<=;<][x;y[1]]}[;x;y]}[;last x]each xprior[-1;,';x];i:1;do[y;t:xprior[i;-;x];i+:1;b:((linfun each ((1,/:neg (neg i)_x)%-1_t)) {(x;y)}' (linfun each (-1,/:(i _x))%1_t)) fdot' xprior[-1;,';b]];b}; /[�ڲ����Ƶ�����knots;degree(�ֶζ���ʽ����)]B����������:http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-basis.html

Dbspline:{[x;y;z](z*1_deltas x)*0f^xprior[z;-;-1_1_y]}; /[Ȩ����;knots;degree]

polybasis:{{xexp[;x]} each $[0<type x;x;til 1+x]}; /[deg]����ʽ������,������deg,1,x,x^2,...x^deg

fourierbasis:{[x;y] (enlist xexp[;0]),raze {((')[sin;(x*y)*];(')[cos;(x*y)*])}[x] each 1+til y}; /[w;m]Fourier������1,sin(wt),cos(wt),sin(2wt),cos(2wt),...,sin(mwt),cos(mwt)

expbasis:{{(')[exp;x*]} each $[0<type x;x;til 1+x]}; /[m]ָ��������,1,e^t,e^2t,...e^mt

basisfit:{(enlist z) lsq x@\:y}; /[������B;������t;����ֵf]�ڻ���������B�ųɵ��ӿռ���к������. 

basisfitpen:{[x;y;z;R]b:x@\:y;(inv (b$flip b)+R)$b$z}; /[]��˳���

//ʱ������
//bincode:{[x;y]0<(deltas fix (y-z)%x*z:first y) except 0}; /error
bincode:{[x;y]k:0b;if[0=type y;t:y[0];y:y[1];k:1b];z:deltas ({[x;y]$[1<=abs z:y-x;x+signum z;x]}\) ({x-first x} $[x>0;log;::] y)%abs x;$[k;[i:where z<>0;(t[i];0<z[i])];0<z except 0]}; /[�ֱ���;�۸�����|(ʱ������|�۸�����)]�ǵ����ж����Ʊ���
pipdist:{abs z[1]-x[1]+(y[1]-x[1])*(z[0]-x[0])%y[0]-x[0]}; /[(t0,p0);(t1;p1);(t,p)]
piplist:{} /[n;p]
lzc:{({[x;y]s:x[0];q:x[1],y;c:x[2];if[{$[1>=count x;not y~x;1=count y;not y[0] in x;0=count ss["c"$x;"c"$y]]}[-1_z:s,q;q];s:z;c,:enlist q;q:()];(s;q;c)}/)[(();();());x]};
lz:{[x] {(0<count x[1])+count last x}[lzc x]%n*2 xlog n:count x};

//Graph
f_sphere:{[x]x$x};
f_foxhole:{[a;x]m:count a;(1%0.002)+sum {1%(1+z)+sum (x-a[z]) xexp 6}[a;x] each til m};
f_schaffer:{[x]y:x$x;0.5+((sin sqrt y)-0.5)%(1+0.001*y) xexp 2};
f_rosenbrock:{[x]sum (100*((1_x)-(-1_x) xexp 2)xexp 2)+((-1_x)-1) xexp 2};
f_rastrigin:{[x]sum 10+(x xexp 2)-10*cos 2*pi*x};
f_schwefel:{[x]sum (neg x)* sin sqrt abs x};
f_griewank:{[x]1+((sum (x-100) xexp 2)%4000)-prd cos (x-100) % sqrt 1+til count x};
f_shubert:{[n;x]prd x {sum y+y*cos x*1+y}\: 1+til n};f_shubert_5:f_shubert[5];
f_levyno3:{[n;x]y:1+til n;(sum y+y*cos x[0]*-1+y)*(sum y+y*cos x[0]*1+y)};
f_ackley:{[x]20+e-(20*exp -0.2*sqrt (x$x)% count x)+exp sum cos 2*pi*x};

adjmat:{[x]V:exec id from x;V in/: x[;`pa] each V}; /[gm]������ͼģ������(����)�ڽӾ���pa(v)->v
connmat:{[x]n:count x;y:(n,n)#0;z:x;do[n-1;y+:z;z*:x];y>0}; /[adjM]���ڽӾ���������ͨ����
moral:{[x]x:x .[;;:;1b]/ (,/){{$[2>n:count x;();x comb[n;2]]} where x}each x;x|flip x}; /[(����)�ڽӾ���]�ڸ��ڵ��ӱ�,����ͼ->����ͼ 

fillin:{[x;y]I:{$[2>n:count x;();x comb[n;2]]} y;n:count I:I where not x ./:I;(n;x .[;;:;1b]/I,reverse each I)} /[�����ڽӾ���,�����б�]�ڲ����ڶ����ӱ�,����(�ӱ���;�ӱߺ��ڽӾ���)      

minfill:{[x;y;z]C:();e:();V:til n:count x;k:0;do[n-1;nb:where each x;fl:fillin[x] each nb;fisize:first each fl;fasize:prd each y V nb,'til count x;i:$[k<count z;V?z[k];first iasc fisize ,' fasize];c:V nb[i],i;if[not any c allin/:C;C,:enlist c];V _:i;x:{x _ y}[;i] each fl[i;1] _ i;k+:1];asc each C}; /[moralized�ڽӾ���;�������;������Ԫ�����б�]ʹ��minfill�㷨����cliques.x:��ǰʣ��ڵ����Ӿ���,nb:���ڽڵ㼯,fl:ģ�����ǻ�,fisize:���ǻ���ӱ���,fasize:family��״̬��,i:����ʽ��Ԫ�±�,c:��Ԫ����clique,x:ȥ����Ԫ�ڵ���ڽӾ���

mst:{[x;y]z:();f:til x;n:count y;i:0;while[(i<n)&(1<x);if[(<>/) j:f e:y[i];z,:enlist e;f[where f=last j]:first j];i+:1];z}; /[������;�߰�Ȩ������(����)]minimal(maximal) spanning tree,�������������б�

cliquetree:{[x]I:comb[n:count x;2];w:{count (inter/) x} each x I;mst[n;I idesc w]}; /[cliqueset]

axehole:{[x;y]x?((x?last y)#x) except y}; /[���򶥵㼯;�����Ӽ�]Ϊ��֤�ƺ�����ȷ��˶��Ӽ�Ҫ����ά���б�

jtinit:{[x;y;z;u]V:exec id from x;y:V?y;z:V?z;u:V?u;if[(count z)&not any z allin/:y;y:(enlist z),y];m:('[last;fillin])/[moral adjmat x;y];N:count cs:minfill[m;D:exec dim from x;()];cs:cs where 1<count each cs;if[count z;i:first where z allin/:cs;cs:(cs _ i),enlist cs[i]];ct:cliquetree cs;F:$[count ct;(!/)flip ct;()!()];R:(til N)except key F;S:(cs key F) inter' cs F;L:sum each (key F)!not null flip value each (F\) F;PC:ones each D cs;PS:ones each D S[til N];fa:V?exec pa {x,y}'id from x;ci:first each where each fa allin/:\: cs;CPD:x[;`cpd] each V;i:0;do[count ci;if[(not i in u)&not null csi:ci[i];I:axehole[cs[csi];fa[i]];PC[csi]*:filldim/[CPD[i];I,'D cs[csi] I]];i+:1];`C`F`S`L`PC`PS`I`D`V!(cs;F;S;L;PC;PS;ci;D;V)}; /[gm;Ҫ�������ͬһClique��Ķ��㼯�б�;Ҫ����jree root�ڵ���Ķ��㼯;unroll���㼯(slice0 for DBN)]junction tree����,unroll���㼯�������ֲ����˵���ӦClique���ƺ�����

propagate:{[x;y]N:count cs:y`C;PC:y`PC;PS:y`PS;S:y`S;F:y`F;D:y`D;I:idesc y`L;i:0;do[N-1;k:I[i];z:PS[k];PS[k]:levelat[count S[k];x/] flipxv[PC[k];cs[k]?S[k]];y:axehole[cs[F[k]];S[k]];PC[F[k]]*:filldim/[0f^PS[k]%z;y,'D cs[F[k]] y];i+:1];i-:1;do[N-1;k:I[i];z:PS[k];PS[k]:levelat[count S[k];x/] flipxv[PC[F[k]];cs[F[k]]?S[k]];y:axehole[cs[k];S[k]];PC[k]*:filldim/[0f^PS[k]%z;y,'D cs[k] y];i-:1];(PC;PS)}; /[��������;Junction tree]��Ϣ�����㷨:cs(Cliques),PC(potential of Clique���ĸ��ڵ�),PS(potential of Clique���ĸ��Ǹ��ڵ��븸�ڵ��Sep),S(Clique���ĸ��Ǹ��ڵ��븸�ڵ��Sep��Ա),F(Clique���ĸ��Ǹ��ڵ㸸�ڵ���cs�����),L(Clique���ĸ��Ǹ��ڵ����������),D(ͼģ�͸�����״̬��),I(��Ϣ�ϴ�˳��)

margin:{[x;y;z]N:dim x;z:((til N) except y[0])?z;levelat[count z;sum/] flipxv[x . @[N#(::);y[0];:;y[1]];z]} /[���ϸ���;֤��(֤��ά;֤��ֵ);��ѯά]����߼ʷֲ���֤����Ȼֵ

jtree:{[J;vq;ev]cs:J`C;PC:J`PC;ci:J`I;D:J`D;qi:vq;ei:key ev;ev:value ev;$[count I:where qi allin/:cs;[i:I[0];k:0;do[count ei;j:ei[k];m:ci[j];lh:@[D[j]#0f;ev[k];:;1f];y:axehole[cs[m];j];PC[m]*:filldim/[lh;y,'D cs[m] y];k+:1];J[`PC]:PC;PC:first propagate[sum;J];margin[PC[i];(();());cs[i]?qi]];()]}; /[BayesNet;��ѯ����;֤�ݱ���]ʹ��Jtree������������,����ѯ����Ϊ��ʱ֤����Ȼֵ,ֻ֧�ֲ�ѯ�����б����ĳ��Clique������� ;(count qi)&count I:where (qi,ei) allin/:cs;[i:I[0];margin[PC[i];(cs[i]?ei;ev);cs[i]?qi]];

jtinf:{[bn;vq;ev]J:bn`J;V:J`V;$[count vq;normalize;::] jtree[J;V?vq;(V?key ev)!(value ev)]};

fullpd:{[x]V:exec id from x;D:exec dim from x;prd exec (pa{x,y}'id) {[x;y;V;D]I:axehole[V;x];filldim/[y;I,'D I]}[;;V;D]' cpd from x}; /[gm]��ͼģ���������Ϸֲ���.V:�����б�,D:����״̬���б�,��ÿ������,x:fa(x)=pa(x)U{x},y:CPD,I:��Ҫ����ǰ����������б�.ȫ����P(V)=P(X)P(Y|X)P(Z|X,Y)...��˳�����μ���ÿ����������չ�������ʱ�

naive:{[bn;vq;ev]F:bn`F;V:exec id from bn`M;$[count vq;normalize;::] margin[bn`F;(V?key ev;value ev);V?vq]}; /[BayesNet;��ѯ����;֤�ݱ���]ʹ��Naive������������,����ѯ����Ϊ��ʱ֤����Ȼֵ

jtinit2:{[x]V:exec id from x;v0:exec id from x where null base;out0:(distinct raze exec pa from x where not null base) inter v0;e0:v0 except out0;J0:jtinit[select from x where null base;();out0;()];out1:exec id from x where base in out0;Jt:jtinit[update pa:(count e0)#() from (update pa:pa except\:e0 from x) where id in e0;(enlist out0);out1;v0];out0:V?out0;out1:V?out1;J0[`OF`OCI]:(out0;first where out0 allin/: J0`C);Jt[`IF`OF`ICI`0CI]:(out0;out1),first each where each (out0;out1) allin/:\:Jt`C;`J0`Jt!(J0;Jt)}; /gm

jtinf2:{[bn;vq;evL]T:-1+count evL;J0:bn[`J2;`J0];Jt:bn[`J2;`Jt];V:Jt`V;D:Jt`D;ev:first evL;if[T=0;:jtree[J0;V?vq;(V?key ev)!(value ev)]];alpha:jtree[J0;J0`OF;(V?key ev)!(value ev)];ics:Jt[`C;Jt`ICI];I:axehole[ics;Jt`IF];ID:I,'D ics I;pci:Jt[`PC;Jt`ICI];i:1;do[T-1;ev:evL[i];Jt[`PC;Jt`ICI]:pci*filldim/[alpha;ID];alpha:jtree[Jt;Jt`OF;(V?key ev)!(value ev)];i+:1];ev:last evL;Jt[`PC;Jt`ICI]:pci*filldim/[alpha;ID];$[count vq;normalize;::] jtree[Jt;V?vq;(V?key ev)!(value ev)]}; /[2TBN�Ͷ�̬BayesNet;��ѯ������;�۲������ʷ]

\d .
//End

\
f:{[n]A:(n,n)#(n*n)?1f;S:A<0.5;t:enlist .z.P;B:(n,n)#@[raze A;where raze S;*;-1f];t,:.z.P;I:raze (til n)(,/:)'where each S;C:.[;;:;]/[A;I;-1f*A ./: I];t,:.z.P;D:ffset[A;0.5>;-1f*];t,:.z.P;((B~C)&(C~D);1e-6*1_deltas t)};

//����ֽ�
cholesky:{[x]};

//[k4] quantile 
perR:{last[x]^x[-1+f]+(h-f)*(x f)-x -1+f:floor h:1+y*-1+count x:asc x}

