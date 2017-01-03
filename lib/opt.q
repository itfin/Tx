//期权计算函数

\d .opt

pi:acos -1;calnaturalday:{[d0;d1] t:`second$.z.T;dt:$[t<09:30:00;1f;t<11:30:00;(7200f+`int$11:30:00-t)%14400f;t<13:00:00;0.5;t<15:00:00;(`int$15:00:00-t)%14400f;0f];:$[d0<=d1;dt+d1-d0;0f]%365f};
g:{abs (neg x>0f)+(1f%sqrt 2f*pi)*(exp -0.5*x*x)*t*0.31938153+t*-0.356563782+t*1.781477937+t*-1.821255978+1.330274429*t:1f%1f+0.2316419*abs x}; //N(0,1)正态累积函数
getatm:{[f;ks] :last ks where a = min a:abs ks-f};

//欧式指数/期货期权
bs:{[F;K;r;T;vol] v:$[vol=0;1e-10;vol];d1:((log F%K)+T*v*v*0.5)%a:v*sqrt T;(exp neg r*T)*(F*g d1)-K*g d1-a}; //vol>0:call,vol<0:put
vol:{[px;F;K;r;T;pc] if[null px*F;:0n];i:1;vol_a:0 10f;vol:avg vol_a;if[px<$[pc=`C;bs[F;K;r;T;1e-10];neg bs[F;K;r;T;-1e-10]];:1e-10];if[px>$[pc=`C;bs[F;K;r;T;10f];neg bs[F;K;r;T;-10f]];:0n];while[(i<100)&1e-5<abs ppx:px-$[pc=`C;bs[F;K;r;T;vol];neg bs[F;K;r;T;neg vol]];vol:$[ppx>0;avg vol_a:vol,max vol_a;avg vol_a:(min vol_a),vol];i+:1];:vol,i}; //二分法求隐含波动率
delta:{[F;K;r;T;vol;pc] :(g ((log F%K)+T*vol*vol*0.5)%vol*sqrt T)-$[pc=`C;0f;1f];};
gamma:{[F;K;r;T;vol] d1:((log F%K)+T*vol*vol*0.5)%a:vol*sqrt T;:((exp neg 0.5*d1*d1)%sqrt 2f*pi)%(F*a);};
theta:{[F;K;r;T;vol;pc] d1:((log F%K)+T*vol*vol*0.5)%a:vol*sqrt T;d2:d1-a;:(neg (F*((exp neg 0.5*d1*d1)%sqrt 2f*pi)*vol)%2f*sqrt T)+$[pc=`C;-1f;1f]*r*K*(exp neg r*T)*g $[pc=`C;1f;-1f]*d2};
vega:{[F;K;r;T;vol] d1:((log F%K)+T*vol*vol*0.5)%vol*sqrt T;:F*(sqrt T)*(exp neg 0.5*d1*d1)%sqrt 2f*pi};

//欧式股票期权

//美式指数/期货期权

//美式股票期权

\d .
