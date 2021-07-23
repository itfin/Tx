\l math.q
\l qffi.q
\l qml.q
\l qr.q
\l qj.q
\l qmma.q
\l qmatlab.q
\l matfile.q


qlbfgs:`:qlbfgs 2:(`qlbfgs;4);
\d .gsl
GSLLIB:`$"/q/l64/libgsl.so";
sf_bessel_J0:.ffi.cf[("f";GSLLIB,`gsl_sf_bessel_J0)];
integration_workspace_alloc:.ffi.cf[("i";GSLLIB,`gsl_integration_workspace_alloc)];
integration_qags:.ffi.cf[("i";GSLLIB,`gsl_integration_qags)];
gsl_qrng_alloc:.ffi.cf[("s";GSLLIB,`gsl_qrng_alloc)];
gsl_qrng_free:.ffi.cf[GSLLIB,`gsl_qrng_free];
gsl_qrng_get:.ffi.cf[("i";GSLLIB,`gsl_qrng_get)];
\d .
lbfgs:qlbfgs[()]; /[f;f';x0] http://search.cpan.org/~laye/Algorithm-LBFGS/lib/Algorithm/LBFGS.pm

speclu:{[x;y]d:sum x;L:(diag reciprocal d)$(diag d)-x;E:.qml.mev L;y:$[y<0;abs y;y&acna[E]];i:(neg y)#where 0<first each E[0];V:flip E[1][i];knn[`K`maxit`tol!(y;500;1e-10);V]}; /[相似度矩阵;分类数]谱聚类算法




/Shogun
Rdo:{0N!x;Rcmd x;};
//Rdo "library('sg')";

threads:{[x]Rdo "sg('threads',",(string x),")";}; 
kernel:{[x;y;z]Rdo "sg('set_kernel', '",(string x),"',",($[null y;"";"'",(string y),"',"]),("," sv string z),")";}; /[核名称;数据类型;参数列表]
distance:{[x;y]Rdo "sg('set_distance', '",(string x),"', '",(string y),"')";}; /[距离函数名称;数据类型]
distmat:{[x;y]Rget "sg('get_distance_matrix', '",(string x),"')"}; /[`TRAIN|`TEST;哑变量]
dmtrain:distmat[`TRAIN];dmtest:distmat[`TEST];
kernmat:{[x;y]Rget "sg('get_kernel_matrix', '",(string x),"')"}; /[`TRAIN|`TEST;哑变量]
kmtrain:kernmat[`TRAIN];kmtest:kernmat[`TEST];

features:{[x;y;z]if[0=count z;:()];if[null y;y:`dump];y:string y;$[-11h=type z;[Rdo y,"<-read.table('",((string z)except ":"),"')";u:()];[$[-11h~type u:z[0];z:x[1];u:()];Rset[y;z];if[10h=type z[0];Rdo y,"<-as.character(",y,")"];]];Rdo"sg('set_features','",(string x),"',as.matrix(as.data.frame(",y,"))",$[count u;",'",(string u),"'";""],")";}; /[`TRAIN|`TEST;特征变量名;特征变量值]
ftrain:features[`TRAIN];ftest:features[`TEST];
labels:{[x;y;z]if[0=count z;:()];if[null y;y:`dump];y:string y;$[-11h=type z;Rdo y,"<-as.real(as.matrix(read.table('",((string z)except ":"),"')))";Rset[y;z]];Rdo "sg('set_labels','",(string x),"',",y,")";}; /[`TRAIN|`TEST;教师变量名;教师变量值]
ltrain:labels[`TRAIN];ltest:labels[`TEST];

classifier:{[x;y]Rdo "sg('new_classifier', '",(string x),"')";{Rdo "sg('",(string x[0]),"', ",(string x[1]),")";} each flip (key;value)@\: y;}; /[分类器名称;分类器选项]
traincf:{[x;y;z]ftrain[`obt;x];ltrain[`lbt;y];Rdo "sg('train_classifier'",$[count z;(",","," sv string z);""],")";}; /[训练样本;训练教师;训练参数]
regression:{[x;y]Rdo "sg('new_regression', '",(string x),"')";{Rdo "sg('",(string x[0]),"', ",(string x[1]),")";} each flip (key;value)@\: y;}; /[分类器名称;分类器选项]
trainrg:{[x;y;z]ftrain[`obt;x];ltrain[`lbt;y];Rdo "sg('train_regression'",$[count z;(",","," sv string z);""],")";}; /[训练样本;训练教师;训练参数]
classify:{[x]ftest[`obp;x];Rget "sg('classify')"}; /[预测样本]

clustering:{[x]Rdo "sg('new_clustering', '",(string x),"')";}; /[聚类器名称]
traincl:{[x;y]ftrain[`obt;x];Rdo "sg('train_clustering'",$[count y;(",","," sv string y);""],")";}; /[训练样本;训练参数]
cluster:{[]Rget "sg('get_clustering')"};


\
Ropen[0];
r:.gsl.sf_bessel_J0[(5f;::)];
w:.gsl.integration_workspace_alloc[(1000;::)];
result:enlist 0n;
error:enlist 0n;
alpha:enlist 1.0;
f:{[x;y](log x)%sqrt x};
z:.gsl.integration_qags ((f;alpha);0;1;0;1e-7;1000;w;result;error);

knn[`K`maxit`tol!(3;1000;1e-3);(0N 2#0.5*randn 10000*2)+(0 0;1 1;-1 -1) 10000?3];

DM1:([id:`A1`B1`C1`D1`A2`B2`C2`D2]obs:00010001b;base:`````A1`B1`C1`D1;equiv:```````C1`;dim:2 2 2 2 2 2 2 2;pa:(();();enlist `A1;`B1`C1;enlist `A1;enlist `B1;enlist `A2;`C1`B2`C2);cpd:(2?1f;2?1f;2 2#4?1f;reshape[2 2 2;8?1f];2 2#4?1f;2 2#4?1f;2 2#4?1f;reshape[2 2 2 2;16?1f]));

DM2:([id:`Q11`Q12`F1`O1`Q21`Q22`F2`O2]obs:00010001b;base:`````Q11`Q12`F1`O1;equiv:```````F1`O1;dim:2 4 2 18 2 4 2 18;pa:(();enlist `Q11;`Q11`Q12;enlist `Q12;`Q11`F1;`Q12`F1`Q21;`Q21`Q22;enlist `Q22);cpd:(2?1f;2 4#8?1f;reshape[2 4 2;16?1f];4 18#72?1f;reshape[2 2 2;8?1f];reshape[4 2 2 4;64?1f];reshape[2 4 2;16?1f];4 18#72?1f));

M1:([id:`C`S`R`W]name:("Cloudy";"Sprinkler";"Raining";"Wet Grass");dim:2 2 2 2;pa:(();enlist `C;enlist `C;`S`R);cpd:(0.5 0.5;(0.5 0.5;0.9 0.1);(0.8 0.2;0.2 0.8);((1.0 0.0;0.1 0.9);(0.1 0.9;0.01 0.99))));

M2:([id:`B`S`C]name:("Brainy";"Sporty";"College");dim:2 2 2;pa:(();();`B`S);cpd:(0.5 0.5;0.5 0.5;((1.0 0.0;0.0 1.0);(0.0 1.0;0.0 1.0))));

M3:([id:`A`B`C`D`E`F`G`H]dim:2 2 2 2 2 2 2 2;pa:(();enlist `A;enlist `A;enlist `B;enlist `C;`D`E;enlist `C;`E`G);cpd:(0.5 0.5;(0.5 0.5;0.4 0.6);(0.7 0.3;0.2 0.8);(0.9 0.1;0.5 0.5);(0.3 0.7;0.6 0.4);((0.01 0.99;0.01 0.99);(0.01 0.99;0.99 0.01));(0.8 0.2;0.1 0.9);((0.05 0.95;0.95 0.05);(0.95 0.05;0.95 0.05))));

M4:([id:`A`T`S`L`B`E`X`D]name:("asia"; "tub"; "smoker";"lcancer";"bronch";"t|lc";"xray";"dys");dim:2 2 2 2 2 2 2 2;pa:(();enlist `A;();enlist `S;enlist `S;`T`L;enlist `E;`B`E);cpd:(0.01 0.99;(0.05 0.95;0.01 0.99);0.5 0.5;(0.1 0.9;0.01 0.99);(0.6 0.4;0.3 0.7);((1 0;1 0);(1 0;0 1));(0.98 0.02;0.05 0.95);((0.9 0.1;0.8 0.2);(0.7 0.3;0.1 0.9))));

DHM1:([id:`h0`v0`h1`v1]obs:0101b;base:```h0`v0;equiv:````v0;dim:2 4 2 4;pa:(();enlist `h0;enlist `h0;enlist `h1);cpd:(0.5 0.5;(0.2 0.3 0.3 0.2;0.3 0.2 0.2 0.3);(0.5 0.5;0.4 0.6);(0.2 0.3 0.3 0.2;0.3 0.2 0.2 0.3)));

bn1:`M`F!(M1;fullpd[M1]);
bn2:`M`F!(M2;fullpd[M2]);
bn3:`M`F!(M3;fullpd[M3]);
bn4:`M`F`J!(M4;fullpd[M4];jtinit[M4;();();()]);
dbn1:`M`F`J2!(DM1;fullpd[DM1];jtinit2[DM1]);
dbn2:`M`F`J2!(DM2;fullpd[DM2];jtinit2[DM2]);
dbn3:`M`J2!(DHM1;jtinit2[DHM1]);

hmm1:`p`T`E!(0.5 0.5;(0.5 0.5;0.4 0.6);(0.2 0.3 0.3 0.2;0.3 0.2 0.2 0.3));
obs1:2 2 1 0 1 3 2 0 0;
obset:-1+(1 2 2 2 2 2 1 1 2 1 1 2 2 2 1 2 1 2 2 1 2 2 2 2 1 2 2 2 2;1 2 2 2 2 2 1 2 1 2 1 1 2 2 2 2 1 2 2 2 2 1;2 2 2 1 1 1 2 1 2 2 2 1 2 2 2 2 2 2 2 2 2 1 1 2 1 2 1 2 2 2;1 2 2 1 1 2 1 2 1 1 2 1 1 1 2 2 1 2 2 2 2 2 2 2 2;2 2 1 2 2 2 1 2 2 2 1 1 2 2 1 2 1 2 2 2 1 2 2 2 2 1;1 1 1 1 1 1 2 1 2 2 1 1 2 2 1 2 2 2 1 2 2 2 1 2 2 1 2 2 2 2;2 2 1 2 2 2 1 2 2 2 1 2 1 2 2 2 1 2 2 1 2 2 2 2 1 1;2 2 2 2 1 2 2 2 2 2 1 1 2 1 2 2 2 1 1 1 2 1 2 2 2 1 2 2;2 2 2 2 2 2 2 2 1 2 2 2 2 2 2 1 1 2 2 2 1;1 1 1 1 2 2 2 1 1 1 2 2 2 2 2 2 2 2 1 2 1 2 2 2);

m1:naive[bn1;enlist `S;(enlist `W)!enlist 1];
m2:naive[bn1;enlist `R;(enlist `W)!enlist 1];
m3:naive[bn1;enlist `S;`W`R!1 1];

m4:naive[bn2;enlist `B;(enlist `C)!enlist 1];
m5:naive[bn2;enlist `B;`C`S!1 1];

m6:naive[bn4;`L`B;`A`D!0 0];
m7:jtinf[bn4;`L`B;`A`D!0 0];

l6:naive[bn4;();`A`D!0 0];
l7:jtinf[bn4;();`A`D!0 0];

h0:hmmmaxlik[hmm1;obs1];
h1:viterbi[hmm1;obs1];
h2:last hmmfilter[hmm1;obs1];
h3:jtinf2[dbn3;enlist `h1;((enlist `v0)!enlist 2;(enlist `v1)!enlist 2;(enlist `v1)!enlist 1;(enlist `v1)!enlist 0;(enlist `v1)!enlist 1;(enlist `v1)!enlist 3;(enlist `v1)!enlist 2;(enlist `v1)!enlist 0;(enlist `v1)!enlist 0)];

r1:hmmem[`maxit`tol!(100;0.1);3 2;obset];
//
//infer[M;enlist `S;(enlist `W)!enlist 1]
//infer[M;enlist `S;`W`R!1 1]

\
v:((`a1.b1.c1`a1.b1.c2;`a1.b2.c1`a1.b2.c2;`a1.b3.c1`a1.b3.c2);(`a2.b1.c1`a2.b1.c2;`a2.b2.c1`a2.b2.c2;`a2.b3.c1`a2.b3.c2))
//adjvert:{[x;y]distinct (,/)where each x y}; /相邻顶点集[邻接矩阵;顶点集]

//elimord:{[gm]x:moral adjmat gm;V:til n:count x;D:exec dim from gm;e:();while[n>ne:count e;nb:where each x;fl:fillin[x] each nb;fisize:first each fl;fasize:prd each D V nb,'x;i:last where 0=iasc fisize ,' fasize;e,:V[i];V _:i;x:{x _ y}[;i] each fl[i;1] _ i];e}; /[图模型]贪婪计算消去序:根据fillin边数和家庭状态总数升序依次消去最小顶点

//elimord:{[x]V:til n:count x;e:();j:();while[n>ne:count e;fr:$[ne;adjvert[e] except e;V];fv:$[ne;{I:adjvert[x;z] inter y;-0.5*(sum/) x[I;I]}[x;e] each fr;(count fr)#0f];v:fr[fv?min fv];];(e;j)};  /[]elimOrderGreedy
\l matfile.q
test1:{[]r:matread[`:/opt/brml/data/chestclinic.mat];V:`A`S`TU`L`B`X`D`TL;P:{-1+1 _ first `int$x} each r[`pot;`variables];I:iasc each P;m:([id:V]name:r[`variable;`name];dim:8#2;pa:V P@'I;cpd:I {flipxv[y;filter[{x=maxs x}] x]}' mx2q each r[`pot;`table]);m};

M5:([id:`V1`V2`V3`V4`V5`V6`V7`V8`V9`V10`V11`V12`V13`V14`V15`V16`V17`V18`V19`V20`V21`V22`V23`V24`V25`V26`V27`V28`V29`V30`V31`V32`V33`V34`V35`V36`V37]dim:2 3 2 2 2 3 2 2 2 2 2 2 2 3 4 3 2 3 3 3 4 3 4 4 4 4 3 3 4 3 2 3 3 3 3 3 3;pa:(();();();();();();();();();();();();`V2`V12;`V3`V9;enlist `V6;enlist `V11;enlist `V9;enlist `V12;`V3`V9;enlist `V19;`V8`V15;enlist `V19;`V1`V2`V21;`V1`V2`V21;`V2`V23;`V2`V23;`V7`V26;enlist `V26;`V3`V28;`V13`V27;`V5`V16`V28`V30;enlist `V31;`V10`V32;`V10`V32;`V14`V32;`V4`V32;`V16`V35);cpd:(0.96 0.04;0.92 0.03 0.05;0.8 0.2;0.95 0.05;0.8 0.2;0.01 0.98 0.01;0.01 0.99;0.95 0.05;0.95 0.05;0.9 0.1;0.99 0.01;0.99 0.01;0.95 0.95 0.05 0.1 0.1 0.01 0.05 0.05 0.95 0.9 0.9 0.99;0.05 0.95 0.5 0.98 0.9 0.04 0.49 0.01 0.05 0.01 0.01 0.01;0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.97;0.3 0.98 0.4 0.01 0.3 0.01;0.99 0.1 0.01 0.9;0.05 0.01 0.9 0.19 0.05 0.8;0.05 0.98 0.01 0.95 0.9 0.01 0.09 0.04 0.05 0.01 0.9 0.01;0.95 0.04 0.01 0.04 0.95 0.29 0.01 0.01 0.7;0.97 0.97 0.01 0.97 0.01 0.97 0.01 0.97 0.01 0.01 0.97 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.01;0.95 0.04 0.01 0.04 0.95 0.04 0.01 0.01 0.95;0.97 0.97 0.97 0.97 0.97 0.97 0.01 0.95 0.97 0.97 0.01 0.95 0.01 0.4 0.97 0.97 0.01 0.5 0.01 0.3 0.97 0.97 0.01 0.3 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.03 0.01 0.01 0.97 0.03 0.01 0.58 0.01 0.01 0.01 0.48 0.01 0.68 0.01 0.01 0.01 0.68 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.97 0.01;0.97 0.97 0.97 0.97 0.97 0.97 0.01 0.01 0.4 0.1 0.01 0.01 0.01 0.01 0.2 0.05 0.01 0.01 0.01 0.01 0.2 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.49 0.58 0.84 0.9 0.29 0.01 0.01 0.75 0.25 0.01 0.01 0.01 0.01 0.7 0.15 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.3 0.01 0.05 0.08 0.3 0.97 0.08 0.04 0.25 0.38 0.08 0.01 0.01 0.09 0.25 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.2 0.01 0.01 0.01 0.4 0.01 0.9 0.01 0.45 0.6 0.9 0.97 0.97 0.01 0.59 0.97 0.97;0.97 0.97 0.97 0.01 0.6 0.01 0.01 0.5 0.01 0.01 0.5 0.01 0.01 0.01 0.01 0.97 0.38 0.97 0.01 0.48 0.01 0.01 0.48 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.01 0.97 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.01 0.97;0.97 0.97 0.97 0.01 0.01 0.03 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.01 0.01 0.97 0.97 0.95 0.01 0.01 0.94 0.01 0.01 0.88 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.97 0.04 0.01 0.01 0.1 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.97 0.01;0.98 0.98 0.98 0.98 0.95 0.01 0.95 0.01 0.01 0.01 0.01 0.01 0.04 0.95 0.04 0.01 0.01 0.01 0.01 0.01 0.01 0.04 0.01 0.98;0.01 0.01 0.04 0.9 0.01 0.01 0.92 0.09 0.98 0.98 0.04 0.01;0.97 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.97 0.01 0.01 0.01 0.01 0.97 0.97 0.97 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.97 0.97 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.97 0.97 0.43;0.98 0.98 0.01 0.98 0.01 0.69 0.01 0.01 0.98 0.01 0.01 0.3 0.01 0.01 0.01 0.01 0.98 0.01;0.05 0.01 0.05 0.01 0.05 0.01 0.05 0.01 0.05 0.01 0.05 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.1 0.01 0.95 0.01 0.95 0.05 0.1 0.01 0.95 0.01 0.95 0.05 0.1 0.01 0.3 0.01 0.3 0.01 0.95 0.01 0.99 0.05 0.95 0.05 0.95 0.01 0.99 0.05 0.99 0.05 0.3 0.01 0.99 0.01 0.3 0.01 0.95 0.99 0.95 0.99 0.95 0.99 0.95 0.99 0.95 0.99 0.95 0.99 0.99 0.99 0.99 0.99 0.99 0.99 0.9 0.99 0.05 0.99 0.05 0.95 0.9 0.99 0.05 0.99 0.05 0.95 0.9 0.99 0.7 0.99 0.7 0.99 0.05 0.99 0.00999999 0.95 0.05 0.95 0.05 0.99 0.01 0.95 0.01 0.95 0.7 0.99 0.01 0.99 0.7 0.99;0.1 0.01 0.89 0.09 0.01 0.9;0.98 0.33333334 0.01 0.33333334 0.01 0.33333334 0.01 0.33333334 0.98 0.33333334 0.01 0.33333334 0.01 0.33333334 0.01 0.33333334 0.98 0.33333334;0.98 0.33333334 0.01 0.33333334 0.01 0.33333334 0.01 0.33333334 0.98 0.33333334 0.01 0.33333334 0.01 0.33333334 0.01 0.33333334 0.98 0.33333334;0.98 0.95 0.3 0.95 0.04 0.01 0.8 0.01 0.01 0.01 0.04 0.69 0.04 0.95 0.3 0.19 0.04 0.01 0.01 0.01 0.01 0.01 0.01 0.69 0.01 0.95 0.98;0.98 0.98 0.01 0.4 0.01 0.3 0.01 0.01 0.98 0.59 0.01 0.4 0.01 0.01 0.01 0.01 0.98 0.3;0.98 0.98 0.3 0.98 0.1 0.05 0.9 0.05 0.01 0.01 0.01 0.6 0.01 0.85 0.4 0.09 0.2 0.09 0.01 0.01 0.1 0.01 0.05 0.55 0.01 0.75 0.9));

update cpd:({M5[;`dim] each x} each pa {x,y}'id) {reshape[x;flatten flip ((last x),0N)#y]}' cpd from `M5;
//naive:{[bn;vq;ev]F:bn`F;V:exec id from bn`M;I:(count V)#(::);I[V?v:key ev]:value ev;M:F . I;k:(V except v)?vq;normalize levelat[count k;sum/] flipxv[M;k]}; /[BayesNet;查询变量;证据变量]使用Naive方法进行推理

load `:/kdb/d;
update lb:?[t>=0.15;1;-1] from `d;
`dobt`dlbt set' value exec s,"e"$lb from d where date within 2003.01.01 2007.12.31;
`dobp`dlbp set' value exec s,"e"$lb from d where date within 2008.01.01 2010.12.31;
`obt`lbt`obp set' `:/tmp/obt`:/tmp/lbt`:/tmp/obp;

obt 0: " " 0: dobt;
obp 0: " " 0: dobp;
lbt 0: raze each string flip enlist dlbt;

//threads[20];
kernel[`GAUSSIAN;`REAL;100000 2.1];
classifier[`LIBSVM;`svm_epsilon`c`svm_use_bias!(1e-5;10f;`TRUE)];
t0:.z.P;traincf[obt;lbt;()];
t1:.z.P;dlbm:classify[obp];
t2:.z.P;show(`time$t1-t0;`time$t2-t1);

obt:flip ("FF";" ") 0: `:/opt/shogun/data/fm_train_real.dat;
lbt:first ((enlist "F");" ") 0: `:/opt/shogun/data/label_train_multiclass.dat;
lbt2:first ((enlist "F");" ") 0: `:/opt/shogun/data/label_train_twoclass.dat;
obp:flip ("FF";" ") 0: `:/opt/shogun/data/fm_test_real.dat;

obdt:read0 `:/opt/shogun/data/fm_train_dna.dat;
lbdt:first ((enlist "F");" ") 0: `:/opt/shogun/data/label_train_dna.dat;
obdp:read0 `:/opt/shogun/data/fm_test_dna.dat;

kernel[`GAUSSIAN;`REAL;10 2.1];
classifier[`GMNPSVM;`svm_epsilon`c`svm_use_bias!(1e-5;10f;`TRUE)];
traincf[obt;lbt;()];
r1:classify[obp];

kernel[`GAUSSIAN;`REAL;10 2.1];
classifier[`GPBTSVM;`svm_epsilon`c`svm_use_bias!(1e-5;10f;`TRUE)];
traincf[obt;lbt2;()];
r2:classify[obp];

distance[`EUCLIDIAN;`REAL];
classifier[`KNN;()!()];
traincf[obt;lbt;enlist 3];
r3:classify[obp];

classifier[`LDA;()!()];
traincf[obt;lbt2;()];
r4:classify[obp];

kernel[`GAUSSIAN;`REAL;10 2.1];
classifier[`LIBSVM;`svm_epsilon`c`svm_use_bias!(1e-5;10f;`TRUE)];
traincf[obt;lbt2;()];
r5:classify[obp];

kernel[`GAUSSIAN;`REAL;10 2.1];
classifier[`LIBSVM_MULTICLASS;`svm_epsilon`c`svm_use_bias!(1e-5;10f;`TRUE)];
traincf[obt;lbt;()];
r6:classify[obp];

kernel[`GAUSSIAN;`REAL;10 2.1];
classifier[`LIBSVM_ONECLASS;`svm_epsilon`svm_nu`svm_use_bias!(1e-5;0.1;`TRUE)];
traincf[obt;();()];
r7:classify[obp];

kernel[`GAUSSIAN;`REAL;10 2.1];
classifier[`MPDSVM;`svm_epsilon`c`svm_use_bias!(1e-5;10f;`TRUE)];
traincf[obt;lbt2;()];
r8:classify[obp];

classifier[`PERCEPTRON;()!()];
traincf[obt;lbt2;()];
r9:classify[obp];

kernel[`WEIGHTEDDEGREE;`CHAR;10 20];
classifier[`LIBSVM;`svm_epsilon`c`svm_use_bias!(1e-5;10f;`TRUE)];
traincf[(`DNA;obdt);lbdt;()];
r10:classify[(`DNA;obdp)];

distance[`EUCLIDIAN;`REAL];
clustering[`HIERARCHICAL];
traincl[obt;enlist 3];
r11:cluster[];

distance[`EUCLIDIAN;`REAL];
clustering[`KMEANS];
traincl[obt;3 1000];
r12:cluster[];

distance[`BRAYCURTIS;`REAL];
ftrain[`obt;obt];
r13:dmtrain[];

distance[`CANBERRA;`REAL];
ftrain[`obt;obt];
r14:dmtrain[];
ftest[`obp;obp];
r15:dmtest[];

distance[`CHEBYSHEW;`REAL];
ftrain[`obt;obt];
r16:dmtrain[];
ftest[`obp;obp];
r17:dmtest[];

distance[`CHISQUARE;`REAL];
ftrain[`obt;obt];
r18:dmtrain[];
ftest[`obp;obp];
r19:dmtest[];

distance[`COSINE;`REAL];
ftrain[`obt;obt];
r20:dmtrain[];
ftest[`obp;obp];
r21:dmtest[];

distance[`GEODESIC;`REAL];
ftrain[`obt;obt];
r22:dmtrain[];
ftest[`obp;obp];
r23:dmtest[];

distance[`JENSEN;`REAL];
ftrain[`obt;obt];
r24:dmtrain[];
ftest[`obp;obp];
r25:dmtest[];

distance[`MANHATTAN;`REAL];
ftrain[`obt;obt];
r26:dmtrain[];
ftest[`obp;obp];
r27:dmtest[];

distance[`TANIMOTO;`REAL];
ftrain[`obt;obt];
r28:dmtrain[];
ftest[`obp;obp];
r29:dmtest[];

kernel[`CHI2;`REAL;10 1.4];
ftrain[`obt;obt];
r30:kmtrain[];
ftest[`obp;obp];
r31:kmtest[];

kernel[`CONST;`REAL;10 23];
ftrain[`obt;obt];
r31:kmtrain[];
ftest[`obp;obp];
r32:kmtest[];

distance[`EUCLIDIAN;`REAL];
kernel[`DISTANCE;`;10 1.7];
ftrain[`obt;obt];
r33:kmtrain[];
ftest[`obp;obp];
r34:kmtest[];

kernel[`GAUSSIAN;`REAL;10 2.1];
regression[`KRR;`krr_tau`c!(1e-6;10f)];
trainrg[obt;lbt;()];
r41:classify[obp];

kernel[`GAUSSIAN;`REAL;10 2.1];
regression[`LIBSVR;`svr_tube_epsilon`c!(1e-2;10f)];
trainrg[obt;lbt;()];
r42:classify[obp];

Rdo "size_cache <- 10"
Rdo "C <- 10"
Rdo "epsilon <- 1e-5"
Rdo "use_bias <- TRUE"
Rdo "width <- 2.1"

Rdo "fm_train_real <- t(as.matrix(read.table('/opt/shogun/data/fm_train_real.dat')))"
Rdo "fm_test_real <- t(as.matrix(read.table('/opt/shogun/data/fm_test_real.dat')))"
Rdo "label_train_twoclass <- as.real(as.matrix(read.table('/opt/shogun/data/label_train_twoclass.dat')))"

Rdo "dump <- sg('set_features', 'TRAIN', fm_train_real)"
Rdo "dump <- sg('set_kernel', 'GAUSSIAN', 'REAL', size_cache, width)"

Rdo "dump <- sg('set_labels', 'TRAIN', label_train_twoclass)"
Rdo "dump <- sg('new_classifier', 'GPBTSVM')"
Rdo "dump <- sg('svm_epsilon', epsilon)"
Rdo "dump <- sg('c', C)"
Rdo "dump <- sg('svm_use_bias', use_bias)"
Rdo "dump <- sg('train_classifier')"

Rdo "dump <- sg('set_features', 'TEST', fm_test_real)"
r:Rget "result <- sg('classify')"

Rcmd "sg('set_kernel', 'GAUSSIAN', 'REAL',10,10)";
Rcmd "sg('new_classifier', 'GMNPSVM')";
Rcmd "sg('svm_epsilon', 1e-5)";
Rcmd "sg('c', 10)";
Rcmd "sg('svm_use_bias',TRUE)";

Rset["obt";obt];
Rset["lbt";lbt];
Rcmd "sg('set_features', 'TRAIN', as.matrix(as.data.frame(obt)))";
Rcmd "sg('set_labels', 'TRAIN', lbt)";
Rcmd "sg('train_classifier')";
Rset["obp";obp];
Rcmd "sg('set_features', 'TEST', as.matrix(as.data.frame(obp)))";
r:Rget "sg('classify')";